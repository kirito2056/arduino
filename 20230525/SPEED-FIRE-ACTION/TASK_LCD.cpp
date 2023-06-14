#include "TASK_MANAGER.h"

char STR_LINE_0[32];
char STR_LINE_1[32];

bool PRINT_READY_0 = false;
bool PRINT_READY_1 = false;

extern void LCD_PRINT(int LOC, char *MSG);

TASK_ARGS ARGS_TASK_LCD;
void TASK_LCD(TASK_ARGS *args) {
	if (PRINT_READY_0) {
		LCD_PRINT(0, STR_LINE_0);
		PRINT_READY_0 = false;
	}
	if (PRINT_READY_1) {
		LCD_PRINT(1, STR_LINE_1);
		PRINT_READY_1 = false;
	}
}
