#include <avr/io.h>
#include <util/delay.h>
#include "TASK_MANAGER.h"
#include "WHITE_BOARD.h"

extern TASK_ARGS ARGS_TASK_DEMO;
extern void TASK_DEMO(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_SW;
extern void TASK_SW(TASK_ARGS *args);

void setup() {
  randomSeed(analogRead(0));
  DDRE = 0XFF; // PORTE 출력으로 설정 FOR  8 LED
  DDRC = 0X00; // PORTC 입력으로 설정 FOR SW INPUT
  DDRB = 0XFF; // PORTB 출력으로 설정 FOR FND
  TASK_MANAGER::SETUP();  // TASK_MANAGER 초기화
  TASK_MANAGER::NEW_TASK(TASK_SW,   &ARGS_TASK_SW, 100, 100);
  TASK_MANAGER::NEW_TASK(TASK_DEMO, &ARGS_TASK_DEMO, 100, 500);
}

void loop() {
  TASK_MANAGER::LOOP();
}