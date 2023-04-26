#define SW0 !(PINC&0X01)
#define SW1 !(PINC&0X02)
#define SW2 !(PINC&0X04)
#define SW3 !(PINC&0X08)
#define SW4 !(PINC&0X10)
#define SW5 !(PINC&0X20)
#define SW6 !(PINC&0X40)
#define SW7 !(PINC&0X80)

#define LED0_ON  (PORTE|=0X01)
#define LED0_OFF (PORTE&=~0X01)

#define LED1_ON  (PORTE|=0X02)
#define LED1_OFF (PORTE&=~0X02)

#define LED2_ON  (PORTE|=0X04)
#define LED2_OFF (PORTE&=~0X04)

#define LED3_ON  (PORTE|=0X08)
#define LED3_OFF (PORTE&=~0X08)

#define LED4_ON  (PORTE|=0X10)
#define LED4_OFF (PORTE&=~0X10)

#define LED5_ON  (PORTE|=0X20)
#define LED5_OFF (PORTE&=~0X20)

#define LED6_ON  (PORTE|=0X40)
#define LED6_OFF (PORTE&=~0X40)

#define LED7_ON  (PORTE|=0X80)
#define LED7_OFF (PORTE&=~0X80)

#define LED_ALL_ON  (PORTE|=0XFF)
#define LED_ALL_OFF (PORTE&=~0XFF)


// 수행평가 제출용
