// Author: 241524006 / Darrell Rafa Raihan

#include <stdio.h>
#include <stdlib.h>
#include "listproduk.h"
#include "others.h"
#include "dashboard.h"
#include "produk.h"

void kategori()
{
    clearScreen();
    puts("**************************LIST PRODUK********************************\n");

    char *kategori[] = {"sembako", "perlengkapan mandi & mencuci", "obat-obatan", "makanan ringan", "minuman", "rokok", "bumbu dapur"};
    puts("Kategori:");
    for (int i = 0; i < 7; i++)
    {
        printf("%d. %s\n", i + 1, kategori[i]);
    }
    printf("\n");
    for (int i = 0; i < 7; i++)
    {
        printf("Input '%d' untuk melihat list produk %s\n", i + 1, kategori[i]);
    }
    puts("Input '0' untuk kembali");
    printf("\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

	if (input == 0) {
		dashboard();
	} else if (input == 1 || input == 2 || input == 3 || input == 4 || input == 5 || input == 6 || input == 7) {
		char selectedCategory[50];
	    strcpy(selectedCategory, kategori[input - 1]);
	    listByKategori(selectedCategory);
	} else {
    	list();
    }
}

void listByKategori(char selectedCategory[])
{
    clearScreen();
    puts("**************************LIST PRODUK********************************\n");

    FILE *file = fopen(PRODUCT_DATABASE, "r");

    ProductStruct produk;
    ProductStruct listProdukByKategori[100];
    int listProdukByKategoriIndex = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file))
    {
        sscanf(buffer, "%d,%[^,],%[^,],%d,%d", &produk.id, produk.nama, produk.kategori, &produk.harga, &produk.stock);
        if (strstr(produk.kategori, selectedCategory) != NULL)
        {
            listProdukByKategori[listProdukByKategoriIndex] = produk;
            listProdukByKategoriIndex++;
        }
    }
    fclose(file);

    if (listProdukByKategoriIndex == 0)
    {
        printf("Tidak ada produk dalam kategori '%s'.\n", selectedCategory);
        puts("\nInput '0' untuk kembali");
        printf("\nInput: ");
        int input;
        scanf("%d", &input);
        getchar();

        kategori();
    }

    printf("List %s:\n", selectedCategory);
    for (int i = 0; i < listProdukByKategoriIndex; i++)
    {
        printf("%d) %s\n", i + 1, listProdukByKategori[i].nama);
    }
    printf("\n");

    for (int i = 0; i < listProdukByKategoriIndex; i++)
    {
        printf("Input '%d' untuk melihat detail %s\n", i + 1, listProdukByKategori[i].nama);
    }
    puts("Input '0' untuk kembali");
    printf("\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    if (input == 0)
    {
        kategori();
    }
    else if (input > 0 && input <= listProdukByKategoriIndex)
    {
        detail(
            listProdukByKategori[input - 1].id,
            listProdukByKategori[input - 1].nama,
            listProdukByKategori[input - 1].kategori,
            listProdukByKategori[input - 1].harga);
    }
    else
    {
    	listByKategori(selectedCategory);
    }
}


