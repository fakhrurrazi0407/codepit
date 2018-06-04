String kolom_spesies[9] = { "Ea", "Th", "Cs", "Cr", "Hu", "Hp", "Ho", "Si", "Tc"};
String substrat [4] = {"Pasir", "Lumpur", "Batu", "Rubble"};

struct Species {
  int name;
  int quadrant[4];
};

struct CoreData {
  int distance;
  float c_lat;
  float c_long;
  int substrat;
  int npl[4];
  Species npls[10];
};

struct Quadrant {
  int number;
  CoreData cds[11];
};

struct CoreMap {
  String cm_location;
  String cm_station;
  String cm_observer;
  int cm_date[3];
  int cm_time[2];
  int cm_depth;
  int cm_visibility;
  int cm_weather;
  Quadrant qds;
};
