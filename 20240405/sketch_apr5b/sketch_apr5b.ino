#include <LedControl.h>
LedControl lc = LedControl(5, 3, 2, 4);
byte thankyou[4][8] = {
  { 0x00, 0x7e, 0x02, 0x12, 0x12, 0x0e, 0x7e, 0x00},
  { 0x00, 0xf4, 0x94, 0x96, 0x94, 0x74, 0xf4, 0x00},
  { 0x00, 0x72, 0x8a, 0x72, 0x0e, 0xfa, 0x22, 0x22},
  { 0x00, 0x38, 0x44, 0x44, 0x38, 0x28, 0xfe, 0x00}
};

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  lc.shutdown(2, false);
  lc.shutdown(3, false);
  lc.setIntensity(0, 5);
  lc.setIntensity(1, 5);
  lc.setIntensity(2, 5);
  lc.setIntensity(2, 5);
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
