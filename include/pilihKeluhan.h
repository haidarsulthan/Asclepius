#ifndef PILIHKELUHAN_H
#define PILIHKELUHAN_H

#include <string>
#include "layanan.h"
#include "dokter.h"
using namespace std;

struct PilihanKeluhan {
    string kodeKeluhan;
    string idLayanan;
    string catatan;
};

void resetPilihan(PilihanKeluhan &p);
bool sudahMemilih(PilihanKeluhan p);
bool isCatatanValid(string catatan);

int hitungKeluhan(TreeKeluhan root);
void tampilKeluhanBernomor(TreeKeluhan root, int &nomor);
void cariKeluhanKeN(TreeKeluhan root, int n, int &hitung, NodeKeluhan* &hasil);
string tentukanLayananTujuan(TreeLayanan rootL, TreeDokter rootD, string idLayananKeluhan, string &alasan);

void pilihKeluhan(TreeKeluhan rootK, TreeLayanan rootL, TreeDokter rootD, PilihanKeluhan &pilihan);
void tampilPilihan(PilihanKeluhan p, TreeKeluhan rootK, TreeLayanan rootL);
void tampilPilihanSingkat(PilihanKeluhan p, TreeKeluhan rootK, TreeLayanan rootL);

#endif