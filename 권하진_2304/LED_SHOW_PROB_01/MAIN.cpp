#include "COMMON.h"
#include "TASK_SIMPLE.h"
#define MAX_SHOW_COUNT 32

LED_SHOW_INFO LED_TASKS[MAX_SHOW_COUNT];

bool ONE_LED_SHOW_COMPLETED = false;

void INIT_LED_TASKS() {
	for (int i=0; i<MAX_SHOW_COUNT; i++) {
		LED_TASKS[i].ENABLE		= false;
		LED_TASKS[i].TOGGLE		= true;
		LED_TASKS[i].PLAY_MAX	= 3;
		LED_TASKS[i].PLAY_CURR	= 0;
	}
  LED_TASKS[0].ENABLE = true;  // LED_SHOW_00 활성화
}

int SHOW_NUMBER = 0;
void LED_SHOW_SELECTOR() {
	if (!ONE_LED_SHOW_COMPLETED) return;
	ONE_LED_SHOW_COMPLETED = false;
//	LED_TASKS[random(4)].ENABLE = true;
//    SHOW_NUMBER += 1;
//   	LED_TASKS[SHOW_NUMBER % 1].ENABLE = true;
    if (LED_TASKS[0].ENABLE) {
      LED_TASKS[0].ENABLE = false;  // LED_SHOW_00 비활성화
      LED_TASKS[1].ENABLE = true;   // LED_SHOW_01 활성화
    } else {
      LED_TASKS[1].ENABLE = false;  // LED_SHOW_01 비활성화
      LED_TASKS[0].ENABLE = true;   // LED_SHOW_00 활성화
    }
  }
}

extern void LED_SHOW_00();

void setup() {
  DDRE = 0b11111111;

  INIT_LED_TASKS();

  TASK_SIMPLE::SETUP();
  TASK_SIMPLE::NEW_TASK(LED_SHOW_SELECTOR, 0, 100, 100);
  TASK_SIMPLE::NEW_TASK(LED_SHOW_00, 1, 100, 250);
  TASK_SIMPLE::NEW_TASK(LED_SHOW_01, 2, 100, 250);

  ONE_LED_SHOW_COMPLETED = true;
}


void loop() {
  TASK_SIMPLE::LOOP();
}
