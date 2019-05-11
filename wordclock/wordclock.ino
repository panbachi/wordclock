#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define NUM_LEDS 121
#define DATA_PIN D4

/**********************
 * SET WIFI CREDENTIALS
 **********************/
const char* ssid  = "";
const char* password = "";



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

int time_it_is[] = {110, 111, 113, 114, 115};
  
int time_minutes[][12] = {
  { 13,  12,  11,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},
  {117, 118, 119, 120,  85,  84,  83,  82,  -1,  -1,  -1,  -1},
  {109, 108, 107, 106,  85,  84,  83,  82,  -1,  -1,  -1,  -1},
  { 92,  93,  94,  95,  96,  97,  98,  85,  84,  83,  82,  -1},
  {105, 104, 103, 102, 101, 100,  99,  85,  84,  83,  82,  -1},
  {117, 118, 119, 120,  81,  80,  79,  66,  67,  68,  69,  -1},
  { 66,  67,  68,  69,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},
  {117, 118, 119, 120,  85,  84,  83,  82,  66,  67,  68,  69},
  {105, 104, 103, 102, 101, 100,  99,  81,  80,  79,  -1,  -1},
  { 92,  93,  94,  95,  96,  97,  98,  81,  80,  79,  -1,  -1},
  {109, 108, 107, 106,  81,  80,  79,  -1,  -1,  -1,  -1,  -1},
  {117, 118, 119, 120,  81,  80,  79,  -1,  -1,  -1,  -1,  -1}
};

int time_hours[][6] = {
  {71, 72, 73, 74, 75, -1},
  {63, 62, 61, 60, -1, -1},
  {65, 64, 63, 62, -1, -1},
  {45, 46, 47, 48, -1, -1},
  {36, 35, 34, 33, -1, -1},
  {51, 52, 53, 54, -1, -1},
  {20, 19, 18, 17, 16, -1},
  {60, 59, 58, 57, 56, 55},
  {23, 24, 25, 26, -1, -1},
  {40, 39, 38, 37, -1, -1},
  {27, 28, 29, 30, -1, -1},
  {43, 42, 41, -1, -1, -1}
};

int degree_minus[] = {108, 107, 106, 105};

int degree_symbol[] = { 119, 101, 99, 97};

int degree_10[] = {70, 61, 48, 39, 26, 17, 4};
int degree_20[] = {67, 68, 69, 70, 61, 48, 42, 41, 40, 39, 23, 20, 1, 2, 3, 4};
int degree_30[] = {67, 68, 69, 70, 61, 48, 42, 41, 40, 39, 26, 17, 1, 2, 3, 4};
int degree_40[] = {67, 70, 64, 61, 45, 48, 42, 41, 40, 39, 26, 17, 4};

int degree_0[] = {72, 73, 74, 75, 59, 56, 50, 53, 37, 34, 28, 31, 15, 12, 6, 7, 8, 9};
int degree_1[] = {75, 56, 53, 34, 31, 12, 9};
int degree_2[] = {72, 73, 74, 75, 56, 53, 37, 36, 35, 34, 28, 15, 6, 7, 8, 9};
int degree_3[] = {72, 73, 74, 75, 56, 53, 37, 36, 35, 34, 31, 12, 6, 7, 8, 9};
int degree_4[] = {72, 75, 59, 56, 50, 53, 37, 36, 35, 34, 31, 12, 9};
int degree_5[] = {72, 73, 74, 75, 59, 50, 37, 36, 35, 34, 31, 12, 6, 7, 8, 9};
int degree_6[] = {72, 73, 74, 75, 59, 50, 37, 36, 35, 34, 28, 31, 15, 12, 6, 7, 8, 9};
int degree_7[] = {72, 73, 74, 75, 56, 53, 34, 31, 12, 9};
int degree_8[] = {72, 73, 74, 75, 59, 56, 50, 53, 37, 36, 35, 34, 28, 31, 15, 12, 6, 7, 8, 9};
int degree_9[] = {72, 73, 74, 75, 59, 56, 50, 53, 37, 36, 35, 34, 31, 12, 6, 7, 8, 9};

pixel_color_t icon_snow[] = {
  { 5, 212, 223, 244 }, { 6, 176, 208, 247 }, { 7, 169, 206, 246 }, { 8, 207, 229, 249 }, { 14, 213, 232, 249 },
  { 15, 114, 175, 239 }, { 16, 86, 159, 237 }, { 17, 86, 159, 237 }, { 18, 155, 198, 244 }, { 19, 233, 233, 233 },
  { 23, 255, 255, 255 }, { 24, 201, 223, 245 }, { 25, 168, 203, 245 }, { 26, 171, 205, 245 }, { 27, 96, 165, 238 },
  { 28, 86, 159, 237 }, { 29, 86, 159, 237 }, { 30, 86, 159, 237 }, { 31, 200, 224, 249 }, { 34, 229, 246, 255 },
  { 35, 193, 220, 245 }, { 36, 166, 205, 244 }, { 37, 86, 159, 237 }, { 38, 86, 159, 237 }, { 39, 86, 159, 237 },
  { 40, 86, 159, 237 }, { 41, 86, 159, 237 }, { 42, 86, 159, 237 }, { 43, 94, 164, 238 }, { 44, 202, 223, 246 },
  { 45, 168, 205, 244 }, { 46, 86, 159, 237 }, { 47, 86, 159, 237 }, { 48, 86, 159, 237 }, { 49, 86, 159, 237 },
  { 50, 86, 159, 237 }, { 51, 86, 159, 237 }, { 52, 86, 159, 237 }, { 53, 86, 159, 237 }, { 54, 86, 160, 237 },
  { 55, 191, 219, 247 }, { 56, 166, 203, 245 }, { 57, 86, 159, 237 }, { 58, 86, 159, 237 }, { 59, 86, 159, 237 },
  { 60, 86, 159, 237 }, { 61, 86, 159, 237 }, { 62, 86, 159, 237 }, { 63, 86, 159, 237 }, { 64, 86, 159, 237 },
  { 65, 86, 159, 237 }, { 66, 168, 205, 244 }, { 67, 202, 223, 246 }, { 68, 96, 165, 238 }, { 69, 86, 159, 237 },
  { 70, 89, 161, 237 }, { 71, 93, 163, 238 }, { 72, 86, 159, 237 }, { 73, 86, 159, 237 }, { 74, 86, 159, 237 },
  { 75, 86, 159, 237 }, { 76, 86, 159, 237 }, { 77, 184, 215, 245 }, { 78, 204, 221, 238 }, { 79, 180, 212, 245 },
  { 80, 148, 194, 242 }, { 81, 210, 228, 245 }, { 82, 156, 199, 241 }, { 83, 145, 193, 242 }, { 84, 193, 219, 244 },
  { 85, 182, 214, 243 }, { 86, 161, 201, 244 }, { 87, 198, 220, 245 }, { 88, 176, 176, 176 }, { 91, 187, 187, 187 },
  { 92, 225, 225, 225 }, { 93, 225, 225, 225 }, { 94, 225, 225, 225 }, { 95, 226, 226, 226 }, { 96, 244, 244, 238 },
  { 97, 225, 225, 225 }, { 103, 237, 237, 237 }, { 104, 139, 139, 139 }, { 106, 246, 246, 237 }, { 107, 239, 239, 235 },
  { 114, 245, 245, 236 }, { 115, 241, 241, 241 }, { 117, 231, 231, 231 }, { 118, 251, 251, 243 }
};

pixel_color_t icon_thunder[] = {
  { 5, 206, 226, 244 }, { 6, 172, 208, 247 }, { 7, 165, 204, 244 }, { 8, 201, 224, 249 }, { 14, 213, 231, 249 },
  { 15, 110, 173, 239 }, { 16, 86, 159, 237 }, { 17, 86, 159, 237 }, { 18, 152, 195, 243 }, { 19, 239, 239, 239 },
  { 20, 255, 255, 255 }, { 23, 223, 223, 223 }, { 24, 193, 220, 247 }, { 25, 157, 198, 243 }, { 26, 171, 207, 245 },
  { 27, 114, 175, 240 }, { 28, 107, 172, 239 }, { 29, 97, 166, 238 }, { 30, 86, 159, 237 }, { 31, 199, 224, 246 },
  { 34, 217, 233, 249 }, { 35, 182, 212, 243 }, { 36, 156, 197, 243 }, { 37, 86, 159, 237 }, { 38, 211, 211, 197 },
  { 39, 239, 193, 104 }, { 40, 241, 198, 118 }, { 41, 230, 217, 185 }, { 42, 86, 159, 237 }, { 43, 89, 161, 237 },
  { 44, 196, 219, 245 }, { 45, 166, 204, 244 }, { 46, 86, 159, 237 }, { 47, 86, 159, 237 }, { 48, 99, 166, 238 },
  { 49, 230, 207, 156 }, { 50, 254, 164, 0 }, { 51, 237, 198, 122 }, { 52, 102, 168, 239 }, { 53, 86, 159, 237 },
  { 54, 86, 159, 237 }, { 55, 185, 214, 246 }, { 56, 164, 201, 243 }, { 57, 86, 159, 237 }, { 58, 86, 159, 237 },
  { 59, 230, 217, 185 }, { 60, 254, 171, 12 }, { 61, 250, 178, 46 }, { 62, 230, 217, 185 }, { 63, 86, 159, 237 },
  { 64, 86, 159, 237 }, { 65, 86, 159, 237 }, { 66, 172, 207, 243 }, { 67, 206, 224, 246 }, { 68, 115, 175, 239 },
  { 69, 86, 159, 237 }, { 70, 181, 209, 234 }, { 71, 230, 217, 185 }, { 72, 243, 194, 99 }, { 73, 254, 164, 0 },
  { 74, 215, 207, 181 }, { 75, 86, 159, 237 }, { 76, 89, 160, 237 }, { 77, 192, 219, 246 }, { 78, 203, 214, 214 },
  { 79, 195, 218, 245 }, { 80, 174, 208, 243 }, { 81, 233, 227, 208 }, { 82, 250, 178, 46 }, { 83, 254, 180, 46 },
  { 84, 232, 223, 203 }, { 85, 170, 207, 243 }, { 86, 178, 211, 245 }, { 87, 207, 221, 240 }, { 93, 165, 165, 165 },
  { 94, 251, 228, 183 }, { 95, 243, 194, 99 }, { 96, 92, 92, 92 }, { 103, 249, 233, 209 }, { 104, 237, 198, 122 },
  { 105, 208, 208, 208 }, { 117, 228, 228, 228 }, { 118, 251, 242, 225 }
};

pixel_color_t icon_rain[] = {
  { 5, 206, 226, 244 }, { 6, 174, 207, 243 }, { 7, 165, 204, 244 }, { 8, 203, 226, 249 }, { 14, 213, 231, 249 },
  { 15, 110, 173, 239 }, { 16, 86, 159, 237 }, { 17, 86, 159, 237 }, { 18, 152, 195, 243 }, { 19, 239, 239, 239 },
  { 20, 255, 255, 255 }, { 23, 223, 223, 223 }, { 24, 193, 220, 247 }, { 25, 155, 198, 243 }, { 26, 158, 200, 244 },
  { 27, 93, 163, 238 }, { 28, 86, 159, 237 }, { 29, 86, 159, 237 }, { 30, 86, 159, 237 }, { 31, 199, 224, 246 },
  { 34, 218, 228, 244 }, { 35, 182, 212, 245 }, { 36, 154, 196, 243 }, { 37, 86, 159, 237 }, { 38, 86, 159, 237 },
  { 39, 86, 159, 237 }, { 40, 86, 159, 237 }, { 41, 86, 159, 237 }, { 42, 86, 159, 237 }, { 43, 89, 161, 237 },
  { 44, 196, 219, 245 }, { 45, 166, 204, 244 }, { 46, 86, 159, 237 }, { 47, 86, 159, 237 }, { 48, 86, 159, 237 },
  { 49, 86, 159, 237 }, { 50, 86, 159, 237 }, { 51, 86, 159, 237 }, { 52, 86, 159, 237 }, { 53, 86, 159, 237 },
  { 54, 86, 159, 237 }, { 55, 185, 215, 245 }, { 56, 166, 203, 245 }, { 57, 86, 159, 237 }, { 58, 86, 159, 237 },
  { 59, 86, 159, 237 }, { 60, 86, 159, 237 }, { 61, 86, 159, 237 }, { 62, 86, 159, 237 }, { 63, 86, 159, 237 },
  { 64, 86, 159, 237 }, { 65, 86, 159, 237 }, { 66, 172, 207, 243 }, { 67, 205, 224, 246 }, { 68, 116, 175, 239 },
  { 69, 86, 159, 237 }, { 70, 86, 159, 237 }, { 71, 86, 159, 237 }, { 72, 86, 159, 237 }, { 73, 86, 159, 237 },
  { 74, 86, 159, 237 }, { 75, 86, 159, 237 }, { 76, 89, 161, 237 }, { 77, 192, 219, 246 }, { 78, 203, 214, 214 },
  { 79, 191, 218, 245 }, { 80, 165, 202, 244 }, { 81, 169, 204, 243 }, { 82, 164, 203, 244 }, { 83, 161, 201, 245 },
  { 84, 169, 204, 243 }, { 85, 165, 204, 244 }, { 86, 165, 203, 244 }, { 87, 207, 226, 245 }, { 91, 140, 187, 241 },
  { 92, 127, 177, 227 }, { 94, 138, 186, 239 }, { 95, 139, 181, 230 }, { 97, 140, 186, 243 }, { 98, 127, 179, 231 },
  { 101, 121, 166, 232 }, { 102, 138, 184, 242 }, { 104, 122, 169, 207 }, { 105, 130, 183, 231 }, { 107, 127, 145, 182 },
  { 108, 123, 177, 231 }, { 113, 137, 180, 239 }, { 114, 127, 178, 229 }
};

pixel_color_t icon_sun[] = {
  { 6, 253, 164, 0 }, { 13, 255, 166, 0 }, { 14, 255, 160, 0 }, { 17, 253, 163, 0 }, { 20, 255, 160, 0 },
  { 21, 255, 166, 0 }, { 24, 243, 156, 0 }, { 25, 253, 163, 0 }, { 26, 235, 156, 0 }, { 28, 226, 169, 0 },
  { 30, 235, 156, 0 }, { 31, 253, 163, 0 }, { 32, 243, 156, 0 }, { 36, 245, 160, 0 }, { 37, 243, 160, 0 },
  { 38, 253, 162, 0 }, { 39, 253, 163, 0 }, { 40, 253, 164, 0 }, { 41, 248, 163, 0 }, { 42, 245, 160, 0 },
  { 48, 253, 162, 0 }, { 49, 254, 164, 0 }, { 50, 254, 164, 0 }, { 51, 254, 164, 0 }, { 52, 253, 162, 0 },
  { 56, 253, 165, 0 }, { 57, 253, 165, 0 }, { 58, 207, 127, 0 }, { 59, 253, 163, 0 }, { 60, 254, 164, 0 },
  { 61, 254, 164, 0 }, { 62, 254, 164, 0 }, { 63, 253, 163, 0 }, { 64, 207, 127, 0 }, { 65, 253, 165, 0 },
  { 66, 253, 165, 0 }, { 70, 253, 163, 0 }, { 71, 254, 164, 0 }, { 72, 254, 164, 0 }, { 73, 254, 164, 0 },
  { 74, 253, 164, 0 }, { 80, 238, 153, 0 }, { 81, 232, 160, 0 }, { 82, 253, 163, 0 }, { 83, 253, 162, 0 },
  { 84, 253, 161, 0 }, { 85, 238, 158, 0 }, { 86, 238, 153, 0 }, { 90, 243, 158, 0 }, { 91, 253, 162, 0 },
  { 92, 238, 153, 0 }, { 94, 159, 127, 0 }, { 96, 238, 153, 0 }, { 97, 253, 162, 0 }, { 98, 243, 158, 0 },
  { 101, 245, 160, 0 }, { 102, 243, 158, 0 }, { 105, 253, 161, 0 }, { 108, 243, 158, 0 }, { 109, 245, 160, 0 },
  { 116, 253, 163, 0 }
};

pixel_color_t icon_cloud[] = {
  { 5, 212, 228, 249 }, { 6, 174, 208, 247 }, { 7, 169, 205, 246 }, { 8, 204, 227, 249 }, { 14, 214, 233, 249 },
  { 15, 113, 175, 240 }, { 16, 86, 159, 237 }, { 17, 86, 159, 237 }, { 18, 152, 196, 243 }, { 19, 235, 235, 235 },
  { 20, 255, 255, 255 }, { 23, 255, 255, 255 }, { 24, 198, 222, 245 }, { 25, 161, 202, 244 }, { 26, 165, 204, 244 },
  { 27, 94, 164, 238 }, { 28, 86, 159, 237 }, { 29, 86, 159, 237 }, { 30, 86, 159, 237 }, { 31, 200, 224, 249 },
  { 34, 226, 247, 247 }, { 35, 190, 217, 244 }, { 36, 163, 203, 244 }, { 37, 86, 159, 237 }, { 38, 86, 159, 237 },
  { 39, 86, 159, 237 }, { 40, 86, 159, 237 }, { 41, 86, 159, 237 }, { 42, 86, 159, 237 }, { 43, 93, 163, 238 },
  { 44, 197, 224, 248 }, { 45, 167, 205, 246 }, { 46, 86, 159, 237 }, { 47, 86, 159, 237 }, { 48, 86, 159, 237 },
  { 49, 86, 159, 237 }, { 50, 86, 159, 237 }, { 51, 86, 159, 237 }, { 52, 86, 159, 237 }, { 53, 86, 159, 237 },
  { 54, 86, 159, 237 }, { 55, 187, 216, 244 }, { 56, 164, 204, 243 }, { 57, 86, 159, 237 }, { 58, 86, 159, 237 },
  { 59, 86, 159, 237 }, { 60, 86, 159, 237 }, { 61, 86, 159, 237 }, { 62, 86, 159, 237 }, { 63, 86, 159, 237 },
  { 64, 86, 159, 237 }, { 65, 86, 159, 237 }, { 66, 167, 205, 243 }, { 67, 205, 223, 244 }, { 68, 102, 168, 238 },
  { 69, 86, 159, 237 }, { 70, 86, 159, 237 }, { 71, 86, 159, 237 }, { 72, 86, 159, 237 }, { 73, 86, 159, 237 },
  { 74, 86, 159, 237 }, { 75, 86, 159, 237 }, { 76, 86, 159, 237 }, { 77, 188, 215, 245 }, { 78, 208, 214, 237 },
  { 79, 189, 214, 245 }, { 80, 162, 200, 244 }, { 81, 162, 201, 244 }, { 82, 162, 201, 244 }, { 83, 162, 201, 244 },
  { 84, 162, 201, 244 }, { 85, 162, 201, 244 }, { 86, 169, 207, 244 }, { 87, 201, 222, 244 }, { 88, 169, 169, 169 }
};

CRGB leds[NUM_LEDS];
int r = 255;
int g = 255;
int b = 255;
int offset = 0;
int hour = -1;
int minute = -1;
String ip = "";

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pool.ntp.org", offset, 3600000);

ESP8266WebServer server(80);
String header;

color_t bgColor;
color_t fgColor;
int timezone;

String mode = "time";
String icon = "";
int degree = 0;

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

void setOffset(String value) {
  timeClient.setTimeOffset(value.toInt() * 3600);
}

pixel_color_t* getIcon(String icon, int& size) {
  if(icon == "cloud") {
    size = (sizeof(icon_cloud) / sizeof(pixel_color_t));
    return icon_cloud;
  } else if(icon == "sun") {
    size = (sizeof(icon_sun) / sizeof(pixel_color_t));
    return icon_sun;
  } else if(icon == "rain") {
    size = (sizeof(icon_rain) / sizeof(pixel_color_t));
    return icon_rain;
  } else if(icon == "thunder") {
    size = (sizeof(icon_thunder) / sizeof(pixel_color_t));
    return icon_thunder;
  } else if(icon == "snow") {
    size = (sizeof(icon_snow) / sizeof(pixel_color_t));
    return icon_snow;
  }  
} 

void setIcon() {
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i].setRGB(0, 0, 0);
  }

  int size = 0;
  pixel_color_t* pixels = getIcon(icon, size);
  
  for(int i = 0; i < size; i++) {
    leds[NUM_LEDS - pixels[i].pixel].setRGB(pixels[i].r, pixels[i].g, pixels[i].b);
  }

  FastLED.show();
}

void setTime(int hour, int minute) { 
  minute = (minute - (minute % 5));
  
  if(minute >= 25) {
    hour += 1;
  }

  minute = minute / 5;
  hour = hour % 12;

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(bgColor.r * 0.2, bgColor.g * 0.2, bgColor.b * 0.2);
  }
  
  for(int i = 0; i < 5; i++) {
    leds[time_it_is[i]].setRGB(fgColor.r, fgColor.g, fgColor.b);
  }

  for(int m = 0; m < 12; m++) {
    if(time_minutes[minute][m] >= 0) {
      leds[time_minutes[minute][m]].setRGB(fgColor.r, fgColor.g, fgColor.b);
    }
  }

  for(int h = 0; h < 6; h++) {
    if(time_hours[hour][h] >= 0) {
        leds[time_hours[hour][h]].setRGB(fgColor.r, fgColor.g, fgColor.b);
    }
  }

  FastLED.show();
}

void setDegree() {
  int value;

  value = degree;
  
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i].setRGB(0, 0, 0);
  }

  for(int i = 0; i < (sizeof(degree_symbol) / sizeof(int)); i++) { 
    leds[degree_symbol[i]].setRGB(255, 255, 255);
  }

  if(value < 0) {
    for(int i = 0; i < (sizeof(degree_minus) / sizeof(int)); i++) { 
      leds[degree_minus[i]].setRGB(255, 255, 255);
    }

    value = value * -1;
  }

  int ten = value / 10;
  int one = value % 10;

  if(ten == 1) {
    for(int i = 0; i < (sizeof(degree_10) / sizeof(int)); i++) { 
      leds[degree_10[i]].setRGB(255, 255, 255);
    }
  } else if(ten == 2) {
    for(int i = 0; i < (sizeof(degree_20) / sizeof(int)); i++) { 
      leds[degree_20[i]].setRGB(255, 255, 255);
    }
  } else if(ten == 3) {
    for(int i = 0; i < (sizeof(degree_30) / sizeof(int)); i++) { 
      leds[degree_30[i]].setRGB(255, 255, 255);
    }
  } else if(ten == 4) {
    for(int i = 0; i < (sizeof(degree_40) / sizeof(int)); i++) { 
      leds[degree_40[i]].setRGB(255, 255, 255);
    }
  }

  if(one == 1) {
    for(int i = 0; i < (sizeof(degree_1) / sizeof(int)); i++) { 
      leds[degree_1[i]].setRGB(255, 255, 255);
    }
  } else if(one == 2) {
    for(int i = 0; i < (sizeof(degree_2) / sizeof(int)); i++) { 
      leds[degree_2[i]].setRGB(255, 255, 255);
    }
  } else if(one == 3) {
    for(int i = 0; i < (sizeof(degree_3) / sizeof(int)); i++) { 
      leds[degree_3[i]].setRGB(255, 255, 255);
    }
  } else if(one == 4) {
    for(int i = 0; i < (sizeof(degree_4) / sizeof(int)); i++) { 
      leds[degree_4[i]].setRGB(255, 255, 255);
    }
  } else if(one == 5) {
    for(int i = 0; i < (sizeof(degree_5) / sizeof(int)); i++) { 
      leds[degree_5[i]].setRGB(255, 255, 255);
    }
  } else if(one == 6) {
    for(int i = 0; i < (sizeof(degree_6) / sizeof(int)); i++) { 
      leds[degree_6[i]].setRGB(255, 255, 255);
    }
  } else if(one == 7) {
    for(int i = 0; i < (sizeof(degree_7) / sizeof(int)); i++) { 
      leds[degree_7[i]].setRGB(255, 255, 255);
    }
  } else if(one == 8) {
    for(int i = 0; i < (sizeof(degree_8) / sizeof(int)); i++) { 
      leds[degree_8[i]].setRGB(255, 255, 255);
    }
  } else if(one == 9) {
    for(int i = 0; i < (sizeof(degree_9) / sizeof(int)); i++) { 
      leds[degree_9[i]].setRGB(255, 255, 255);
    }
  } else if(one == 0) {
    for(int i = 0; i < (sizeof(degree_0) / sizeof(int)); i++) { 
      leds[degree_0[i]].setRGB(255, 255, 255);
    }
  }

  FastLED.show();
}

String getTimeForm() {
  String content = "";

  content += "<div>";
  content += "<label>Foreground color</label>";
  content += "<input name=\"fg\" value=\"#" + rgbToHex(fgColor) + "\" type=\"color\">";
  content += "</div>";
  content += "<div>";
  content += "<label>Background color</label>";
  content += "<input name=\"bg\" value=\"#" + rgbToHex(bgColor) + "\" type=\"color\">";
  content += "</div>";
  content += "<div>";
  content += "<label>Timezone</label>";
  content += "<select name=\"tz\">";
  
  for(int i = -12; i < 13; i++) {

    String label = String(i);
    
    if(i > 0) {
      label = "+" + label; 
    }    

    content += htmlOption(label, String(i), String(timezone));
  }
  
  content += "</select>";
  content += "</div>";

  return content;
}

String getIconForm() {
  String content = "";
  content += "<div>";
  content += "<select name=\"icon\">";

  content += htmlOption("Cloud", "cloud", icon);
  content += htmlOption("Snow", "snow", icon);
  content += htmlOption("Rain", "rain", icon);
  content += htmlOption("Sun", "sun", icon);
  content += htmlOption("Thunder", "thunder", icon);

  content += "</select>";
  content += "</div>";

  return content;
}

String getDegreeForm() {
  String content = "";
  content += "<div>";
  content += "<input type=\"number\" name=\"degree\" value=\"" + String(degree) + "\">";
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
      fgColor = hexToRgb(server.arg("fg"));
      change = true;
    }
  
    if(server.hasArg("bg")) {
      bgColor = hexToRgb(server.arg("bg"));
      change = true;
    }
    
    if(server.hasArg("tz")) {
      timezone = server.arg("tz").toInt();
      timeClient.setTimeOffset(timezone * 3600);
      change = true;
    }
  } else if(mode == "icon") {
    if(server.hasArg("icon")) {
      icon = server.arg("icon");
    }
    change = true;
  } else if(mode == "degree") {
    if(server.hasArg("degree")) {
      String in = server.arg("degree");
      int factor = 1;
      Serial.println(String(in.toInt()) + " - " + in);
      
      
      if(in.charAt(0) == '-') {
        factor = -1;
        in.replace("-", "");
      }
  
      degree = in.toInt();
      degree = degree * factor;
      
      if(degree < -49) {
        degree = -49;
      } else if(degree > 49) {
        degree = 49;
      }
    }
    
    change = true;
  }

  if(change == true) {
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
  content += "button { display: inline-block; width: 100%; font-size: 1.4rem; background-color: green; border: 1px solid #eee; color: #fff; padding-top: 10px; padding-bottom: 10px; }";
  content += "</style>";
  content += "</head>";
  content += "<body>";  
  
  content += "<h1>WordClock WebServer</h1>";
  content += "<form class=\"form\" method=\"post\" action=\"\">";
  content += "<div>";
  content += "<select name=\"mode\">";

  content += htmlOption("Time", "time", mode);
  content += htmlOption("Icon", "icon", mode);
  content += htmlOption("Degree", "degree", mode);

  content += "</select>";
  content += "</div>";
  content += "<div>";
  content += "<button type=\"submit\">Change mode</button>";
  content += "</div>";
  content += "</form>";
  
  content += "<form class=\"form\" method=\"post\" action=\"\">";

  if(mode == "time") {
    content += getTimeForm();
  } else if(mode == "icon") {
    content += getIconForm();
  } else if(mode == "degree") {
    content += getDegreeForm();
  }
  
  content += "<div>";
  content += "<button type=\"submit\">Save</button>";
  content += "</div>";
  content += "</form>";
  content += "</body></html>";

  server.sendHeader("Location", "http://" + ip);
  server.send(200, "text/html", content);
 
}

void show() {
  Serial.println(mode);
  
  if(mode == "time") {
    setTime(hour, minute);
  } else if(mode == "icon") {
    setIcon();
  } else if(mode == "degree") {
    setDegree();
  }
}

void setup() {
  Serial.begin(74880);

  bgColor.r = 0;
  bgColor.g = 0;
  bgColor.b = 0;

  fgColor.r = 255;
  fgColor.g = 255;
  fgColor.b = 255;

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ip = WiFi.localIP() + "";
  
  server.on("/", handleRootPath);
  server.begin();

  timeClient.begin();
  timeClient.update();

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 0);
  }

  FastLED.show();

  show();
}

void loop() {
  timeClient.update();
  
  int h = timeClient.getHours();
  int m = timeClient.getMinutes();

  if(h != hour || m != minute) {
    if(mode == "time") {
      show();
    }
    hour = h;
    minute = m;
  }
  
  server.handleClient();
}
