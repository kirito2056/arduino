/********************************************************************************
  Product : LKino-MEGA128
  Project : LED, 스위치 기본 동작 테스트
  Date    : 2017-01-19
  Author  : Kyung Nam Lee
  Company : LKEMBEDDED ( http://www.lkembedded.co.kr )
  Comments: 스위치를 누르면 LED가 2개씩 ON/OFF 되는 프로그램

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
  PC0   D28     SW0
  PC1   D29     SW1
  PC2   D30     SW2
  PC3   D31     SW3
********************************************************************************/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SW0 (PINC&0X01)
#define SW1 (PINC&0X02)
#define SW2 (PINC&0X04)
#define SW3 (PINC&0X08)

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

#define LED_ALL_OFF (PORTE&=~0XFF)
void setup()  // 초기화
{
  DDRE = 0XFF; // PORTE 출력으로 설정
  DDRC = 0X00; // PORTC 입력으로 설정
}
void loop()  // 무한루프
{
  if (!SW0)  // 0번 스위치를 누르면
  {
    LED0_ON;  // 0번 LED ON
    LED1_ON;  // 1번 LED ON
  }
  else if (!SW1)  // 1번 스위치를 누르면
  {
    LED2_ON;  // 2번 LED ON
    LED3_ON;  // 3번 LED ON
  }
  else if (!SW2)  //2번 스위치 누르면
  {
    LED4_ON;  // 4번 LED ON
    LED5_ON;  // 5번 LED ON
  }
  else if (!SW3) // 3번 스위치 누르면
  {
    LED6_ON;  // 6번 LED ON
    LED7_ON;  // 7번 LED ON
  }
  else
  {
    LED_ALL_OFF;  // 모든 LED OFF
  }
}
