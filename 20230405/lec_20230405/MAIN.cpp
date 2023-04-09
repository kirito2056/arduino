#include <avr/io.h>
#include <util/delay.h>
#include "TASK_MANAGER.h"
#include "WHITE_BOARD.h"

extern TASK_ARGS ARGS_TASK_DEMO;
extern void TASK_DEMO(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_BEEP;
extern void TASK_BEEP(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_SW_0;
extern void TASK_SW_0(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_SW_1;
extern void TASK_SW_1(TASK_ARGS *args);

void setup() {
  randomSeed(analogRead(0));
  DDRE = 0XFF; // PORTE 출력으로 설정 FOR  8 LED
  DDRC = 0X00; // PORTC 입력으로 설정 FOR SW INPUT
  DDRB = 0XFF; // PORTB 출력으로 설정 FOR FND
  DDRD = 0XFF; // PORTD 출력으로 설정 FOR BUZZ
  TASK_MANAGER::SETUP();  // TASK_MANAGER 초기화
  TASK_MANAGER::NEW_TASK(TASK_SW_0,   &ARGS_TASK_SW_0, 100, 100);
  TASK_MANAGER::NEW_TASK(TASK_SW_1,   &ARGS_TASK_SW_1, 100, 100);
  TASK_MANAGER::NEW_TASK(TASK_DEMO, &ARGS_TASK_DEMO, 100, 500);
  TASK_MANAGER::NEW_TASK(TASK_BEEP, &ARGS_TASK_BEEP, 100, 200);
}

void loop() {
  TASK_MANAGER::LOOP();
}