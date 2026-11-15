#include <iostream>
#include "layanan.h"
using namespace std;

static string kecil(string s) {
    size_t i;
    for (i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = (char)(s[i] + 32);
        }
    }
    return s;
}

static NodeLayanan* terkecilLayanan(NodeLayanan *root) {
    NodeLayanan *cur = root;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

static NodeKeluhan* terkecilKeluhan(NodeKeluhan *root) {
    NodeKeluhan *cur = root;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

// =====================================================
//                    BST LAYANAN
// =====================================================

void createTreeLayanan(TreeLayanan &root) {
    root = NULL;
}

bool isEmptyLayanan(TreeLayanan root) {
    return root == NULL;
}

// Mengembalikan alamat node baru berisi l (left dan right = NULL)
NodeLayanan* alokasiLayanan(Layanan l) {
    NodeLayanan *baru = new NodeLayanan;
    baru->info = l;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

bool insertLayanan(TreeLayanan &root, Layanan l) {
    bool berhasil = false;
    if (root == NULL) {
        root = alokasiLayanan(l);
        berhasil = true;
    } else if (l.idLayanan < root->info.idLayanan) {
        berhasil = insertLayanan(root->left, l);
    } else if (l.idLayanan > root->info.idLayanan) {
        berhasil = insertLayanan(root->right, l);
    }
    return berhasil;
}

// Mengembalikan alamat node dengan ID yang dicari, NULL jika tidak ada
NodeLayanan* searchLayanan(TreeLayanan root, string idLayanan) {
    NodeLayanan *cur = root;
    bool ketemu = false;
    while (cur != NULL && !ketemu) {
        if (idLayanan == cur->info.idLayanan) {
            ketemu = true;
        } else if (idLayanan < cur->info.idLayanan) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return cur;
}

bool deleteLayanan(TreeLayanan &root, string idLayanan) {
    bool berhasil = false;
    NodeLayanan *hapus;
    NodeLayanan *pengganti;
    string kunciPengganti;
    if (root != NULL) {
        if (idLayanan < root->info.idLayanan) {
            berhasil = deleteLayanan(root->left, idLayanan);
        } else if (idLayanan > root->info.idLayanan) {
            berhasil = deleteLayanan(root->right, idLayanan);
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
                pengganti = terkecilLayanan(root->right);
                kunciPengganti = pengganti->info.idLayanan;
                root->info = pengganti->info;
                deleteLayanan(root->right, kunciPengganti);
            }
        }
    }
    return berhasil;
}

void tampilLayanan(TreeLayanan root) {
    if (root != NULL) {
        tampilLayanan(root->left);
        cout << root->info.idLayanan << " | " << root->info.nama << " | "
            << root->info.jenis << " | " << root->info.status << endl;
        tampilLayanan(root->right);
    }
}

void tampilLayananAktif(TreeLayanan root) {
    if (root != NULL) {
        tampilLayananAktif(root->left);
        if (root->info.status == "aktif") {
            cout << root->info.idLayanan << " | " << root->info.nama << " | "
                << root->info.jenis << endl;
        }
        tampilLayananAktif(root->right);
    }
}

void tampilDetailLayanan(NodeLayanan *l) {
    if (l != NULL) {
        cout << "ID        : " << l->info.idLayanan << endl;
        cout << "Nama      : " << l->info.nama << endl;
        cout << "Jenis     : " << l->info.jenis << endl;
        cout << "Deskripsi : " << l->info.deskripsi << endl;
        cout << "Status    : " << l->info.status << endl;
    }
}

// Mengembalikan true jika nama layanan sudah dipakai layanan lain
// (tidak peka huruf besar/kecil; idKecuali = layanan yang dikecualikan)
bool namaLayananTerdaftar(TreeLayanan root, string nama, string idKecuali) {
    bool ada = false;
    if (root != NULL) {
        ada = (kecil(root->info.nama) == kecil(nama) && root->info.idLayanan != idKecuali)
            || namaLayananTerdaftar(root->left, nama, idKecuali)
            || namaLayananTerdaftar(root->right, nama, idKecuali);
    }
    return ada;
}

// Mengembalikan alamat layanan pertama (urut ID) yang berjenis "dasar" dan
// berstatus "aktif", NULL jika tidak ada. Dipakai sebagai layanan pengalihan.
NodeLayanan* cariLayananDasarAktif(TreeLayanan root) {
    NodeLayanan *hasil = NULL;
    if (root != NULL) {
        hasil = cariLayananDasarAktif(root->left);
        if (hasil == NULL && root->info.jenis == "dasar" && root->info.status == "aktif") {
            hasil = root;
        }
        if (hasil == NULL) {
            hasil = cariLayananDasarAktif(root->right);
        }
    }
    return hasil;
}

// Mengembalikan angka ID layanan terbesar (node paling kanan), 0 jika kosong
int nomorTerbesarLayanan(TreeLayanan root) {
    NodeLayanan *cur = root;
    int nomor = 0;
    if (cur != NULL) {
        while (cur->right != NULL) {
            cur = cur->right;
        }
        nomor = stoi(cur->info.idLayanan.substr(2));
    }
    return nomor;
}

// =====================================================
//                    BST KELUHAN
// =====================================================

void createTreeKeluhan(TreeKeluhan &root) {
    root = NULL;
}

bool isEmptyKeluhan(TreeKeluhan root) {
    return root == NULL;
}

NodeKeluhan* alokasiKeluhan(Keluhan k) {
    NodeKeluhan *baru = new NodeKeluhan;
    baru->info = k;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

bool insertKeluhan(TreeKeluhan &root, Keluhan k) {
    bool berhasil = false;
    if (root == NULL) {
        root = alokasiKeluhan(k);
        berhasil = true;
    } else if (k.kode < root->info.kode) {
        berhasil = insertKeluhan(root->left, k);
    } else if (k.kode > root->info.kode) {
        berhasil = insertKeluhan(root->right, k);
    }
    return berhasil;
}

NodeKeluhan* searchKeluhan(TreeKeluhan root, string kode) {
    NodeKeluhan *cur = root;
    bool ketemu = false;
    while (cur != NULL && !ketemu) {
        if (kode == cur->info.kode) {
            ketemu = true;
        } else if (kode < cur->info.kode) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return cur;
}

bool deleteKeluhan(TreeKeluhan &root, string kode) {
    bool berhasil = false;
    NodeKeluhan *hapus;
    NodeKeluhan *pengganti;
    string kunciPengganti;
    if (root != NULL) {
        if (kode < root->info.kode) {
            berhasil = deleteKeluhan(root->left, kode);
        } else if (kode > root->info.kode) {
            berhasil = deleteKeluhan(root->right, kode);
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
                pengganti = terkecilKeluhan(root->right);
                kunciPengganti = pengganti->info.kode;
                root->info = pengganti->info;
                deleteKeluhan(root->right, kunciPengganti);
            }
        }
    }
    return berhasil;
}

void tampilKeluhan(TreeKeluhan root, TreeLayanan rootL) {
    NodeLayanan *tujuan;
    if (root != NULL) {
        tampilKeluhan(root->left, rootL);
        tujuan = searchLayanan(rootL, root->info.idLayanan);
        cout << root->info.kode << " | " << root->info.nama << " -> ";
        if (tujuan != NULL) {
            cout << tujuan->info.nama << " (" << tujuan->info.idLayanan << ")" << endl;
        } else {
            cout << "(layanan tidak ditemukan)" << endl;
        }
        tampilKeluhan(root->right, rootL);
    }
}

void tampilDetailKeluhan(NodeKeluhan *k, TreeLayanan rootL) {
    NodeLayanan *tujuan;
    if (k != NULL) {
        tujuan = searchLayanan(rootL, k->info.idLayanan);
        cout << "Kode            : " << k->info.kode << endl;
        cout << "Nama keluhan    : " << k->info.nama << endl;
        cout << "Layanan tujuan  : ";
        if (tujuan != NULL) {
            cout << tujuan->info.nama << " (" << tujuan->info.idLayanan << ")" << endl;
        } else {
            cout << k->info.idLayanan << endl;
        }
    }
}

bool namaKeluhanTerdaftar(TreeKeluhan root, string nama, string kodeKecuali) {
    bool ada = false;
    if (root != NULL) {
        ada = (kecil(root->info.nama) == kecil(nama) && root->info.kode != kodeKecuali)
            || namaKeluhanTerdaftar(root->left, nama, kodeKecuali)
            || namaKeluhanTerdaftar(root->right, nama, kodeKecuali);
    }
    return ada;
}

// Mengembalikan banyaknya keluhan yang menunjuk ke layanan tertentu
int jumlahKeluhanKeLayanan(TreeKeluhan root, string idLayanan) {
    int jumlah = 0;
    if (root != NULL) {
        jumlah = jumlahKeluhanKeLayanan(root->left, idLayanan)
                + jumlahKeluhanKeLayanan(root->right, idLayanan);
        if (root->info.idLayanan == idLayanan) {
            jumlah++;
        }
    }
    return jumlah;
}

int nomorTerbesarKeluhan(TreeKeluhan root) {
    NodeKeluhan *cur = root;
    int nomor = 0;
    if (cur != NULL) {
        while (cur->right != NULL) {
            cur = cur->right;
        }
        nomor = stoi(cur->info.kode.substr(2));
    }
    return nomor;
}

// Banyaknya booking yang mencatat keluhan tersebut.
// Saat ini selalu 0 karena modul Booking belum dibuat (diisi pada Tahap 3).
int jumlahBookingDenganKeluhan(string kode) {
    (void)kode;
    return 0;
}