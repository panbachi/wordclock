# WordClock
[![Version](https://img.shields.io/badge/version-3.0.0-green.svg?style=for-the-badge)](#) [![mantained](https://img.shields.io/maintenance/yes/2019.svg?style=for-the-badge)](#)

[![maintainer](https://img.shields.io/badge/maintainer-Goran%20Zunic%20%40panbachi-blue.svg?style=for-the-badge)](https://www.panbachi.de)

**Font and german layout based on https://www.mikrocontroller.net/articles/Word_Clock**

# Requirements

## Healthcheck
* [FastLED](https://github.com/FastLED/FastLED)

## WordClock
* [FastLED](https://github.com/FastLED/FastLED)
* [NTPClient](https://github.com/arduino-libraries/NTPClient)
* [WifiManager](https://github.com/tzapu/WiFiManager)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

# Assemble
[![Word-Clock - Die WLAN Wort-Uhr zum selber bauen](https://img.youtube.com/vi/FvAM1t0tISE/0.jpg)](https://www.youtube.com/watch?v=FvAM1t0tISE)

# Customizations
- If you connect additional 4 LEDs to the end of the stripe, they will be used to show the single minutes. This will work automatically without the need of any configuration.
- You can now use an 11x11 or 11x10 grid for the clock. This can be configured in the `wordclock/wordclock.ino`.
- You can define the position of the first LED in the `wordclock/wordclock.ino`

# Installation
- Change the grid settings in the `wordclock/wordclock.ino`.
- Upload the sketch `wordclock/wordclock.ino` to your Wemos D1 mini (or other ESP8266).
- Enjoy

# Usage
The WordClock creates a WiFi-Hotspot with the name "WordClock". Connect e.g. your smartphone to the hotspot and you will be forwared to the config page, where you can set the WiFi credentials.
Check in your router what IP-adress your WordClock got. Open a webbrowser and go to `http://[YOUR_WORDCLOCK_IP]`. For (example) the IP-adress `192.168.178.20` go to `http://192.168.178.20`.

# Functions

## Mode = Time

### Set color
You can set a foreground and background color on your clock.

#### API example
`http://[YOUR_WORDCLOCK_IP]/?mode=time&fg=#ffffff&bg=#000000`

### Set time offset
You can set a time offset to specify your timezone.

#### API example
`http://[YOUR_WORDCLOCK_IP]/?mode=time&tz=3`

### Set DND
You can set a time span in which the clock should be switched off.

#### API example
`http://[YOUR_WORDCLOCK_IP]/?mode=time&dnd_active=1&dnd_start_hour=23&dnd_start_minute=0&dnd_end_hour=6&dnd_end_hour=15`

### Set brightness
You can set the brightness on your clock.

#### API example
`http://[YOUR_WORDCLOCK_IP]/?mode=time&brightness=100`



# Support me / Follow me
[![Web](https://img.shields.io/badge/www-panbachi.de-blue.svg?style=flat-square&colorB=3d72a8&colorA=333333)](https://www.panbachi.de)
[![Facebook](https://img.shields.io/badge/-%40panbachi.de-blue.svg?style=flat-square&logo=facebook&colorB=3B5998&colorA=eee)](https://www.facebook.com/panbachi.de/)
[![Twitter](https://img.shields.io/badge/-%40panbachi-blue.svg?style=flat-square&logo=twitter&colorB=1DA1F2&colorA=eee)](https://twitter.com/panbachi)
[![Instagram](https://img.shields.io/badge/-%40panbachi.de-blue.svg?style=flat-square&logo=instagram&colorB=E4405F&colorA=eee)](http://instagram.com/panbachi.de)
[![YouTube](https://img.shields.io/badge/-%40panbachi-blue.svg?style=flat-square&logo=youtube&colorB=FF0000&colorA=eee)](https://www.youtube.com/channel/UCO7f2L7ZsDCpOtRfKnPqNow)
