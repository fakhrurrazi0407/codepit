void menuquadrant() {
  lcd.clear();
  int qd = 0;
  while (1) {
    tampilLcd(0, 0, "Pilih Kuadran   ");
    tampilLcd(0, 1, "%c1  %c2  %c3  %c4", sc(qd == 0 ? true : false), sc(qd == 1 ? true : false));

    char key = kpd.getKey();
    if (key) {
      lcd.clear();
      if (key == 'E') {
        //        break;
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
    }
  }
}
