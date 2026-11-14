#ifndef KELUHAN_H
#define KELUHAN_H

#include "user.h"
#include <string>
using namespace std;

struct Keluhan {
    string idKeluhan;
    string idPasien;
    string teks;
};

struct ElmKeluhan {
    Keluhan info;
    ElmKeluhan *next;
};

typedef ElmKeluhan* ListKeluhan;

void createListKeluhan(ListKeluhan &L);
bool isEmptyKeluhan(ListKeluhan L);
ElmKeluhan* alokasiKeluhan(Keluhan k);
void insertLastKeluhan(ListKeluhan &L, Keluhan k);
int nomorTerbesarKeluhan(ListKeluhan L);
void tampilKeluhanPasien(ListKeluhan L, string idPasien);

bool isKeluhanValid(string teks);
void tulisKeluhan(ListKeluhan &L, User u);
//pp
#endif