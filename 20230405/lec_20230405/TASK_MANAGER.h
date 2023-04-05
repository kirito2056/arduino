/*
  TASK_MANAGER.h
*/

#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include "Arduino.h"

#define TASK_MAX_COUNT	16

typedef struct _TASK_ARGS {
	int TASK_INDEX;
	void * AUX_ARGS;
} TASK_ARGS;

typedef struct _TASK_INFO {
	void (*TASK_FUNC)(TASK_ARGS *ARGS);
	TASK_ARGS *ARGS;
	bool FLAG_ENABLE;
	int  TIME_LOOP;
	int  TIME_OUT;
	unsigned long TASK_EXEC_TIME;
} TASK_INFO;

class TASK_MANAGER
{
public:
	static TASK_INFO TASK_INFO_TABLE[];
    TASK_MANAGER();
	static void SETUP();
	static void LOOP();
	static int  NEW_TASK(void (*TASK_FUNC)(TASK_ARGS *ARGS), TASK_ARGS *ARGS, int TIME_OUT, int TIME_LOOP);
	static int  END_TASK(int TASK_INDEX);
	static TASK_INFO* GET_TASK_INFO(int TASK_INDEX);
};
#endif