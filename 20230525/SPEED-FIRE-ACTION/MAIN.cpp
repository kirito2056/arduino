#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TASK_MANAGER.h"

extern void LED_ALL_ON();
extern void LED_ALL_OFF();
extern void LED_ON(int INDEX);
extern void LED_OFF(int INDEX);

extern char STR_LINE_0[];
extern char STR_LINE_1[];
extern void Tlcd_init();
extern void LCD_PRINT(int LOC, char *MSG);
	
unsigned long TIME_1ST_SENSOR = 0;
unsigned long TIME_2ND_SENSOR = 0;
bool FLAG_1ST_SENSOR = false;
bool FLAG_2ND_SENSOR = false;

extern bool PRINT_READY_0;
extern bool PRINT_READY_1;

void DISP_DURATION() {
    if (FLAG_1ST_SENSOR && FLAG_2ND_SENSOR) {
		char L_STR[16];
		float D_VAL_1ST = TIME_1ST_SENSOR;
		float D_VAL_2ND = TIME_2ND_SENSOR;
		float D_VAL = fabs(D_VAL_2ND - D_VAL_1ST);
		dtostrf(D_VAL / 1000000.0, 12, 6, L_STR);
	    sprintf(STR_LINE_1, "DUR:%s", L_STR);
	    PRINT_READY_1 = true;
    }
}

extern bool TASK_FIRE_ACTION_ENABLE;

bool FIRE_INTERRUPT =false;
ISR(INT4_vect) {
  if (FIRE_INTERRUPT) return;
  FIRE_INTERRUPT = true;
  TASK_FIRE_ACTION_ENABLE = true;
}

// 외부인터럽스5 (INT5레지스터) 서비스 루틴
ISR(INT5_vect) {
	if (FLAG_1ST_SENSOR && FLAG_2ND_SENSOR) {
		FLAG_1ST_SENSOR = false;
		FLAG_2ND_SENSOR = false;
		TIME_1ST_SENSOR = 0;
		TIME_2ND_SENSOR = 0;
		LED_ALL_OFF();

    	sprintf(STR_LINE_0, "Measure READY!  ");
	    PRINT_READY_0 = true;
    	sprintf(STR_LINE_1, "                ");
	    PRINT_READY_1 = true;
	}
}

// 외부인터럽스6 (INT6레지스터) 서비스 루틴
ISR(INT6_vect) {
	if (FLAG_2ND_SENSOR) return;
//	TIME_2ND_SENSOR = millis();
	TIME_2ND_SENSOR = micros();
	FLAG_2ND_SENSOR = true;
	LED_ON(3);

	char L_STR[16];
	float D_VAL = TIME_2ND_SENSOR;
	dtostrf(D_VAL / 1000000.0, 12, 6, L_STR);
    sprintf(STR_LINE_0, "2ND:%s", L_STR);
    PRINT_READY_0 = true;
    
    DISP_DURATION();
}

// 외부인터럽스7 (INT7레지스터) 서비스 루틴
ISR(INT7_vect){
	if (FLAG_1ST_SENSOR) return;
//	TIME_1ST_SENSOR = millis();
	TIME_1ST_SENSOR = micros();
	FLAG_1ST_SENSOR = true;
	LED_ON(2);

	char L_STR[16];
	float D_VAL = TIME_1ST_SENSOR;
	dtostrf(D_VAL / 1000000.0, 12, 6, L_STR);
    sprintf(STR_LINE_0, "1ST:%s", L_STR);
    PRINT_READY_0 = true;

    DISP_DURATION();
}

void INTERRUPT_SETUP() {
	// 0b00011111 으로 PE7, PE6, PE5 을 입력세팅,  나머지 PE0 ~ PE4 출력 세팅
	DDRE = 0b00011111;
	// PE7, PE6, PE5을 Pull-up으로 하기위해 AND마스크 (DDRn을 입력설정 후 PORTn을 Set하면 내부 Pullup 사용)
	PORTE &= 0b11100000;
	// 사용할 외부인터럽트 bit를 Set해줌. INT5, INT6, INT7 사용하므로 0b11100000 으로 세팅
	EIMSK = 0b11100000; // INT7, 6, 5 Interrupt Enable
	// 인터럽트 동작 방식 설정
	EICRA = 0b00000000;
	EICRB = 0b10101000; // INT7, 6, 5 Falling Edge에 동작
	// 인터럽트 발생시 필요, 7번 bit를 Set해주어야 함
	SREG |= 0b10000000; // Global Interrupt Enable
}

extern TASK_ARGS ARGS_TASK_FIRE_ACTION;
extern void TASK_FIRE_ACTION(TASK_ARGS *args);

extern TASK_ARGS ARGS_TASK_LCD;
extern void TASK_LCD(TASK_ARGS *args);

void setup() {

	DDRB = 0XFF;  // PORTB 출력으로 설정 -> LED 회로 연결

	DDRA = 0XFF;  // PORTA 출력으로 설정 -> LCD 회로 연결
	Tlcd_init();  //--  Text형LCD 초기화

  TASK_MANAGER::SETUP();  // TASK_MANAGER 초기화
  TASK_MANAGER::NEW_TASK(TASK_FIRE_ACTION, &ARGS_TASK_FIRE_ACTION, 100, 200);
  TASK_MANAGER::NEW_TASK(TASK_LCD, &ARGS_TASK_LCD, 100, 10);

  INTERRUPT_SETUP();

	LED_ALL_OFF();

  sprintf(STR_LINE_0, "Measure READY!  ");
  PRINT_READY_0 = true;

}

void loop() {
  TASK_MANAGER::LOOP();
}
