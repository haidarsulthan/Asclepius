#include <iostream>
#include "admin.h"
#include "pilihKeluhan.h"
using namespace std;


void fiturMenyusul(string namaFitur) {
    cout << "[" << namaFitur << "] belum tersedia (menyusul)." << endl;
}

void dashboardAdmin(TreeUser &rootU, TreePasien &rootP, TreeDokter &rootD,
                    TreeLayanan &rootL, TreeKeluhan &rootK, User u) {
    string pilih;
    do {
        cout << "\n=== DASHBOARD ADMIN (" << u.username << ") ===" << endl;
        cout << "1. Buat akun Perawat" << endl;
        cout << "2. Lihat daftar akun" << endl;
        cout << "3. Kelola Pasien" << endl;
        cout << "4. Kelola Dokter" << endl;
        cout << "5. Kelola Layanan" << endl;
        cout << "6. Kelola Keluhan" << endl;
        cout << "7. Kelola Jadwal Dokter" << endl;
        cout << "8. Lihat Booking" << endl;
        cout << "9. Laporan" << endl;
        cout << "0. Logout" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            tambahAkunPerawat(rootU);
        } else if (pilih == "2") {
            cout << "\nusername | role | ID" << endl;
            tampilUser(rootU);
        } else if (pilih == "3") {
            menuKelolaPasien(rootP, rootU);
        } else if (pilih == "4") {
            menuKelolaDokter(rootD, rootL, rootU);
        } else if (pilih == "5") {
            menuKelolaLayanan(rootL, rootK, rootD);
        } else if (pilih == "6") {
            menuKelolaKeluhan(rootK, rootL);
        } else if (pilih == "7") {
            fiturMenyusul("Kelola Jadwal Dokter");
        } else if (pilih == "8") {
            fiturMenyusul("Lihat Booking");
        } else if (pilih == "9") {
            fiturMenyusul("Laporan");
        } else if (pilih != "0") {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != "0");
    cout << "Logout berhasil." << endl;
}

void dashboardDokter(TreeDokter rootD, TreeLayanan rootL, User u) {
    string pilih;
    NodeDokter *dataDokter = searchDokter(rootD, u.idPenghubung);
    NodeLayanan *lay = NULL;
    if (dataDokter != NULL) {
        lay = searchLayanan(rootL, dataDokter->info.idLayanan);
    }
    do {
        cout << "\n=== DASHBOARD DOKTER ===" << endl;
        if (dataDokter != NULL) {
            cout << "Selamat datang, " << dataDokter->info.nama;
            if (dataDokter->info.spesialisasi != "-") {
                cout << ", " << dataDokter->info.spesialisasi;
            }
            cout << " (" << dataDokter->info.idDokter << ")" << endl;
            if (lay != NULL) {
                cout << "Bertugas di: " << lay->info.nama << endl;
            }
        }
        cout << "1. Lihat jadwal periksa" << endl;
        cout << "2. Lihat pasien yang booking" << endl;
        cout << "3. Tandai booking selesai" << endl;
        cout << "4. Rujuk pasien" << endl;
        cout << "5. Riwayat booking" << endl;
        cout << "0. Logout" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            fiturMenyusul("Lihat jadwal periksa");
        } else if (pilih == "2") {
            fiturMenyusul("Lihat pasien yang booking");
        } else if (pilih == "3") {
            fiturMenyusul("Tandai booking selesai");
        } else if (pilih == "4") {
            fiturMenyusul("Rujuk pasien");
        } else if (pilih == "5") {
            fiturMenyusul("Riwayat booking");
        } else if (pilih != "0") {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != "0");
    cout << "Logout berhasil." << endl;
}

void dashboardPasien(TreePasien rootP, TreeLayanan rootL, TreeDokter rootD,
                    TreeKeluhan rootK, User u) {
    string pilih;
    NodePasien *dataPasien = searchPasien(rootP, u.idPenghubung);
    PilihanKeluhan pilihan;
    resetPilihan(pilihan);
    do {
        cout << "\n=== DASHBOARD PASIEN ===" << endl;
        if (dataPasien != NULL) {
            cout << "Selamat datang, " << dataPasien->info.nama
                << " (" << dataPasien->info.idPasien << ")" << endl;
        }
        tampilPilihanSingkat(pilihan, rootK, rootL);
        cout << "1. Pilih keluhan" << endl;
        cout << "2. Lihat layanan dan dokter" << endl;
        cout << "3. Booking jadwal periksa" << endl;
        cout << "4. Riwayat booking" << endl;
        cout << "5. Batalkan booking" << endl;
        cout << "0. Logout" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            pilihKeluhan(rootK, rootL, rootD, pilihan);
        } else if (pilih == "2") {
            cout << "\n--- Layanan dan dokter yang tersedia ---" << endl;
            tampilLayananDenganDokter(rootL, rootD);
        } else if (pilih == "3") {
            if (!sudahMemilih(pilihan)) {
                cout << "Pilih keluhan terlebih dahulu (menu 1)." << endl;
            } else {
                cout << "\nBooking akan memakai pilihan berikut:" << endl;
                tampilPilihan(pilihan, rootK, rootL);
                fiturMenyusul("Booking jadwal periksa");
            }
        } else if (pilih == "4") {
            fiturMenyusul("Riwayat booking");
        } else if (pilih == "5") {
            fiturMenyusul("Batalkan booking");
        } else if (pilih != "0") {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != "0");
    cout << "Logout berhasil." << endl;
}

void dashboardPerawat(User u) {
    string pilih;
    do {
        cout << "\n=== DASHBOARD PERAWAT (" << u.username << ", " << u.idPenghubung << ") ===" << endl;
        cout << "1. Lihat jadwal dokter per layanan" << endl;
        cout << "2. Lihat booking per layanan dan tanggal" << endl;
        cout << "3. Alihkan pasien ke layanan lain" << endl;
        cout << "0. Logout" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            fiturMenyusul("Lihat jadwal dokter per layanan");
        } else if (pilih == "2") {
            fiturMenyusul("Lihat booking per layanan dan tanggal");
        } else if (pilih == "3") {
            fiturMenyusul("Alihkan pasien ke layanan lain");
        } else if (pilih != "0") {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != "0");
    cout << "Logout berhasil." << endl;
}

int main() {
    TreeUser rootU;
    TreePasien rootP;
    TreeDokter rootD;
    TreeLayanan rootL;
    TreeKeluhan rootK;
    User userAktif;
    bool berhasil;
    string pilih;

    createTreeUser(rootU);
    createTreePasien(rootP);
    createTreeDokter(rootD);
    createTreeLayanan(rootL);
    createTreeKeluhan(rootK);
    isiDataAwalUser(rootU);
    isiDataAwalKlinik(rootL, rootK, rootD, rootU);

    do {
        cout << "\n=== KLINIK ASCLEPIUS ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Registrasi Pasien" << endl;
        cout << "0. Keluar" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            loginUser(rootU, berhasil, userAktif);
            if (berhasil) {
                if (userAktif.role == "Admin") {
                    dashboardAdmin(rootU, rootP, rootD, rootL, rootK, userAktif);
                } else if (userAktif.role == "Dokter") {
                    dashboardDokter(rootD, rootL, userAktif);
                } else if (userAktif.role == "Pasien") {
                    dashboardPasien(rootP, rootL, rootD, rootK, userAktif);
                } else if (userAktif.role == "Perawat") {
                    dashboardPerawat(userAktif);
                }
            }
        } else if (pilih == "2") {
            registrasiPasien(rootU, rootP);
        } else if (pilih != "0") {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != "0");

    cout << "Terima kasih." << endl;
    return 0;
};