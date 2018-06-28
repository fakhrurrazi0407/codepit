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
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include "structure.h"
#include "sd.h"

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
#include "coredata.h"

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  SDSetup();
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
  CoreMap cm;
  cm.cm_location = "                ";
  cm.cm_station = "                ";
  cm.cm_observer = "                ";
  cm.cm_date = "                ";
  cm.cm_time = "                ";
  cm.cm_depth = 0;
  cm.cm_visibility = 0;
  cm.cm_weather = 0;
  String menuSB[] = {"Lokasi", "Stasiun", "Pengamat", "Tanggal", "Waktu", "Kedalaman", "Visibility", "Cuaca", "Quadrant", "   "};
  int mnB = 0;
  while (1) {
    char key = kpd.getKey();
    if (key) {
      Serial.println(key);
      if (key == 'v') { // Naik
        mnB++;
        if (mnB > 8)mnB = 0;
      }

      else if (key == '^') { // Turun
        mnB--;
        if (mnB < 0)mnB = 8;
      }

      else if (key == 'E') {
        switch (mnB) {
          case 0:
            cm.cm_location = lokasi(cm.cm_location);
            break;
          case 1:
            cm.cm_station = stasiun(cm.cm_station);
            break;
          case 2:
            cm.cm_observer = pengamat(cm.cm_observer);
            break;
          case 3:
            cm.cm_date = tanggal(cm.cm_date);
            break;
          case 4:
            cm.cm_time = waktu(cm.cm_time);
            break;
          case 5:
            cm.cm_depth = kedalaman(cm.cm_depth);
            break;
          case 6 :
            cm.cm_visibility = visibility(cm.cm_visibility);
            break;
          case 7 :
            cm.cm_weather = cuaca(cm.cm_weather);
            break;
          case 8 :
            menuquadrant();
            break;
        }
      }
      lcd.clear();
    }

    tampilMenu(menuSB, mnB);

    if (xs(key)) {
      writeToSD(cm);
      break;
    }
    delay(50);
  }
}

String lokasi(String loc) {
  lcd.clear();
  int cr = 46;
  int pos = 0;
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
      return loc;
    }
    delay(50);
  }
}

String stasiun(String stat) {
  lcd.clear();
  int cr = 46;
  int pos = 0;
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
      return stat;
    }
    delay(50);
  }
}

String pengamat(String obs) {
  lcd.clear();
  int cr = 46;
  int pos = 0;
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
      return obs;
    }
    delay(50);
  }
}

int kedalaman(int depth) {
  lcd.clear();
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
        return depth;
      }
      delay(50);
    }
  }
}

String tanggal (String dt) {
  lcd.clear();
  int cr = 46;
  int pos = 0;
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
      return dt;
    }
    delay(50);
  }
}

String waktu (String tm) {
  lcd.clear();
  while (1) {
    char key = kpd.getKey();
    tampilLcd(0, 0, "Waktu :        ");
    lcd.setCursor(0, 1);
    lcd.print(tm);
    if (key) {
      if (key == '>') {
        tm = ascii("Waktu", tm);
      }
      if (xs(key)) {
        return tm;
      }
    }
    delay(50);
  }
}

int visibility (int vs) {
  lcd.clear();
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
        return vs;
      }
      delay(50);
    }
  }
}

int cuaca(int cuaca) {
  lcd.clear();
  while (1) {
    tampilLcd(0, 0, "Cuaca :         ");
    lcd.setCursor(0, 1);
    lcd.print(data_cuaca[cuaca]);
    char key = kpd.getKey();
    if (key) {
      if (key == 'X') {
        return cuaca;
      }
      else if (key == '>') {
        while (1) {
          tampilLcd(0, 0, ">Cuaca :        ");
          lcd.setCursor(0, 1);
          lcd.print(data_cuaca[cuaca]);
          char key = kpd.getKey();
          if (key) {
            lcd.clear();
            if (key == 'E') {
              break;
            }
            else if (key == '^') {
              cuaca++;
              if (cuaca > 2) {
                cuaca = 0;
              }
            }
            else if (key == 'v') {
              cuaca--;
              if (cuaca < 0) {
                cuaca = 2;
              }
            }
            else if (key == 'X') {
              break;
            }
          }
        }
      }
    }
  }
}
