#include <avr/io.h>
#include <util/delay.h>

const char msg_font[][5] = {
  {
  0b11111111,
  0b00010000,
  0b00010000,
  0b00010000,
  0b11111111,
},
{
  0b11111111,
  0b10010001,
  0b10010001,
  0b10000001,
  0b00000000,
},
{
  0b11111111,
  0b00000001,
  0b00000001,
  0b00000001,
  0b00000000,
},
{
  0b11111111,
  0b00000001,
  0b00000001,
  0b00000001,
  0b00000000,
},
{
  0b00011000,
  0b01100110,
  0b11000011,
  0b01100110,
  0b00011000,
}
};

void setup() {
  // put your setup code here, to run once:
  DDRE = 0XFF; PORTE = 0X00;
}

void loop() {
  // put your main code here, to run repeatedly:
  int DATA = 3;
  for ( int i = 0 ; i < 5 ; i++) {
    for ( int j = 0 ; j < 5 ; j++) {
      PORTE = msg_font[i][j];
      delay(50);
    }
  }
}

