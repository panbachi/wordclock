#include "httpServer.h"
#include "gui.h"
#include "controller.h"
    
void HttpServer::setup() {
    HttpServer::ip = WiFi.localIP().toString();
    
    HttpServer::web.on("/", Controller::index);
  
	HttpServer::web.on("/manifest.json", Controller::getManifest);
	HttpServer::web.on("/logo.svg", Controller::getLogoSvg);

	HttpServer::web.on("/api/color", HTTP_PUT, Controller::saveColor);
	HttpServer::web.on("/api/time", HTTP_PUT, Controller::saveTime);
	HttpServer::web.on("/api/dnd", HTTP_PUT, Controller::saveDnd);
	HttpServer::web.on("/api/wifi", HTTP_DELETE, Controller::deleteWiFi);

	HttpServer::web.onNotFound(Controller::notFound);
    HttpServer::web.begin();
}
  
void HttpServer::loop() {
    HttpServer::web.handleClient();
}

ESP8266WebServer HttpServer::web(80);
String HttpServer::ip;
