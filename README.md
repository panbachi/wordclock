# WordClock
[![Version](https://img.shields.io/badge/version-0.0.1-green.svg?style=for-the-badge)](#) [![mantained](https://img.shields.io/maintenance/yes/2018.svg?style=for-the-badge)](#)

[![maintainer](https://img.shields.io/badge/maintainer-Goran%20Zunic%20%40panbachi-blue.svg?style=for-the-badge)](https://www.panbachi.de)

**Font and german layout based on https://www.mikrocontroller.net/articles/Word_Clock**

# Requirements
## Healthcheck
* FastLED

## WordClock
* FastLED
* Homie

# Installation
- Rename the file `data/homie/example.config.json` to `data/homie/config.json` and fill it with your data.
- Upload the data to your Wemos D1 mini (or other ESP8266). You can find a howto at http://esp8266.github.io/Arduino/versions/2.3.0/doc/filesystem.html#uploading-files-to-file-system.
- Upload the sketch `src/wordclock.ino` to your Wemos D1 mini (or other ESP8266).
- Enjoy

# MQTT
For now there are two MQTT services available. This part will be changed completely in future.

## Set color
Send the color (`rrggbb`, example for white: `ffffff`) to the address `/wordclock/c01/color/rgb/set`

## Set time offset
Send the offset in hours to the address `/wordclock/c01/offset/offset/set`

# Support me / Follow me
[![Web](https://img.shields.io/badge/www-panbachi.de-blue.svg?style=flat-square&colorB=3d72a8&colorA=333333)](https://www.panbachi.de)
[![Facebook](https://img.shields.io/badge/-%40panbachi.de-blue.svg?style=flat-square&logo=facebook&colorB=3B5998&colorA=eee)](https://www.facebook.com/panbachi.de/)
[![Twitter](https://img.shields.io/badge/-%40panbachi-blue.svg?style=flat-square&logo=twitter&colorB=1DA1F2&colorA=eee)](https://twitter.com/panbachi)
[![Instagram](https://img.shields.io/badge/-%40panbachi.de-blue.svg?style=flat-square&logo=instagram&colorB=E4405F&colorA=eee)](http://instagram.com/panbachi.de)
[![YouTube](https://img.shields.io/badge/-%40panbachi-blue.svg?style=flat-square&logo=youtube&colorB=FF0000&colorA=eee)](https://www.youtube.com/channel/UCO7f2L7ZsDCpOtRfKnPqNow)