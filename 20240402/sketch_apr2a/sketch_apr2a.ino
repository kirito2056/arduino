int LED = 13;
int pushbutton = 3;
bool toggle = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(pushbutton,INPUT_PULLUP);

  digitalWrite(LED, LOW);
  attachInterrupt(digitalPinToInterrupt(pushbutton), BUTTON, CHANGE);

}

void loop() {
  
}

void BUTTON() {
  if(digitalRead(pushbutton)==LOW){
    if ( toggle == false) {
      digitalWrite(LED, HIGH);
      toggle = true;
    } else {
      digitalWrite(LED, LOW);
      toggle = false;
    }
}
}