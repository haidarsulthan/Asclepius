#include <iostream>
#include "admin.h"
using namespace std;


// Membaca ID dan mengubah huruf kecil menjadi besar (ly001 -> LY001)
static string bacaId(string prompt) {
    string s = bacaInput(prompt);
    size_t i;
    for (i = 0; i < s.length(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = (char)(s[i] - 32);
        }
    }
    return s;
}

static void pilihLayananAktif(TreeLayanan rootL, string &idLayanan, bool bolehKosong, bool &batal) {
    bool valid = false;
    NodeLayanan *n;
    batal = false;
    idLayanan = "";
    cout << "Daftar layanan aktif:" << endl;
    tampilLayananAktif(rootL);
    while (!valid && !batal) {
        if (bolehKosong) {
            idLayanan = bacaId("ID layanan (kosong = tetap, 0 = batal): ");
        } else {
            idLayanan = bacaId("ID layanan (0 = batal): ");
        }
        if (idLayanan == "0") {
            batal = true;
        } else if (idLayanan.empty() && bolehKosong) {
            valid = true;
        } else {
            n = searchLayanan(rootL, idLayanan);
            if (n == NULL || n->info.status != "aktif") {
                cout << "ID layanan tidak ditemukan atau tidak aktif." << endl;
            } else {
                valid = true;
            }
        }
    }
}

// Meminta pilihan status: 1 = aktif, 2 = nonaktif, kosong = tetap.
static void bacaStatusOpsional(string &statusBaru, bool &batal) {
    string s;
    bool valid = false;
    batal = false;
    statusBaru = "";
    while (!valid && !batal) {
        s = bacaInput("Status (1 = aktif, 2 = nonaktif, kosong = tetap, 0 = batal): ");
        if (s == "0") {
            batal = true;
        } else if (s.empty()) {
            valid = true;
        } else if (s == "1") {
            statusBaru = "aktif";
            valid = true;
        } else if (s == "2") {
            statusBaru = "nonaktif";
            valid = true;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}

// =====================================================
//                     DATA AWAL
// =====================================================

// Menyisipkan data[awal..akhir] dengan urutan elemen tengah lebih dulu
// agar BST awal seimbang (data terurut jika disisipkan berurutan akan
// membuat pohon miring seperti linked list).
static void isiLayananSeimbang(TreeLayanan &root, Layanan data[], int awal, int akhir) {
    int tengah;
    if (awal <= akhir) {
        tengah = (awal + akhir) / 2;
        insertLayanan(root, data[tengah]);
        isiLayananSeimbang(root, data, awal, tengah - 1);
        isiLayananSeimbang(root, data, tengah + 1, akhir);
    }
}

static void isiKeluhanSeimbang(TreeKeluhan &root, Keluhan data[], int awal, int akhir) {
    int tengah;
    if (awal <= akhir) {
        tengah = (awal + akhir) / 2;
        insertKeluhan(root, data[tengah]);
        isiKeluhanSeimbang(root, data, awal, tengah - 1);
        isiKeluhanSeimbang(root, data, tengah + 1, akhir);
    }
}

static void isiDokterSeimbang(TreeDokter &root, Dokter data[], int awal, int akhir) {
    int tengah;
    if (awal <= akhir) {
        tengah = (awal + akhir) / 2;
        insertDokter(root, data[tengah]);
        isiDokterSeimbang(root, data, awal, tengah - 1);
        isiDokterSeimbang(root, data, tengah + 1, akhir);
    }
}

void isiDataAwalKlinik(TreeLayanan &rootL, TreeKeluhan &rootK, TreeDokter &rootD, TreeUser &rootU) {
    Layanan lay[5] = {
        {"LY001", "Layanan Umum", "dasar", "Pemeriksaan umum oleh dokter umum (pintu masuk pelayanan)", "aktif"},
        {"LY002", "Layanan Gigi", "spesialistik", "Pemeriksaan dan perawatan gigi oleh dokter gigi spesialis", "aktif"},
        {"LY003", "Layanan Anak", "spesialistik", "Pemeriksaan kesehatan anak oleh dokter spesialis anak", "aktif"},
        {"LY004", "Layanan Mata", "spesialistik", "Pemeriksaan mata oleh dokter spesialis mata", "aktif"},
        {"LY005", "Layanan THT", "spesialistik", "Pemeriksaan telinga, hidung, dan tenggorokan oleh dokter spesialis THT", "aktif"}
    };
    Keluhan kel[19] = {
        {"KL001", "Lainnya / belum tahu", "LY001"},
        {"KL002", "Demam", "LY001"},
        {"KL003", "Batuk dan pilek", "LY001"},
        {"KL004", "Sakit kepala", "LY001"},
        {"KL005", "Nyeri perut", "LY001"},
        {"KL006", "Sakit gigi", "LY002"},
        {"KL007", "Gusi bengkak atau berdarah", "LY002"},
        {"KL008", "Gigi berlubang", "LY002"},
        {"KL009", "Gigi goyang", "LY002"},
        {"KL010", "Anak demam", "LY003"},
        {"KL011", "Imunisasi anak", "LY003"},
        {"KL012", "Gangguan tumbuh kembang", "LY003"},
        {"KL013", "Mata merah", "LY004"},
        {"KL014", "Pandangan kabur", "LY004"},
        {"KL015", "Mata berair", "LY004"},
        {"KL016", "Nyeri tenggorokan", "LY005"},
        {"KL017", "Telinga berdenging", "LY005"},
        {"KL018", "Hidung tersumbat", "LY005"},
        {"KL019", "Gangguan pendengaran", "LY005"}
    };
    Dokter dok[4] = {
        {"DK001", "dokter01", "dr. Andi Pratama", "LY001", "-", "081200000001", "Jl. Melati No. 1", "aktif"},
        {"DK002", "dokter02", "dr. Sari Wulandari", "LY003", "Sp.A", "081200000002", "Jl. Mawar No. 2", "aktif"},
        {"DK003", "dokter03", "drg. Budi Hartono", "LY002", "Sp.KG", "081200000003", "Jl. Kenanga No. 3", "aktif"},
        {"DK004", "dokter04", "dr. Maya Putri", "LY004", "Sp.M", "081200000004", "Jl. Anggrek No. 4", "aktif"}
    };
    int i;
    User u;

    isiLayananSeimbang(rootL, lay, 0, 4);
    isiKeluhanSeimbang(rootK, kel, 0, 18);
    for (i = 0; i < 4; i++) {
        u.username = dok[i].username;
        u.passwordHash = hashPassword(dok[i].username, "dokter123");
        u.role = "Dokter";
        u.idPenghubung = dok[i].idDokter;
        insertUser(rootU, u);
    }
    isiDokterSeimbang(rootD, dok, 0, 3);
}

// =====================================================
//                    KELOLA LAYANAN
// =====================================================

static void tambahLayanan(TreeLayanan &rootL) {
    Layanan l;
    bool batal = false;
    bool valid = false;
    string pilih;
    int nomor;

    cout << "\n--- Tambah Layanan ---" << endl;
    while (!valid && !batal) {
        l.nama = bacaTeks("Nama layanan (maks. 30 karakter, 0 = batal): ", 30, false, batal);
        if (!batal) {
            if (namaLayananTerdaftar(rootL, l.nama, "")) {
                cout << "Nama layanan sudah ada." << endl;
            } else {
                valid = true;
            }
        }
    }

    valid = false;
    while (!valid && !batal) {
        cout << "Jenis: 1. dasar (dokter umum)  2. spesialistik (dokter spesialis)" << endl;
        pilih = bacaInput("Pilih jenis (0 = batal): ");
        if (pilih == "1") {
            l.jenis = "dasar";
            valid = true;
        } else if (pilih == "2") {
            l.jenis = "spesialistik";
            valid = true;
        } else if (pilih == "0") {
            batal = true;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    if (!batal) {
        l.deskripsi = bacaTeks("Deskripsi (maks. 100 karakter, 0 = batal): ", 100, false, batal);
    }

    if (batal) {
        cout << "Penambahan layanan dibatalkan." << endl;
    } else {
        nomor = nomorTerbesarLayanan(rootL) + 1;
        if (nomor > 999) {
            cout << "Kapasitas ID layanan penuh." << endl;
        } else {
            l.idLayanan = buatId("LY", nomor);
            l.status = "aktif";
            insertLayanan(rootL, l);
            cout << "Layanan berhasil ditambahkan dengan ID " << l.idLayanan << "." << endl;
        }
    }
}

static void cariLayanan(TreeLayanan rootL) {
    string id = bacaId("ID layanan (0 = batal): ");
    NodeLayanan *n;
    if (id != "0") {
        n = searchLayanan(rootL, id);
        if (n == NULL) {
            cout << "Layanan tidak ditemukan." << endl;
        } else {
            tampilDetailLayanan(n);
        }
    }
}

static void ubahLayanan(TreeLayanan &rootL) {
    string id = bacaId("ID layanan yang diubah (0 = batal): ");
    NodeLayanan *n;
    string namaBaru = "", deskBaru = "", statusBaru = "", tmp;
    bool batal = false;
    bool valid;

    if (id != "0") {
        n = searchLayanan(rootL, id);
        if (n == NULL) {
            cout << "Layanan tidak ditemukan." << endl;
        } else {
            tampilDetailLayanan(n);
            cout << "Kosongkan isian untuk tidak mengubah." << endl;

            valid = false;
            while (!valid && !batal) {
                tmp = bacaTeks("Nama baru: ", 30, true, batal);
                if (!batal) {
                    if (tmp.empty()) {
                        valid = true;
                    } else if (namaLayananTerdaftar(rootL, tmp, n->info.idLayanan)) {
                        cout << "Nama layanan sudah ada." << endl;
                    } else {
                        namaBaru = tmp;
                        valid = true;
                    }
                }
            }
            if (!batal) {
                deskBaru = bacaTeks("Deskripsi baru: ", 100, true, batal);
            }
            valid = false;
            while (!valid && !batal) {
                bacaStatusOpsional(statusBaru, batal);
                if (!batal) {
                    if (statusBaru == "nonaktif" && n->info.jenis == "dasar") {
                        cout << "Layanan dasar harus tetap aktif (menjadi pintu masuk pelayanan)." << endl;
                        statusBaru = "";
                    } else {
                        valid = true;
                    }
                }
            }

            if (batal) {
                cout << "Perubahan dibatalkan." << endl;
            } else {
                if (!namaBaru.empty()) {
                    n->info.nama = namaBaru;
                }
                if (!deskBaru.empty()) {
                    n->info.deskripsi = deskBaru;
                }
                if (!statusBaru.empty()) {
                    n->info.status = statusBaru;
                }
                cout << "Data layanan berhasil diubah." << endl;
            }
        }
    }
}

static void hapusLayanan(TreeLayanan &rootL, TreeKeluhan rootK, TreeDokter rootD) {
    string id = bacaId("ID layanan yang dihapus (0 = batal): ");
    NodeLayanan *n;
    if (id != "0") {
        n = searchLayanan(rootL, id);
        if (n == NULL) {
            cout << "Layanan tidak ditemukan." << endl;
        } else if (n->info.jenis == "dasar") {
            cout << "Ditolak: layanan dasar tidak dapat dihapus karena menjadi pintu masuk pelayanan." << endl;
        } else if (jumlahDokterDiLayanan(rootD, id) > 0) {
            cout << "Ditolak: masih ada dokter yang bertugas di layanan ini." << endl;
        } else if (jumlahKeluhanKeLayanan(rootK, id) > 0) {
            cout << "Ditolak: masih ada keluhan yang diarahkan ke layanan ini." << endl;
        } else {
            tampilDetailLayanan(n);
            if (bacaYaTidak("Yakin menghapus layanan ini?")) {
                deleteLayanan(rootL, id);
                cout << "Layanan berhasil dihapus." << endl;
            } else {
                cout << "Penghapusan dibatalkan." << endl;
            }
        }
    }
}

void menuKelolaLayanan(TreeLayanan &rootL, TreeKeluhan rootK, TreeDokter rootD) {
    string pilih;
    do {
        cout << "\n=== KELOLA LAYANAN ===" << endl;
        cout << "1. Tambah layanan" << endl;
        cout << "2. Lihat semua layanan" << endl;
        cout << "3. Cari layanan berdasarkan ID" << endl;
        cout << "4. Ubah layanan" << endl;
        cout << "5. Hapus layanan" << endl;
        cout << "0. Kembali" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            tambahLayanan(rootL);
        } else if (pilih == "2") {
            cout << "\nID | nama | jenis | status" << endl;
            tampilLayanan(rootL);
        } else if (pilih == "3") {
            cariLayanan(rootL);
        } else if (pilih == "4") {
            ubahLayanan(rootL);
        } else if (pilih == "5") {
            hapusLayanan(rootL, rootK, rootD);
        } else if (pilih != "0") {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != "0");
}

// =====================================================
//                    KELOLA KELUHAN
// =====================================================

static void tambahKeluhan(TreeKeluhan &rootK, TreeLayanan rootL) {
    Keluhan k;
    bool batal = false;
    bool valid = false;
    int nomor;

    cout << "\n--- Tambah Keluhan ---" << endl;
    while (!valid && !batal) {
        k.nama = bacaTeks("Nama keluhan (maks. 40 karakter, 0 = batal): ", 40, false, batal);
        if (!batal) {
            if (namaKeluhanTerdaftar(rootK, k.nama, "")) {
                cout << "Nama keluhan sudah ada." << endl;
            } else {
                valid = true;
            }
        }
    }
    if (!batal) {
        cout << "Pilih layanan tujuan untuk keluhan ini." << endl;
        pilihLayananAktif(rootL, k.idLayanan, false, batal);
    }

    if (batal) {
        cout << "Penambahan keluhan dibatalkan." << endl;
    } else {
        nomor = nomorTerbesarKeluhan(rootK) + 1;
        if (nomor > 999) {
            cout << "Kapasitas kode keluhan penuh." << endl;
        } else {
            k.kode = buatId("KL", nomor);
            insertKeluhan(rootK, k);
            cout << "Keluhan berhasil ditambahkan dengan kode " << k.kode << "." << endl;
        }
    }
}

static void cariKeluhan(TreeKeluhan rootK, TreeLayanan rootL) {
    string kode = bacaId("Kode keluhan (0 = batal): ");
    NodeKeluhan *n;
    if (kode != "0") {
        n = searchKeluhan(rootK, kode);
        if (n == NULL) {
            cout << "Keluhan tidak ditemukan." << endl;
        } else {
            tampilDetailKeluhan(n, rootL);
        }
    }

}
static void ubahKeluhan(TreeKeluhan &rootK, TreeLayanan rootL) {
    string kode = bacaId("Kode keluhan yang diubah (0 = batal): ");
    NodeKeluhan *n;
    string namaBaru = "", layananBaru = "", tmp;
    bool batal = false;
    bool valid;

    if (kode != "0") {
        n = searchKeluhan(rootK, kode);
        if (n == NULL) {
            cout << "Keluhan tidak ditemukan." << endl;
        } else {
            tampilDetailKeluhan(n, rootL);
            cout << "Kosongkan isian untuk tidak mengubah." << endl;

            valid = false;
            while (!valid && !batal) {
                tmp = bacaTeks("Nama baru: ", 40, true, batal);
                if (!batal) {
                    if (tmp.empty()) {
                        valid = true;
                    } else if (namaKeluhanTerdaftar(rootK, tmp, n->info.kode)) {
                        cout << "Nama keluhan sudah ada." << endl;
                    } else {
                        namaBaru = tmp;
                        valid = true;
                    }
                }
            }
            if (!batal) {
                if (n->info.kode == "KL001") {
                    cout << "Layanan tujuan keluhan KL001 tidak dapat diubah." << endl;
                } else {
                    pilihLayananAktif(rootL, layananBaru, true, batal);
                }
            }

            if (batal) {
                cout << "Perubahan dibatalkan." << endl;
            } else {
                if (!namaBaru.empty()) {
                    n->info.nama = namaBaru;
                }
                if (!layananBaru.empty()) {
                    n->info.idLayanan = layananBaru;
                }
                cout << "Data keluhan berhasil diubah." << endl;
            }
        }
    }
}

static void hapusKeluhan(TreeKeluhan &rootK, TreeLayanan rootL) {
    string kode = bacaId("Kode keluhan yang dihapus (0 = batal): ");
    NodeKeluhan *n;
    if (kode != "0") {
        n = searchKeluhan(rootK, kode);
        if (n == NULL) {
            cout << "Keluhan tidak ditemukan." << endl;
        } else if (kode == "KL001") {
            cout << "Ditolak: keluhan KL001 (Lainnya) dibutuhkan sebagai pilihan bawaan." << endl;
        } else if (jumlahBookingDenganKeluhan(kode) > 0) {
            cout << "Ditolak: keluhan sudah tercatat pada booking." << endl;
        } else {
            tampilDetailKeluhan(n, rootL);
            if (bacaYaTidak("Yakin menghapus keluhan ini?")) {
                deleteKeluhan(rootK, kode);
                cout << "Keluhan berhasil dihapus." << endl;
            } else {
                cout << "Penghapusan dibatalkan." << endl;
            }
        }
    }
}

void menuKelolaKeluhan(TreeKeluhan &rootK, TreeLayanan rootL) {
    string pilih;
    do {
        cout << "\n=== KELOLA KELUHAN ===" << endl;
        cout << "1. Tambah keluhan" << endl;
        cout << "2. Lihat semua keluhan" << endl;
        cout << "3. Cari keluhan berdasarkan kode" << endl;
        cout << "4. Ubah keluhan" << endl;
        cout << "5. Hapus keluhan" << endl;
        cout << "0. Kembali" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            tambahKeluhan(rootK, rootL);
        } else if (pilih == "2") {
            cout << "\nkode | keluhan -> layanan tujuan" << endl;
            tampilKeluhan(rootK, rootL);
        } else if (pilih == "3") {
            cariKeluhan(rootK, rootL);
        } else if (pilih == "4") {
            ubahKeluhan(rootK, rootL);
        } else if (pilih == "5") {
            hapusKeluhan(rootK, rootL);
        } else if (pilih != "0") {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != "0");
}

// =====================================================
//                     KELOLA DOKTER
// =====================================================

static void tambahDokter(TreeDokter &rootD, TreeLayanan rootL, TreeUser &rootU) {
    Dokter d;
    string username, password;
    bool batal = false;
    bool valid;
    int nomor;
    NodeLayanan *lay;
    User u;

    cout << "\n--- Tambah Dokter (beserta akun login) ---" << endl;
    inputKredensial(rootU, username, password, batal);

    valid = false;
    while (!valid && !batal) {
        d.nama = bacaTeks("Nama dokter (mis. dr. Andi Pratama, 0 = batal): ", 50, false, batal);
        if (!batal) {
            if (isNamaValid(d.nama)) {
                valid = true;
            } else {
                cout << "Nama hanya boleh huruf, spasi, titik, atau apostrof." << endl;
            }
        }
    }

    if (!batal) {
        pilihLayananAktif(rootL, d.idLayanan, false, batal);
    }

    if (!batal) {
        lay = searchLayanan(rootL, d.idLayanan);
        if (lay->info.jenis == "spesialistik") {
            d.spesialisasi = bacaTeks("Spesialisasi (mis. Sp.A, maks. 20 karakter, 0 = batal): ", 20, false, batal);
        } else {
            d.spesialisasi = "-";
            cout << "Layanan dasar: dokter umum (spesialisasi diisi \"-\")." << endl;
        }
    }

    valid = false;
    while (!valid && !batal) {
        d.telepon = bacaInput("Telepon (10-13 digit, 0 = batal): ");
        if (d.telepon == "0") {
            batal = true;
        } else if (isTeleponValid(d.telepon)) {
            valid = true;
        } else {
            cout << "Telepon harus 10-13 digit angka." << endl;
        }
    }

    if (!batal) {
        d.alamat = bacaTeks("Alamat (maks. 100 karakter, 0 = batal): ", 100, false, batal);
    }

    if (batal) {
        cout << "Penambahan dokter dibatalkan." << endl;
    } else {
        nomor = nomorTerbesarRole(rootU, "Dokter") + 1;
        if (nomor > 999) {
            cout << "Kapasitas ID dokter penuh. Dokter tidak ditambahkan." << endl;
        } else {
            d.idDokter = buatId("DK", nomor);
            d.username = username;
            d.status = "aktif";
            insertDokter(rootD, d);

            u.username = username;
            u.passwordHash = hashPassword(username, password);
            u.role = "Dokter";
            u.idPenghubung = d.idDokter;
            insertUser(rootU, u);

            cout << "Dokter berhasil ditambahkan. ID: " << d.idDokter
                << ", username: " << username << endl;
        }
    }
}

static void cariDokter(TreeDokter rootD, TreeLayanan rootL) {
    string id = bacaId("ID dokter (0 = batal): ");
    NodeDokter *n;
    if (id != "0") {
        n = searchDokter(rootD, id);
        if (n == NULL) {
            cout << "Dokter tidak ditemukan." << endl;
        } else {
            tampilDetailDokter(n, rootL);
        }
    }
}

static void lihatDokterPerLayanan(TreeDokter rootD, TreeLayanan rootL) {
    string id = bacaId("ID layanan (0 = batal): ");
    NodeLayanan *lay;
    int jumlah;
    if (id != "0") {
        lay = searchLayanan(rootL, id);
        if (lay == NULL) {
            cout << "Layanan tidak ditemukan." << endl;
        } else {
            cout << "Dokter pada " << lay->info.nama << ":" << endl;
            jumlah = tampilDokterPerLayanan(rootD, id, false);
            if (jumlah == 0) {
                cout << "   (belum ada dokter)" << endl;
            }
        }
    }
}

static void ubahDokter(TreeDokter &rootD, TreeLayanan rootL) {
    string id = bacaId("ID dokter yang diubah (0 = batal): ");
    NodeDokter *n;
    NodeLayanan *layEfektif;
    string namaBaru = "", layananBaru = "", spesBaru = "", telpBaru = "", alamatBaru = "", statusBaru = "", tmp;
    bool batal = false;
    bool valid;

    if (id != "0") {
        n = searchDokter(rootD, id);
        if (n == NULL) {
            cout << "Dokter tidak ditemukan." << endl;
        } else {
            tampilDetailDokter(n, rootL);
            cout << "Kosongkan isian untuk tidak mengubah." << endl;

            valid = false;
            while (!valid && !batal) {
                tmp = bacaTeks("Nama baru: ", 50, true, batal);
                if (!batal) {
                    if (tmp.empty()) {
                        valid = true;
                    } else if (isNamaValid(tmp)) {
                        namaBaru = tmp;
                        valid = true;
                    } else {
                        cout << "Nama hanya boleh huruf, spasi, titik, atau apostrof." << endl;
                    }
                }
            }

            if (!batal) {
                pilihLayananAktif(rootL, layananBaru, true, batal);
            }

            if (!batal) {
                if (layananBaru.empty()) {
                    layEfektif = searchLayanan(rootL, n->info.idLayanan);
                } else {
                    layEfektif = searchLayanan(rootL, layananBaru);
                }
                spesBaru = n->info.spesialisasi;
                if (layEfektif != NULL && layEfektif->info.jenis == "dasar") {
                    spesBaru = "-";
                } else {
                    valid = false;
                    while (!valid && !batal) {
                        tmp = bacaTeks("Spesialisasi baru: ", 20, true, batal);
                        if (!batal) {
                            if (!tmp.empty()) {
                                spesBaru = tmp;
                                valid = true;
                            } else if (spesBaru != "-") {
                                valid = true;
                            } else {
                                cout << "Dokter spesialis wajib memiliki spesialisasi." << endl;
                            }
                        }
                    }
                }
            }

            valid = false;
            while (!valid && !batal) {
                tmp = bacaTeks("Telepon baru: ", 13, true, batal);
                if (!batal) {
                    if (tmp.empty()) {
                        valid = true;
                    } else if (isTeleponValid(tmp)) {
                        telpBaru = tmp;
                        valid = true;
                    } else {
                        cout << "Telepon harus 10-13 digit angka." << endl;
                    }
                }
            }

            if (!batal) {
                alamatBaru = bacaTeks("Alamat baru: ", 100, true, batal);
            }
            if (!batal) {
                bacaStatusOpsional(statusBaru, batal);
            }

            if (batal) {
                cout << "Perubahan dibatalkan." << endl;
            } else {
                if (!namaBaru.empty()) {
                    n->info.nama = namaBaru;
                }
                if (!layananBaru.empty()) {
                    n->info.idLayanan = layananBaru;
                }
                n->info.spesialisasi = spesBaru;
                if (!telpBaru.empty()) {
                    n->info.telepon = telpBaru;
                }
                if (!alamatBaru.empty()) {
                    n->info.alamat = alamatBaru;
                }
                if (!statusBaru.empty()) {
                    n->info.status = statusBaru;
                }
                cout << "Data dokter berhasil diubah." << endl;
            }
        }
    }
}

static void hapusDokter(TreeDokter &rootD, TreeLayanan rootL, TreeUser &rootU) {
    string id = bacaId("ID dokter yang dihapus (0 = batal): ");
    NodeDokter *n;
    string username;
    if (id != "0") {
        n = searchDokter(rootD, id);
        if (n == NULL) {
            cout << "Dokter tidak ditemukan." << endl;
        } else if (jumlahJadwalDokter(id) > 0) {
            cout << "Ditolak: dokter masih memiliki jadwal. Hapus jadwalnya terlebih dahulu." << endl;
        } else {
            tampilDetailDokter(n, rootL);
            if (bacaYaTidak("Yakin menghapus dokter dan akun loginnya?")) {
                username = n->info.username;
                deleteDokter(rootD, id);
                deleteUser(rootU, username);
                cout << "Dokter dan akun login berhasil dihapus." << endl;
            } else {
                cout << "Penghapusan dibatalkan." << endl;
            }
        }
    }
}

void menuKelolaDokter(TreeDokter &rootD, TreeLayanan rootL, TreeUser &rootU) {
    string pilih;
    do {
        cout << "\n=== KELOLA DOKTER ===" << endl;
        cout << "1. Tambah dokter (beserta akun login)" << endl;
        cout << "2. Lihat semua dokter" << endl;
        cout << "3. Cari dokter berdasarkan ID" << endl;
        cout << "4. Lihat dokter per layanan" << endl;
        cout << "5. Ubah dokter" << endl;
        cout << "6. Hapus dokter" << endl;
        cout << "0. Kembali" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            tambahDokter(rootD, rootL, rootU);
        } else if (pilih == "2") {
            cout << "\nID | nama | layanan | spesialisasi | status" << endl;
            tampilDokter(rootD, rootL);
        } else if (pilih == "3") {
            cariDokter(rootD, rootL);
        } else if (pilih == "4") {
            lihatDokterPerLayanan(rootD, rootL);
        } else if (pilih == "5") {
            ubahDokter(rootD, rootL);
        } else if (pilih == "6") {
            hapusDokter(rootD, rootL, rootU);
        } else if (pilih != "0") {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != "0");
}

// =====================================================
//                     KELOLA PASIEN
// =====================================================

static void cariPasienId(TreePasien rootP) {
    string id = bacaId("ID pasien (0 = batal): ");
    NodePasien *n;
    if (id != "0") {
        n = searchPasien(rootP, id);
        if (n == NULL) {
            cout << "Pasien tidak ditemukan." << endl;
        } else {
            tampilDetailPasien(n);
        }
    }
}

static void cariPasienNik(TreePasien rootP) {
    string nik = bacaInput("NIK (0 = batal): ");
    NodePasien *n;
    if (nik != "0") {
        n = searchPasienByNik(rootP, nik);
        if (n == NULL) {
            cout << "Pasien tidak ditemukan." << endl;
        } else {
            tampilDetailPasien(n);
        }
    }
}

static void cariPasienNama(TreePasien rootP) {
    string kata = bacaInput("Kata kunci nama (0 = batal): ");
    int jumlah;
    if (kata != "0") {
        cout << "\nID | nama | NIK | telepon" << endl;
        jumlah = cariPasienByNama(rootP, kata);
        if (jumlah == 0) {
            cout << "Tidak ada pasien yang cocok." << endl;
        }
    }
}

static void ubahPasien(TreePasien &rootP) {
    string id = bacaId("ID pasien yang diubah (0 = batal): ");
    NodePasien *n;
    string namaBaru = "", nikBaru = "", telpBaru = "", tmp;
    bool batal = false;
    bool valid;

    if (id != "0") {
        n = searchPasien(rootP, id);
        if (n == NULL) {
            cout << "Pasien tidak ditemukan." << endl;
        } else {
            tampilDetailPasien(n);
            cout << "Kosongkan isian untuk tidak mengubah." << endl;

            valid = false;
            while (!valid && !batal) {
                tmp = bacaTeks("Nama baru: ", 50, true, batal);
                if (!batal) {
                    if (tmp.empty()) {
                        valid = true;
                    } else if (isNamaValid(tmp)) {
                        namaBaru = tmp;
                        valid = true;
                    } else {
                        cout << "Nama hanya boleh huruf, spasi, titik, atau apostrof." << endl;
                    }
                }
            }
            valid = false;
            while (!valid && !batal) {
                tmp = bacaTeks("NIK baru: ", 16, true, batal);
                if (!batal) {
                    if (tmp.empty()) {
                        valid = true;
                    } else if (!isNikValid(tmp)) {
                        cout << "NIK harus tepat 16 digit angka." << endl;
                    } else if (nikDipakaiOrangLain(rootP, tmp, n->info.idPasien)) {
                        cout << "NIK sudah dipakai pasien lain." << endl;
                    } else {
                        nikBaru = tmp;
                        valid = true;
                    }
                }
            }
            valid = false;
            while (!valid && !batal) {
                tmp = bacaTeks("Telepon baru: ", 13, true, batal);
                if (!batal) {
                    if (tmp.empty()) {
                        valid = true;
                    } else if (isTeleponValid(tmp)) {
                        telpBaru = tmp;
                        valid = true;
                    } else {
                        cout << "Telepon harus 10-13 digit angka." << endl;
                    }
                }
            }

            if (batal) {
                cout << "Perubahan dibatalkan." << endl;
            } else {
                if (!namaBaru.empty()) {
                    n->info.nama = namaBaru;
                }
                if (!nikBaru.empty()) {
                    n->info.nik = nikBaru;
                }
                if (!telpBaru.empty()) {
                    n->info.telepon = telpBaru;
                }
                cout << "Data pasien berhasil diubah." << endl;
            }
        }
    }
}

static void hapusPasien(TreePasien &rootP, TreeUser &rootU) {
    string id = bacaId("ID pasien yang dihapus (0 = batal): ");
    NodePasien *n;
    string username;
    if (id != "0") {
        n = searchPasien(rootP, id);
        if (n == NULL) {
            cout << "Pasien tidak ditemukan." << endl;
        } else if (jumlahBookingAktifPasien(id) > 0) {
            cout << "Ditolak: pasien masih memiliki booking aktif." << endl;
        } else {
            tampilDetailPasien(n);
            if (bacaYaTidak("Yakin menghapus pasien dan akun loginnya?")) {
                username = n->info.username;
                deletePasien(rootP, id);
                deleteUser(rootU, username);
                cout << "Pasien dan akun login berhasil dihapus." << endl;
            } else {
                cout << "Penghapusan dibatalkan." << endl;
            }
        }
    }
}

void menuKelolaPasien(TreePasien &rootP, TreeUser &rootU) {
    string pilih;
    do {
        cout << "\n=== KELOLA PASIEN ===" << endl;
        cout << "1. Lihat semua pasien" << endl;
        cout << "2. Cari pasien berdasarkan ID" << endl;
        cout << "3. Cari pasien berdasarkan NIK" << endl;
        cout << "4. Cari pasien berdasarkan nama" << endl;
        cout << "5. Ubah data pasien" << endl;
        cout << "6. Hapus pasien" << endl;
        cout << "0. Kembali" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            cout << "\nID | nama | NIK | telepon" << endl;
            tampilPasien(rootP);
        } else if (pilih == "2") {
            cariPasienId(rootP);
        } else if (pilih == "3") {
            cariPasienNik(rootP);
        } else if (pilih == "4") {
            cariPasienNama(rootP);
        } else if (pilih == "5") {
            ubahPasien(rootP);
        } else if (pilih == "6") {
            hapusPasien(rootP, rootU);
        } else if (pilih != "0") {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != "0");
}