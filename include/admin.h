#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "pasien.h"
#include "layanan.h"
#include "dokter.h"

void isiDataAwalKlinik(TreeLayanan &rootL, TreeKeluhan &rootK, TreeDokter &rootD, TreeUser &rootU);

void menuKelolaPasien(TreePasien &rootP, TreeUser &rootU);
void menuKelolaDokter(TreeDokter &rootD, TreeLayanan rootL, TreeUser &rootU);
void menuKelolaLayanan(TreeLayanan &rootL, TreeKeluhan rootK, TreeDokter rootD);
void menuKelolaKeluhan(TreeKeluhan &rootK, TreeLayanan rootL);

#endif