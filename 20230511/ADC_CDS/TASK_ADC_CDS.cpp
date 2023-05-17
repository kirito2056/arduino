
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>

#include "TASK_MANAGER.h"

#define ADC_VREF_TYPE 0x40

extern void LCD_PRINT(int LOC, char *MSG);
extern char STR_LINE[16];

unsigned int ad_table[] = {  //10bit, 155ea
  982, 979, 977, 974, 971, 968, 965, 962, 959, 956,  // -40'C~-31'C
  952, 948, 944, 940, 936, 932, 927, 923, 918, 913,  // -30'C~-21'C
  907, 902, 896, 891, 885, 878, 872, 866, 859, 852,  // -20'C~-11'C
  845, 837, 830, 822, 814, 806, 798, 790, 781, 772,  // -10'C~ -1'C

  763, 754, 745, 736, 726, 717, 707, 697, 687, 677,  // 0'C~  9'C
  667, 657, 647, 636, 626, 616, 605, 595, 584, 574,  // 10'C~ 19'C
  563, 553, 542, 532, 521, 511, 501, 490, 480, 470,  // 20'C~ 29'C
  460, 450, 441, 431, 421, 412, 403, 393, 384, 375,  // 30'C~ 39'C

  366, 358, 349, 341, 333, 324, 316, 309, 301, 294,  // 40'C~ 49'C
  286, 279, 272, 265, 258, 252, 245, 239, 233, 227,  // 50'C~ 59'C
  221, 215, 209, 204, 199, 193, 188, 183, 179, 174,  // 60'C~ 69'C
  169, 165, 161, 156, 152, 148, 144, 140, 137, 133,  // 70'C~ 79'C

  130, 126, 123, 120, 117, 114, 111, 108, 105, 102,  // 80'C~ 89'C
  100,  97,  94,  92,  90,  87,  85,  83,  81,  79,  // 90'C~ 99'C
   77,  75,  73,  71,  69,  68,  66,  64,  63,  61,  // 100'C~109'C
   60,  58,  57,  55,  54,  53,  51,  50,  49,  48,  // 110'C~119'C
   47,  45,  44,  43,  42,  41
}; // 120'C ~125'C


void ADC_CDS_SETUP() {
  DDRF = 0x00;  // PORTF 입력으로 설정
  // ADC initialization
  // ADC Clock frequency: 1000.000 kHz
  // ADC Voltage Reference: AVCC pin
  ADMUX = ADC_VREF_TYPE & 0xff;
  ADCSRA = 0x84;
}

unsigned int READ_ADC(unsigned char adc_input) { // Read the AD conversion result
	unsigned int data,data2 = 0;
	ADMUX = adc_input | (ADC_VREF_TYPE & 0xff); // Delay needed for the stabilization of the ADC input voltage
	_delay_us(10);// Start the AD conversion
	ADCSRA |= 0x40; // Wait for the AD conversion to complete
	while ((ADCSRA & 0x10) == 0);
	ADCSRA |= 0x10;
	data = ADCL;
	data2 = ADCH;
	data2 = data2 << 8;
	data |=data2;
	return data;
}

unsigned int TemperatureCheck(int data) {	//온도 체크 함수

  char i, tmp = 0;
  int temp = 0;
  if (data > 763) { //-40도 이상일때
    tmp = 0;
    for (i = 0; i < 40; ++i) {
      if (data >= ad_table[tmp]) goto end_run;  //adc 데이터를 비교 0도 이상이면 goto문 실행
      ++tmp;                                    //adc 데이터를 비교 0도 이하이면 배열증가
    }
    goto end_run;
  }

  if (data > 366) { //0도 이상일때
    tmp = 40;
    for (i = 0; i < 40; ++i) {
      if (data >= ad_table[tmp]) goto end_run;  //adc 데이터를 비교 40도 이상이면 goto문 실행
      ++tmp;                                    //adc 데이터를 비교 40도 이하이면 배열증가
    }
    goto end_run;
  }
  
  if (data > 130) { //40도 이상일때
    tmp = 80;
    for (i = 0; i < 40; ++i) {
      if (data >= ad_table[tmp]) goto end_run;  //adc 데이터를 비교 80도 이상이면 goto문 실행
      ++tmp;                                    //adc 데이터를 비교 80도 이하이면 배열증가
    }
    goto end_run;
  } else {
    tmp = 120;    //80도 이상일때
    for (i = 0; i < 45; ++i) {
      if (data >= ad_table[tmp]) goto end_run;  //adc 데이터를 비교 120도 이상이면 goto문 실행
      ++tmp;                                    //adc 데이터를 비교 120도 이하이면 배열증가
    }
  }

end_run:
  if (tmp < 25) {
    temp = 25 - tmp;
  } else {
    temp = tmp - 25;
  }
  return temp;
}


TASK_ARGS ARGS_TASK_ADC;
void TASK_ADC(TASK_ARGS *args) {
	int temperature = TemperatureCheck(READ_ADC(2));
	int volume = READ_ADC(0);
	sprintf(STR_LINE, "Temp:%3d,VOL:%3d", temperature, volume);
	LCD_PRINT(0, STR_LINE);
}

TASK_ARGS ARGS_TASK_CDS;
void TASK_CDS(TASK_ARGS *args) {
	int CDS_VALUE = READ_ADC(1);
	sprintf(STR_LINE, "CDS_VALUE : %6d", CDS_VALUE);
	LCD_PRINT(1, STR_LINE);
}

