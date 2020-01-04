#include "dnd.h"
#include "config.h"

bool DND::active(int hour, int minute) {
  if(!Config::dnd_active) {
    return false;
  }

  if(Config::dnd_start.hour < Config::dnd_end.hour) {
    if(hour > Config::dnd_start.hour && hour < Config::dnd_end.hour) {
      return true;
    } else if(hour == Config::dnd_start.hour && minute >= Config::dnd_start.minute) {
      return true;
    } else if(hour == Config::dnd_end.hour && minute < Config::dnd_end.minute) {
      return true;
    }
  } else if(Config::dnd_start.hour > Config::dnd_end.hour) {
    if(hour > Config::dnd_start.hour || hour < Config::dnd_end.hour) {
      return true;
    } else if(hour == Config::dnd_start.hour && minute >= Config::dnd_start.minute) {
      return true;
    } else if(hour == Config::dnd_end.hour && minute < Config::dnd_end.minute) {
      return true;
    }
  } else if(hour == Config::dnd_start.hour && minute >= Config::dnd_start.minute && minute < Config::dnd_end.minute) {
    return true;
  }
  
  return false;  
}
