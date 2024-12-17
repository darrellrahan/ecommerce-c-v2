// Author: 241524006 / Darrell Rafa Raihan

#include <stdio.h>
#include <stdlib.h>
#include "cart.h"
#include "auth.h"
#include "others.h"
#include "dashboard.h"

void addToCart(int id, char nama[])
{
    FILE *file = fopen(CART_DATABASE, "a+");

    fprintf(file, "%s %d\n", currentUser.email, id);
    fclose(file);

	clearScreen();
    printf("\nBerhasil menambahkan %s ke keranjang.\n\n", nama);

    puts("Input '1' untuk lihat keranjang");
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
        cartFunction();
        break;
    default:
    	cartFunction();
        break;
    }
}

void getCart(ProductStruct outputCart[], CartDatabaseStruct cartDatabase[])
{	
	getJumlahProduk(&jumlahProduk);
	
    for (int i = 0; i < jumlahProduk; i++)
    {
        strcpy(outputCart[i].nama, "");
    }

    for (int i = 0; i < jumlahProduk; i++)
    {
        strcpy(cartDatabase[i].email, "");
    }
    
    FILE *productFile = fopen(PRODUCT_DATABASE, "r");	
    char buffer[256];
    ProductStruct listProduk[jumlahProduk];
    int index = 0;

    while (fgets(buffer, sizeof(buffer), productFile))
    {
        sscanf(buffer, "%d,%[^,],%[^,],%d,%d",
               &listProduk[index].id,
               listProduk[index].nama,
               listProduk[index].kategori,
               &listProduk[index].harga,
               &listProduk[index].stock);
        index++;
    }
    fclose(productFile);

    FILE *file = fopen(CART_DATABASE, "r");

    int fileId;
    char fileUserEmail[MAX_EMAIL_LENGTH];
    int outputCartIndex = 0;
    int cartDatabaseIndex = 0;

    while (fscanf(file, "%s %d", fileUserEmail, &fileId) != EOF)
    {
        strcpy(cartDatabase[cartDatabaseIndex].email, fileUserEmail);
        cartDatabase[cartDatabaseIndex].id = fileId;
        cartDatabaseIndex++;
        if (strcmp(fileUserEmail, currentUser.email) == 0)
        {
            for (int i = 0; i < jumlahProduk ; i++)
            {
                if (listProduk[i].id == fileId)
                {
                    outputCart[outputCartIndex] = listProduk[i];
                    outputCartIndex++;
                }
            }
        }
    }
    fclose(file);
}

void checkout(int totalHarga)
{
    clearScreen();
    puts("**************************CHECKOUT********************************\n");
    printf("Total harga: Rp%d\n\n", totalHarga);

    int uang;
    printf("Masukkan uang: Rp");
    scanf("%d", &uang);

    if (uang == totalHarga)
    {
        puts("\nUang anda pas.\n");
        puts("Terima kasih sudah berbelanja! :)");
    }
    else if (uang > totalHarga)
    {
        printf("\nKembalian Rp%d.\n\n", uang - totalHarga);
        puts("Terima kasih sudah berbelanja! :)");
    }
    else if (uang < totalHarga)
    {
        printf("\nUang anda kurang! Anda berhutang Rp%d ke warung ini!\n\n", totalHarga - uang);
        puts("Hari hari nganjuk...");
    }
    else
    {
        puts("\nInvalid input.\n");
    }

    ProductStruct cart[jumlahProduk];
    CartDatabaseStruct cartDatabase[jumlahProduk];
    getCart(cart, cartDatabase);

    CartDatabaseStruct newCartDatabase[jumlahProduk];
    for (int i = 0; i < (sizeof(newCartDatabase) / sizeof(newCartDatabase[0])); i++)
    {
        strcpy(newCartDatabase[i].email, "");
    }

    int newCartDatabaseIndex = 0;
    for (int i = 0; i < (sizeof(cartDatabase) / sizeof(cartDatabase[0])); i++)
    {
        if (cartDatabase[i].email[0] != '\0')
        {
            if (strcmp(cartDatabase[i].email, currentUser.email) == 0)
            {
                FILE *rekapPenjualanFile = fopen(REKAP_PENJUALAN_DATABASE, "a");
                if (rekapPenjualanFile == NULL)
                {
                    perror("Gagal membuka database keuntungan");
                    exit(EXIT_FAILURE);
                }
                fprintf(rekapPenjualanFile, "%s %d\n", cartDatabase[i].email, cartDatabase[i].id);
                fclose(rekapPenjualanFile);
            }
            else
            {
                strcpy(newCartDatabase[newCartDatabaseIndex].email, cartDatabase[i].email);
                newCartDatabase[newCartDatabaseIndex].id = cartDatabase[i].id;
                newCartDatabaseIndex++;
            }
        }
    }

    FILE *file = fopen(CART_DATABASE, "w");
    for (int i = 0; i < (sizeof(newCartDatabase) / sizeof(newCartDatabase[0])); i++)
    {
        if (newCartDatabase[i].email[0] != '\0')
        {
            fprintf(file, "%s %d\n", newCartDatabase[i].email, newCartDatabase[i].id);
        }
    }

    fclose(file);

    puts("\nInput '0' untuk kembali ke dashboard\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    dashboard();
}

void deleteProductFromCart()
{
    clearScreen();
    puts("**************************HAPUS PRODUK DARI KERANJANG********************************\n");

    ProductStruct cart[jumlahProduk];
    CartDatabaseStruct cartDatabase[jumlahProduk];
    getCart(cart, cartDatabase);

    puts("Produk di keranjang:");
    for (int i = 0; i < (sizeof(cart) / sizeof(cart[0])); i++)
    {
        if (cart[i].nama[0] != '\0')
        {
            printf("%d. %s\n", i + 1, cart[i].nama);
        }
    }
    printf("\n");
    
    for (int i = 0; i < (sizeof(cart) / sizeof(cart[0])); i++)
    {
        if (cart[i].nama[0] != '\0')
        {
            printf("Input '%d' untuk menghapus %s dari keranjang\n", i + 1, cart[i].nama);
        }
    }
    puts("Input '0' untuk kembali ke keranjang");
    printf("\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();
	
	if(input == 0) {
		cartFunction();
	} else {
	    int removeId = cart[input - 1].id;
	
	    CartDatabaseStruct newCartDatabase[jumlahProduk];
	    for (int i = 0; i < (sizeof(newCartDatabase) / sizeof(newCartDatabase[0])); i++)
	    {
	        strcpy(newCartDatabase[i].email, "");
	    }
	
	    int newCartDatabaseIndex = 0;
	    for (int i = 0; i < (sizeof(cartDatabase) / sizeof(cartDatabase[0])); i++)
	    {
	        if (cartDatabase[i].email[0] != '\0')
	        {
	            if (cartDatabase[i].id == removeId && strcmp(cartDatabase[i].email, currentUser.email) == 0)
	            {
	                continue;
	            }
	            else
	            {
	                strcpy(newCartDatabase[newCartDatabaseIndex].email, cartDatabase[i].email);
	                newCartDatabase[newCartDatabaseIndex].id = cartDatabase[i].id;
	                newCartDatabaseIndex++;
	            }
	        }
	    }
	
	    FILE *file = fopen(CART_DATABASE, "w");
	    for (int i = 0; i < (sizeof(newCartDatabase) / sizeof(newCartDatabase[0])); i++)
	    {
	        if (newCartDatabase[i].email[0] != '\0')
	        {
	            fprintf(file, "%s %d\n", newCartDatabase[i].email, newCartDatabase[i].id);
	        }
	    }
	
	    fclose(file);
	
	    clearScreen();
	    printf("\nBerhasil menghapus %s dari keranjang\n", cart[input - 1].nama);
	
	    puts("\nInput '1' untuk melihat keranjang\n");
	
	    int input2;
	    printf("Input: ");
	    scanf("%d", &input2);
	    getchar();
	
	    cartFunction();
    }
}

