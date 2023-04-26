#include <avr/io.h>
#include <util/delay.h>

#include "TASK_MANAGER.h"
#include "WHITE_BOARD.h"
extern char STR_LINE[];

extern TASK_ARGS ARGS_TASK_DEMO;
extern void TASK_DEMO(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_SW_0;
extern void TASK_SW_0(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_BEEP;
extern void TASK_BEEP(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_SW_1;
extern void TASK_SW_1(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_LED;
extern void TASK_LED(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_SW_2;
extern void TASK_SW_2(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_USER;
extern void TASK_USER(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_SW_USER;
extern void TASK_SW_USER(TASK_ARGS *args);

extern void Tlcd_init();

extern void LCD_PRINT(int LOC, char *MSG);

int SCORE = 0;
void setup() {
  randomSeed(analogRead(0));
  DDRE = 0XFF; // PORTE 출력으로 설정 FOR  8 LED
  DDRC = 0X00; // PORTC 입력으로 설정 FOR SW INPUT
  DDRB = 0XFF; // PORTB 출력으로 설정 FOR FND
  DDRD = 0X14; // PORTD 출력으로 설정 FOR BUZZZ AND SERIAL -> 0B00011000

  PORTD = 0x10; // 최초 실행시 소리 안나게
  
  DDRA = 0XFF;
  Tlcd_init();  //--  Text형LCD 초기화
  
  TASK_MANAGER::SETUP();  // TASK_MANAGER 초기화

//  TASK_MANAGER::NEW_TASK(TASK_SW_1, &ARGS_TASK_SW_1, 100, 100);
//  TASK_MANAGER::NEW_TASK(TASK_SW_2, &ARGS_TASK_SW_2, 100, 100);

  TASK_MANAGER::NEW_TASK(TASK_SW_0, &ARGS_TASK_SW_0, 100, 100);
  TASK_MANAGER::NEW_TASK(TASK_DEMO, &ARGS_TASK_DEMO, 100, 500);
  TASK_MANAGER::NEW_TASK(TASK_BEEP, &ARGS_TASK_BEEP, 100, 200);
  TASK_MANAGER::NEW_TASK(TASK_LED,  &ARGS_TASK_LED,  100, 200);

  TASK_MANAGER::NEW_TASK(TASK_USER, &ARGS_TASK_USER, 100, 100);
  TASK_MANAGER::NEW_TASK(TASK_SW_USER, &ARGS_TASK_SW_USER, 100, 10);

  LCD_PRINT(0, "1ST SW TO START ");
  sprintf(STR_LINE, "SCORE : %08d", SCORE);
  LCD_PRINT(1, STR_LINE);
  
}

void loop() {
  TASK_MANAGER::LOOP();
}


// 수행평가 제출용
