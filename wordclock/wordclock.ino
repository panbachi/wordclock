#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <FS.h>

/***********************************************
 * CONFIG START
 **********************************************/
#define GRID_ROWS 11 // supported 10 and 11
#define GRID_COLS 11 // supported 11

/* 
 * 0: top-left
 * 1: top-right
 * 2: buttom-left
 * 3: buttom-right
 */
#define GRID_FIRST 2

#define GRID_LANGUAGE = "de" // supported "de"

#define DATA_PIN D4

/***********************************************
 * CONFIG END
 **********************************************/

// DO NOT TOUCH
#define NUM_LEDS (GRID_ROWS * GRID_COLS) + 4

typedef struct { 
  int r;
  int g;
  int b;
} color_t;

typedef struct {
  int pixel;
  int r;
  int g;
  int b;
} pixel_color_t;

typedef struct {
  int hour;
  int minute;
} clock_time_t;

typedef struct {
  color_t color_bg;
  color_t color_fg;
  int brightness;
  int timezone;
  bool dnd_active;
  clock_time_t dnd_start;
  clock_time_t dnd_end;
} config_t;


int time_it_is[] = {0, 1, 3, 4, 5}; // es ist

int time_minutes[][12] = {
  {107, 108, 109,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // uhr
  {  7,   8,   9,  10,  35,  36,  37,  38,  -1,  -1,  -1,  -1}, // fünf nach
  { 11,  12,  13,  14,  35,  36,  37,  38,  -1,  -1,  -1,  -1}, // zehn nach
  { 26,  27,  28,  29,  30,  31,  32,  35,  36,  37,  38,  -1}, // viertel nach
  { 15,  16,  17,  18,  19,  20,  21,  35,  36,  37,  38,  -1}, // zwanzig nach
  {  7,   8,   9,  10,  39,  40,  41,  44,  45,  46,  47,  -1}, // fünf vor halb
  { 44,  45,  46,  47,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // halb
  {  7,   8,   9,  10,  35,  36,  37,  38,  44,  45,  46,  47}, // fünf nach halb
  { 15,  16,  17,  18,  19,  20,  21,  39,  40,  41,  -1,  -1}, // zwanzig vor
  { 26,  27,  28,  29,  30,  31,  32,  39,  40,  41,  -1,  -1}, // viertel vor
  { 11,  12,  13,  14,  39,  40,  41,  -1,  -1,  -1,  -1,  -1}, // zehn vor
  {  7,   8,   9,  10,  39,  40,  41,  -1,  -1,  -1,  -1,  -1}  // fünf vor
};

int time_hours[][6] = {
  { 49,  50,  51,  52,  53,  -1}, // zwölf
  { 57,  58,  59,  60,  -1,  -1}, // eins
  { 55,  56,  57,  58,  -1,  -1}, // zwei
  { 67,  68,  69,  70,  -1,  -1}, // drei
  { 84,  85,  86,  87,  -1,  -1}, // vier
  { 73,  74,  75,  76,  -1,  -1}, // fünf
  {100, 101, 102, 103, 104,  -1}, // sechs
  { 60,  61,  62,  63,  64,  65}, // sieben
  { 89,  90,  91,  92,  -1,  -1}, // acht
  { 80,  81,  82,  83,  -1,  -1}, // neun
  { 93,  94,  95,  96,  -1,  -1}, // zehn
  { 77,  78,  79,  -1,  -1,  -1}  // elf
};

CRGB leds[NUM_LEDS];
int r = 255;
int g = 255;
int b = 255;
int offset = 0;
int hour = -1;
int minute = -1;
String ip = "";

config_t CONFIG;

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pool.ntp.org", offset, 3600000);

ESP8266WebServer server(80);
String header;

String mode = "time";

void loadConfig() {
  CONFIG.color_bg.r = 0;
  CONFIG.color_bg.g = 0;
  CONFIG.color_bg.b = 0;
  
  CONFIG.color_fg.r = 255;
  CONFIG.color_fg.g = 255;
  CONFIG.color_fg.b = 255;

  CONFIG.brightness = 50;
  
  CONFIG.timezone = 0;

  CONFIG.dnd_active = false;
  CONFIG.dnd_start.hour = -1;
  CONFIG.dnd_start.minute = -1;
  CONFIG.dnd_end.hour = -1;
  CONFIG.dnd_end.minute = -1;
  
  File file = SPIFFS.open("/wordclock_config.json", "r");

  if(!file) {
    Serial.println("Failed to open config file.");
    saveConfig();
    return;
  }

  Serial.println("Load config.");
  
  StaticJsonDocument<1024> doc;
  deserializeJson(doc, file);

  CONFIG.color_bg.r = doc["color_bg_r"].as<int>();
  CONFIG.color_bg.g = doc["color_bg_g"].as<int>();
  CONFIG.color_bg.b = doc["color_bg_b"].as<int>();

  CONFIG.color_fg.r = doc["color_fg_r"].as<int>();
  CONFIG.color_fg.g = doc["color_fg_g"].as<int>();
  CONFIG.color_fg.b = doc["color_fg_b"].as<int>();

  CONFIG.brightness = doc["brightness"].as<int>();

  CONFIG.timezone = doc["timezone"].as<int>();

  CONFIG.dnd_active = doc["dnd_active"].as<bool>();
  CONFIG.dnd_start.hour = doc["dnd_start_hour"].as<int>();
  CONFIG.dnd_start.minute = doc["dnd_start_minute"].as<int>();
  CONFIG.dnd_end.hour = doc["dnd_end_hour"].as<int>();
  CONFIG.dnd_end.minute = doc["dnd_end_minute"].as<int>();

  timeClient.setTimeOffset(CONFIG.timezone * 3600);
  
  file.close();
}

void saveConfig() {
  File file = SPIFFS.open("/wordclock_config.json", "w");

  if(!file) {
    Serial.println("Can't open wordclock_config.json for writing");
    return;
  }

  Serial.println("Save config.");

  StaticJsonDocument<1024> doc;
  doc["color_bg_r"] = CONFIG.color_bg.r;
  doc["color_bg_g"] = CONFIG.color_bg.g;
  doc["color_bg_b"] = CONFIG.color_bg.b;
  doc["color_fg_r"] = CONFIG.color_fg.r;
  doc["color_fg_g"] = CONFIG.color_fg.g;
  doc["color_fg_b"] = CONFIG.color_fg.b;
  doc["brightness"] = CONFIG.brightness;
  doc["timezone"] = CONFIG.timezone;
  doc["dnd_active"] = CONFIG.dnd_active;
  doc["dnd_start_hour"] = CONFIG.dnd_start.hour;
  doc["dnd_start_minute"] = CONFIG.dnd_start.minute;
  doc["dnd_end_hour"] = CONFIG.dnd_end.hour;
  doc["dnd_end_minute"] = CONFIG.dnd_end.minute;

  
  serializeJson(doc, file);

  file.close();
}

color_t hexToRgb(String value) {
  value.replace("#", "");
  int number = (int) strtol( value.c_str(), NULL, 16);
  
  // Split them up into r, g, b values
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;
  
  color_t rgb;
  rgb.r = r;
  rgb.g = g;
  rgb.b = b;

  return rgb;
}

String rgbToHex(const color_t hex) {
  long hexColor = ((long)hex.r << 16L) | ((long)hex.g << 8L) | (long)hex.b;

  String out = String(hexColor, HEX);

  while(out.length() < 6) {
    out = "0" + out;
  }

  return out;
}

int getLedId(int id) { 
  int col = id % GRID_COLS;
  int row = (floor)(id / GRID_COLS);
  int led = 0;
        
  if(GRID_ROWS % 2 == 0) {
    if(GRID_FIRST == 3) {       
      led = (row % 2 == 1) ? ((GRID_ROWS * 11) - 1) - ((row * 11) + col) : ((GRID_ROWS * 11) - 1) - (((row + 1) * 11) - col) + 1;
    } else if(GRID_FIRST == 2) {
      led = (row % 2 == 0) ? ((GRID_ROWS * 11) - 1) - ((row * 11) + col) : ((GRID_ROWS * 11) - 1) - (((row + 1) * 11) - col) + 1;
    } else if(GRID_FIRST == 1) {
      led = (row % 2 == 1) ? ((row * 11) + col) : (((row + 1) * 11) - col) - 1;
    } else if(GRID_FIRST == 0) {
      led = (row % 2 == 0) ? ((row * 11) + col) : (((row + 1) * 11) - col) - 1;
    }
  } else {
    if(GRID_FIRST == 3) {       
      led = (row % 2 == 0) ? ((GRID_ROWS * 11) - 1) - ((row * 11) + col) : ((GRID_ROWS * 11) - 1) - (((row + 1) * 11) - col) + 1;
    } else if(GRID_FIRST == 2) {
      led = (row % 2 == 1) ? ((GRID_ROWS * 11) - 1) - ((row * 11) + col) : ((GRID_ROWS * 11) - 1) - (((row + 1) * 11) - col) + 1;
    }else if(GRID_FIRST == 1) {
      led = (row % 2 == 1) ? ((row * 11) + col) : (((row + 1) * 11) - col) - 1;
    } else if(GRID_FIRST == 0) {
      led = (row % 2 == 0) ? ((row * 11) + col) : (((row + 1) * 11) - col) - 1;
    } 
  }

  return led;
}

void setOffset(String value) {
  timeClient.setTimeOffset(value.toInt() * 3600);
}

bool isDND(int hour, int minute) {
  if(!CONFIG.dnd_active) {
    return false;
  }
  
  if(CONFIG.dnd_start.hour < CONFIG.dnd_end.hour) {
    if(hour > CONFIG.dnd_start.hour && hour < CONFIG.dnd_end.hour) {
      return true;
    } else if(hour == CONFIG.dnd_start.hour && minute >= CONFIG.dnd_start.minute) {
      return true;
    } else if(hour == CONFIG.dnd_end.hour && minute < CONFIG.dnd_end.minute) {
      return true;
    }
    
    return false;
  } else if(CONFIG.dnd_start.hour > CONFIG.dnd_end.hour) {
    if(hour > CONFIG.dnd_start.hour) {
      return true;
    } else if(hour < CONFIG.dnd_end.hour) {
      return true;
    } else if(hour == CONFIG.dnd_start.hour && minute >= CONFIG.dnd_start.minute) {
      return true;
    } else if(hour == CONFIG.dnd_end.hour && minute < CONFIG.dnd_end.minute) {
      return true;
    }
    
    return false;
  } else {
    if(hour == CONFIG.dnd_start.hour && minute >= CONFIG.dnd_start.minute && minute < CONFIG.dnd_end.minute) {
      return true;
    }
    
    return false;
  }
  
  return false;  
}

void setTime(int hour, int minute) { 
  if(hour == -1 || minute == -1) {
    return;
  }

  if(isDND(hour, minute)) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(0, 0, 0);
    }

    FastLED.show();
    
    return;
  }
  
  int singleMinute = minute % 5;
  int hourLimit = 6;
  
  minute = (minute - (minute % 5));
  
  if(minute >= 25) {
    hour += 1;
  }

  minute = minute / 5;
  hour = hour % 12;

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(CONFIG.color_bg.r * 0.2, CONFIG.color_bg.g * 0.2, CONFIG.color_bg.b * 0.2);
  }
  
  for(int i = 0; i < 5; i++) {
    leds[getLedId(time_it_is[i])].setRGB(CONFIG.color_fg.r, CONFIG.color_fg.g, CONFIG.color_fg.b);
  }

  for(int m = 0; m < 12; m++) {
    if(time_minutes[minute][m] >= 0) {
      leds[getLedId(time_minutes[minute][m])].setRGB(CONFIG.color_fg.r, CONFIG.color_fg.g, CONFIG.color_fg.b);
    }
  }

  if(hour == 1 && minute == 0) {
    hourLimit = 3;
  }
  
  for(int h = 0; h < hourLimit; h++) {   
    if(time_hours[hour][h] >= 0) {
      leds[getLedId(time_hours[hour][h])].setRGB(CONFIG.color_fg.r, CONFIG.color_fg.g, CONFIG.color_fg.b);
    }
  }

  // single minutes
  for(int s = (NUM_LEDS - 4); s < (NUM_LEDS - 4 + singleMinute); s++) {
    leds[s].setRGB(CONFIG.color_fg.r, CONFIG.color_fg.g, CONFIG.color_fg.b);
  }

  FastLED.setBrightness(CONFIG.brightness);
  FastLED.show();
}

String pad(int value) {
  if(value < 10) {
    return "0" + String(value);
  }

  return String(value);
}

String getTimeForm() {
  String content = "";

  content += "<div>";
  content += "<label>Vordergrundfarbe</label>";
  content += "<input name=\"fg\" value=\"#" + rgbToHex(CONFIG.color_fg) + "\" type=\"color\">";
  content += "</div>";
  content += "<div>";
  content += "<label>Hintergrundfarbe</label>";
  content += "<input name=\"bg\" value=\"#" + rgbToHex(CONFIG.color_bg) + "\" type=\"color\">";
  content += "</div>";

  content += "<div>";
  content += "<label>Helligkeit</label>";
  //content += "<input name=\"brightness\" type=\"range\" min=\"0\" max=\"100\">";
  content += "<select name=\"brightness\">";

  for (int i = 10; i < 101; i+=10) {
    String label = String(i) + " &percnt;";
    content += htmlOption(label, String(i), String(CONFIG.brightness));
  }

  content += "</select>";
  content += "</div>";

  content += "<div>";
  content += "<label>Zeitzone</label>";
  content += "<select name=\"tz\">";
  
  for(int i = -12; i < 13; i++) {

    String label = String(i);
    
    if(i > 0) {
      label = "+" + label; 
    }    

    content += htmlOption(label, String(i), String(CONFIG.timezone));
  }
  
  content += "</select>";
  content += "</div>";

  content += "<div>";
  content += "<label>Nachtmodus</label>";
  content += "<select name=\"dnd_active\">";
  content += htmlOption("Inaktiv", String(0), String(CONFIG.dnd_active));
  content += htmlOption("Aktiv", String(1), String(CONFIG.dnd_active));
  content += "</select>";
  content += "</div>";
  
  content += "<div>";
  content += "<label>Nachtmodus Startzeit</label>";
  content += "<select class=\"time\" name=\"dnd_start_hour\">";
  
  for(int i = 0; i < 24; i++) {
    content += htmlOption(pad(i), String(i), String(CONFIG.dnd_start.hour));
  }
  
  content += "</select>:";
  content += "<select class=\"time\" name=\"dnd_start_minute\">";

  for(int i = 0; i < 60; i = i + 5) {
    content += htmlOption(pad(i), String(i), String(CONFIG.dnd_start.minute));
  }
  
  content += "</select>";
  content += "</div>";
  
  content += "<div>";
  content += "<label>Nachtmodus Endzeit</label>";
  content += "<select class=\"time\" name=\"dnd_end_hour\">";
  
  for(int i = 0; i < 24; i++) {
    content += htmlOption(pad(i), String(i), String(CONFIG.dnd_end.hour));
  }
  
  content += "</select>:";
  content += "<select class=\"time\" name=\"dnd_end_minute\">";

  for(int i = 0; i < 60; i = i + 5) {
    content += htmlOption(pad(i), String(i), String(CONFIG.dnd_end.minute));
  }
  
  content += "</select>";
  content += "</div>";

  return content;
}
String htmlOption(String label, String value, String store) {
  String content = "<option value=\"" + value + "\"";
  
  if (store == value) {
    content += " selected=\"selected\"";
  }
  
  content += ">" + label + "</option>";

  return content;
}

void change() {
  bool change = false;

  if(server.hasArg("mode")) {
    mode = server.arg("mode");
  }
  
  if(mode == "time"){
    if(server.hasArg("fg")) {
      CONFIG.color_fg = hexToRgb(server.arg("fg"));
      change = true;
    }
  
    if(server.hasArg("bg")) {
      CONFIG.color_bg = hexToRgb(server.arg("bg"));
      change = true;
    }

    if(server.hasArg("brightness")) {
      CONFIG.brightness = server.arg("brightness").toInt();
      change = true;
    }
    
    if(server.hasArg("tz")) {
      CONFIG.timezone = server.arg("tz").toInt();
      timeClient.setTimeOffset(CONFIG.timezone * 3600);
      change = true;
    }

    if(server.hasArg("dnd_active")) {
      int dnd_active = server.arg("dnd_active").toInt();
      
      CONFIG.dnd_active = dnd_active == 1;      
      change = true;
    }

    if(server.hasArg("dnd_start_hour")) {
      CONFIG.dnd_start.hour = server.arg("dnd_start_hour").toInt();
      change = true;
    }

    if(server.hasArg("dnd_start_minute")) {
      CONFIG.dnd_start.minute = server.arg("dnd_start_minute").toInt();
      change = true;
    }

    if(server.hasArg("dnd_end_hour")) {
      CONFIG.dnd_end.hour = server.arg("dnd_end_hour").toInt();
      change = true;
    }
    if(server.hasArg("dnd_end_minute")) {
      CONFIG.dnd_end.minute = server.arg("dnd_end_minute").toInt();
      change = true;
    }
  }

  if(change == true) {
    saveConfig();
    show();
  }
}

void handleRootPath() {  
  String content = "";

  change();

  content += "<!DOCTYPE html><html>";
  content += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  content += "<style>";
  content += "* { box-sizing: border-box; }";
  content += "html, body { font-family: Helvetica; margin: 0; padding: 0; }";
  content += ".form { margin: auto; max-width: 400px; }";
  content += ".form div { margin: 0; padding: 20px 0; width: 100%; font-size: 1.4rem; }";
  content += "label { width: 60%; display: inline-block; margin: 0; vertical-align: middle; }";
  content += "input, select { width: 38%; display: inline-block; margin: 0; border: 1px solid #eee; padding: 0; height: 40px; vertical-align: middle; }";
  content += "select.time { width: 18%; }";
  content += "button { display: inline-block; width: 100%; font-size: 1.4rem; background-color: green; border: 1px solid #eee; color: #fff; padding-top: 10px; padding-bottom: 10px; }";
  content += "</style>";
  content += "</head>";
  content += "<body>";  
  
  content += "<h1>WordClock WebServer</h1>";
  content += "<form class=\"form\" method=\"post\" action=\"\">";

  content += getTimeForm();
  
  content += "<div>";
  content += "<button name=\"submit\" type=\"submit\">Save</button>";
  content += "</div>";
  content += "</form>";
  content += "</body></html>";

  server.sendHeader("Location", "http://" + ip);
  server.send(200, "text/html", content);
 
}

void show() {
  Serial.println(mode);
  
  setTime(hour, minute);
}

void setup() {
  Serial.begin(74880);
  SPIFFS.begin();
  
  loadConfig();

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  WiFi.hostname("WordClock");

  WiFiManager wifiManager;
  wifiManager.autoConnect("WordClock");
  
  server.on("/", handleRootPath);
  server.begin();

  timeClient.begin();
  timeClient.update();

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 0);
  }

  FastLED.show();

  delay(1000);
  setTime(hour, minute);
}

void loop() {
  timeClient.update();
  
  int h = timeClient.getHours();
  int m = timeClient.getMinutes();

  if(h != hour || m != minute) {
    hour = h;
    minute = m;
    show();
  }
  
  server.handleClient();
}
