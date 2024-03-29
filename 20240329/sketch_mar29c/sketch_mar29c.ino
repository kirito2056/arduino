const int led = 13;
int ledState = LOW;
unsigned long previousMillis = 0;
unsigned long interval = 1000;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
      
  }
}