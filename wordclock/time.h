#ifndef WORDCLOCK_TIME_H
#define WORDCLOCK_TIME_H
void setTime(int h, int m);

int TIME_HOUR = -1;
int TIME_MINUTE = -1;
WiFiUDP TIME_NTP_UDP;
NTPClient TIME_CLIENT(TIME_NTP_UDP);

void TIME_setup() {
  TIME_CLIENT.begin();
  TIME_CLIENT.update();
}

void TIME_loop() {
  TIME_CLIENT.update();
  
  int h = TIME_CLIENT.getHours();
  int m = TIME_CLIENT.getMinutes();

  if(m != TIME_MINUTE) {
    TIME_HOUR = h;
    TIME_MINUTE = m;
    setTime(TIME_HOUR, TIME_MINUTE);
  }
}
#endif
