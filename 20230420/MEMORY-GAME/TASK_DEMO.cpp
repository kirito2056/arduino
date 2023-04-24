#include "TASK_MANAGER.h"
#include "WHITE_BOARD.h"

#define MAX_MEMORY	500

char FND[] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X27, 0X7F, 0X6F}; //FND 0~9 �迭����

extern bool FLAG_TASK_USER_ENABLE;
extern int  USER_INDEX;
extern bool USER_SW_REQUIRE;
extern bool FLAG_SW_OK;

bool FLAG_TASK_DEMO_ENABLE = false;
int DEMO_DATA[MAX_MEMORY];
int DEMO_COUNT = 0;
int DEMO_INDEX = 0;
bool FLAG_ON = true;
TASK_ARGS ARGS_TASK_DEMO;
void TASK_DEMO(TASK_ARGS *args) {
	if (!FLAG_TASK_DEMO_ENABLE) return;
    TASK_INFO* P_TASK_INFO = TASK_MANAGER::GET_TASK_INFO(args->TASK_INDEX);

	if (FLAG_ON) {
		if (DEMO_DATA[DEMO_INDEX] == 1) {
			LED0_ON;
			PORTB = FND[1];
		} else if (DEMO_DATA[DEMO_INDEX] == 2) {
			LED1_ON;
			PORTB = FND[2];
		} else if (DEMO_DATA[DEMO_INDEX] == 3) {
			LED2_ON;
			PORTB = FND[3];
		} else if (DEMO_DATA[DEMO_INDEX] == 4) {
			LED3_ON;
			PORTB = FND[4];
		} else if (DEMO_DATA[DEMO_INDEX] == 5) {
			LED4_ON;
			PORTB = FND[5];
		} else if (DEMO_DATA[DEMO_INDEX] == 6) {
			LED5_ON;
			PORTB = FND[6];
		} else if (DEMO_DATA[DEMO_INDEX] == 7) {
			LED6_ON;
			PORTB = FND[7];
		} else if (DEMO_DATA[DEMO_INDEX] == 8) {
			LED7_ON;
			PORTB = FND[8];
		}
	    P_TASK_INFO->TIME_LOOP = 200;
	} else {
		LED_ALL_OFF;
		PORTB = 0x00;
		DEMO_INDEX += 1;
	    P_TASK_INFO->TIME_LOOP = 500;
	}
	FLAG_ON = !FLAG_ON;

	if (DEMO_INDEX >= DEMO_COUNT) {
		FLAG_TASK_DEMO_ENABLE = false;

		FLAG_TASK_USER_ENABLE = true;
		USER_INDEX = 0;
		USER_SW_REQUIRE = true;
		FLAG_SW_OK = false;
	}

}

TASK_ARGS ARGS_TASK_SW_0;
void TASK_SW_0(TASK_ARGS *args) {
	if (!FLAG_TASK_DEMO_ENABLE && SW0 && !FLAG_TASK_USER_ENABLE) {
		if (DEMO_COUNT < MAX_MEMORY) {
			DEMO_DATA[DEMO_COUNT] = random(8) + 1;
			DEMO_COUNT += 1;
		}
		DEMO_INDEX = 0;
		FLAG_ON = true;
		FLAG_TASK_DEMO_ENABLE = true;
	}
}
