#define AN_PIN A2
#define LED A3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(AN_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //  Serial.println("value : " + value);

  int value = analogRead(AN_PIN);
  int val = map(value, 0, 1023, 0, 255);
  analogWrite(LED, val);

}
