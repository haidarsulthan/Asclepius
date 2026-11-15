#ifndef LAYANAN_H
#define LAYANAN_H

#include <string>
using namespace std;

struct Layanan {
    string idLayanan;
    string nama;
    string jenis;
    string deskripsi;
    string status;
};

struct NodeLayanan {
    Layanan info;
    NodeLayanan *left;
    NodeLayanan *right;
};

typedef NodeLayanan* TreeLayanan;

struct Keluhan {
    string kode;
    string nama;
    string idLayanan;
};

struct NodeKeluhan {
    Keluhan info;
    NodeKeluhan *left;
    NodeKeluhan *right;
};

typedef NodeKeluhan* TreeKeluhan;

void createTreeLayanan(TreeLayanan &root);
bool isEmptyLayanan(TreeLayanan root);
NodeLayanan* alokasiLayanan(Layanan l);
bool insertLayanan(TreeLayanan &root, Layanan l);
NodeLayanan* searchLayanan(TreeLayanan root, string idLayanan);
bool deleteLayanan(TreeLayanan &root, string idLayanan);
void tampilLayanan(TreeLayanan root);
void tampilLayananAktif(TreeLayanan root);
void tampilDetailLayanan(NodeLayanan *l);
bool namaLayananTerdaftar(TreeLayanan root, string nama, string idKecuali);
NodeLayanan* cariLayananDasarAktif(TreeLayanan root);
int nomorTerbesarLayanan(TreeLayanan root);

void createTreeKeluhan(TreeKeluhan &root);
bool isEmptyKeluhan(TreeKeluhan root);
NodeKeluhan* alokasiKeluhan(Keluhan k);
bool insertKeluhan(TreeKeluhan &root, Keluhan k);
NodeKeluhan* searchKeluhan(TreeKeluhan root, string kode);
bool deleteKeluhan(TreeKeluhan &root, string kode);
void tampilKeluhan(TreeKeluhan root, TreeLayanan rootL);
void tampilDetailKeluhan(NodeKeluhan *k, TreeLayanan rootL);
bool namaKeluhanTerdaftar(TreeKeluhan root, string nama, string kodeKecuali);
int jumlahKeluhanKeLayanan(TreeKeluhan root, string idLayanan);
int nomorTerbesarKeluhan(TreeKeluhan root);
int jumlahBookingDenganKeluhan(string kode);

#endif