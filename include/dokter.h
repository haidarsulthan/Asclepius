#ifndef DOKTER_H
#define DOKTER_H

#include <string>
#include "layanan.h"
using namespace std;

// ADT BST Dokter (kunci: idDokter, contoh "DK001").
// idDokter sama dengan idPenghubung pada akun User role Dokter.
// spesialisasi: gelar spesialis (mis. "Sp.A"), "-" untuk dokter umum.
// status: "aktif" atau "nonaktif".
struct Dokter {
    string idDokter;
    string username;
    string nama;
    string idLayanan;
    string spesialisasi;
    string telepon;
    string alamat;
    string status;
};

struct NodeDokter {
    Dokter info;
    NodeDokter *left;
    NodeDokter *right;
};

typedef NodeDokter* TreeDokter;

void createTreeDokter(TreeDokter &root);
bool isEmptyDokter(TreeDokter root);
NodeDokter* alokasiDokter(Dokter d);
bool insertDokter(TreeDokter &root, Dokter d);
NodeDokter* searchDokter(TreeDokter root, string idDokter);
bool deleteDokter(TreeDokter &root, string idDokter);
void tampilDokter(TreeDokter root, TreeLayanan rootL);
void tampilDetailDokter(NodeDokter *d, TreeLayanan rootL);
int tampilDokterPerLayanan(TreeDokter root, string idLayanan, bool hanyaAktif);
void tampilLayananDenganDokter(TreeLayanan rootL, TreeDokter rootD);
int jumlahDokterDiLayanan(TreeDokter root, string idLayanan);
int jumlahDokterAktifDiLayanan(TreeDokter root, string idLayanan);
int jumlahJadwalDokter(string idDokter);

#endif