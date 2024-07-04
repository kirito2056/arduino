#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SoftWire.h>

// 소프트웨어 I2C 설정 (SDA = 10, SCL = 11)
SoftWire myWire(10, 11);
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD의 주소 설정

// 키패드의 행과 열의 수를 정의합니다.
const byte ROWS = 4; 
const byte COLS = 4; 

// 키패드의 키 배열을 정의합니다.
char keys[ROWS][COLS] = {
  {'1','2','3','C'}, // 'A'를 'C'로 변경
  {'4','5','6','B'},
  {'7','8','9','D'}, // 'C'를 'D'로 변경
  {'A','0','#','O'}  // '*'를 'A'로 변경
};

// 행과 열에 대한 핀 배열을 정의합니다.
byte rowPins[ROWS] = { 5, 4, 3, 2 };
byte colPins[COLS] = {6, 7, 8, 9};

// 키패드를 초기화합니다.
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input = "";  // 현재 입력 중인 숫자
String saved = "";  // 저장된 숫자
String deleteSequence = ""; // # 입력 횟수를 저장

void setup() {
  Serial.begin(9600); // 시리얼 통신을 시작합니다.
  myWire.begin(); // 소프트웨어 I2C 초기화
  lcd.begin();    // LCD 초기화
  lcd.backlight(); // 백라이트 켜기
  lcd.print("Enter: "); // 초기 메시지를 LCD에 출력합니다.
}

void loop() {
  char key = keypad.getKey(); // 키패드에서 키 입력을 받습니다.

  if (key) { // 키가 눌렸다면
    if (key >= '0' && key <= '9') {
      input += key; // 숫자를 입력 중인 문자열에 추가합니다.
      lcd.print(key); // LCD에 출력합니다.
    } else if (key == 'C') {
      input = ""; // 입력 중인 숫자를 전체 삭제합니다.
      lcd.clear();
      lcd.print("Enter: ");
    } else if (key == 'B') {
      if (input.length() > 0) {
        input.remove(input.length() - 1); // 입력 중인 숫자에서 뒤에서 한 글자 삭제합니다.
        lcd.clear();
        lcd.print("Enter: ");
        lcd.print(input); // 남은 입력을 LCD에 다시 출력합니다.
      }
    } else if (key == 'O') {
      saved = input; // 입력된 숫자를 저장합니다.
      input = ""; // 입력 중인 숫자를 초기화합니다.
      lcd.clear();
      lcd.print("Saved: ");
      lcd.print(saved); // 저장된 숫자를 LCD에 출력합니다.
    } else if (key == 'D') {
      if (deleteSequence == "#######") {
        saved = ""; // 저장된 숫자를 전체 삭제합니다.
        lcd.clear();
        lcd.print("Deleted");
      }
      deleteSequence = ""; // 조건 충족 후 시퀀스 초기화
    } else if (key == '#') {
      deleteSequence += key; // # 입력 시 deleteSequence에 추가
      if (deleteSequence.length() > 7) {
        deleteSequence = ""; // 7번 이상 누르면 시퀀스를 초기화
      }
    } else if (key == 'A') {
      lcd.clear();
      lcd.print("Saved: ");
      lcd.print(saved); // 저장된 숫자를 LCD에 출력합니다.
    }
    Serial.println(key); // 키 값을 시리얼 모니터에 출력합니다.
  }
}
