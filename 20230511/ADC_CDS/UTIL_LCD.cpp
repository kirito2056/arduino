/********************************************************************************
  Product : LKino-MEGA128
  Project : 텍스트형 LCD 기본 동작 테스트
  Date    : 2017-01-19
  Author  : Kyung Nam Lee
  Company : LKEMBEDDED ( http://www.lkembedded.co.kr )
  Comments: 텍스트형LCD모듈에 아래와 같은 문자가 출력 된다.
  "LK EMBEDDED"
  "==TLCD TEST==="

  Pin map
  AVR    Arduino   Device
  PA0   D44     RS
  PA1   D43     RW
  PA2   D42     E
  PA3   D41
  PA4   D40     DB4
  PA5   D39     DB5
  PA6   D38     DB6
  PA7   D37     DB7
********************************************************************************/
#define F_CPU 16000000UL
#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

#define RS 0X01
#define EN 0X04

char STR_LINE[16];

/* 코드 테스트 74hc574 Q핀으로 출력 값이 저장되고 있음을 프로그램머는 인지하여야 한다.*/
char Number[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

unsigned char TlcdCon = 0;  // TLCD control 변수이다. PORTD 레지스터를 공용으로 사용해야 하므로 컨트롤 신호의 상태를 저장하는 임시버퍼로 활용 된다.
volatile unsigned int toggle_cnt = 0;
void instruction_out(unsigned char b)  // 명령어 쓰기 함수
{
  delay(1);
  PORTA &= ~RS;  // RS = 0
  PORTA = (b & 0xf0);  // 상위 4bit 출력
  PORTA |= EN;  // EN = 1
  PORTA &= ~EN;  // EN = 0

  PORTA = ((b << 4) & 0xf0);  //하위 4bit 출력
  PORTA |= EN;  // EN = 1
  PORTA &= ~EN;  // EN = 0
}
void char_out(unsigned char b)  // LCD에 문자 출력 함수
{
  delay(1);
  PORTA = (b & 0xf0);  // 상위 4비트 출력,RS핀 출력으로 설정
  PORTA |= RS;  // RS = 1
  PORTA |= EN;  // EN = 1
  PORTA &= ~EN;  // EN =0

  PORTA = ((b << 4) & 0xf0);  // 하위 4비트 출력, 4비트 전송모드,RS핀 출력으로 설정
  PORTA |= RS;  // RS = 1
  PORTA |= EN;  // EN = 1
  PORTA &= ~EN;  // EN =0
  /*Busy Flag-----------------------------------------------------------------------------------------
    ▶ LCD모듈 내부 동작중임을 나타내는 busy flag(BF) 및 어드레스 카운터의 내용을 리드한다.
    LCD모듈이 각제어 코드를 실행하는데는 지정된 시간이 필요하므로 CPU는 다음제어 코드를 보내기 전에
    충분히 시간 지연을 주어 대기하는 방법을 수용할수도 있으며, CPU가 이 BF를 읽어서 이것이 1로 표시되어
    있는 경우에는 계속 기다리고 0인 경우에는 다음 제어 코드를 보내는 방법을 사용한다면 보다
    효율적인 처리가 가능하다.
    ---------------------------------------------------------------------------------------------------*/
}
void clcd_line1()
{
  instruction_out(0x80);
} //line1
void clcd_line2()
{
  instruction_out(0XC0);
} //line2
void Tlcd_init()  // TLCD 초기화 함수 16x2line
{
  delay(30);
  instruction_out(0X28);
  delay(5);
  instruction_out(0X28);
  delay(100);
  instruction_out(0x0c);  // Display on, Cursor off, Blank off
  delay(1);
  instruction_out(0x06);  // Display on, Cursor off, Blank off
  delay(1);
  instruction_out(0x01);  // 화면 클리어
  delay(50);
}
void string_out(char *str)  //문자열 출력 함수
{
  unsigned int i = 0;
  do {
    char_out(str[i]);  //-----문자 출력
  }
  while (str[++i] != '\0');
}
void int_display(int i)  // 텍스트 LCD에 정수를 표현 하기 위한 함수
{
  int j, k, l = 0;
  j = (i % 1000) / 100;
  k = (i % 100) / 10;
  l = i % 10 ;
  char_out(Number[j]);  // 100의 자리
  char_out(Number[k]);  // 10의 자리
  char_out('.');  // 1의 자리
  char_out(Number[l]);  // 1의 자리
}

void LCD_PRINT(int LOC, char *MSG) {
	if (LOC == 0) {
		clcd_line1();
		string_out(MSG);
	} else if (LOC == 1) {
		clcd_line2();
		string_out(MSG);	
	}
}
