#include <iostream>
#include "keluhan.h"
#include "user.h"   
using namespace std;

void createListKeluhan(ListKeluhan &L) {
    L = NULL;
}

bool isEmptyKeluhan(ListKeluhan L) {
    return L == NULL;
}

ElmKeluhan* alokasiKeluhan(Keluhan k) {
    ElmKeluhan *baru = new ElmKeluhan;
    baru->info = k;
    baru->next = NULL;
    return baru;
}

void insertLastKeluhan(ListKeluhan &L, Keluhan k) {
    ElmKeluhan *baru = alokasiKeluhan(k);
    ElmKeluhan *cur;
    if (L == NULL) {
        L = baru;
    } else {
        cur = L;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = baru;
    }
}

int nomorTerbesarKeluhan(ListKeluhan L) {
    int maks = 0;
    int n;
    ElmKeluhan *cur = L;
    while (cur != NULL) {
        n = stoi(cur->info.idKeluhan.substr(2));
        if (n > maks) {
            maks = n;
        }
        cur = cur->next;
    }
    return maks;
}

void tampilKeluhanPasien(ListKeluhan L, string idPasien) {
    ElmKeluhan *cur = L;
    bool ada = false;
    while (cur != NULL) {
        if (cur->info.idPasien == idPasien) {
            cout << cur->info.idKeluhan << " | " << cur->info.teks << endl;
            ada = true;
        }
        cur = cur->next;
    }
    if (!ada) {
        cout << "Belum ada keluhan." << endl;
    }
}

bool isKeluhanValid(string teks) {
    bool ok = (teks.length() >= 5 && teks.length() <= 200);
    bool adaIsi = false;
    size_t i = 0;
    while (ok && i < teks.length()) {
        if (teks[i] != ' ' && teks[i] != '\t') {
            adaIsi = true;
        }
        i++;
    }
    return ok && adaIsi;
}

void tulisKeluhan(ListKeluhan &L, User u) {
    string teks;
    bool valid = false;
    bool batal = false;
    int nomor;
    Keluhan k;

    if (u.role != "Pasien") {
        cout << "Hanya pasien yang dapat menulis keluhan." << endl;
    } else {
        cout << "\n=== TULIS KELUHAN ===" << endl;
        while (!valid && !batal) {
            teks = bacaInput("Tulis keluhan Anda (0 = batal): ");
            if (teks == "0") {
                batal = true;
            } else if (!isKeluhanValid(teks)) {
                cout << "Keluhan 5-200 karakter dan tidak boleh kosong." << endl;
            } else {
                valid = true;
            }
        }

        if (batal) {
            cout << "Penulisan keluhan dibatalkan." << endl;
        } else {
            nomor = nomorTerbesarKeluhan(L) + 1;
            if (nomor > 999) {
                cout << "Kapasitas ID keluhan penuh. Keluhan gagal disimpan." << endl;
            } else {
                k.idKeluhan = buatId("KL", nomor);
                k.idPasien = u.idPenghubung;
                k.teks = teks;
                insertLastKeluhan(L, k);
                cout << "Keluhan tersimpan dengan ID: " << k.idKeluhan << endl;
            }
        }
    }
}