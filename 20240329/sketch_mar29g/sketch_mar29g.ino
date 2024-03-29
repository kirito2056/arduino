#define PIEZOPIN 10
int numTones = 8;
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};

int DO = 261;
int RE = 294;
int ME = 330;
int PA = 349;
int SOL = 392;
int RA = 440;
int CI = 494;
int DDO = 523;

int[] plane = [ME, RE, DO, RE, ME, ME, ME, RE, RE, RE, ME, ME, ME, ME, RE, DO, RE, ME, ME, ME, RE, RE, ME, RE, DO];
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