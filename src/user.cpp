#include <iostream>
#include "user.h"
using namespace std;

static bool isAlnum(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}


void createTreeUser(TreeUser &root) {
    root = NULL;
}

bool isEmptyUser(TreeUser root) {
    return root == NULL;
}

NodeUser* alokasiUser(User u) {
    NodeUser *baru = new NodeUser;
    baru->info = u;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

bool insertUser(TreeUser &root, User u) {
    bool berhasil = false;
    if (root == NULL) {
        root = alokasiUser(u);
        berhasil = true;
    } else if (u.username < root->info.username) {
        berhasil = insertUser(root->left, u);
    } else if (u.username > root->info.username) {
        berhasil = insertUser(root->right, u);
    }
    return berhasil;
}

static NodeUser* terkecilUser(NodeUser *root) {
    NodeUser *cur = root;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

NodeUser* searchUser(TreeUser root, string username) {
    NodeUser *cur = root;
    bool ketemu = false;
    while (cur != NULL && !ketemu) {
        if (username == cur->info.username) {
            ketemu = true;
        } else if (username < cur->info.username) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return cur;
}

bool deleteUser(TreeUser &root, string username) {
    bool berhasil = false;
    NodeUser *hapus;
    NodeUser *pengganti;
    string kunciPengganti;
    if (root != NULL) {
        if (username < root->info.username) {
            berhasil = deleteUser(root->left, username);
        } else if (username > root->info.username) {
            berhasil = deleteUser(root->right, username);
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
                pengganti = terkecilUser(root->right);
                kunciPengganti = pengganti->info.username;
                root->info = pengganti->info;
                deleteUser(root->right, kunciPengganti);
            }
        }
    }
    return berhasil;
}

void tampilUser(TreeUser root) {
    if (root != NULL) {
        tampilUser(root->left);
        cout << root->info.username << " | " << root->info.role
            << " | " << root->info.idPenghubung << endl;
        tampilUser(root->right);
    }
}

int nomorTerbesarRole(TreeUser root, string role) {
    int hasil = 0;
    int kiri, kanan, sendiri = 0;
    if (root != NULL) {
        kiri = nomorTerbesarRole(root->left, role);
        kanan = nomorTerbesarRole(root->right, role);
        if (root->info.role == role && root->info.idPenghubung.length() > 2) {
            sendiri = stoi(root->info.idPenghubung.substr(2));
        }
        hasil = kiri;
        if (kanan > hasil) {
            hasil = kanan;
        }
        if (sendiri > hasil) {
            hasil = sendiri;
        }
    }
    return hasil;
}

string hashPassword(string username, string password) {
    string data = username + ":" + password;
    unsigned long long h = 14695981039346656037ULL;
    size_t i;
    int j;
    string hasil = "";
    const char digit[] = "0123456789abcdef";

    for (i = 0; i < data.length(); i++) {
        h = h ^ (unsigned char)data[i];
        h = h * 1099511628211ULL;
    }
    for (j = 15; j >= 0; j--) {
        hasil = hasil + digit[(h >> (j * 4)) & 0xF];
    }
    return hasil;
}

string buatId(string prefix, int nomor) {
    string angka = to_string(nomor);
    while (angka.length() < 3) {
        angka = "0" + angka;
    }
    return prefix + angka;
}

string bacaInput(string prompt) {
    string s;
    cout << prompt;
    if (!getline(cin, s)) {
        s = "0";
    }
    if (!s.empty() && s[s.length() - 1] == '\r') {
        s.erase(s.length() - 1);
    }
    return s;
}

bool isUsernameValid(string username) {
    bool ok = (username.length() >= 4 && username.length() <= 15);
    size_t i = 0;
    while (ok && i < username.length()) {
        if (!isAlnum(username[i])) {
            ok = false;
        }
        i++;
    }
    return ok;
}

bool isPasswordValid(string password) {
    bool ok = (password.length() >= 6);
    size_t i = 0;
    while (ok && i < password.length()) {
        if (password[i] == ' ' || password[i] == '\t') {
            ok = false;
        }
        i++;
    }
    return ok;
}

string bacaTeks(string prompt, size_t maxPanjang, bool bolehKosong, bool &batal) {
    string s = "";
    bool valid = false;
    bool kosong;
    size_t i;
    batal = false;
    while (!valid && !batal) {
        s = bacaInput(prompt);
        kosong = true;
        for (i = 0; i < s.length(); i++) {
            if (s[i] != ' ') {
                kosong = false;
            }
        }
        if (s == "0") {
            batal = true;
        } else if (kosong && !bolehKosong) {
            cout << "Input tidak boleh kosong." << endl;
        } else if (s.length() > maxPanjang) {
            cout << "Maksimal " << maxPanjang << " karakter." << endl;
        } else {
            if (kosong) {
                s = "";
            }
            valid = true;
        }
    }
    return s;
}

bool bacaYaTidak(string prompt) {
    string s;
    bool valid = false;
    bool ya = false;
    while (!valid) {
        s = bacaInput(prompt + " (y/n): ");
        if (s == "y" || s == "Y") {
            ya = true;
            valid = true;
        } else if (s == "n" || s == "N" || s == "0") {
            valid = true;
        } else {
            cout << "Ketik y atau n." << endl;
        }
    }
    return ya;
}

void isiDataAwalUser(TreeUser &rootU) {
    User admin;
    admin.username = "admin";
    admin.passwordHash = hashPassword("admin", "admin123");
    admin.role = "Admin";
    admin.idPenghubung = "-";
    insertUser(rootU, admin);
}

void inputKredensial(TreeUser root, string &username, string &password, bool &batal) {
    bool valid = false;
    string konfirmasi;

    batal = false;
    username = "";
    password = "";

    while (!valid && !batal) {
        username = bacaInput("Username (4-15 huruf/angka, 0 = batal): ");
        if (username == "0") {
            batal = true;
        } else if (!isUsernameValid(username)) {
            cout << "Username harus 4-15 karakter, hanya huruf dan angka." << endl;
        } else if (searchUser(root, username) != NULL) {
            cout << "Username sudah dipakai, pilih yang lain." << endl;
        } else {
            valid = true;
        }
    }

    valid = false;
    while (!valid && !batal) {
        password = bacaInput("Password (min. 6 karakter, tanpa spasi, 0 = batal): ");
        if (password == "0") {
            batal = true;
        } else if (!isPasswordValid(password)) {
            cout << "Password minimal 6 karakter dan tidak boleh mengandung spasi." << endl;
        } else {
            konfirmasi = bacaInput("Ulangi password: ");
            if (konfirmasi == password) {
                valid = true;
            } else {
                cout << "Konfirmasi password tidak cocok." << endl;
            }
        }
    }
}

void registrasiPasien(TreeUser &rootU, TreePasien &rootP) {
    string username, password, nama, nik, telepon;
    bool batal = false;
    bool valid;
    int nomor;
    Pasien p;
    User u;

    cout << "\n=== REGISTRASI PASIEN ===" << endl;
    inputKredensial(rootU, username, password, batal);

    valid = false;
    while (!valid && !batal) {
        nama = bacaInput("Nama lengkap (0 = batal): ");
        if (nama == "0") {
            batal = true;
        } else if (!isNamaValid(nama)) {
            cout << "Nama maksimal 50 karakter, hanya huruf, spasi, titik, atau apostrof." << endl;
        } else {
            valid = true;
        }
    }

    valid = false;
    while (!valid && !batal) {
        nik = bacaInput("NIK (16 digit, 0 = batal): ");
        if (nik == "0") {
            batal = true;
        } else if (!isNikValid(nik)) {
            cout << "NIK harus tepat 16 digit angka." << endl;
        } else if (nikTerdaftar(rootP, nik)) {
            cout << "NIK sudah terdaftar. Satu NIK hanya boleh memiliki satu akun." << endl;
        } else {
            valid = true;
        }
    }

    valid = false;
    while (!valid && !batal) {
        telepon = bacaInput("Telepon (10-13 digit, 0 = batal): ");
        if (telepon == "0") {
            batal = true;
        } else if (!isTeleponValid(telepon)) {
            cout << "Telepon harus 10-13 digit angka." << endl;
        } else {
            valid = true;
        }
    }

    if (batal) {
        cout << "Registrasi dibatalkan." << endl;
    } else {
        nomor = nomorTerbesarPasien(rootP) + 1;
        if (nomor > 999) {
            cout << "Kapasitas ID pasien penuh. Registrasi gagal." << endl;
        } else {
            p.idPasien = buatId("PS", nomor);
            p.username = username;
            p.nama = nama;
            p.nik = nik;
            p.telepon = telepon;
            insertPasien(rootP, p);

            u.username = username;
            u.passwordHash = hashPassword(username, password);
            u.role = "Pasien";
            u.idPenghubung = p.idPasien;
            insertUser(rootU, u);

            cout << "Registrasi berhasil. ID Pasien Anda: " << p.idPasien << endl;
            cout << "Silakan login menggunakan username dan password Anda." << endl;
        }
    }
}

void loginUser(TreeUser rootU, bool &berhasil, User &userAktif) {
    int percobaan = 0;
    bool batal = false;
    string username, password;
    NodeUser *node;

    berhasil = false;
    cout << "\n=== LOGIN ===" << endl;
    while (!berhasil && !batal && percobaan < 3) {
        username = bacaInput("Username (0 = kembali): ");
        if (username == "0") {
            batal = true;
        } else {
            password = bacaInput("Password: ");
            node = searchUser(rootU, username);
            if (node != NULL && node->info.passwordHash == hashPassword(username, password)) {
                berhasil = true;
                userAktif = node->info;
            } else {
                percobaan++;
                cout << "Username atau password salah.";
                if (percobaan < 3) {
                    cout << " Sisa percobaan: " << (3 - percobaan) << endl;
                } else {
                    cout << "\nPercobaan habis. Kembali ke menu utama." << endl;
                }
            }
        }
    }
}

void tambahAkunPerawat(TreeUser &rootU) {
    string username, password;
    bool batal = false;
    int nomor;
    User u;

    cout << "\n=== BUAT AKUN PERAWAT ===" << endl;
    inputKredensial(rootU, username, password, batal);

    if (batal) {
        cout << "Pembuatan akun dibatalkan." << endl;
    } else {
        nomor = nomorTerbesarRole(rootU, "Perawat") + 1;
        if (nomor > 999) {
            cout << "Kapasitas ID Perawat penuh. Akun tidak dibuat." << endl;
        } else {
            u.username = username;
            u.passwordHash = hashPassword(username, password);
            u.role = "Perawat";
            u.idPenghubung = buatId("PR", nomor);
            insertUser(rootU, u);
            cout << "Akun Perawat berhasil dibuat. ID: " << u.idPenghubung << endl;
        }
    }
};