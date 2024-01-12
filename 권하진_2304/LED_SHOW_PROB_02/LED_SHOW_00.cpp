#include <Arduino.h>
#include "COMMON.h"

void LED_SHOW_00() {
  if (!LED_TASKS[0].ENABLE) return;

  if (LED_TASKS[0].TOGGLE) {
    if (LED_TASKS[0].PLAY_CURR % 2 == 0) {
      PORTE = 0b00000001 << LED_TASKS[0].PLAY_CURR / 2;
    } else {
      PORTE = 0b10000000 >> LED_TASKS[0].PLAY_CURR / 2;
    }
  } else {
    PORTE = 0b00000000;
  }

  LED_TASKS[0].TOGGLE = !LED_TASKS[0].TOGGLE;
  LED_TASKS[0].PLAY_CURR += 1;

  if (LED_TASKS[0].PLAY_CURR >= 16) {
    LED_TASKS[0].ENABLE = false;
    LED_TASKS[0].PLAY_CURR = 0;
    ONE_LED_SHOW_COMPLETED = true;
  }
}

void LED_SHOW_01() {
  if (!LED_TASKS[1].ENABLE) return;

  if (LED_TASKS[1].TOGGLE) {
    if (LED_TASKS[1].PLAY_CURR % 2 == 0) {
      PORTE = 0b10000000 >> LED_TASKS[1].PLAY_CURR / 2;
    } else {
      PORTE = 0b00000001 << LED_TASKS[1].PLAY_CURR / 2;
    }
  } else {
    PORTE = 0b00000000;
  }

  LED_TASKS[1].TOGGLE = !LED_TASKS[1].TOGGLE;
  LED_TASKS[1].PLAY_CURR += 1;

  if (LED_TASKS[1].PLAY_CURR >= 16) {
    LED_TASKS[1].ENABLE = false;
    LED_TASKS[1].PLAY_CURR = 0;
    ONE_LED_SHOW_COMPLETED = true;
  }
}