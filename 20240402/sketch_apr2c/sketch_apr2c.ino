int INB = 11;
int INA = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(INB, OUTPUT);
  pinMode(INA, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(INB, HIGH);
  digitalWrite(INA, LOW);
}
