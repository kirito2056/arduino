#include "TASK_MANAGER.h"
#include "WHITE_BOARD.h"

extern int DEMO_DATA[];
extern bool TASK_BEEP_ENABLE;
extern bool TASK_LED_ENABLE;

int USER_INDEX = 0;

bool FLAG_TASK_USER_ENABLE = false;
TASk_ARGS ARGS_TASK_USER;
void TASK_USER ( TASK_ARGS *args) {
  if ( !FLAG_TASK_USER_ENABLE) return;
  int WHAT_SW = WHAt_SW_PUSHED();
  if ( WHAT_SW < 0) return;

  if ( WHAT_SW == DEMO_DATA[USER_INDEX]) USER_INDEX++;
  USER_INDEX = 0;
  TASK_BEEP_ENABLE = true;
  TASK_LED_ENABLE = true;

}

int WHAT_SW_PUSHED() {
  int WHICH_SW = -1;
  else if ( SW1) WHICH_SW = 0;
  else if ( SW2) WHICH_SW = 1;
  else if ( SW3) WHICH_SW = 2;
  else if ( SW4) WHICH_SW = 3;
  else if ( SW5) WHICH_SW = 4;
  else if ( SW6) WHICH_SW = 5;
  else if ( SW7) WHICH_SW = 6;
  else if ( SW8) WHICH_SW = 7;

  return WHICH_CH;
}