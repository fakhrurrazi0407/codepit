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
  pinMode(A7, OUTPUT);
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

void writeCoreData(CoreMap cm, JsonArray& quadrant_1_0_species, int qd, int qd_data, int cd_data) {
  JsonObject& quadrant_1_0_species_0 = quadrant_1_0_species.createNestedObject();
  quadrant_1_0_species_0["name"] = kolom_spesies[cd_data];

  JsonArray& quadrant_1_0_species_0_npl = quadrant_1_0_species_0.createNestedArray("npl");
  for (int i = 0; i < 4; i++) {
    quadrant_1_0_species_0_npl.add(cm.qds[qd].cds[qd_data].npls[cd_data].kuadran[i]);
  }
}

void writeQuadrantData(CoreMap cm, JsonArray& quadrant_1, int qd, int qd_data) {
  JsonObject& quadrant_1_0 = quadrant_1.createNestedObject();
  quadrant_1_0["distance"] = String(rangecoredata[qd_data]) + " Meter";
  quadrant_1_0["lat"] = cm.qds[qd].cds[qd_data].c_lat;
  quadrant_1_0["long"] = cm.qds[qd].cds[qd_data].c_long;
  quadrant_1_0["substrat"] = substrat[cm.qds[qd].cds[qd_data].substrat];
  JsonArray& quadrant_1_0_npl = quadrant_1_0.createNestedArray("npl");
  for (int i = 0; i < 4; i++) {
    quadrant_1_0_npl.add(cm.qds[qd].cds[qd_data].npl[i]);
  }
  JsonArray& quadrant_1_0_species = quadrant_1_0.createNestedArray("species");

  for (int i = 0; i < 9; i++) {
    writeCoreData(cm, quadrant_1_0_species, qd, qd_data, i);
  }
}

void writeQuadrant(CoreMap cm, JsonObject& quadrant, int qd) {
  JsonArray& quadrant_1 = quadrant.createNestedArray(String(qd));
  for (int i = 0; i < 11; i++) {
    writeQuadrantData(cm, quadrant_1, qd, i);
  }
}

void writeToSD(CoreMap cm) {
  Serial.println("Write to SD");
  const size_t bufferSize = 320 * JSON_ARRAY_SIZE(4) + 22 * JSON_ARRAY_SIZE(9) + 2 * JSON_ARRAY_SIZE(11) + 199 * JSON_OBJECT_SIZE(2) + 22 * JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(9);  
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
  JsonObject& quadrant = root.createNestedObject("quadrant");
  for (int i = 0; i < 2; i++) {
    writeQuadrant(cm, quadrant, i);
  }

  root.printTo(output);

  myFile = SD.open("data/namabaru.txt", O_WRITE | O_CREAT | O_TRUNC);
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
