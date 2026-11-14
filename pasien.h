#ifndef PASIEN_H
#define PASIEN_H

#include <string>
using namespace std;

struct Pasien {
    string idPasien;
    string nama;
    string nik;
    string telepon;
};

struct NodePasien {
    Pasien info;
    NodePasien *left;
    NodePasien *right;
};

typedef NodePasien* TreePasien;

void createTreePasien(TreePasien &root);
bool isEmptyPasien(TreePasien root);
NodePasien* alokasiPasien(Pasien p);
bool insertPasien(TreePasien &root, Pasien p);
NodePasien* searchPasien(TreePasien root, string idPasien);
bool nikTerdaftar(TreePasien root, string nik);
int nomorTerbesarPasien(TreePasien root);
void tampilPasien(TreePasien root);

bool isNamaValid(string nama);
bool isNikValid(string nik);
bool isTeleponValid(string telepon);

#endif