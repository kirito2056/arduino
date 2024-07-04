int leds[] = {2, 3, 4, 5, 10, 11, 12, 13};
int led_num = 8;
int num = 0;

int set_number[10][8] = {
  {0, 0, 0, 0, 0, 0, 1, 1},
  {1, 0, 0, 1, 1, 1, 1, 1},
  {0, 0, 1, 0, 0, 1, 0, 1},
  {0, 0, 0, 0, 1, 1, 0, 1},
  {1, 0, 0, 1, 1, 0, 0, 1},
  {0, 1, 0, 0, 1, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1, 0, 0, 1}
};

void setup() {
  for ( int i = 0 ; i < led_num ; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  if ( num == 9) num = 0;
  else num++;

  for ( int i = 0 ; i < led_num ; i++) {
    digitalWrite(leds[set_number[num][i]], HIGH);
  }

  delay(150);

  for ( int i = 0 ; i < led_num ; i++) {
    digitalWrite(leds[i], LOW);
  }  
}