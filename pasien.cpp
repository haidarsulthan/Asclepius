#include <iostream>
#include "pasien.h"
using namespace std;

// ---------- fungsi bantu internal ----------
static bool isHuruf(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

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

// ---------- operasi BST Pasien ----------

// I.S.: root sembarang
// F.S.: root = NULL (pohon kosong)
void createTreePasien(TreePasien &root) {
    root = NULL;
}

// Mengembalikan true jika pohon kosong
bool isEmptyPasien(TreePasien root) {
    return root == NULL;
}

// Mengembalikan alamat node baru berisi p (left dan right = NULL)
NodePasien* alokasiPasien(Pasien p) {
    NodePasien *baru = new NodePasien;
    baru->info = p;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

// I.S.: root terdefinisi (boleh kosong), p berisi data pasien
// F.S.: p tersisip pada BST berdasarkan idPasien jika idPasien belum ada
//       (mengembalikan true); jika idPasien sudah ada, pohon tidak berubah
//       (mengembalikan false)
bool insertPasien(TreePasien &root, Pasien p) {
    bool berhasil = false;
    if (root == NULL) {
        root = alokasiPasien(p);
        berhasil = true;
    } else if (p.idPasien < root->info.idPasien) {
        berhasil = insertPasien(root->left, p);
    } else if (p.idPasien > root->info.idPasien) {
        berhasil = insertPasien(root->right, p);
    }
    return berhasil;
}

// Mengembalikan alamat node dengan idPasien yang dicari, NULL jika tidak ada
NodePasien* searchPasien(TreePasien root, string idPasien) {
    NodePasien *cur = root;
    bool ketemu = false;
    while (cur != NULL && !ketemu) {
        if (idPasien == cur->info.idPasien) {
            ketemu = true;
        } else if (idPasien < cur->info.idPasien) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return cur;
}

// Mengembalikan true jika ada pasien dengan NIK tersebut.
// NIK bukan kunci BST, sehingga seluruh pohon ditelusuri.
bool nikTerdaftar(TreePasien root, string nik) {
    bool ada = false;
    if (root != NULL) {
        ada = (root->info.nik == nik)
              || nikTerdaftar(root->left, nik)
              || nikTerdaftar(root->right, nik);
    }
    return ada;
}

// Mengembalikan angka pada ID pasien terbesar (mis. "PS007" -> 7), 0 jika
// pohon kosong. ID terbesar berada pada node paling kanan karena nomor ID
// dibuat dengan 3 digit (zero-padded) sehingga urutan string = urutan angka.
int nomorTerbesarPasien(TreePasien root) {
    NodePasien *cur = root;
    int nomor = 0;
    if (cur != NULL) {
        while (cur->right != NULL) {
            cur = cur->right;
        }
        nomor = stoi(cur->info.idPasien.substr(2));
    }
    return nomor;
}

// I.S.: root terdefinisi
// F.S.: seluruh pasien tercetak urut idPasien (in-order)
void tampilPasien(TreePasien root) {
    if (root != NULL) {
        tampilPasien(root->left);
        cout << root->info.idPasien << " | " << root->info.nama << " | "
             << root->info.nik << " | " << root->info.telepon << endl;
        tampilPasien(root->right);
    }
}

// ---------- validasi input ----------

// Nama: 1-50 karakter, hanya huruf, spasi, titik, atau apostrof,
// dan minimal memuat satu huruf.
bool isNamaValid(string nama) {
    bool ok = (nama.length() >= 1 && nama.length() <= 50);
    bool adaHuruf = false;
    size_t i = 0;
    while (ok && i < nama.length()) {
        char c = nama[i];
        if (isHuruf(c)) {
            adaHuruf = true;
        } else if (!(c == ' ' || c == '.' || c == '\'')) {
            ok = false;
        }
        i++;
    }
    return ok && adaHuruf;
}

// NIK: tepat 16 digit angka
bool isNikValid(string nik) {
    return nik.length() == 16 && semuaDigit(nik);
}

// Telepon: 10-13 digit angka
bool isTeleponValid(string telepon) {
    return telepon.length() >= 10 && telepon.length() <= 13 && semuaDigit(telepon);
}