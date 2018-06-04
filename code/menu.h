void tampilLcd(uint8_t x, uint8_t y, const char* fmtstr, ...) // dinggo lcd ben penak
{
  char lcd_string[21];
  va_list ap;

  va_start(ap, fmtstr);
  vsprintf(lcd_string, fmtstr, ap);
  va_end(ap);

  lcd.setCursor(x, y);
  lcd.print(lcd_string);
}

char sc(bool c) {
  if (c) {
    return '~';
  }
  else {
    return ' ';
  }
}

tampilMenu(String t[], int idx) {
  //  if ((idx%2)) {
  //
  //  }
  int a, b;
  bool c = false;
  if ((idx % 2) == 0) {
    a = idx;
    b = idx + 1;
    c = true;
  }
  else if ((idx % 2) == 1) {
    a = idx - 1;
    b = idx;
    c = false;
  }

  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print (c);
  Serial.print("\n");
  lcd.setCursor(0, 0);
  lcd.print(sc(c));
  lcd.setCursor(1, 0);
  lcd.print(t[a]);
  lcd.setCursor(0, 1);
  lcd.print(sc(!c));
  lcd.setCursor(1, 1);
  lcd.print(t[b]);
}

bool x() {
  char key = kpd.getKey();
  if (key) {
    if (key == 'X') {
      return true;
    }
  }
  return false;
}

bool xs(char key) {
  if (key) {
    if (key == 'X') {
      return true;
    }
  }
  return false;
}



