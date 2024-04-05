int rows[8] = {10, A1, 9, 13, 2, 8, 3, 6};
int cols[8] = {A0, 4, 5, 11, 7, 12, A2, A3};


void setup() {
  // put your setup code here, to run once:
  for( int i = 0 ; i < 8 ; i++) {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
