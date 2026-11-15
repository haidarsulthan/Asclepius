#ifndef TRIASE_H
#define TRIASE_H

#include <string>
#include "user.h"
#include "layanan.h"
#include "dokter.h"
using namespace std;

// Hasil pemilihan keluhan oleh pasien. Disimpan sebagai variabel lokal pada
// dashboard Pasien (bukan variabel global) dan akan dipakai oleh modul Booking.
//   kodeKeluhan : kode keluhan terpilih dari BST Keluhan ("" = belum memilih)
//   idLayanan   : layanan tujuan akhir (sudah memperhitungkan pengalihan)
//   catatan     : catatan tambahan opsional ("" = tidak ada)
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