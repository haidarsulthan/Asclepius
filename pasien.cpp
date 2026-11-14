#include <iostream>
#include "pasien.h"
using namespace std;

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

void createTreePasien(TreePasien &root) {
    root = NULL;
}

bool isEmptyPasien(TreePasien root) {
    return root == NULL;
}

NodePasien* alokasiPasien(Pasien p) {
    NodePasien *baru = new NodePasien;
    baru->info = p;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

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

bool nikTerdaftar(TreePasien root, string nik) {
    bool ada = false;
    if (root != NULL) {
        ada = (root->info.nik == nik)
              || nikTerdaftar(root->left, nik)
              || nikTerdaftar(root->right, nik);
    }
    return ada;
}

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

void tampilPasien(TreePasien root) {
    if (root != NULL) {
        tampilPasien(root->left);
        cout << root->info.idPasien << " | " << root->info.nama << " | "
             << root->info.nik << " | " << root->info.telepon << endl;
        tampilPasien(root->right);
    }
}

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

bool isNikValid(string nik) {
    return nik.length() == 16 && semuaDigit(nik);
}

bool isTeleponValid(string telepon) {
    return telepon.length() >= 10 && telepon.length() <= 13 && semuaDigit(telepon);
}