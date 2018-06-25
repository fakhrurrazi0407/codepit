void selectcoredata(int);
void menucoredata(int, int);
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
    menuSBq[i] = "Quadrant " + String(q + 1) + "," + String(range[i]) + "m";
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
  lcd.clear();
  while (1) {
    tampilLcd(0, 0, "CD %d jarak %d", q, m);
    char key = kpd.getKey();
    if (xs(key)) {
      break;
    }
  }
}
