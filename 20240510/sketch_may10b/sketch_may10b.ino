#define ADPIN A3
#define LEDPIN 6

int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ADPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  analogWrite(LEDPIN, 0);
}

void loop() {
  val = analogRead(ADPIN);
  int duty_cycle = val/4;
  analogWrite(LEDPIN, duty_cycle);
  }