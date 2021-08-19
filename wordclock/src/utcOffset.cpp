#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include "utcOffset.h"
#include "config.h"

void UtcOffset::updateLocalizedUtcOffset() {
/* remove the depricated ESP8266 API call:  
 *HTTPClient http;
 *http.begin("http://worldtimeapi.org/api/ip");
*/

//  use the new API like below:
  WiFiClient client;
  HTTPClient http;
  http.begin(client, "http://worldtimeapi.org/api/ip");
  int responseCode = http.GET();

  if (responseCode == 200) {
    String payload = http.getString();

    StaticJsonDocument<1024> doc;
    deserializeJson(doc, payload);

    int utcOffset = doc["raw_offset"].as<int>();
    int dstOffset = doc["dst_offset"].as<int>();

    http.end();

    const int oldTimezone = Config::timezone;
    const int newTimezone = utcOffset + dstOffset;

    if (oldTimezone != newTimezone) {

      // save new timezone to config
      Serial.print("Old timezone: ");
      Serial.println(Config::timezone);
      Serial.print("New timezone: ");
      Serial.println(utcOffset + dstOffset);

      Config::timezone = utcOffset + dstOffset;
      Config::save();
    }

    return;
  }
  http.end();

  // use last known offset
  return;
}
