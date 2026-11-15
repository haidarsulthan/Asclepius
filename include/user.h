#ifndef USER_H
#define USER_H

#include <string>
#include "pasien.h"
using namespace std;

// ADT BST User (kunci: username).
// role: "Admin", "Dokter", "Pasien", atau "Perawat".
// idPenghubung: ID pasien (PSxxx) / dokter (DKxxx) / perawat (PRxxx),
//               "-" untuk Admin.
struct User {
    string username;
    string passwordHash;
    string role;
    string idPenghubung;
};

struct NodeUser {
    User info;
    NodeUser *left;
    NodeUser *right;
};

typedef NodeUser* TreeUser;

// ---- operasi BST User ----
void createTreeUser(TreeUser &root);
bool isEmptyUser(TreeUser root);
NodeUser* alokasiUser(User u);
bool insertUser(TreeUser &root, User u);
bool deleteUser(TreeUser &root, string username);
NodeUser* searchUser(TreeUser root, string username);
void tampilUser(TreeUser root);
int nomorTerbesarRole(TreeUser root, string role);

// ---- utilitas ----
string hashPassword(string username, string password);
string buatId(string prefix, int nomor);
string bacaInput(string prompt);
bool isUsernameValid(string username);
bool isPasswordValid(string password);
string bacaTeks(string prompt, size_t maxPanjang, bool bolehKosong, bool &batal);
bool bacaYaTidak(string prompt);

// ---- proses autentikasi ----
void isiDataAwalUser(TreeUser &rootU);
void registrasiPasien(TreeUser &rootU, TreePasien &rootP);
void loginUser(TreeUser rootU, bool &berhasil, User &userAktif);
void inputKredensial(TreeUser root, string &username, string &password, bool &batal);
void tambahAkunPerawat(TreeUser &rootU);

#endif