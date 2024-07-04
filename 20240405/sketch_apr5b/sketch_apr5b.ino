#include <LedControl.h>
LedControl lc = LedControl(5, 3, 2, 2);
LedControl rc = LedControl(7, 8, 9, 2);
byte thank[2][8] = {
  { 0X40, 0x4C, 0x72, 0x52, 0x72, 0x4C, 0X40, 0x00},
  { 0x24, 0x2A, 0xEA, 0x2A, 0x04, 0x20, 0x20, 0xFF}
};

byte you[2][8] = {
  { 0x04, 0x42, 0x84, 0x72, 0x00, 0x84, 0x22, 0x00},
  { 0x00, 0x38, 0x44, 0x44, 0x38, 0x28, 0xfe, 0x00}
};

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  rc.shutdown(0, false);
  rc.shutdown(1, false);
  lc.setIntensity(0, 3);
  lc.setIntensity(1, 3);
  rc.setIntensity(0, 3);
  rc.setIntensity(1, 3);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  rc.clearDisplay(0);
  rc.clearDisplay(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  for ( int i = 0 ; i < 2 ; i++) {
    display_dot_lc(thank[i], 1-i);
    display_dot_rc(you[i], 1-i);
  }
}

void display_dot_lc(byte *bt, int num) {
  for ( int  i = 0 ; i < 8 ; i++) {
    lc.setRow(num, i, *(bt+i));
  }
}

void display_dot_rc(byte *bt, int num) {
  for ( int i = 0 ; i < 8 ; i++) {
    rc.setRow(num, i, *(bt+i));
  }
}
