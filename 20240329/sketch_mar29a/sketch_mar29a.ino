int pushButtonB = 3;

int LEDB = 2;

int count=0;
bool flag=true;
int excount=0;
bool ledState=true;
void setup() {
  Serial.begin(9600);

  // for(int i=2;i<=10;i++){
  //   pinMode(i,OUTPUT);
  // }

  pinMode(pushButtonB,INPUT_PULLUP);

  pinMode(LEDB,OUTPUT);
  
  digitalWrite(LEDB, LOW);

  attachInterrupt(digitalPinToInterrupt(pushButtonB), BUTTON, CHANGE);
}

 if(count==excount){
    Serial.println(count);
    excount++;
  }
  digitalWrite(LEDB,!ledState);

}


void BUTTON() {
  if(digitalRead(pushButtonB)==LOW){
    if(flag){
      flag=false;
      ledState=false;
      count++;
    }
  }else {
    flag=true;
    ledState=true;
  }
}