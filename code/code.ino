// Spesies
// 1 Ea  6 Hp
// 2 Th  7 Ho
// 3 Cs  8 Si
// 4 Cr  9 Tc
// 5 Hu

// Substrat
// 1 Pasir
// 2 Lumpur
// 3 Batu
// 4 Rubble

#include <Keypad.h>
#include <LiquidCrystal.h>
#include "structure.h"

LiquidCrystal lcd(22, 24, 26, 28, 30, 32);

char keys[4][4] =
{
  {'1', '2', '3', 'E'},
  {'4', '5', '6', '^'},
  {'7', '8', '9', 'v'},
  {'<', '0', '>', 'X'}
};

byte rowPins[4] = { 6, 7, 8, 9 };
byte colPins[4] = { 2, 3, 4, 5 };

Keypad kpd = Keypad( makeKeymap(keys), rowPins,
                     colPins, 4, 4 );

String persenTemp;
int digit = 0;
int persen = 0;
int menuIdx = 0;

const int menuA = 2;
int mnA = 2;
unsigned long currentMillis;
unsigned long previousMillis;
const long interval = 500;

#include "menu.h"

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  char key = kpd.getKey();
  if (key) {
    lcd.clear();
    Serial.println(key);
    if (key == '^') { // Naik
      mnA++;
      if (mnA > menuA)mnA = 1;
    }
    else if (key == 'v') { // Turun
      mnA--;
      if (mnA < 1)mnA = menuA;
    }
    else if (key == 'E') {
      switch (mnA) {
        case 1:
          bacaData();
          break;
        case 2:
          tulisData();
          break;
      }
    }
  }

  switch (mnA) {
    case 1:
      tampilLcd(0, 0, "~Baca Data      ");
      tampilLcd(0, 1, " Tulis Data     ");
      break;
    case 2:
      tampilLcd(0, 0, " Baca Data      ");
      tampilLcd(0, 1, "~Tulis Data     ");
      break;
  }

}

void bacaData() {
  while (1) {
    tampilLcd(0, 0, "Ini baca data   ");
    tampilLcd(0, 1, "                ");
    if (x()) {
      break;
    }
  }
}

void tulisData() {
  String menuSB[] = {"Lokasi", "Stasiun", "Pengamat", "Tanggal", "Waktu", "Kedalaman", "Visibility", "Cuaca"};
  int mnB = 0;
  while (1) {
    char key = kpd.getKey();
    if (key) {
      Serial.println(key);
      if (key == 'v') { // Naik
        mnB++;
        if (mnB > 7)mnB = 0;
      }

      else if (key == '^') { // Turun
        mnB--;
        if (mnB < 0)mnB = 7;
      }

      else if (key == 'E') {
        switch (mnB) {
          case 0:
            lokasi();
            break;
          case 1:
            stasiun();
            break;
          case 2:
            pengamat();
            break;
          case 3:
            tanggal();
            break;
          case 4:
            waktu();
            break;
          case 5:
            kedalaman();
            break;
          case 6 :
            visibility();
            break;
          case 7 :
            //            cuaca();
            break;
        }
      }
      lcd.clear();
    }
    tampilMenu(menuSB, mnB);

    if (xs(key)) {
      break;
    }
    delay(50);
  }
}

void lokasi() {
  lcd.clear();
  int cr = 46;
  int pos = 0;
  String loc = "                ";
  while (1) {
    char key = kpd.getKey();
    tampilLcd(0, 0, "Lokasi :        ");
    lcd.setCursor(0, 1);
    lcd.print(loc);

    if (key) {
      if (key == '>') {
        loc = ascii("Lokasi :", loc);
      }
    }

    if (xs(key)) {
      break;
    }
    delay(50);
  }
}


void stasiun() {
  lcd.clear();
  int cr = 46;
  int pos = 0;
  String stat = "----------------";
  while (1) {
    char key = kpd.getKey();
    tampilLcd(0, 0, "Stasiun :        ");
    lcd.setCursor(0, 1);
    lcd.print(stat);

    if (key) {
      if (key == '>') {
        stat = ascii("Stasiun :", stat);
      }
    }

    if (xs(key)) {
      break;
    }
    delay(50);
  }
}

void pengamat() {
  lcd.clear();
  int cr = 46;
  int pos = 0;
  String obs = "----------------";
  while (1) {
    char key = kpd.getKey();
    tampilLcd(0, 0, "Pengamat :        ");
    lcd.setCursor(0, 1);
    lcd.print(obs);

    if (key) {
      if (key == '>') {
        obs = ascii("Pengamat :", obs);
      }
    }

    if (xs(key)) {
      break;
    }
    delay(50);
  }
}

void kedalaman() {

  lcd.clear();
  int depth = 0;
  while (1) {
    char key = kpd.getKey();
    tampilLcd(0, 0, "Kedalaman :        ");
    lcd.setCursor(0, 1);
    lcd.print(depth);
    if (key) {
      if (key == '>') {
        depth = integer("Kedalaman", depth, 2);
      }
      if (xs(key)) {
        break;
      }
      delay(50);
    }
  }
}

void tanggal () {
  lcd.clear();
  int cr = 46;
  int pos = 0;
  String dt = "----------------";
  while (1) {
    char key = kpd.getKey();
    tampilLcd(0, 0, "Tanggal :        ");
    lcd.setCursor(0, 1);
    lcd.print(dt);

    if (key) {
      if (key == '>') {
        dt = ascii("Tanggal :", dt);
      }
    }

    if (xs(key)) {
      break;
    }
    delay(50);
  }
}

void waktu () {
  lcd.clear();
  int tm = 0;
  while (1) {
    char key = kpd.getKey();
    tampilLcd(0, 0, "Waktu :        ");
    lcd.setCursor(0, 1);
    lcd.print(tm);
    if (key) {
      if (key == '>') {
        tm = integer("Waktu", tm, 4);
      }
      if (xs(key)) {
        break;
      }
    }
    delay(50);
  }
}

void visibility () {
  lcd.clear();
  int vs = 0;
  while (1) {
    char key = kpd.getKey();
    tampilLcd(0, 0, "Visibility :        ");
    lcd.setCursor(0, 1);
    lcd.print(vs);
    if (key) {
      if (key == '>') {
        vs = integer("Visibility", vs, 2);
      }
      if (xs(key)) {
        break;
      }
    }
    delay(50);
  }
}

