// Author: 241524006 / Darrell Rafa Raihan

#include <stdio.h>
#include <stdlib.h>
#include "dashboard.h"
#include "others.h"
#include "listproduk.h"
#include "search.h"
#include "cart.h"
#include "akun.h"
#include "auth.h"
#include "produk.h"

void dashboard()
{
    clearScreen();
    puts("**************************DASHBOARD********************************\n");
    puts("Input '1' untuk List Produk");
    puts("Input '2' untuk Cari Produk");
    puts("Input '3' untuk Keranjang");
    puts("Input '4' untuk Akun");
    puts("Input '5' untuk Keluar dari aplikasi\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 1:
        list();
        break;
    case 2:
        search();
        break;
    case 3:
        cartFunction();
        break;
    case 4: 
        akun();
        break;
    case 5:
        exitProgram();
        break;
    default:
    	dashboard();
        break;
    }
}

void list()
{
    kategori();
}

void search()
{
    getSearchKeyword();
}

void cartFunction()
{
    clearScreen();
    puts("**************************KERANJANG********************************\n");

    ProductStruct cart[jumlahProduk];
    CartDatabaseStruct cartDatabase[jumlahProduk];
    getCart(cart, cartDatabase);

    if (strcmp(cart[0].nama, "") == 0)
    {
        puts("Keranjang kosong.\n");
        puts("Input '1' untuk List Produk");
        puts("Input '2' untuk Cari Produk");
        puts("Input '0' untuk kembali ke dashboard\n");

        int input;
        printf("Input: ");
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 0:
            dashboard();
            break;
        case 1:
            list();
            break;
        case 2:
            search();
            break;
        default:
        	cartFunction();
            break;
        }
    }
    else
    {
    	printf("%-4s %-30s %-10s\n", "No", "Nama produk", "Harga produk");
    	printf("---------------------------------------------------\n");
        int totalHarga = 0;
        for (int i = 0; i < (sizeof(cart) / sizeof(cart[0])); i++)
        {
            if (cart[i].nama[0] != '\0')
            {
                totalHarga += cart[i].harga;
                printf("%-4d %-30s Rp%-10d\n", i + 1, cart[i].nama, cart[i].harga);
            }
        }

        printf("\nTotal harga: Rp%d\n", totalHarga);

        puts("\nInput '1' untuk checkout");
        puts("Input '2' untuk hapus produk dari keranjang");
        puts("Input '0' untuk kembali ke dashboard\n");

        int input;
        printf("Input: ");
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 0:
            dashboard();
            break;
        case 1:
            checkout(totalHarga);
            break;
        case 2:
            deleteProductFromCart();
            break;
        default:
        	cartFunction();
            break;
        }
    }
}

void akun()
{
    clearScreen();
    puts("**************************AKUN********************************\n");
    puts("Input '1' untuk Info Akun");
    puts("Input '2' untuk Edit Info Akun");
    puts("Input '3' untuk Ganti Password");
    puts("Input '4' untuk Info Aplikasi");
    puts("Input '5' untuk Pusat Bantuan");
    puts("Input '6' untuk Log Out");
    puts("Input '0' untuk kembali ke dashboard\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 1:
        infoAkun();
        break;
    case 2:
        editAkun();
        break;
    case 3:
        gantiPassword();
        break;
    case 4:
        infoAplikasi();
        break;
    case 5:
        pusatBantuan();
        break;
    case 6:
        logout();
        break;
    case 0:
        dashboard();
        break;
    default:
    	akun();
        break;
    }
}

void detail(
    int id,
    char nama[],
    char kategori[],
    int harga)
{
    clearScreen();
    puts("**************************DETAIL PRODUK********************************\n");
    printf("Nama produk: %s\n", nama);
    printf("Kategori produk: %s\n", kategori);
    printf("Harga produk: Rp%d\n", harga);

    puts("\nInput '1' untuk tambah ke keranjang");
    puts("Input '0' untuk kembali ke dashboard");

    printf("\n");
    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 0:
        dashboard();
        break;
    case 1:
        addToCart(id, nama);
        break;
    default:
    	detail(id, nama, kategori, harga);
        break;
    }
}

