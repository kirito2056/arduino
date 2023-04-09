#include "TASK_MANAGER.h"
#include "WHITE_BOARD.h"

bool TASK_LED_ENABLE = false;
bool TASK_LED_ON = true;
int MAX_LED_COUNT = 5;
int CUR_LED_COUNT = 0;
TASK_ARGS ARGS_TASK_LED;
void TASK_LED(TASK_ARGS *args) {
  if ( !TASK_LED_ENABLE) return;
  if ( CUR_LED_COUNT >= MAX_LED_COUNT) {
    TASK_LED_ENABLE = false;
    CUR_LED_COUNT = 0;
    return;
  }
  if ( TASK_LED_ON ) {
    LED_ALL_ON;
    PORTD = 0X00;
  } else {
    LED_ALL_OFF;
    PORTD = 0X10;
    CUR_LED_COUNT += 1;
  }
  TASK_LED_ON = !TASK_LED_ON;
}

TASK_ARGS ARGS_TASK_SW_1;
void TASK_SW_1(TASK_ARGS *args) {
	if (!FLAG_TASK_DEMO_ENABLE && SW0) {
    TASK_LED_ENABLE = true;
	}
}