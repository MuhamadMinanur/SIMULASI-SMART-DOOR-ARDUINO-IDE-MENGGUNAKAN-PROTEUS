#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};

byte rowPins[ROWS] = {3, 2, 19, 18};
byte colPins[COLS] = {17, 16, 15, 14};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const int LED_RED = 10;
const int LED_GREEN = 11;
const int RELAY = 12;
const int BUZZER = 13;

char keycount = 0;
char code[4];

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.begin(20, 4);  // Inisialisasi LCD 20x4
  lcd.print("MASUKAN PIN:");
  lcd.setCursor(0, 1);
  lcd.cursor();

  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  digitalWrite(RELAY, LOW);
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey && (keycount < 4) && (customKey != '=') && (customKey != 'C')) {
    lcd.print('*');
    code[keycount] = customKey;
    keycount++;
  }

  if (customKey == 'C') {
    Lock();
  }

  if (customKey == '=') {
    if ((code[0] == '1') && (code[1] == '2') && (code[2] == '3') && (code[3] == '4')) {
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_RED, HIGH);
      digitalWrite(RELAY, HIGH);
      lcd.clear();  // Menghapus layar LCD
      lcd.setCursor(0, 1);
      lcd.print("PINTU TERBUKA       ");
      lcd.setCursor(0, 2);
      lcd.print("SILAHKAN MASUK!!");
      lcd.setCursor(0, 3);
      lcd.print("TUTUP KEMBALI!!   ");
      delay(4000);
      Lock();
    }
    else {
      lcd.clear();  // Menghapus layar LCD
      lcd.setCursor(0, 1);
      lcd.print("PASSWORD SALAH");
      lcd.setCursor(0, 2);
      lcd.print("HARAP MASUKAN PIN ");
      lcd.setCursor(0, 3);
      lcd.print("YANG BENAR   ");
      digitalWrite(BUZZER, HIGH);
      delay(1500);
      digitalWrite(BUZZER, LOW);
      Lock();
    }
  }
}

void Lock() {
  lcd.clear();  // Menghapus layar LCD
  lcd.setCursor(0, 1);
  lcd.print("PINTU TERTUTIP");
  lcd.setCursor(0, 2);
  lcd.print("KEMBALI");
  lcd.setCursor(0, 3);
  lcd.print("                ");
  delay(1500);
  lcd.clear();  // Menghapus layar LCD
  lcd.setCursor(0, 1);
  lcd.print("MASUKAN PIN");
  lcd.setCursor(0, 2);
  lcd.print("                ");
  lcd.setCursor(0, 3);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  keycount = 0;
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  digitalWrite(RELAY, LOW);
}
