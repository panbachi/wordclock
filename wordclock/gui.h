#ifndef WORDCLOCK_GUI_H
#define WORDCLOCK_GUI_H

String&& GUI_pad(int value) {
  if(value < 10) {
    return std::move("0" + String(value));
  }

  return std::move(String(value));
}

String&& GUI_htmlOption(const String& label, const String& value, const String& store) {
  String content = "<option value=\"" + value + "\"";
  
  if (store == value) {
    content += " selected=\"selected\"";
  }
  
  content += ">" + label + "</option>";

  return std::move(content);
}

String GUI_getTimeForm() {
  String content = "";

  content += "<div>";
  content += "<label>Vordergrundfarbe</label>";
  content += "<input name=\"fg\" value=\"#" + Color::rgbToHex(Config::color_fg) + "\" type=\"color\">";
  content += "</div>";
  content += "<div>";
  content += "<label>Hintergrundfarbe</label>";
  content += "<input name=\"bg\" value=\"#" + Color::rgbToHex(Config::color_bg) + "\" type=\"color\">";
  content += "</div>";
  content += "<div>";
  content += "<label>Zeitzone</label>";
  content += "<select name=\"tz\">";
  
  for(int i = -12; i < 13; i++) {

    String label = String(i);
    
    if(i > 0) {
      label = "+" + label; 
    }    

    content += GUI_htmlOption(label, String(i), String(Config::timezone));
  }
  
  content += "</select>";
  content += "</div>";
  
  content += "<div>";
  content += "<label>NTP-Server</label>";
  content += "<input name=\"ntp\" type=\"text\" value=\"" + Config::ntp + "\">";
  content += "</div>";

  content += "<div>";
  content += "<label>Nachtmodus</label>";
  content += "<select name=\"dnd_active\">";
  content += GUI_htmlOption("Inaktiv", String(0), String(Config::dnd_active));
  content += GUI_htmlOption("Aktiv", String(1), String(Config::dnd_active));
  content += "</select>";
  content += "</div>";
  
  content += "<div>";
  content += "<label>Nachtmodus Startzeit</label>";
  content += "<select class=\"time\" name=\"dnd_start_hour\">";
  
  for(int i = 0; i < 24; i++) {
    content += GUI_htmlOption(GUI_pad(i), String(i), String(Config::dnd_start.hour));
  }
  
  content += "</select>:";
  content += "<select class=\"time\" name=\"dnd_start_minute\">";

  for(int i = 0; i < 60; i = i + 5) {
    content += GUI_htmlOption(GUI_pad(i), String(i), String(Config::dnd_start.minute));
  }
  
  content += "</select>";
  content += "</div>";
  
  content += "<div>";
  content += "<label>Nachtmodus Endzeit</label>";
  content += "<select class=\"time\" name=\"dnd_end_hour\">";
  
  for(int i = 0; i < 24; i++) {
    content += GUI_htmlOption(GUI_pad(i), String(i), String(Config::dnd_end.hour));
  }
  
  content += "</select>:";
  content += "<select class=\"time\" name=\"dnd_end_minute\">";

  for(int i = 0; i < 60; i = i + 5) {
    content += GUI_htmlOption(GUI_pad(i), String(i), String(Config::dnd_end.minute));
  }
  
  content += "</select>";
  content += "</div>";

  return content;
}

String GUI_createStyleSheet() {
  String content = "";

  content += "body { font-family: Arial, \"Helvetica Neue\", Helvetica, sans-serif; background-color: #eee; color: #333;}";
  content += "nav { position: fixed; top: 0; left: 0; right: 0; background-color: #3d72a8; list-style: none; margin: 0; display: flex;}";
  content += "nav li  {margin: 0; padding: 10px; flex: 1; text-align: center; color: #eee; cursor: pointer; }";
  content += "nav li.icon { padding: 6px; width: 50px; flex-grow: 0; flex-shrink: 0; flex-basis: 50px; cursor: inherit; }";
  content += "nav li.icon img { vertical-align: middle; }";
  content += "nav li.active { color: #ccc; }";
  content += "nav li svg path { fill: #eee; }";
  content += "nav li.active svg path { fill: #ccc; }";
  content += "main { margin-top: 60px; }";
  content += "main section { display: none; }";
  content += "main section.active { display: block; }";
  content += "footer { position: fixed; bottom: 0; left: 0; right: 0; background-color: #3d72a8; text-align: right; }";
  content += "footer button { background-color: #3d72a8; color: #eee; border: 0; padding: 15px; text-transform: uppercase; font-weight: bold; }";
  content += "footer button:hover,footer button:active { color: #ccc; cursor: pointer; }";
  content += "form div { color: #3d72a8; margin-bottom: 20px; }";
  content += "form div label { display: block; font-size: 0.8em; margin-bottom: 5px; }";
  content += "form div input { display: block; width: 100%; border: 0; padding: 0; margin: 0; border-bottom: 1px solid #3d72a8; height: 30px; }";
  content += "form div select { display: block; width: 100%; border: 0; padding: 0; margin: 0; border-bottom: 1px solid #3d72a8; height: 30px; }";
  content += "form div input[type=\"color\"] { border: 0; }";
  content += "form div div.time { display: flex; }";
  content += "form div div.time span { flex-basis: 20px; text-align: center; font-weight: bold; font-size: 1.3em; }";
  content += "form div div.time select { display: inline-block; flex: 1; }";
  content += "#wifi button { background-color: #3d72a8; border: 0; width: 100%; color: #eee; padding: 10px; cursor: pointer; }";

  return content;
}

String GUI_createNav() {
  String content = "";
  
  content += "<nav>";
  content += "<li class=\"icon\"><img src=\"/logo.svg\" width=\"32\"></li>";
  content += "<li class=\"active\" name=\"color\">";
  content += "<svg style=\"width:24px;height:24px\" viewBox=\"0 0 24 24\">";
  content += "<path fill=\"#eee\" d=\"M17.5,12A1.5,1.5 0 0,1 16,10.5A1.5,1.5 0 0,1 17.5,9A1.5,1.5 0 0,1 19,10.5A1.5,1.5 0 0,1 17.5,12M14.5,8A1.5,1.5 0 0,1 13,6.5A1.5,1.5 0 0,1 14.5,5A1.5,1.5 0 0,1 16,6.5A1.5,1.5 0 0,1 14.5,8M9.5,8A1.5,1.5 0 0,1 8,6.5A1.5,1.5 0 0,1 9.5,5A1.5,1.5 0 0,1 11,6.5A1.5,1.5 0 0,1 9.5,8M6.5,12A1.5,1.5 0 0,1 5,10.5A1.5,1.5 0 0,1 6.5,9A1.5,1.5 0 0,1 8,10.5A1.5,1.5 0 0,1 6.5,12M12,3A9,9 0 0,0 3,12A9,9 0 0,0 12,21A1.5,1.5 0 0,0 13.5,19.5C13.5,19.11 13.35,18.76 13.11,18.5C12.88,18.23 12.73,17.88 12.73,17.5A1.5,1.5 0 0,1 14.23,16H16A5,5 0 0,0 21,11C21,6.58 16.97,3 12,3Z\" />";
  content += "</svg>";
  content += "</li>";
  content += "<li name=\"time\">";
  content += "<svg style=\"width:24px;height:24px\" viewBox=\"0 0 24 24\">";
  content += "<path fill=\"#eee\" d=\"M12,20A8,8 0 0,0 20,12A8,8 0 0,0 12,4A8,8 0 0,0 4,12A8,8 0 0,0 12,20M12,2A10,10 0 0,1 22,12A10,10 0 0,1 12,22C6.47,22 2,17.5 2,12A10,10 0 0,1 12,2M12.5,7V12.25L17,14.92L16.25,16.15L11,13V7H12.5Z\" />";
  content += "</svg>";
  content += "</li>";
  content += "<li name=\"dnd\">";
  content += "<svg style=\"width:24px;height:24px\" viewBox=\"0 0 24 24\">";
  content += "<path fill=\"#eee\" d=\"M17.75,4.09L15.22,6.03L16.13,9.09L13.5,7.28L10.87,9.09L11.78,6.03L9.25,4.09L12.44,4L13.5,1L14.56,4L17.75,4.09M21.25,11L19.61,12.25L20.2,14.23L18.5,13.06L16.8,14.23L17.39,12.25L15.75,11L17.81,10.95L18.5,9L19.19,10.95L21.25,11M18.97,15.95C19.8,15.87 20.69,17.05 20.16,17.8C19.84,18.25 19.5,18.67 19.08,19.07C15.17,23 8.84,23 4.94,19.07C1.03,15.17 1.03,8.83 4.94,4.93C5.34,4.53 5.76,4.17 6.21,3.85C6.96,3.32 8.14,4.21 8.06,5.04C7.79,7.9 8.75,10.87 10.95,13.06C13.14,15.26 16.1,16.22 18.97,15.95M17.33,17.97C14.5,17.81 11.7,16.64 9.53,14.5C7.36,12.31 6.2,9.5 6.04,6.68C3.23,9.82 3.34,14.64 6.35,17.66C9.37,20.67 14.19,20.78 17.33,17.97Z\" />";
  content += "</svg>";
  content += "</li>";
  content += "<li name=\"wifi\">";
  content += "<svg style=\"width:24px;height:24px\" viewBox=\"0 0 24 24\">";
  content += "<path fill=\"#eee\" d=\"M12,21L15.6,16.2C14.6,15.45 13.35,15 12,15C10.65,15 9.4,15.45 8.4,16.2L12,21M12,3C7.95,3 4.21,4.34 1.2,6.6L3,9C5.5,7.12 8.62,6 12,6C15.38,6 18.5,7.12 21,9L22.8,6.6C19.79,4.34 16.05,3 12,3M12,9C9.3,9 6.81,9.89 4.8,11.4L6.6,13.8C8.1,12.67 9.97,12 12,12C14.03,12 15.9,12.67 17.4,13.8L19.2,11.4C17.19,9.89 14.7,9 12,9Z\" />";
  content += "</svg>";
  content += "</li>";
  content += "</nav>";

  return content;
}

String GUI_createScript() {
  String content = "";
  
  content += "window.onload = function() {";
  content += "var nav = document.querySelector('nav');";
  content += "var navItems = nav.querySelectorAll('li');";
  content += "var sections = document.querySelectorAll('main section');";
  content += "navItems.forEach(function (navItem) {";
  content += "navItem.onclick = function(e) {";
  content += "if(e.currentTarget.tagName.toLowerCase() == 'li' && e.currentTarget.hasAttribute('name')) {";
  content += "for(var i = 0; i < navItems.length; i++) { navItems[i].classList.remove('active'); }";
  content += "e.currentTarget.classList.add('active');";
  content += "for(var i = 0; i < sections.length; i++) { sections[i].classList.remove('active'); }";
  content += "document.getElementById(e.currentTarget.getAttribute('name')).classList.add('active');";
  content += "}}});}";
}

String GUI_index() {
    String content = "";

    SERVER_change();
  
    content += "<!DOCTYPE html><html>";
    content += "<link rel=\"manifest\" href=\"/manifest.json\">";
    content += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    content += "<style>";
    content += GUI_createStyleSheet();
    content += "</style>";
    content += "<script>";
    content += GUI_createScript();
    content += "</script>";
    content += "</head>";
    content += "<body>";  
    
    content += "<div id=\"c\"";

    
    content += GUI_createNav();

    
    content += "<form class=\"form\" method=\"post\" action=\"\">";
  
    content += GUI_getTimeForm();
    
    content += "<div>";
    content += "<button name=\"submit\" type=\"submit\">Save</button>";
    content += "</div>";
    content += "</form>";


    content += "</div>";
    content += "</body></html>";
  
    return content;
  }



void GUI_handleRootPath() {  
  String content = "";

  SERVER_change();

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

  content += GUI_getTimeForm();
  
  content += "<div>";
  content += "<button name=\"submit\" type=\"submit\">Save</button>";
  content += "</div>";
  content += "</form>";
  content += "</body></html>";

  SERVER.sendHeader("Location", "http://" + SERVER_IP);
  SERVER.send(200, "text/html", content);
 
}
#endif
