#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void LED_ALL_ON() {
	PORTE = 0b11111111;
}

void LED_ALL_OFF() {
	PORTE = 0b00000000;
}

void LED_ON(int INDEX) {
	int D = 0b00000001 << INDEX;
	PORTE |= D;
}

void LED_OFF(int INDEX) {
	int D = 0b00000001 << INDEX;
	PORTE &= ~D;
}

extern char STR_LINE_0[];
extern char STR_LINE_1[];
extern void Tlcd_init();
extern void LCD_PRINT(int LOC, char *MSG);
	
unsigned long TIME_1ST_SENSOR = 0;
unsigned long TIME_2ND_SENSOR = 0;
bool FLAG_1ST_SENSOR = false;
bool FLAG_2ND_SENSOR = false;

bool PRINT_READY_0 = false;
bool PRINT_READY_1 = false;

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

void setup() {

/*
	// Open serial communications and wait for port to open:
	Serial.begin(115200);
	while (!Serial); // wait for serial port to connect. Needed for native USB port only
	Serial.println("Speed Test Example");
//*/

	DDRA = 0XFF;  // PORTA 출력으로 설정 -> LCD 회로 연결
	Tlcd_init();  //--  Text형LCD 초기화


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

	LED_ALL_OFF();

  sprintf(STR_LINE_0, "Measure READY!  ");
  PRINT_READY_0 = true;

}

void loop() {
	if (PRINT_READY_0) {
		LCD_PRINT(0, STR_LINE_0);
		PRINT_READY_0 = false;
	}
	if (PRINT_READY_1) {
		LCD_PRINT(1, STR_LINE_1);
		PRINT_READY_1 = false;
	}
}
