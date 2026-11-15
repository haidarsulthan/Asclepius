#include <iostream>
#include "pilihKeluhan.h"
#include "user.h"
using namespace std;

static bool semuaDigit(string s) {
    bool ok = true;
    size_t i = 0;
    while (i < s.length() && ok) {
        if (!(s[i] >= '0' && s[i] <= '9')) {
            ok = false;
        }
        i++;
    }
    return ok;
}

void resetPilihan(PilihanKeluhan &p) {
    p.kodeKeluhan = "";
    p.idLayanan = "";
    p.catatan = "";
}

bool sudahMemilih(PilihanKeluhan p) {
    return p.kodeKeluhan != "";
}

bool isCatatanValid(string catatan) {
    bool ok = (catatan.length() >= 5 && catatan.length() <= 200);
    bool adaIsi = false;
    size_t i = 0;
    while (ok && i < catatan.length()) {
        if (catatan[i] != ' ' && catatan[i] != '\t') {
            adaIsi = true;
        }
        i++;
    }
    return ok && adaIsi;
}

int hitungKeluhan(TreeKeluhan root) {
    int jumlah = 0;
    if (root != NULL) {
        jumlah = 1 + hitungKeluhan(root->left) + hitungKeluhan(root->right);
    }
    return jumlah;
}

void tampilKeluhanBernomor(TreeKeluhan root, int &nomor) {
    if (root != NULL) {
        tampilKeluhanBernomor(root->left, nomor);
        nomor++;
        cout << nomor << ". " << root->info.nama << endl;
        tampilKeluhanBernomor(root->right, nomor);
    }
}

void cariKeluhanKeN(TreeKeluhan root, int n, int &hitung, NodeKeluhan* &hasil) {
    if (root != NULL && hasil == NULL) {
        cariKeluhanKeN(root->left, n, hitung, hasil);
        hitung++;
        if (hitung == n && hasil == NULL) {
            hasil = root;
        }
        cariKeluhanKeN(root->right, n, hitung, hasil);
    }
}

string tentukanLayananTujuan(TreeLayanan rootL, TreeDokter rootD, string idLayananKeluhan, string &alasan) {
    NodeLayanan *lay = searchLayanan(rootL, idLayananKeluhan);
    NodeLayanan *dasar;
    string hasil = idLayananKeluhan;
    alasan = "";

    if (lay == NULL || lay->info.status != "aktif") {
        dasar = cariLayananDasarAktif(rootL);
        if (dasar != NULL) {
            hasil = dasar->info.idLayanan;
            alasan = "layanan tujuan sedang tidak aktif";
        }
    } else if (lay->info.jenis != "dasar" && jumlahDokterAktifDiLayanan(rootD, idLayananKeluhan) == 0) {
        dasar = cariLayananDasarAktif(rootL);
        if (dasar != NULL) {
            hasil = dasar->info.idLayanan;
            alasan = lay->info.nama + " belum memiliki dokter aktif";
        }
    }
    return hasil;
}

void pilihKeluhan(TreeKeluhan rootK, TreeLayanan rootL, TreeDokter rootD, PilihanKeluhan &pilihan) {
    string input, catatan, alasan, idTujuan;
    bool batal = false;
    bool valid = false;
    bool lanjut = true;
    int total, nomor, hitung, jumlahDokter;
    NodeKeluhan *terpilih = NULL;
    NodeLayanan *lay;

    cout << "\n=== PILIH KELUHAN ===" << endl;
    total = hitungKeluhan(rootK);
    if (total == 0) {
        cout << "Belum ada daftar keluhan. Silakan hubungi Admin." << endl;
        lanjut = false;
    }

    if (lanjut && sudahMemilih(pilihan)) {
        cout << "Pilihan Anda saat ini:" << endl;
        tampilPilihan(pilihan, rootK, rootL);
        if (!bacaYaTidak("Ganti pilihan keluhan?")) {
            lanjut = false;
        }
    }

    if (lanjut) {
        nomor = 0;
        cout << "Pilih keluhan yang paling sesuai:" << endl;
        tampilKeluhanBernomor(rootK, nomor);

        while (!valid && !batal) {
            input = bacaInput("Nomor keluhan (0 = batal): ");
            if (input == "0") {
                batal = true;
            } else if (input.empty() || input.length() > 4 || !semuaDigit(input)) {
                cout << "Masukkan nomor yang tertera pada daftar." << endl;
            } else {
                nomor = stoi(input);
                if (nomor < 1 || nomor > total) {
                    cout << "Nomor di luar daftar." << endl;
                } else {
                    hitung = 0;
                    terpilih = NULL;
                    cariKeluhanKeN(rootK, nomor, hitung, terpilih);
                    valid = true;
                }
            }
        }

        if (!batal) {
            idTujuan = tentukanLayananTujuan(rootL, rootD, terpilih->info.idLayanan, alasan);
            lay = searchLayanan(rootL, idTujuan);
            cout << "\nKeluhan        : " << terpilih->info.nama << endl;
            cout << "Layanan tujuan : ";
            if (lay != NULL) {
                cout << lay->info.nama << " (" << lay->info.jenis << ")" << endl;
            } else {
                cout << idTujuan << endl;
            }
            if (!alasan.empty()) {
                cout << "Info sistem    : " << alasan << ", Anda diarahkan ke layanan dasar." << endl;
            }
            cout << "Dokter tersedia:" << endl;
            jumlahDokter = tampilDokterPerLayanan(rootD, idTujuan, true);
            if (jumlahDokter == 0) {
                cout << "   (belum ada dokter aktif)" << endl;
            }

            valid = false;
            catatan = "";
            while (!valid && !batal) {
                catatan = bacaTeks("Catatan tambahan (opsional, Enter = lewati, 0 = batal): ", 200, true, batal);
                if (!batal) {
                    if (catatan.empty() || isCatatanValid(catatan)) {
                        valid = true;
                    } else {
                        cout << "Catatan minimal 5 karakter dan maksimal 200 karakter." << endl;
                    }
                }
            }
        }

        if (batal) {
            cout << "Pemilihan keluhan dibatalkan. Pilihan sebelumnya tidak berubah." << endl;
        } else {
            pilihan.kodeKeluhan = terpilih->info.kode;
            pilihan.idLayanan = idTujuan;
            pilihan.catatan = catatan;
            cout << "Keluhan tersimpan dan akan dipakai pada menu Booking." << endl;
        }
    }
}

void tampilPilihan(PilihanKeluhan p, TreeKeluhan rootK, TreeLayanan rootL) {
    NodeKeluhan *k;
    NodeLayanan *l;
    if (!sudahMemilih(p)) {
        cout << "Belum ada keluhan terpilih." << endl;
    } else {
        k = searchKeluhan(rootK, p.kodeKeluhan);
        l = searchLayanan(rootL, p.idLayanan);
        cout << "Keluhan        : ";
        if (k != NULL) {
            cout << k->info.nama << endl;
        } else {
            cout << p.kodeKeluhan << endl;
        }
        cout << "Layanan tujuan : ";
        if (l != NULL) {
            cout << l->info.nama << endl;
        } else {
            cout << p.idLayanan << endl;
        }
        cout << "Catatan        : ";
        if (p.catatan.empty()) {
            cout << "-" << endl;
        } else {
            cout << p.catatan << endl;
        }
    }
}

void tampilPilihanSingkat(PilihanKeluhan p, TreeKeluhan rootK, TreeLayanan rootL) {
    NodeKeluhan *k;
    NodeLayanan *l;
    if (sudahMemilih(p)) {
        k = searchKeluhan(rootK, p.kodeKeluhan);
        l = searchLayanan(rootL, p.idLayanan);
        cout << "Keluhan terpilih: ";
        if (k != NULL) {
            cout << k->info.nama;
        } else {
            cout << p.kodeKeluhan;
        }
        cout << " -> ";
        if (l != NULL) {
            cout << l->info.nama << endl;
        } else {
            cout << p.idLayanan << endl;
        }
    }
}