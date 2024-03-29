#define PIEZOPIN 10
int numTones = 8;
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};

void setup() {
  // put your setup code here, to run once:
  pinMode(PIEZOPIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for ( int i = 0 ; i < numTones ; i++) {
    tone(PIEZOPIN, tones[i]);
    delay(500);
  }
  noTone(PIEZOPIN);
}
