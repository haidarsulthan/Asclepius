#include <iostream>
#include "user.h"
#include "pasien.h"
using namespace std;

// ---------- kerangka dashboard (isi fitur menyusul) ----------

// I.S.: sembarang
// F.S.: pesan bahwa fitur belum tersedia tercetak
void fiturMenyusul(string namaFitur) {
    cout << "[" << namaFitur << "] belum tersedia (menyusul)." << endl;
}

// I.S.: rootU terdefinisi, u adalah akun Admin yang sedang login
// F.S.: menu Admin ditampilkan sampai Admin memilih logout (0)
void dashboardAdmin(TreeUser &rootU, User u) {
    string pilih;
    do {
        cout << "\n=== DASHBOARD ADMIN (" << u.username << ") ===" << endl;
        cout << "1. Buat akun Dokter / Perawat" << endl;
        cout << "2. Lihat daftar akun" << endl;
        cout << "3. Kelola Pasien" << endl;
        cout << "4. Kelola Dokter" << endl;
        cout << "5. Kelola Layanan dan Keluhan" << endl;
        cout << "6. Kelola Jadwal Dokter" << endl;
        cout << "7. Lihat Booking" << endl;
        cout << "8. Laporan" << endl;
        cout << "0. Logout" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            tambahAkunStaf(rootU);
        } else if (pilih == "2") {
            cout << "\nusername | role | ID" << endl;
            tampilUser(rootU);
        } else if (pilih == "3") {
            fiturMenyusul("Kelola Pasien");
        } else if (pilih == "4") {
            fiturMenyusul("Kelola Dokter");
        } else if (pilih == "5") {
            fiturMenyusul("Kelola Layanan dan Keluhan");
        } else if (pilih == "6") {
            fiturMenyusul("Kelola Jadwal Dokter");
        } else if (pilih == "7") {
            fiturMenyusul("Lihat Booking");
        } else if (pilih == "8") {
            fiturMenyusul("Laporan");
        } else if (pilih != "0") {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != "0");
    cout << "Logout berhasil." << endl;
}

// I.S.: u adalah akun Dokter yang sedang login
// F.S.: menu Dokter ditampilkan sampai Dokter memilih logout (0)
void dashboardDokter(User u) {
    string pilih;
    do {
        cout << "\n=== DASHBOARD DOKTER (" << u.username << ", " << u.idPenghubung << ") ===" << endl;
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

// I.S.: rootP terdefinisi, u adalah akun Pasien yang sedang login
// F.S.: menu Pasien ditampilkan sampai Pasien memilih logout (0)
void dashboardPasien(TreePasien rootP, User u) {
    string pilih;
    NodePasien *dataPasien = searchPasien(rootP, u.idPenghubung);
    do {
        cout << "\n=== DASHBOARD PASIEN ===" << endl;
        if (dataPasien != NULL) {
            cout << "Selamat datang, " << dataPasien->info.nama
                 << " (" << dataPasien->info.idPasien << ")" << endl;
        }
        cout << "1. Pilih keluhan" << endl;
        cout << "2. Lihat layanan, dokter, dan jadwal" << endl;
        cout << "3. Booking jadwal periksa" << endl;
        cout << "4. Riwayat booking" << endl;
        cout << "5. Batalkan booking" << endl;
        cout << "0. Logout" << endl;
        pilih = bacaInput("Pilihan: ");

        if (pilih == "1") {
            fiturMenyusul("Pilih keluhan");
        } else if (pilih == "2") {
            fiturMenyusul("Lihat layanan, dokter, dan jadwal");
        } else if (pilih == "3") {
            fiturMenyusul("Booking jadwal periksa");
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

// I.S.: u adalah akun Perawat yang sedang login
// F.S.: menu Perawat ditampilkan sampai Perawat memilih logout (0)
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

// ---------- program utama ----------
int main() {
    TreeUser rootU;
    TreePasien rootP;
    User userAktif;
    bool berhasil;
    string pilih;

    createTreeUser(rootU);
    createTreePasien(rootP);
    isiDataAwalUser(rootU);

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
                    dashboardAdmin(rootU, userAktif);
                } else if (userAktif.role == "Dokter") {
                    dashboardDokter(userAktif);
                } else if (userAktif.role == "Pasien") {
                    dashboardPasien(rootP, userAktif);
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
}