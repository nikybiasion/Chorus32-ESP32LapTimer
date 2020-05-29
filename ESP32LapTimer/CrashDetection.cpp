#include "CrashDetection.h"

#include <rom/rtc.h>
#include <Arduino.h>

// positive values indicate a crashing system. negative values a manual reboot loop
RTC_NOINIT_ATTR static int crash_count = 0;

bool is_crash_mode() {
  return (crash_count > MAX_CRASH_COUNT) || (crash_count > -MAX_CRASH_COUNT);
}

void init_crash_detection() {
  // crash reason is not sw reset, so not a crash!
  if(rtc_get_reset_reason(0) != 12) {
    crash_count = 0;
  } else {
    ++crash_count;
  }
}

int get_crash_count() {
  return crash_count;
}

void reset_crash_count() {
  crash_count = 0;
}

void restart_esp() {
  --crash_count;
  ESP.restart();
}

void verbose_print_reset_reason(RESET_REASON reason)
{
  switch ( reason)
  {
    case 1  : Serial.println ("Vbat power on reset");break;
    case 3  : Serial.println ("Software reset digital core");break;
    case 4  : Serial.println ("Legacy watch dog reset digital core");break;
    case 5  : Serial.println ("Deep Sleep reset digital core");break;
    case 6  : Serial.println ("Reset by SLC module, reset digital core");break;
    case 7  : Serial.println ("Timer Group0 Watch dog reset digital core");break;
    case 8  : Serial.println ("Timer Group1 Watch dog reset digital core");break;
    case 9  : Serial.println ("RTC Watch dog Reset digital core");break;
    case 10 : Serial.println ("Instrusion tested to reset CPU");break;
    case 11 : Serial.println ("Time Group reset CPU");break;
    case 12 : Serial.println ("Software reset CPU");break;
    case 13 : Serial.println ("RTC Watch dog Reset CPU");break;
    case 14 : Serial.println ("for APP CPU, reseted by PRO CPU");break;
    case 15 : Serial.println ("Reset when the vdd voltage is not stable");break;
    case 16 : Serial.println ("RTC Watch dog reset digital core and rtc module");break;
    default : Serial.println ("NO_MEAN");
  }
}

void print_reset_reason_cpu(int cpu){
  verbose_print_reset_reason(rtc_get_reset_reason(cpu));
}
