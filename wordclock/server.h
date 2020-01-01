#ifndef WORDCLOCK_SERVER_H
#define WORDCLOCK_SERVER_H

ESP8266WebServer SERVER(80);
String SERVER_IP = "";

void SERVER_change() {
  bool change = false;
  
  if(SERVER.hasArg("fg")) {
    Config::color_fg = Color::hexToRgb(SERVER.arg("fg"));
    change = true;
  }

  if(SERVER.hasArg("bg")) {
    Config::color_bg = Color::hexToRgb(SERVER.arg("bg"));
    change = true;
  }
  
  if(SERVER.hasArg("tz")) {
    Config::timezone = SERVER.arg("tz").toInt();
    change = true;
  }

  if(SERVER.hasArg("dnd_active")) {
    int dnd_active = SERVER.arg("dnd_active").toInt();
    
    Config::dnd_active = dnd_active == 1;      
    change = true;
  }

  if(SERVER.hasArg("dnd_start_hour")) {
    Config::dnd_start.hour = SERVER.arg("dnd_start_hour").toInt();
    change = true;
  }

  if(SERVER.hasArg("dnd_start_minute")) {
    Config::dnd_start.minute = SERVER.arg("dnd_start_minute").toInt();
    change = true;
  }

  if(SERVER.hasArg("dnd_end_hour")) {
    Config::dnd_end.hour = SERVER.arg("dnd_end_hour").toInt();
    change = true;
  }
  if(SERVER.hasArg("dnd_end_minute")) {
    Config::dnd_end.minute = SERVER.arg("dnd_end_minute").toInt();
    change = true;
  }

  if(SERVER.hasArg("ntp")) {
    Config::ntp = SERVER.arg("ntp");
    change = true;  
  }

  if(change == true) {
    Config::save();
    setTime(TIME_HOUR, TIME_MINUTE);
  }
}

void SERVER_setup() {
  SERVER_IP = WiFi.localIP().toString();
  
  SERVER.on("/", GUI_handleRootPath);
  SERVER.begin();
}

void SERVER_loop() {
  SERVER.handleClient();
}
#endif
