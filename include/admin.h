#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "pasien.h"
#include "layanan.h"
#include "dokter.h"

// Data awal untuk demo: 5 layanan, 19 keluhan, 4 dokter beserta akun loginnya
void isiDataAwalKlinik(TreeLayanan &rootL, TreeKeluhan &rootK, TreeDokter &rootD, TreeUser &rootU);

// Menu CRUD pada dashboard Admin
void menuKelolaPasien(TreePasien &rootP, TreeUser &rootU);
void menuKelolaDokter(TreeDokter &rootD, TreeLayanan rootL, TreeUser &rootU);
void menuKelolaLayanan(TreeLayanan &rootL, TreeKeluhan rootK, TreeDokter rootD);
void menuKelolaKeluhan(TreeKeluhan &rootK, TreeLayanan rootL);

#endif