#ifndef PASIEN_H
#define PASIEN_H

#include <string>
using namespace std;

struct Pasien {
    string idPasien;
    string username;
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
bool deletePasien(TreePasien &root, string idPasien);
NodePasien* searchPasienByNik(TreePasien root, string nik);
bool nikDipakaiOrangLain(TreePasien root, string nik, string idSendiri);
int cariPasienByNama(TreePasien root, string kataKunci);
void tampilPasien(TreePasien root);
void tampilDetailPasien(NodePasien *p);
int jumlahBookingAktifPasien(string idPasien);

bool isNamaValid(string nama);
bool isNikValid(string nik);
bool isTeleponValid(string telepon);

#endif