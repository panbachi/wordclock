#include <Arduino.h>

#include "gui.h"
#include "color.h"
#include "config.h"
#include "led.h"

String Gui::pad(int value) {
  if(value < 10) {
    return "0" + String(value);
  }

  return String(value);
}

String Gui::htmlOption(const String& label, const String& value, const String& store) {
  String content = "<option value=\"" + value + "\"";
  if (store == value) {
    content += " selected=\"selected\"";
  }

  content += ">" + label + "</option>";

  return content;
}

String Gui::getTimeForm() {
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
  content += "<label>Stromversorgung in mA</label>";
  content += "<input id=\"power_supply\" type=\"number\" step=\"100\" value=\"" + String(Config::power_supply) + "\">";
  content += "</div>";
  content += "<div>";
  content += "<label>Helligkeit</label>";
  content += "<select name=\"brightness\">";

  for (double brightness_percnt = 0.0; brightness_percnt < Led::getMaxBrightnessPercnt(); brightness_percnt+=0.05) {
    String label = String((int) (brightness_percnt * 100 + 0.5)) + "&percnt;"; // adding 0.5 for rounding.
    content += Gui::htmlOption(label, String(brightness_percnt), String(Config::brightness));
  }
  if (Led::getMaxBrightnessPercnt() < 1.0) { // show maximum brightness percentage between the 5% steps.
    String label = String((int) (Led::getMaxBrightnessPercnt() * 100 + 0.5)) + "&percnt;";
    content += Gui::htmlOption(label, String(Led::getMaxBrightnessPercnt()), String(Config::brightness));
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

    content += Gui::htmlOption(label, String(i), String(Config::timezone));
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
  content += Gui::htmlOption("Inaktiv", String(0), String(Config::dnd_active));
  content += Gui::htmlOption("Aktiv", String(1), String(Config::dnd_active));
  content += "</select>";
  content += "</div>";

  content += "<div>";
  content += "<label>Nachtmodus Startzeit</label>";
  content += "<select class=\"time\" name=\"dnd_start_hour\">";

  for(int i = 0; i < 24; i++) {
    content += Gui::htmlOption(Gui::pad(i), String(i), String(Config::dnd_start.hour));
  }

  content += "</select>:";
  content += "<select class=\"time\" name=\"dnd_start_minute\">";

  for(int i = 0; i < 60; i = i + 5) {
    content += Gui::htmlOption(Gui::pad(i), String(i), String(Config::dnd_start.minute));
  }

  content += "</select>";
  content += "</div>";

  content += "<div>";
  content += "<label>Nachtmodus Endzeit</label>";
  content += "<select class=\"time\" name=\"dnd_end_hour\">";

  for(int i = 0; i < 24; i++) {
    content += Gui::htmlOption(Gui::pad(i), String(i), String(Config::dnd_end.hour));
  }

  content += "</select>:";
  content += "<select class=\"time\" name=\"dnd_end_minute\">";

  for(int i = 0; i < 60; i = i + 5) {
    content += Gui::htmlOption(Gui::pad(i), String(i), String(Config::dnd_end.minute));
  }

  content += "</select>";
  content += "</div>";

  return content;
}

String Gui::createStyleSheet() {
  String content = "";

  content += "body { font-family: Arial, \"Helvetica Neue\", Helvetica, sans-serif; background-color: #eee; color: #333;}";
  content += "nav { position: fixed; top: 0; left: 0; right: 0; background-color: #3d72a8; list-style: none; margin: 0; display: flex;}";
  content += "nav li  {margin: 0; padding: 10px; flex: 1; text-align: center; color: #eee; cursor: pointer; }";
  content += "nav li.icon { padding: 6px; width: 50px; flex-grow: 0; flex-shrink: 0; flex-basis: 50px; cursor: inherit; }";
  content += "nav li.icon img { vertical-align: middle; }";
  content += "nav li.active { color: #ccc; }";
  content += "nav li svg path { fill: #eee; }";
  content += "nav li.active svg path { fill: #ccc; }";
  content += "nav.disabled li:not(.icon) { display: none; }";
  content += "main { margin-top: 60px; }";
  content += "section { display: none; }";
  content += "section.active { display: block; }";
  content += "section div { color: #3d72a8; margin-bottom: 20px; }";
  content += "section div label { display: block; font-size: 0.8em; margin-bottom: 5px; }";
  content += "section div input { display: block; background-color:#fff; width: 100%; border: 0; padding: 0; margin: 0; border-bottom: 1px solid #3d72a8; height: 30px; }";
  content += "section div select { display: block; background-color:#fff; width: 100%; border: 0; padding: 0; margin: 0; border-bottom: 1px solid #3d72a8; height: 30px; }";
  content += "section div input[type=\"color\"] { border: 0; }";
  content += "section div div.time { display: flex; }";
  content += "section div div.time span { flex-basis: 20px; text-align: center; font-weight: bold; font-size: 1.3em; }";
  content += "section div div.time select { display: inline-block; flex: 1; }";
  content += "#reset_wifi { background-color: #3d72a8; border: 0; width: 100%; color: #eee; padding: 10px; cursor: pointer; }";
  content += "#reset_wifi_message { display: none; text-align: center;}";
  content += "footer { position: fixed; bottom: 0; left: 0; right: 0; background-color: #3d72a8; text-align: right; }";
  content += "footer button { background-color: #3d72a8; color: #eee; border: 0; padding: 15px; text-transform: uppercase; font-weight: bold; }";
  content += "footer button:hover,footer button:active { color: #ccc; cursor: pointer; }";

  return content;
}

String Gui::createNav() {
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

String Gui::createScript() {
  String content = "";

  content += "window.onload=function(){var e=function(e){return document.getElementById(e)},n=document.querySelector('nav'),t=n.querySelectorAll('li'),d=document.querySelectorAll('main section'),i=e('save'),a=e('reset_wifi'),o=e('reset_wifi_message'),c='color',l={fg:e('fg'),bg:e('bg'),power_supply:e('power_supply'),brightness:e('brightness'),healthcheck:e('healthcheck'),tzAuto:e('tz_auto'),tz:e('tz'),ntp:e('ntp'),dndActive:e('dnd_active'),dndSH:e('dnd_s_h'),dndSM:e('dnd_s_m'),dndEH:e('dnd_e_h'),dndEM:e('dnd_e_m')};t.forEach((function(n){n.onclick=function(n){if('li'==n.currentTarget.tagName.toLowerCase()&&n.currentTarget.hasAttribute('name')){c=n.currentTarget.getAttribute('name');for(var a=0;a<t.length;a++)t[a].classList.remove('active');for(n.currentTarget.classList.add('active'),a=0;a<d.length;a++)d[a].classList.remove('active');i.style.display='wifi'==c?'none':'inline-block',e(c).classList.add('active')}}})),i.onclick=function(e){var n={},t='/api/'+c;if('color'==c)n.fg=l.fg.value,n.bg=l.bg.value,n.power_supply=l.power_supply.value,n.brightness=l.brightness.value,n.healthcheck=l.healthcheck.value;else if('time'==c)n.tz_auto=l.tzAuto.value,n.tz=l.tz.value,n.ntp=l.ntp.value;else{if('dnd'!=c)return;n.dnd_active=l.dndActive.value,n.dnd_start_hour=l.dndSH.value,n.dnd_start_minute=l.dndSM.value,n.dnd_end_hour=l.dndEH.value,n.dnd_end_minute=l.dndEM.value}fetch(t,{method:'PUT',headers:{'Content-Type':'application/json'},body:JSON.stringify(n)}).then((function(e){}))},a.onclick=function(e){fetch('/api/wifi',{method:'DELETE',headers:{'Content-Type':'application/json'},body:''}).then((function(e){})),n.classList.add('disabled'),a.style.display='none',o.style.display='block'}};";

  return content;
}

String Gui::createContent() {
  String content = "";

  content += "<main>";

  content += "<section id=\"color\" class=\"active\">";
  content += "<div><label>Vordergrundfarbe</label><input id=\"fg\" value=\"#" + Color::rgbToHex(Config::color_fg) + "\" type=\"color\"></div>";
  content += "<div><label>Hintergrundfarbe</label><input id=\"bg\" value=\"#" + Color::rgbToHex(Config::color_bg) + "\" type=\"color\"></div>";
  content += "<div><label>Stromversorgung in mA</label><input id=\"power_supply\" type=\"number\" min=0 step=\"100\" value=\"" + String(Config::power_supply) + "\"></div>";
  content += "<div>";
  content += "<label>Helligkeit</label>";
  content += "<select id=\"brightness\">";

  for (double brightness_percnt = 0.0; brightness_percnt < Led::getMaxBrightnessPercnt(); brightness_percnt+=0.05) {
    String label = String((int) (brightness_percnt * 100 + 0.5)) + "&percnt;"; // adding 0.5 for rounding.
    content += Gui::htmlOption(label, String(brightness_percnt), String(Config::brightness));
  }
  if (Led::getMaxBrightnessPercnt() < 1.0) { // show maximum brightness percentage between the 5% steps.
    String label = String((int) (Led::getMaxBrightnessPercnt() * 100 + 0.5)) + "&percnt;";
    content += Gui::htmlOption(label, String(Led::getMaxBrightnessPercnt()), String(Config::brightness));
  }

  content += "</select>";
  content += "<div><label>LED check bei Start durchführen</label><select id=\"healthcheck\">";
  content += Gui::htmlOption("Inaktiv", String(0), String(Config::healthcheck));
  content += Gui::htmlOption("Aktiv", String(1), String(Config::healthcheck));
  content += "</select></div>";

  content += "</div>";
  content += "</section>";

  content += "<section id=\"time\">";
  content += "<div><label>Automatische Zeitzone</label><select id=\"tz_auto\">";
  content += Gui::htmlOption("Inaktiv", String(0), String(Config::automatic_timezone));
  content += Gui::htmlOption("Aktiv", String(1), String(Config::automatic_timezone));
  content += "</select></div>";
  content += "<div><label>Zeitzone</label>";
  if (Config::automatic_timezone) {
    content += "<select id=\"tz\" disabled>";
  } else {
    content += "<select id=\"tz\">";
  }

  for(int i = -12; i < 13; i++) {
    String label = String(i);

    if(i > 0) {
      label = "+" + label;
    }

    content += Gui::htmlOption(label, String(i * 3600), String(Config::timezone));
  }

  content += "</select></div>";
  content += "<div><label>NTP-Server</label><input id=\"ntp\" type=\"text\" value=\"" + Config::ntp + "\"></div>";
  content += "</section>";

  content += "<section id=\"dnd\">";
  content += "<div><label>Nachtmodus</label><select id=\"dnd_active\">";
  content += Gui::htmlOption("Inaktiv", String(0), String(Config::dnd_active));
  content += Gui::htmlOption("Aktiv", String(1), String(Config::dnd_active));
  content += "</select></div>";
  content += "<div><label>Start</label><div class=\"time\">";
  content += "<select id=\"dnd_s_h\">";

  for(int i = 0; i < 24; i++) {
    content += Gui::htmlOption(Gui::pad(i), String(i), String(Config::dnd_start.hour));
  }

  content += "</select><span>:</span><select id=\"dnd_s_m\">";

  for(int i = 0; i < 60; i = i + 5) {
    content += Gui::htmlOption(Gui::pad(i), String(i), String(Config::dnd_start.minute));
  }

  content += "</select></div></div>";
  content += "<div><label>Ende</label><div class=\"time\"><select id=\"dnd_e_h\">";

  for(int i = 0; i < 24; i++) {
    content += Gui::htmlOption(Gui::pad(i), String(i), String(Config::dnd_end.hour));
  }

  content += "</select><span>:</span><select id=\"dnd_e_m\">";

  for(int i = 0; i < 60; i = i + 5) {
    content += Gui::htmlOption(Gui::pad(i), String(i), String(Config::dnd_end.minute));
  }

  content += "</select></div></div>";
  content += "</section>";

  content += "<section id=\"wifi\">";
  content += "<button id=\"reset_wifi\" type=\"submit\">WiFi Einstellungen zurücksetzen</button>";
  content += "<div id=\"reset_wifi_message\">Die WiFi Einstellungen wurden zurückgesetzt. Es besteht keine Verbindung mehr zu der WordClock. Um die WordClock weiterhin zu verwenden muss das WiFi erneut eingerichtet werden.</div>";
  content += "</section>";
  content += "</main>";

  return content;
}

String Gui::createFooter() {
  String content = "";

  content += "<footer>";
  content += "<button id=\"save\" type=\"submit\" class=\"button\">Speichern</button>";
  content += "</footer>";

  return content;
}


String Gui::index() {
  String content = "";

  //HttpServer::change();

  content += "<!DOCTYPE html><html><head>";
  content += "<meta charset=\"utf-8\">";
  content += "<link rel=\"manifest\" href=\"/manifest.json\">";
  content += "<link rel=\"icon\" type=\"image/svg+xml\" href=\"logo.svg\" sizes=\"any\">";
  content += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  content += "<style>";
  content += Gui::createStyleSheet();
  content += "</style>";
  content += "<script>";
  content += Gui::createScript();
  content += "</script>";
  content += "</head>";
  content += "<body>";

  content += "<div id=\"c\">";
  content += Gui::createNav();
  content += Gui::createContent();
  content += Gui::createFooter();
  content += "</div>";
  content += "</body></html>";

  return content;
}
