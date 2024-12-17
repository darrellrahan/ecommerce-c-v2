#ifndef PRODUK_H
#define PRODUK_H
#include "header.h"

typedef struct
{
    int id;
    char nama[50];
    char kategori[50];
    int harga;
    int stock;
} ProductStruct;

extern int jumlahProduk;

void getJumlahProduk(int *jumlahProduk);

#endif
