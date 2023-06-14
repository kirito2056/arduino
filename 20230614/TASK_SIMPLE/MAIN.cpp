#include "COMMON.h"
#include "TASK_SIMPLE.h"

bool TASK_LED0_ENABLE = false;
bool FLAG_LED0_ON = true;
void TASK_LED0() {
  if (!TASK_LED0_ENABLE) return;
  if (FLAG_LED0_ON) {
    LED0_ON;
  } else {
    LED0_OFF;
  }
  FLAG_LED0_ON = !FLAG_LED0_ON;
}

bool TASK_LED1_ENABLE = false;
bool FLAG_LED1_ON = true;
void TASK_LED1() {
  if (!TASK_LED1_ENABLE) return;
  if (FLAG_LED1_ON) {
    LED1_ON;
  } else {
    LED1_OFF;
  }
  FLAG_LED1_ON = !FLAG_LED1_ON;
}

bool TASK_LED2_ENABLE = false;
bool FLAG_LED2_ON = true;
void TASK_LED2() {
  if (!TASK_LED2_ENABLE) return;
  if (FLAG_LED2_ON) {
    LED2_ON;
  } else {
    LED2_OFF;
  }
  FLAG_LED2_ON = !FLAG_LED2_ON;
}

bool TASK_LED3_ENABLE = false;
bool FLAG_LED3_ON = true;
void TASK_LED3() {
  if (!TASK_LED3_ENABLE) return;
  if (FLAG_LED3_ON) {
    LED3_ON;
  } else {
    LED3_OFF;
  }
  FLAG_LED3_ON = !FLAG_LED3_ON;
}

bool TASK_LED4_ENABLE = false;
bool FLAG_LED4_ON = true;
void TASK_LED4() {
  if (!TASK_LED4_ENABLE) return;
  if (FLAG_LED4_ON) {
    LED4_ON;
  } else {
    LED4_OFF;
  }
  FLAG_LED4_ON = !FLAG_LED4_ON;
}

bool TASK_LED5_ENABLE = false;
bool FLAG_LED5_ON = true;
void TASK_LED5() {
  if (!TASK_LED5_ENABLE) return;
  if (FLAG_LED5_ON) {
    LED5_ON;
  } else {
    LED5_OFF;
  }
  FLAG_LED5_ON = !FLAG_LED5_ON;
}

bool TASK_LED6_ENABLE = false;
bool FLAG_LED6_ON = true;
void TASK_LED6() {
  if (!TASK_LED6_ENABLE) return;
  if (FLAG_LED6_ON) {
    LED6_ON;
  } else {
    LED6_OFF;
  }
  FLAG_LED6_ON = !FLAG_LED6_ON;
}

bool TASK_LED7_ENABLE = false;
bool FLAG_LED7_ON = true;
void TASK_LED7() {
  if (!TASK_LED7_ENABLE) return;
  if (FLAG_LED7_ON) {
    LED7_ON;
  } else {
    LED7_OFF;
  }
  FLAG_LED7_ON = !FLAG_LED7_ON;
}

void setup() {
  TASK_SIMPLE::SETUP();
  DDRE = 0b11111111;
  TASK_SIMPLE::NEW_TASK(TASK_LED0, 0, 100, 1000);
  TASK_SIMPLE::NEW_TASK(TASK_LED1, 1, 100, 1100);
  TASK_SIMPLE::NEW_TASK(TASK_LED2, 2, 100, 1200);
  TASK_SIMPLE::NEW_TASK(TASK_LED3, 3, 100, 1300);
  TASK_SIMPLE::NEW_TASK(TASK_LED4, 4, 100, 1400);
  TASK_SIMPLE::NEW_TASK(TASK_LED5, 5, 100, 1500);
  TASK_SIMPLE::NEW_TASK(TASK_LED6, 6, 100, 1600);
  TASK_SIMPLE::NEW_TASK(TASK_LED7, 7, 100, 1700);
  TASK_LED0_ENABLE = true;
  TASK_LED1_ENABLE = true;
  TASK_LED2_ENABLE = true;
  TASK_LED3_ENABLE = true;
  TASK_LED4_ENABLE = true;
  TASK_LED5_ENABLE = true;
  TASK_LED6_ENABLE = true;
  TASK_LED7_ENABLE = true;
}

void loop() {
  TASK_SIMPLE::LOOP();
}
