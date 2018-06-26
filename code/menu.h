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

char se(bool c) {
  if (c) {
    return '>';
  }
  else {
    return '=';
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

String ascii(String text, String val) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">");
  lcd.setCursor(1, 0);
  lcd.print(text);
  int pos = 0;
  int cr = 46;
  bool bl = true;
  currentMillis = millis();
  previousMillis = 0;
  String lastval = val;
  lcd.setCursor(0, 1);
  lcd.print(val);
  while (1) {
    char key = kpd.getKey();
    currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      bl = !bl;
      previousMillis = currentMillis;
    }

    if (bl) {
      lcd.setCursor(pos, 1);
      lcd.write(255);
    }
    else {
      lcd.setCursor(pos, 1);
      lcd.print(val.charAt(pos));
    }

    if (key) {
      if (key == 'v') {
        cr++;
        if (cr > 90)cr = 46;
      }
      else if (key == '^') {
        cr--;
        if (cr < 46)cr = 90;
      }
      else if (key == '>') {
        pos++;
        if (pos > 15)pos = 0;
        cr = val.charAt(pos);
      }
      else if (key == '<') {
        pos--;
        if (pos < 0)pos = 15;
        cr = val.charAt(pos);
      }
      else if (key == 'E') {
        return val;
      }
      else if (key == 'X') {
        return lastval;
      }
      lcd.setCursor(0, 1);
      lcd.print(val);
      val.setCharAt(pos, (char)cr);
    }
  }
}

int integer(String text, int last, int max) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">");
  lcd.setCursor(1, 0);
  lcd.print(text);
  String x = String(last);
  int digit = x.length();
  int pos = digit;
  while (1) {
    char key = kpd.getKey();
    lcd.setCursor(0, 1);
    lcd.print(x);
    lcd.setCursor(pos, 1);
    lcd.print("<");
    if (key)
    {
      if (digit < max) {
        x += key;
      }
      if (key == 'E') {
        lcd.clear();
        return x.toInt();
      }
      else if (key == '<') {
        tampilLcd(0, 1, "                ");
        pos = pos - 1;
        x.remove(pos);
        digit = x.length();
      }
      else {
        digit++;
        if (digit <= max) {
          pos++;
        }
      }
    }
  }
}
