void selectcoredata(int);
void menucoredata(int, int);
CoreData cdcoordinate(CoreData);
CoreData cdsubstrat(CoreData);
CoreData npl(int, CoreData);
CoreData menunpls(CoreData);

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
        menucoredata(q, mnB);
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
  lcd.clear();
  String menuSB[] = {"Koordinat     ", "Substrat      ", "NPL           ", "NPL Jenis     "};
  int mnB = 0;
  CoreData cd = cm.qds[q].cds[m];
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
            cd = npl(-1, cd);
            break;
          case 3:
            Serial.println("y");
            cd = menunpls(cd);
            break;
        }
      }
      tampilMenu(menuSB, mnB);

      if (xs(key)) {
        cm.qds[q].cds[m] = cd;
        break;
      }
      delay(50);
    }
  }
}

CoreData cdcoordinate(CoreData cd) {
  float c_lat, c_long;
  lcd.clear();
  while (1) {
    char key = kpd.getKey();
    if (key) {
      if (key == 'E') {
        cd.c_lat = c_lat;
        cd.c_long = c_long;
        lcd.clear();
        tampilLcd(0, 0, "Save Data GPS");
        delay(2000);
        return cd;
      }
    }
    while (Serial2.available() > 0) {
      gps.encode(Serial2.read());
      if (gps.location.isUpdated()) {
        c_lat = gps.location.lat();
        c_long = gps.location.lng();
        lcd.setCursor(0, 0);
        lcd.print("Lat :");
        lcd.setCursor(6, 0);
        lcd.print(c_lat, 6);
        lcd.setCursor(0, 1);
        lcd.print("Long:");
        lcd.setCursor(6, 1);
        lcd.print(c_long, 6);
      }
    }
    if (xs(key)) {
      lcd.clear();
      return cd;
    }
  }
}

CoreData cdsubstrat(CoreData cd) {
  lcd.clear();
  int sbs = cd.substrat;
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

CoreData npl(int np, CoreData cd) {
  String sp;
  bool edit = false;
  int digit = 0;
  String data[4];
  if (np < 0) {
    sp = "NP";
    for (int i = 0; i < 4; i++) {
      data[i] = String(cd.npl[i]);
    }
  }
  else {
    sp = kolom_spesies[np];
    for (int i = 0; i < 4; i++) {
      data[i] = cd.npls[np].kuadran[i];
    }
  }
  int col = 0;
  int pos = 0;
  lcd.clear();
  while (1) {
    lcd.setCursor(0, 0);
    lcd.print(sc(col == 0 ? true : false));
    lcd.setCursor(1, 0);
    lcd.print(sp);
    lcd.print(1);
    lcd.print(se(col == 0 && edit ? true : false));
    lcd.print(data[0]);

    lcd.setCursor(8, 0);
    lcd.print(sc(col == 1 ? true : false));
    lcd.setCursor(9, 0);
    lcd.print(sp);
    lcd.print(2);
    lcd.print(se(col == 1 && edit ? true : false));
    lcd.print(data[1]);

    lcd.setCursor(0, 1);
    lcd.print(sc(col == 2 ? true : false));
    lcd.setCursor(1, 1);
    lcd.print(sp);
    lcd.print(3);
    lcd.print(se(col == 2 && edit ? true : false));
    lcd.print(data[2]);

    lcd.setCursor(8, 1);
    lcd.print(sc(col == 3 ? true : false));
    lcd.setCursor(9, 1);
    lcd.print(sp);
    lcd.print(4);
    lcd.print(se(col == 3 && edit ? true : false));
    lcd.print(data[3]);

    char key = kpd.getKey();
    if (key) {
      lcd.clear();
      if (key == 'X') {
        if (np < 0) {
          for (int i = 0; i < 4; i++) {
            cd.npl[i] = data[i].toInt();
          }
        }
        else {
          for (int i = 0; i < 4; i++) {
            cd.npls[np].kuadran[i] = data[i].toInt();
          }
        }
        return cd;
      }
      else if (key == 'v') { // Naik
        col++;
        if (col > 3)col = 0;
      }
      else if (key == '^') { // Turun
        col--;
        if (col < 0)col = 3;
      }
      else if (key == '>') {
        edit = true;
        if (edit) {
          digit = data[col].length();
          pos = digit;
        }
      }
      else if (key == '<') {
        pos = pos - 1;
        data[col].remove(pos);
      }
      else if (key == 'E') {
        edit = false;
      }
      else {
        if (edit) {
          if (pos < 3) {
            data[col] += key;
            pos++;
          }
        }
      }

    }
  }
}

CoreData menunpls(CoreData cd) {
  String menuSB[10] = { "Ea", "Th", "Cs", "Cr", "Hu", "Hp", "Ho", "Si", "Tc", ""};
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
        cd = npl(mnB, cd);
      }
      lcd.clear();
    }
    tampilMenu(menuSB, mnB);

    if (xs(key)) {
      return cd;
    }
    delay(50);
  }
}
