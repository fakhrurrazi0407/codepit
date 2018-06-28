String kolom_spesies[9] = { "Ea", "Th", "Cs", "Cr", "Hu", "Hp", "Ho", "Si", "Tc"};
String substrat [4] = { "Pasir", "Lumpur", "Batu", "Rubble" };
String data_cuaca[3] = { "Cerah", "Berawan", "Hujan" };
int rangecoredata[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

struct Species {
  int name;
  int kuadran[4];
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
  String cm_date;
  String cm_time;
  int cm_depth;
  int cm_visibility;
  int cm_weather;
  Quadrant qds;
};
