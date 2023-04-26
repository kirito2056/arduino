#include "TASK_MANAGER.h"
#include "WHITE_BOARD.h"


bool TASK_LED_ENABLE = false;
bool LED_ON = true;
int  MAX_LED_COUNT = 5;
int  CUR_LED_COUNT = 0;
TASK_ARGS ARGS_TASK_LED;
void TASK_LED(TASK_ARGS *args) {
	if (!TASK_LED_ENABLE) return;
	if (CUR_LED_COUNT >= MAX_LED_COUNT) {
		TASK_LED_ENABLE = false;
		CUR_LED_COUNT = 0;
		return;
	}
	
	if (LED_ON) {
		LED_ALL_ON;
	} else {
		LED_ALL_OFF;
		CUR_LED_COUNT += 1;
	}
	LED_ON = !LED_ON;
}

TASK_ARGS ARGS_TASK_SW_2;
void TASK_SW_2(TASK_ARGS *args) {
	if (!TASK_LED_ENABLE && SW2) {
		TASK_LED_ENABLE = true;
	}
}


// 수행평가 제출용
