#ifndef WORDCLOCK_SERVER_H
#define WORDCLOCK_SERVER_H

#include <ESP8266WebServer.h>

class HttpServer {
  public:
    static ESP8266WebServer web;
    static String ip;
    
    static void setup();
    static void loop();
};

#endif
