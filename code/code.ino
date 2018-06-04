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
            //waktu();
            break;
          case 5:
            //kedalaman();
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
  String loc = "----------------";
  while (1) {
    char key = kpd.getKey();
    tampilLcd(0, 0, "Lokasi :        ");
    lcd.setCursor(0, 1);
    lcd.print(loc);

    if (key) {
      Serial.println(key);
      if (key == 'v') { // Naik
        cr++;
        if (cr > 90)cr = 46;
      }
      else if (key == '^') { // Turun
        cr--;
        if (cr < 46)cr = 90;
      }
      else if (key == '>') { // Naik
        pos++;
        if (pos > 15)pos = 0;
      }
      else if (key == '<') { // Turun
        pos--;
        if (pos < 0)pos = 15;
      }
      loc.setCharAt(pos, (char)cr);
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
      Serial.println(key);
      if (key == 'v') { // Naik
        cr++;
        if (cr > 90)cr = 46;
      }
      else if (key == '^') { // Turun
        cr--;
        if (cr < 46)cr = 90;
      }
      else if (key == '>') { // Naik
        pos++;
        if (pos > 15)pos = 0;
      }
      else if (key == '<') { // Turun
        pos--;
        if (pos < 0)pos = 15;
      }
      stat.setCharAt(pos, (char)cr);
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
      Serial.println(key);
      if (key == 'v') { // Naik
        cr++;
        if (cr > 90)cr = 46;
      }
      else if (key == '^') { // Turun
        cr--;
        if (cr < 46)cr = 90;
      }
      else if (key == '>') { // Naik
        pos++;
        if (pos > 15)pos = 0;
      }
      else if (key == '<') { // Turun
        pos--;
        if (pos < 0)pos = 15;
      }
      obs.setCharAt(pos, (char)cr);
    }

    if (xs(key)) {
      break;
    }
    delay(50);
  }
}

void tanggal () {
  lcd.clear ();
  int digit = 0;
  int persen = 0;
  String persenTemp;
  char key = kpd.getKey();
  if (key)
  {
    //    lcd.setCursor(0, 1);
    //    lcd.print("persenTemp= ");
    //    lcd.print(key);
    if (digit < 3) {
      persenTemp += key;
      digit++;
    }
    if (key == 'D') {
      persen = persenTemp.toInt();
    }
  }
  lcd.setCursor(11, 0);
  lcd.print(persenTemp);
  lcd.setCursor(0, 1);
  lcd.print(persen);
}
