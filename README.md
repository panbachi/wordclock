# WordClock
[![Version](https://img.shields.io/badge/version-2.0.0-green.svg?style=for-the-badge)](#) [![mantained](https://img.shields.io/maintenance/yes/2019.svg?style=for-the-badge)](#)

[![maintainer](https://img.shields.io/badge/maintainer-Goran%20Zunic%20%40panbachi-blue.svg?style=for-the-badge)](https://www.panbachi.de)

**Font and german layout based on https://www.mikrocontroller.net/articles/Word_Clock**

# Requirements

## Healthcheck
* FastLED

## WordClock
* FastLED
* NTPClient

# Assemble
[![Word-Clock - Die WLAN Wort-Uhr zum selber bauen](https://img.youtube.com/vi/FvAM1t0tISE/0.jpg)](https://www.youtube.com/watch?v=FvAM1t0tISE)

# Installation
- Change the WiFi credentials in whe `wordclock/wordclock.ini`.
- Upload the sketch `wordclock/wordclock.ino` to your Wemos D1 mini (or other ESP8266).
- Enjoy

# Usage
Check in your router what IP-adress your Wemos got. Open a webbrowser and go to `http://[YOUR_WEMOS_IP]`. For (example) the IP-adress `192.168.178.20` go to `http://192.168.178.20`.

# Functions

## Mode = Time

### Set color
You can set a foreground and background color on your clock.

#### API example
`http://[YOUR_WEMOS_IP]/?mode=time&fg=#ffffff&bg=#000000`

### Set time offset
You can set a time offset to specify your timezone.

#### API example
`http://[YOUR_WEMOS_IP]/?mode=time&tz=3`


## Mode = Icon

### Set icon
For now there are some (not so good looking) icons implemented. They will be changed in future.

#### API example
`http://[YOUR_WEMOS_IP]/?mode=icon&icon=sun`


## Mode = Degree

### Set degree
Not it is possible to display degree values for temperatures. The values could be send for example by a home automation software.

#### API example
`http://[YOUR_WEMOS_IP]/?mode=degree&degree=27`

# Support me / Follow me
[![Web](https://img.shields.io/badge/www-panbachi.de-blue.svg?style=flat-square&colorB=3d72a8&colorA=333333)](https://www.panbachi.de)
[![Facebook](https://img.shields.io/badge/-%40panbachi.de-blue.svg?style=flat-square&logo=facebook&colorB=3B5998&colorA=eee)](https://www.facebook.com/panbachi.de/)
[![Twitter](https://img.shields.io/badge/-%40panbachi-blue.svg?style=flat-square&logo=twitter&colorB=1DA1F2&colorA=eee)](https://twitter.com/panbachi)
[![Instagram](https://img.shields.io/badge/-%40panbachi.de-blue.svg?style=flat-square&logo=instagram&colorB=E4405F&colorA=eee)](http://instagram.com/panbachi.de)
[![YouTube](https://img.shields.io/badge/-%40panbachi-blue.svg?style=flat-square&logo=youtube&colorB=FF0000&colorA=eee)](https://www.youtube.com/channel/UCO7f2L7ZsDCpOtRfKnPqNow)
