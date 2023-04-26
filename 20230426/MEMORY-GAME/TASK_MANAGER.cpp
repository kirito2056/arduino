/*
  TASK_MANAGER.cpp
*/
#include "TASK_MANAGER.h"

TASK_INFO TASK_MANAGER::TASK_INFO_TABLE[TASK_MAX_COUNT];

TASK_MANAGER::TASK_MANAGER() {
}

void TASK_MANAGER::SETUP(){
	for (int i=0; i<TASK_MAX_COUNT; i++) {
		TASK_INFO_TABLE[i].FLAG_ENABLE	= false;
		TASK_INFO_TABLE[i].TIME_LOOP	= 0;
	}
}

void TASK_MANAGER::LOOP(){
	unsigned long TIME_CURRENT	= millis();
	for (int i=0; i<TASK_MAX_COUNT; i++) {
		if (TASK_INFO_TABLE[i].FLAG_ENABLE) {
			if (TASK_INFO_TABLE[i].TASK_EXEC_TIME <= TIME_CURRENT) {
				if (TASK_INFO_TABLE[i].TIME_LOOP > 0) {
					TASK_INFO_TABLE[i].TASK_EXEC_TIME = millis() + TASK_INFO_TABLE[i].TIME_LOOP;
				} else {
					TASK_INFO_TABLE[i].FLAG_ENABLE = false;
				}
				TASK_INFO_TABLE[i].TASK_FUNC(TASK_INFO_TABLE[i].ARGS);
			}
		}
	}
}

void TASK_MANAGER::RESTART() {
  unsigned long TIME_PLUS_FIVESECOND = millis() + 5000;
  while ( millis() < TIME_PLUS_FIVESECOND) {
      LCD_PRINT(0, "GAME OVER       ");
      sprintf(STR_LINE, "SCORE : %08d", SCORE);
      LCD_PRINT(1, STR_LINE);
  }
  TASK_MANAGER::LOOP();
}

int TASK_MANAGER::NEW_TASK(void (*TASK_FUNC)(TASK_ARGS *ARGS), TASK_ARGS *ARGS, int TIME_OUT, int TIME_LOOP) {
	int TASK_INDEX = 0;
	for (int i=0; i<TASK_MAX_COUNT; i++) {
		if (!TASK_INFO_TABLE[i].FLAG_ENABLE) {
			TASK_INFO_TABLE[i].TASK_FUNC		= TASK_FUNC;
			TASK_INFO_TABLE[i].TASK_EXEC_TIME	= millis() + TIME_OUT;
			TASK_INFO_TABLE[i].FLAG_ENABLE		= true;
			TASK_INFO_TABLE[i].TIME_LOOP		= TIME_LOOP;
			TASK_INFO_TABLE[i].TIME_OUT			= TIME_OUT;
			TASK_INFO_TABLE[i].ARGS				= ARGS;
			TASK_INFO_TABLE[i].ARGS->TASK_INDEX = i;
			TASK_INDEX = i;
			break;
		}
	}
	return TASK_INDEX;
}

int TASK_MANAGER::END_TASK(int TASK_INDEX) {
	TASK_INFO_TABLE[TASK_INDEX].FLAG_ENABLE = false;
	return TASK_INDEX;
}

TASK_INFO* TASK_MANAGER::GET_TASK_INFO(int TASK_INDEX) {
	return &TASK_INFO_TABLE[TASK_INDEX];
}


// ������ �����
