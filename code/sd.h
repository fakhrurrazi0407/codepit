void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }

    entry.close();
  }
}

void SDSetup() {
  pinMode(53, OUTPUT);
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  //  File root;
  //  root = SD.open("/DATA");
  //  printDirectory(root, 0);
}

String valString(String s) {
  s.trim();
  return s;
}

void writeToSD(CoreMap cm) {
  const size_t bufferSize = JSON_OBJECT_SIZE(7);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  String output;
  File myFile;

  JsonObject& root = jsonBuffer.createObject();
  root["location"] = valString(cm.cm_location);
  root["station"] = valString(cm.cm_station);
  root["observer"] = valString(cm.cm_observer);
  root["date"] = valString(cm.cm_date);
  root["time"] = valString(cm.cm_time);
  root["depth"] = cm.cm_depth;
  root["visibility"] = cm.cm_visibility;
  root["weather"] = valString(data_cuaca[cm.cm_weather]);

  root.printTo(output);

  myFile = SD.open("data/namabaru.txt", FILE_WRITE);
  if (myFile) {
    Serial.println("Writing to file...");
    myFile.println(output);
    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening IniCoba.txt");
  }
}
