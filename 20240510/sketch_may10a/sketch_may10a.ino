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
  previousMillis = millis();

  while(1) {
  currentMillis = millis();

    if ( previousMillis + interval == currentMillis ) {
      digitalWrite(led, ledState);
      previousMillis = currentMillis;
      
      if ( ledState == LOW) ledState = HIGH;
      else ledState = LOW;
    }
  }

  digitalWrite(led, ledState);
}