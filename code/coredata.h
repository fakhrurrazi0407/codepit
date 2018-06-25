void selectcoredata(int);
void menucoredata(int, int);
CoreData cdcoordinate(CoreData);
CoreData cdsubstrat(CoreData);
CoreData npl(String, CoreData);

void menuquadrant() {
  lcd.clear();
  int qd = 0;
  while (1) {
    tampilLcd(0, 0, "Pilih Kuadran   ");
    tampilLcd(0, 1, "%c1  %c2", sc(qd == 0 ? true : false), sc(qd == 1 ? true : false));

    char key = kpd.getKey();
    if (key) {
      lcd.clear();
      if (key == 'E') {
        selectcoredata(qd);
      }
      else if (key == '>') {
        qd++;
        if (qd > 1) {
          qd = 0;
        }
      }
      else if (key == '<') {
        qd--;
        if (qd < 0) {
          qd = 1;
        }
      }
      else if (key == 'X') {
        break;
      }
      lcd.clear();
    }
  }
}

void selectcoredata(int q) {
  lcd.clear();
  int jml = 11;
  int mnB = 0;
  int jmls, i;
  if (jml % 2 == 1) {
    jmls = jml + 1;
  }
  else {
    jmls = jml;
  }
  String menuSBq[jmls];
  int range[jml];
  memcpy(range, rangecoredata, sizeof(rangecoredata));
  for (i = 0; i < jml; i++) {
    menuSBq[i] = "Quadrant " + String(q + 1) + ";" + String(range[i]) + "m";
  }
  if (jml % 2 == 1) {
    menuSBq[i] = " ";
  }

  while (1) {
    char key = kpd.getKey();
    if (key) {
      Serial.println(key);
      if (key == 'v') { // Naik
        mnB++;
        if (mnB > jml - 1)mnB = 0;
      }
      else if (key == '^') { // Turun
        mnB--;
        if (mnB < 0)mnB = jml - 1;
      }
      else if (key == 'E') {
        menucoredata(q, range[mnB]);
      }
      lcd.clear();
    }
    tampilMenu(menuSBq, mnB);

    if (xs(key)) {
      break;
    }
    delay(50);
  }
}

void menucoredata(int q, int m) {
  String menuSB[] = {"Koordinat     ", "Substrat      ", "NPL           ", "NPL Jenis     "};
  int mnB = 0;
  CoreData cd;
  tampilMenu(menuSB, mnB);
  while (1) {
    char key = kpd.getKey();
    if (key) {
      Serial.println(key);
      if (key == 'v') { // Naik
        mnB++;
        if (mnB > 3)mnB = 0;
      }

      else if (key == '^') { // Turun
        mnB--;
        if (mnB < 0)mnB = 3;
      }

      else if (key == 'E') {
        lcd.clear();
        switch (mnB) {
          case 0:
            cd = cdcoordinate(cd);
            break;
          case 1:
            cd = cdsubstrat(cd);
            break;
          case 2:
            cd = npl("NPL", cd);
            break;
        }
      }
      tampilMenu(menuSB, mnB);

      if (xs(key)) {
        break;
      }
      delay(50);
    }
  }
}

CoreData cdcoordinate(CoreData cd) {
  lcd.clear();
  while (1) {
    char key = kpd.getKey();
    tampilLcd(0, 0, "Ini menu Koordinat");
    // cd.c_lat = 393939;
    // cd.c_long = 908789;
    if (xs(key)) {
      lcd.clear();
      return cd;
    }
  }
}

CoreData cdsubstrat(CoreData cd) {
  lcd.clear();
  int sbs = 0;
  while (1) {
    tampilLcd(0, 0, "Substrat :      ");
    lcd.setCursor(0, 1);
    lcd.print(substrat[sbs]);
    char key = kpd.getKey();
    if (key) {
      if (key == 'X') {
        return cd;
      }
      else if (key == '>') {
        while (1) {
          tampilLcd(0, 0, ">Substrat :     ");
          lcd.setCursor(0, 1);
          lcd.print(substrat[sbs]);
          char key = kpd.getKey();
          if (key) {
            lcd.clear();
            if (key == 'E') {
              cd.substrat = sbs;
              break;
            }
            else if (key == '^') {
              sbs++;
              if (sbs > 3) {
                sbs = 0;
              }
            }
            else if (key == 'v') {
              sbs--;
              if (sbs < 0) {
                sbs = 3;
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

CoreData npl(String sp, CoreData cd) {
  lcd.clear();
  int data[4] = {0, 0, 0, 0};
  while (1) {
    lcd.setCursor(0, 0);
    lcd.print(sp);
    lcd.print("=");
    lcd.print(data[0]);
    
    lcd.setCursor(8, 0);
    lcd.print(sp);
    lcd.print("=");
    lcd.print(data[1]);
    
    lcd.setCursor(0, 1);
    lcd.print(sp);
    lcd.print("=");
    lcd.print(data[2]);
    
    lcd.setCursor(8, 1);
    lcd.print(sp);
    lcd.print("=");
    lcd.print(data[3]);
    
    char key = kpd.getKey();
    if (key) {
      lcd.clear();
      if (key == 'X') {        
        break;
      }
    }
  }
}
