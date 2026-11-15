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

static string kecil(string s) {
    size_t i;
    for (i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = (char)(s[i] + 32);
        }
    }
    return s;
}

static NodePasien* terkecilPasien(NodePasien *root) {
    NodePasien *cur = root;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
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

bool deletePasien(TreePasien &root, string idPasien) {
    bool berhasil = false;
    NodePasien *hapus;
    NodePasien *pengganti;
    string kunciPengganti;
    if (root != NULL) {
        if (idPasien < root->info.idPasien) {
            berhasil = deletePasien(root->left, idPasien);
        } else if (idPasien > root->info.idPasien) {
            berhasil = deletePasien(root->right, idPasien);
        } else {
            berhasil = true;
            if (root->left == NULL) {
                hapus = root;
                root = root->right;
                delete hapus;
            } else if (root->right == NULL) {
                hapus = root;
                root = root->left;
                delete hapus;
            } else {
                pengganti = terkecilPasien(root->right);
                kunciPengganti = pengganti->info.idPasien;
                root->info = pengganti->info;
                deletePasien(root->right, kunciPengganti);
            }
        }
    }
    return berhasil;
}

NodePasien* searchPasienByNik(TreePasien root, string nik) {
    NodePasien *hasil = NULL;
    if (root != NULL) {
        if (root->info.nik == nik) {
            hasil = root;
        } else {
            hasil = searchPasienByNik(root->left, nik);
            if (hasil == NULL) {
                hasil = searchPasienByNik(root->right, nik);
            }
        }
    }
    return hasil;
}

bool nikDipakaiOrangLain(TreePasien root, string nik, string idSendiri) {
    NodePasien *p = searchPasienByNik(root, nik);
    return p != NULL && p->info.idPasien != idSendiri;
}

int cariPasienByNama(TreePasien root, string kataKunci) {
    int jumlah = 0;
    if (root != NULL) {
        jumlah = cariPasienByNama(root->left, kataKunci);
        if (kecil(root->info.nama).find(kecil(kataKunci)) != string::npos) {
            cout << root->info.idPasien << " | " << root->info.nama << " | "
                << root->info.nik << " | " << root->info.telepon << endl;
            jumlah++;
        }
        jumlah = jumlah + cariPasienByNama(root->right, kataKunci);
    }
    return jumlah;
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

void tampilDetailPasien(NodePasien *p) {
    if (p != NULL) {
        cout << "ID       : " << p->info.idPasien << endl;
        cout << "Username : " << p->info.username << endl;
        cout << "Nama     : " << p->info.nama << endl;
        cout << "NIK      : " << p->info.nik << endl;
        cout << "Telepon  : " << p->info.telepon << endl;
    }
}

int jumlahBookingAktifPasien(string idPasien) {
    (void)idPasien;
    return 0;
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