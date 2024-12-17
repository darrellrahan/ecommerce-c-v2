#include <stdio.h>
#include <stdlib.h>
#include "produk.h"

int jumlahProduk;

void getJumlahProduk(int *jumlahProduk) {
	FILE *file = fopen(PRODUCT_DATABASE, "r");
	
	ProductStruct produk;

	*jumlahProduk = 0;
	while (fscanf(file, "%d,%49[^,],%49[^,],%d,%d\n",
                  &produk.id,
                  produk.nama,
                  produk.kategori,
                  &produk.harga,
                  &produk.stock) != EOF)
    {
        (*jumlahProduk)++;
    }

    fclose(file);
}


