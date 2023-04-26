#include "TASK_MANAGER.h"
#include "WHITE_BOARD.h"

bool FLAG_TASK_USER_ENABLE = false;


extern	int DEMO_DATA[];
extern	bool TASK_BEEP_ENABLE;
extern	bool TASK_LED_ENABLE;

extern	int	MAX_BEEP_COUNT;
extern	int	MAX_LED_COUNT;
extern	int	DEMO_COUNT;

extern void LCD_PRINT(int LOC, char *MSG);


extern bool FLAG_TASK_DEMO_ENABLE;
extern int  DEMO_INDEX;
extern bool FLAG_ON;

int  USER_INDEX = 0;

int  CONFIRM_USER_SW_MAX = 3; 
int  CONFIRM_USER_SW_COUNT = 0; 
bool USER_SW_REQUIRE = false;
int  USER_SW_VALUE = -1;
bool FLAG_READ_PUSH = true;
bool FLAG_SW_OK = false;


TASK_ARGS ARGS_TASK_USER;
void TASK_USER(TASK_ARGS *args) {
  int WRONG_COUNT = 0;
	if (!FLAG_TASK_USER_ENABLE) return;
	if (!FLAG_SW_OK) return;
		
	if (DEMO_DATA[USER_INDEX] == USER_SW_VALUE) {
    LCD_PRINT(0, "USER MODE      " + USER_SW_VALUE);
    sprintf(STR_LINE, "SCORE : %08d", SCORE);
    LCD_PRINT(1, STR_LINE);
		USER_INDEX += 1;
		MAX_LED_COUNT = 1;
		TASK_LED_ENABLE = true;
		if (USER_INDEX >= DEMO_COUNT) {
			MAX_LED_COUNT = 2;
			TASK_LED_ENABLE = true;
			FLAG_TASK_USER_ENABLE = false;
			USER_SW_REQUIRE = false;
		} else {
			USER_SW_REQUIRE = true;
		}
    SCORE++;
	} else {
    WRONG_COUNT++;
		MAX_LED_COUNT = 5;
		TASK_LED_ENABLE = true;
		USER_INDEX = 0;
		USER_SW_REQUIRE = true;
	}

    LCD_PRINT(0, "1ST SW TO NEXT  ");
    sprintf(STR_LINE, "SCORE : %08d", SCORE);
    LCD_PRINT(1, STR_LINE);

  if ( WRONG_COUNT == 3) {
    TASK_MANAGER::RESTART(); 
  }

	FLAG_SW_OK		= false;
}

TASK_ARGS ARGS_TASK_SW_USER;
void TASK_SW_USER(TASK_ARGS *args) {
	if (!USER_SW_REQUIRE) return;

	int TEMP_CURR_SW	= -1;
	if (SW0) {
		TEMP_CURR_SW = 1;
	} else if(SW1) {
		TEMP_CURR_SW = 2;
	} else if(SW2) {
		TEMP_CURR_SW = 3;
	} else if(SW3) {
		TEMP_CURR_SW = 4;
	} else if(SW4) {
		TEMP_CURR_SW = 5;
	} else if(SW5) {
		TEMP_CURR_SW = 6;
	} else if(SW6) {
		TEMP_CURR_SW = 7;
	} else if(SW7) {
		TEMP_CURR_SW = 8;
	}
	if (FLAG_READ_PUSH) {
		if (TEMP_CURR_SW > 0) {
			if (CONFIRM_USER_SW_COUNT < CONFIRM_USER_SW_MAX) {
				if (USER_SW_VALUE != TEMP_CURR_SW) {
					USER_SW_VALUE = TEMP_CURR_SW;
					CONFIRM_USER_SW_COUNT = 0;
				} else {
					CONFIRM_USER_SW_COUNT += 1;
				}
			} else {
				FLAG_READ_PUSH = false;
			}
		}
	} else {
		if (TEMP_CURR_SW < 0) {
			USER_SW_REQUIRE = false;
			FLAG_SW_OK		= true;
			CONFIRM_USER_SW_COUNT = 0;
			FLAG_READ_PUSH  = true;
		}
	}
	
}


// ������ �����
