#include "TASK_MANAGER.h"
#include "WHITE_BOARD.h"

bool TASK_BEEP_ENABLE = false;
bool TASK_BEEP_ON = true;
int MAX_BEEP_COUNT = 5;
int CUR_BEEP_COUNT = 0;
TASK_ARGS ARGS_TASK_BEEP;
void TASK_BEEP(TASK_ARGS *args) {
  if ( !TASK_BEEP_ENABLE) return;
  if ( CUR_BEEP_COUNT >= MAX_BEEP_COUNT) {
    TASK_BEEP_ENABLE = false;
    CUR_BEEP_COUNT = 0;
    return;
  }
  if ( TASK_BEEP_ON ) {
    PORTD = 0X00;
  } else {
    PORTD = 0X10;
    CUR_BEEP_COUNT += 1;
  }
  TASK_BEEP_ON = !TASK_BEEP_ON;
}

TASK_ARGS ARGS_TASK_SW_1;
void TASK_SW_1(TASK_ARGS *args) {
	if (!FLAG_TASK_DEMO_ENABLE && SW0) {
    TASK_BEEP_ENABLE = true;
	}
}