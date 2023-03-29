/********************************************************************************
  Product : LKino-MEGA128
  Project : LED, BUZZER 출력 테스트
  Date    : 2017-01-19
  Author  : Kyung Nam Lee
  Company : LKEMBEDDED ( http://www.lkembedded.co.kr )
  Comments: LED와 부저가 주기적으로 ON/OFF를 반복하는 프로그램

  Pin map
  AVR    Arduino   Device
  PE0   D0      LED0
  PE1   D1      LED1
  PE2   D2      LED2
  PE3   D3      LED3
  PE4   D4      LED4
  PE5   D5      LED5
  PE6   D6      LED6
  PE7   D7      LED7
  PD4   D22     BUZZ
********************************************************************************/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
void setup()  // 초기화
{
  // 모든 포트를 출력으로 설정 및 초기화
  DDRE = 0XFF; PORTE = 0X00;

}
void loop()  // 무한루프
{
  int DATA = 1;

  for ( int i = 0 ; i < 7 ; i++) {
    PORTE = DATA;
    DATA = DATA << 1;
      delay(200);
  }
}
