// Author: 241524006 / Darrell Rafa Raihan

#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "others.h"
#include "dashboard.h"
#include "produk.h"

void getSearchKeyword()
{
    clearScreen();
    puts("**************************CARI PRODUK********************************\n");

    char keyword[50];
    printf("Masukkan keyword pencarian: ");
    gets(keyword);

    listBySearchKeyword(keyword);
}

void listBySearchKeyword(char keyword[])
{
    FILE *file = fopen(PRODUCT_DATABASE, "r");

    clearScreen();
    puts("************************HASIL PENCARIAN********************************\n");

    ProductStruct produk;
    ProductStruct foundProduk[100]; 
    int foundProdukIndex = 0;

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file))
    {
        sscanf(buffer, "%d,%[^,],%[^,],%d,%d", &produk.id, produk.nama, produk.kategori, &produk.harga, &produk.stock);
        if (strstr(produk.nama, keyword) != NULL)
        {
            foundProduk[foundProdukIndex] = produk;
            foundProdukIndex++;
        }
    }
    fclose(file);

    if (foundProdukIndex == 0)
    {
        puts("Pencarian tidak ditemukan.");
        puts("\nInput '1' untuk coba lagi");
        puts("Input '0' untuk kembali ke dashboard\n");

        int input;
        printf("Input: ");
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            getSearchKeyword();
            break;
        case 0:
            dashboard();
            break;
        default:
        	listBySearchKeyword(keyword);
            break;
        }
    }

    printf("Hasil pencarian untuk keyword '%s':\n", keyword);
    for (int i = 0; i < foundProdukIndex; i++)
    {
        printf("%d) %s\n", i + 1, foundProduk[i].nama);
    }

    printf("\n");
    for (int i = 0; i < foundProdukIndex; i++)
    {
        printf("Input '%d' untuk melihat detail %s\n", i + 1, foundProduk[i].nama);
    }
    puts("Input '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    if (input == 0)
    {
        getSearchKeyword();
    }
    else if (input > 0 && input <= foundProdukIndex)
    {
        detail(
            foundProduk[input - 1].id,
            foundProduk[input - 1].nama,
            foundProduk[input - 1].kategori,
            foundProduk[input - 1].harga);
    }
    else
    {
        listBySearchKeyword(keyword);
    }
}

