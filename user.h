#ifndef USER_H
#define USER_H

#include <string>
#include "pasien.h"
using namespace std;

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

void createTreeUser(TreeUser &root);
bool isEmptyUser(TreeUser root);
NodeUser* alokasiUser(User u);
bool insertUser(TreeUser &root, User u);
NodeUser* searchUser(TreeUser root, string username);
void tampilUser(TreeUser root);
int nomorTerbesarRole(TreeUser root, string role);

string hashPassword(string username, string password);
string buatId(string prefix, int nomor);
string bacaInput(string prompt);
bool isUsernameValid(string username);
bool isPasswordValid(string password);

void isiDataAwalUser(TreeUser &rootU);
void registrasiPasien(TreeUser &rootU, TreePasien &rootP);
void loginUser(TreeUser rootU, bool &berhasil, User &userAktif);
void tambahAkunStaf(TreeUser &rootU);

#endif