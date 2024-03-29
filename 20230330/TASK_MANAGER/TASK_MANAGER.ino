#include <avr/io.h>
#include <util/delay.h>
#include "TASK_MANAGER.h"

#define LED0_ON (PORTE|=0X01)
#define LED0_OFF (PORTE&=~0X01)

#define LED1_ON (PORTE|=0X02)
#define LED1_OFF (PORTE&=~0X02)

#define LED2_ON (PORTE|=0X04)
#define LED2_OFF (PORTE&=~0X04)

#define LED3_ON (PORTE|=0X08)
#define LED3_OFF (PORTE&=~0X08)

#define LED4_ON (PORTE|=0X10)
#define LED4_OFF (PORTE&=~0X10)

#define LED5_ON (PORTE|=0X20)
#define LED5_OFF (PORTE&=~0X20)

#define LED6_ON (PORTE|=0X40)
#define LED6_OFF (PORTE&=~0X40)

#define LED7_ON (PORTE|=0X80)
#define LED7_OFF (PORTE&=~0X80)

/*
	void TASK_XYZ(TASK_ARGS *args) {
    // NO NORE REPEAT
    TASK_MANAGER::END_TASK(args->TASK_INDEX); 

    // FOR CHANGE CYCLE TIME
    TASK_INFO* P_TASK_INFO = TASK_MANAGER::GET_TASK_INFO(args->TASK_INDEX);
    P_TASK_INFO->TIME_LOOP = TLV_CYCLE_TIME;
	}
//*/

TASK_ARGS ARGS_TASK_LED0;
uint16_t TASK_LED0_CYCLE_TIME = 1 * 1000; // 1 Seconds

bool TASK_LED0_STATUS = true;
void TASK_LED0(TASK_ARGS *args) {
  if (TASK_LED0_STATUS) {
    LED0_ON;
  } else {
    LED0_OFF;
  }
  TASK_LED0_STATUS = !TASK_LED0_STATUS;
}

TASK_ARGS ARGS_TASK_LED1;
uint16_t TASK_LED1_CYCLE_TIME = 1.7 * 1000; // 1.5 Seconds

bool TASK_LED1_STATUS = true;
void TASK_LED1(TASK_ARGS *args) {
  if (TASK_LED1_STATUS) {
    LED1_ON;
  } else {
    LED1_OFF;
  }
  TASK_LED1_STATUS = !TASK_LED1_STATUS;
}

TASK_ARGS ARGS_TASK_LED2;
uint16_t TASK_LED2_CYCLE_TIME = 2.1 * 1000;

bool TASK_LED2_STATUS = true;
void TASK_LED2(TASK_ARGS *args) {
  if (TASK_LED2_STATUS) {
    LED2_ON;
  } else {
    LED2_OFF;
  }
  TASK_LED2_STATUS = !TASK_LED2_STATUS;
}

TASK_ARGS ARGS_TASK_LED3;
uint16_t TASK_LED3_CYCLE_TIME = 2.4 * 1000;

bool TASK_LED3_STATUS = true;
void TASK_LED3(TASK_ARGS *args) {
  if (TASK_LED3_STATUS) {
    LED3_ON;
  } else {
    LED3_OFF;
  }
  TASK_LED3_STATUS = !TASK_LED3_STATUS;
}

TASK_ARGS ARGS_TASK_LED4;
uint16_t TASK_LED4_CYCLE_TIME = 2.7 * 1000;

bool TASK_LED4_STATUS = true;
void TASK_LED4(TASK_ARGS *args) {
  if (TASK_LED4_STATUS) {
    LED4_ON;
  } else {  
    LED4_OFF;
  }
  TASK_LED4_STATUS = !TASK_LED4_STATUS;
}

TASK_ARGS ARGS_TASK_LED5;
uint16_t TASK_LED5_CYCLE_TIME = 2.9 * 1000;

bool TASK_LED5_STATUS = true;
void TASK_LED5(TASK_ARGS *args) {
  if (TASK_LED5_STATUS) {
    LED5_ON;
  } else {
    LED5_OFF;
  }
  TASK_LED5_STATUS = !TASK_LED5_STATUS;
}

TASK_ARGS ARGS_TASK_LED6;
uint16_t TASK_LED6_CYCLE_TIME = 2.1 * 1000;

bool TASK_LED6_STATUS = true;
void TASK_LED6(TASK_ARGS *args) {
  if (TASK_LED6_STATUS) {
    LED6_ON;
  } else {
    LED6_OFF;
  }
  TASK_LED6_STATUS = !TASK_LED6_STATUS;
}

TASK_ARGS ARGS_TASK_LED7;
uint16_t TASK_LED7_CYCLE_TIME = 1.9 * 1000;

bool TASK_LED7_STATUS = true;
void TASK_LED7(TASK_ARGS *args) {
  if (TASK_LED7_STATUS) {
    LED7_ON;
  } else {
    LED7_OFF;
  }
  TASK_LED7_STATUS = !TASK_LED7_STATUS;
}


void setup() {
  DDRE = 0XFF; // PORTE 출력으로 설정
  DDRC = 0X00; // PORTC 입력으로 설정
  TASK_MANAGER::SETUP();  // TASK_MANAGER 초기화
  TASK_MANAGER::NEW_TASK(TASK_LED0, &ARGS_TASK_LED0, 100, TASK_LED0_CYCLE_TIME);
  TASK_MANAGER::NEW_TASK(TASK_LED1, &ARGS_TASK_LED1, 100, TASK_LED1_CYCLE_TIME);
  TASK_MANAGER::NEW_TASK(TASK_LED2, &ARGS_TASK_LED2, 100, TASK_LED2_CYCLE_TIME);
  TASK_MANAGER::NEW_TASK(TASK_LED3, &ARGS_TASK_LED3, 100, TASK_LED3_CYCLE_TIME);
  TASK_MANAGER::NEW_TASK(TASK_LED4, &ARGS_TASK_LED4, 100, TASK_LED4_CYCLE_TIME);
  TASK_MANAGER::NEW_TASK(TASK_LED5, &ARGS_TASK_LED5, 100, TASK_LED5_CYCLE_TIME);
  TASK_MANAGER::NEW_TASK(TASK_LED6, &ARGS_TASK_LED6, 100, TASK_LED6_CYCLE_TIME);
  TASK_MANAGER::NEW_TASK(TASK_LED7, &ARGS_TASK_LED7, 100, TASK_LED7_CYCLE_TIME);
}

void loop() {
  TASK_MANAGER::LOOP();
}
