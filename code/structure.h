String kolom_spesies[9] = { "Ea", "Th", "Cs", "Cr", "Hu", "Hp", "Ho", "Si", "Tc"};
String substrat [4] = { "Pasir", "Lumpur", "Batu", "Rubble" };
String data_cuaca[3] = { "Cerah", "Berawan", "Hujan" };
int rangecoredata[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

struct Species {
  int name = 0;
  int kuadran[4] = {0, 0, 0, 0};
};

struct CoreData {
  int distance = 0;
  float c_lat = 0.0;
  float c_long = 0.0;
  int substrat = 0;
  int npl[4] = {0, 0, 0, 0};
  Species npls[10];
};

struct Quadrant {
  int number = 0;
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
  Quadrant qds[1];
};

Species dummy_sp() {
  Species sp;
  sp.name = 0;
  for (int i = 0; i < 4; i++) {
    sp.kuadran[i] = 0;
  }
  return sp;
}

CoreData dummy_cd(Species sp[]) {
  CoreData cd;
  cd.distance = 0;
  cd.c_lat = 0.0;
  cd.c_long = 0.0;
  cd.substrat = 0;
  for (int i = 0; i < 4; i++) {
    cd.npl[i] = 0;
  }
  for (int i = 0; i < 10; i++) {
    cd.npls[i] = sp[i];
  }
  return cd;
}

Quadrant dummy_qd(CoreData cd[]) {
  Quadrant qd;
  qd.number = 0;
  for (int i = 0; i < 11; i++) {
    qd.cds[i] = cd[i];
  }
  return qd;
}
