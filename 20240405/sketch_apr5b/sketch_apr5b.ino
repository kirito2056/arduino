#include <LedControl.h>
LedControl lc = LedControl(5, 3, 2, 4);
byte thankyou[4][8] = {
  { 0X40, 0x4C, 0x72, 0x52, 0x72, 0x4C, 0X40, 0x00},
  { 0x24, 0x2A, 0xEA, 0x2A, 0x04, 0x20, 0x20, 0xFF},
};

byte you[2][8] = {
  { 0x4, 0x42, 0x84, 0x72, 0x00, 0x84, 0x22, 0x00},
  { 0x00, 0x38, 0x44, 0x44, 0x38, 0x28, 0xfe, 0x00}
}

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  lc.shutdown(2, false);
  lc.shutdown(3, false);
  lc.setIntensity(0, 3);
  lc.setIntensity(1, 3);
  lc.setIntensity(2, 3);
  lc.setIntensity(2, 3);
  lc.clearDisplay(0);
  lc.clearDisplay(0);
  lc.clearDisplay(0);
  lc.clearDisplay(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for ( int i = 0 ; i < 4 ; i++) {
    display_dot(thankyou[i], 3-i);
  }
}

void display_dot(byte *bt, int num) {
  for ( int  i = 0 ; i < 8 ; i++) {
    lc.setRow(num, i, *(bt+i));
  }
}
