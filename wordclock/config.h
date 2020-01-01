/***********************************************
 * CONFIG START
 **********************************************/
 
/* Grid rows
 * 
 * Options
 * -------
 * 10: 10 rows
 * 11: 11 rows
 */
#define GRID_ROWS 11

/* Grid cols
 * 
 * Options
 * ------- 
 * 11: 11 cols
 */
#define GRID_COLS 11

/* Postition of first LED  
 *   
 * Options
 * -------
 * 0: top-left
 * 1: top-right
 * 2: buttom-left
 * 3: buttom-right
 */
#define GRID_FIRST 2

/* Grid language
 *  
 * Options
 * -------
 * 1: de-DE: german
 * 2: de-DA: german alternative
 */
//#define GRID_LANGUAGE de-DE // default
//#define GRID_LANGUAGE de-DA

/* Position of single minute LEDs
 *  
 * Options
 * -------
 * 0: before
 * 1: after
 */
#define GRID_SINGLE_MINUTES 1

/* Data PIN, where the LED strip is connected to */
#define DATA_PIN D4

/***********************************************
 * CONFIG END
 **********************************************/






/*
 * Do not touch the code below this line
 */

class Config {
  public:
    static color_t color_bg;
    static color_t color_fg;
    static int timezone;
    static bool dnd_active;
    static clock_time_t dnd_start;
    static clock_time_t dnd_end;
    static String ntp;


    static void save() {
      File file = SPIFFS.open("/wordclock_config.json", "w");
    
      if(!file) {
        Serial.println("Can't open wordclock_config.json for writing");
        return;
      }
    
      Serial.println("Save config.");
      
      TIME_CLIENT.setPoolServerName(Config::ntp.c_str());
      TIME_CLIENT.setTimeOffset(Config::timezone * 3600);
      
      StaticJsonDocument<1024> doc;
      doc["color_bg_r"] = Config::color_bg.r;
      doc["color_bg_g"] = Config::color_bg.g;
      doc["color_bg_b"] = Config::color_bg.b;
      doc["color_fg_r"] = Config::color_fg.r;
      doc["color_fg_g"] = Config::color_fg.g;
      doc["color_fg_b"] = Config::color_fg.b;
      doc["timezone"] = Config::timezone;
      doc["dnd_active"] = Config::dnd_active;
      doc["dnd_start_hour"] = Config::dnd_start.hour;
      doc["dnd_start_minute"] = Config::dnd_start.minute;
      doc["dnd_end_hour"] = Config::dnd_end.hour;
      doc["dnd_end_minute"] = Config::dnd_end.minute;
      doc["ntp"] = Config::ntp;
      
      serializeJson(doc, file);
    
      file.close();
    }
    
    static void load() {
      Config::color_bg.r = 0;
      Config::color_bg.g = 0;
      Config::color_bg.b = 0;
      
      Config::color_fg.r = 255;
      Config::color_fg.g = 255;
      Config::color_fg.b = 255;
      
      Config::timezone = 0;
    
      Config::dnd_active = false;
      Config::dnd_start.hour = -1;
      Config::dnd_start.minute = -1;
      Config::dnd_end.hour = -1;
      Config::dnd_end.minute = -1;
      Config::ntp = "pool.ntp.org";
      
      File file = SPIFFS.open("/wordclock_config.json", "r");
    
      if(!file) {
        Serial.println("Failed to open config file.");
        Config::save();
        return;
      }
    
      Serial.println("Load config.");
      
      StaticJsonDocument<1024> doc;
      deserializeJson(doc, file);
    
      Config::color_bg.r = doc["color_bg_r"].as<int>();
      Config::color_bg.g = doc["color_bg_g"].as<int>();
      Config::color_bg.b = doc["color_bg_b"].as<int>();
    
      Config::color_fg.r = doc["color_fg_r"].as<int>();
      Config::color_fg.g = doc["color_fg_g"].as<int>();
      Config::color_fg.b = doc["color_fg_b"].as<int>();
    
      Config::timezone = doc["timezone"].as<int>();
    
      Config::dnd_active = doc["dnd_active"].as<bool>();
      Config::dnd_start.hour = doc["dnd_start_hour"].as<int>();
      Config::dnd_start.minute = doc["dnd_start_minute"].as<int>();
      Config::dnd_end.hour = doc["dnd_end_hour"].as<int>();
      Config::dnd_end.minute = doc["dnd_end_minute"].as<int>();
    
      if(doc["ntp"]) {
        Config::ntp = doc["ntp"].as<String>();
      }
      
      TIME_CLIENT.setPoolServerName(Config::ntp.c_str()); 
      TIME_CLIENT.setTimeOffset(Config::timezone * 3600);
      
      file.close();
    }
};
