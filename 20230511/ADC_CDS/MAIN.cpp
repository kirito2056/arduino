#include <avr/io.h>
#include <util/delay.h>

#include "TASK_MANAGER.h"

extern void Tlcd_init();
extern void LCD_PRINT(int LOC, char *MSG);

extern void ADC_CDS_SETUP();

extern TASK_ARGS ARGS_TASK_ADC;
extern void TASK_ADC(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_CDS;
extern void TASK_CDS(TASK_ARGS *args);

#define ADC_VREF_TYPE 0x40

void setup() {

  DDRA = 0XFF;  // PORTA 출력으로 설정 -> LED 회로 연결
  DDRE = 0XFF;  // PORTE 출력으로 설정 -> LCD 회로 연결
  
  ADC_CDS_SETUP();

  Tlcd_init();  //--  Text형LCD 초기화
  TASK_MANAGER::SETUP();  // TASK_MANAGER 초기화
  TASK_MANAGER::NEW_TASK(TASK_ADC, &ARGS_TASK_ADC, 100, 100);
  TASK_MANAGER::NEW_TASK(TASK_CDS, &ARGS_TASK_CDS, 100, 100);
}

void loop() {
  TASK_MANAGER::LOOP();
}


// 수행평가 제출용
