#include <iostream>
#include "dokter.h"
using namespace std;

static NodeDokter* terkecilDokter(NodeDokter *root) {
    NodeDokter *cur = root;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

void createTreeDokter(TreeDokter &root) {
    root = NULL;
}

bool isEmptyDokter(TreeDokter root) {
    return root == NULL;
}

NodeDokter* alokasiDokter(Dokter d) {
    NodeDokter *baru = new NodeDokter;
    baru->info = d;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

bool insertDokter(TreeDokter &root, Dokter d) {
    bool berhasil = false;
    if (root == NULL) {
        root = alokasiDokter(d);
        berhasil = true;
    } else if (d.idDokter < root->info.idDokter) {
        berhasil = insertDokter(root->left, d);
    } else if (d.idDokter > root->info.idDokter) {
        berhasil = insertDokter(root->right, d);
    }
    return berhasil;
}

NodeDokter* searchDokter(TreeDokter root, string idDokter) {
    NodeDokter *cur = root;
    bool ketemu = false;
    while (cur != NULL && !ketemu) {
        if (idDokter == cur->info.idDokter) {
            ketemu = true;
        } else if (idDokter < cur->info.idDokter) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return cur;
}

bool deleteDokter(TreeDokter &root, string idDokter) {
    bool berhasil = false;
    NodeDokter *hapus;
    NodeDokter *pengganti;
    string kunciPengganti;
    if (root != NULL) {
        if (idDokter < root->info.idDokter) {
            berhasil = deleteDokter(root->left, idDokter);
        } else if (idDokter > root->info.idDokter) {
            berhasil = deleteDokter(root->right, idDokter);
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
                pengganti = terkecilDokter(root->right);
                kunciPengganti = pengganti->info.idDokter;
                root->info = pengganti->info;
                deleteDokter(root->right, kunciPengganti);
            }
        }
    }
    return berhasil;
}

void tampilDokter(TreeDokter root, TreeLayanan rootL) {
    NodeLayanan *lay;
    if (root != NULL) {
        tampilDokter(root->left, rootL);
        lay = searchLayanan(rootL, root->info.idLayanan);
        cout << root->info.idDokter << " | " << root->info.nama << " | ";
        if (lay != NULL) {
            cout << lay->info.nama;
        } else {
            cout << root->info.idLayanan;
        }
        cout << " | " << root->info.spesialisasi << " | " << root->info.status << endl;
        tampilDokter(root->right, rootL);
    }
}

void tampilDetailDokter(NodeDokter *d, TreeLayanan rootL) {
    NodeLayanan *lay;
    if (d != NULL) {
        lay = searchLayanan(rootL, d->info.idLayanan);
        cout << "ID           : " << d->info.idDokter << endl;
        cout << "Username     : " << d->info.username << endl;
        cout << "Nama         : " << d->info.nama << endl;
        cout << "Layanan      : ";
        if (lay != NULL) {
            cout << lay->info.nama << " (" << lay->info.idLayanan << ")" << endl;
        } else {
            cout << d->info.idLayanan << endl;
        }
        cout << "Spesialisasi : " << d->info.spesialisasi << endl;
        cout << "Telepon      : " << d->info.telepon << endl;
        cout << "Alamat       : " << d->info.alamat << endl;
        cout << "Status       : " << d->info.status << endl;
    }
}

int tampilDokterPerLayanan(TreeDokter root, string idLayanan, bool hanyaAktif) {
    int jumlah = 0;
    if (root != NULL) {
        jumlah = tampilDokterPerLayanan(root->left, idLayanan, hanyaAktif);
        if (root->info.idLayanan == idLayanan && (!hanyaAktif || root->info.status == "aktif")) {
            cout << "   - " << root->info.idDokter << " | " << root->info.nama;
            if (root->info.spesialisasi != "-") {
                cout << ", " << root->info.spesialisasi;
            }
            cout << endl;
            jumlah++;
        }
        jumlah = jumlah + tampilDokterPerLayanan(root->right, idLayanan, hanyaAktif);
    }
    return jumlah;
}

void tampilLayananDenganDokter(TreeLayanan rootL, TreeDokter rootD) {
    int jumlah;
    if (rootL != NULL) {
        tampilLayananDenganDokter(rootL->left, rootD);
        if (rootL->info.status == "aktif") {
            cout << rootL->info.nama << " (" << rootL->info.jenis << ")" << endl;
            jumlah = tampilDokterPerLayanan(rootD, rootL->info.idLayanan, true);
            if (jumlah == 0) {
                cout << "   (belum ada dokter aktif)" << endl;
            }
        }
        tampilLayananDenganDokter(rootL->right, rootD);
    }
}

// Mengembalikan banyaknya dokter (semua status) pada layanan tertentu
int jumlahDokterDiLayanan(TreeDokter root, string idLayanan) {
    int jumlah = 0;
    if (root != NULL) {
        jumlah = jumlahDokterDiLayanan(root->left, idLayanan)
                + jumlahDokterDiLayanan(root->right, idLayanan);
        if (root->info.idLayanan == idLayanan) {
            jumlah++;
        }
    }
    return jumlah;
}

// Mengembalikan banyaknya dokter berstatus aktif pada layanan tertentu
int jumlahDokterAktifDiLayanan(TreeDokter root, string idLayanan) {
    int jumlah = 0;
    if (root != NULL) {
        jumlah = jumlahDokterAktifDiLayanan(root->left, idLayanan)
                + jumlahDokterAktifDiLayanan(root->right, idLayanan);
        if (root->info.idLayanan == idLayanan && root->info.status == "aktif") {
            jumlah++;
        }
    }
    return jumlah;
}

// Banyaknya jadwal yang dimiliki dokter.
int jumlahJadwalDokter(string idDokter) {
    (void)idDokter;
    return 0;
}