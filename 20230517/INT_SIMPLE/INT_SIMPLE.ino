#include <avr/io.h>
#include <avr/interrupt.h>

extern char STR_LINE[];
extern void Tlcd_init();
extern void LCD_PRINT(int LOC, char *MSG);

// 외부인터럽스6 (INT6레지스터) 서비스 루틴
ISR(INT5_vect) {

}


double TIME_END = 0;
bool   FLAG_END = false;
ISR(INT6_vect) {
    if (FLAG_END) return;
    TIME_END = micros() / 1000000.0;
    FLAG_END = true;
}

double TIME_START = 0;
bool   FLAG_START = false;
ISR(INT7_vect) {
    if (FLAG_START) return;
    TIME_START = micros() / 1000000.0;
    FLAG_START = true;
}

void setup() {
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

  Tlcd_init();
}

void loop() {
  if(FLAG_START && FLAG_END) {
    sprintf(STR_LINE, "DIFF: %10.6f", abs(TIME_END - TIME_START));
    LCD_PRINT(0, STR_LINE);
  }

}
