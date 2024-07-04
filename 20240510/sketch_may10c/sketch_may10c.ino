int digitComPin[] = {2, 3, 4, 5};
int segmentPin[] = {6, 7, 8, 9, 10, 11, 12, 13};
int delayTime = 5;
const int potenPin = A0;

byte digitData[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6};

void setup() {
  Serial.begin(9600);
  for ( int i = 0 ; i < 4 ; i++) {
    pinMode(digitComPin[i], OUTPUT);
    digitalWrite(digitComPin[i], LOW);
  }

  for ( int i = 0 ; i < 8 ; i++) {
    pinMode(segmentPin[i], OUTPUT);
  }
}

void showDigit(int pos, int num) {
  for ( int i = 0 ; i < 4 ; i++) {
    if ( i + 1 == pos) digitalWrite(digitComPin[i], LOW);
    else digitalWrite(digitComPin[i], HIGH);
  }

  for ( int i = 0 ; i < 8 ; i++) {
    byte segmentData = num;
    if ( segmentData == 1) digitalWrite(segmentPin[7-i], LOW);
    else digitalWrite(segmentPin[7-i], HIGH);
  }
}

void loop() {
  int res = analogRead(potenPin);

  int num1 = res / 1000;
  int num2 = (res % 1000) / 100;
  int num3 = (res % 100 / 10);
  int num4 = res % 10;

  showDigit(1, num1);
  delay(delayTime);
  showDigit(2, num2);
  delay(delayTime);
  showDigit(3, num3);
  delay(delayTime);
  showDigit(3, num4);
  delay(delayTime);
}