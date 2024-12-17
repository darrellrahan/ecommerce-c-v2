//Author: 241524002 / Afriza Choirie Saputra

#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include "others.h"
#include "auth.h"
#include "cart.h"

void adminDashboard()
{
    clearScreen();
    puts("**************************ADMIN DASHBOARD********************************\n");
    puts("Input '1' untuk List Produk");
    puts("Input '2' untuk Tambah Produk");
    puts("Input '3' untuk Edit Produk");
    puts("Input '4' untuk Hapus Produk");
    puts("Input '5' untuk Rekap Penjualan");
    puts("Input '6' untuk Log Out");
    puts("Input '7' untuk Keluar dari aplikasi\n");
    
    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 1:
        listprodukadmin();
        break;
    case 2:
        tambahProduk();
        break;
    case 3:
        editProduk();
        break;
    case 4:
        hapusProduk();
        break;
    case 5:
        rekapPenjualan();
        break;
    case 6:
        logout(); 
        break;
    case 7:
        exitProgram(); 
        break;
    default:
        adminDashboard();
        break;
    }
}

void listprodukadmin() {
	clearScreen();
	puts("**************************LIST PRODUK********************************\n");
	
	FILE *file = fopen(PRODUCT_DATABASE, "r");

    ProductStruct produk;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file))
    {
        sscanf(buffer, "%d,%[^,],%[^,],%d,%d", &produk.id, produk.nama, produk.kategori, &produk.harga, &produk.stock);
        printf("ID produk: %d\nNama produk: %s\nKategori produk: %s\nHarga produk: Rp%d\nStock: %d\n\n", produk.id, produk.nama, produk.kategori, produk.harga, produk.stock);
    }
    
    fclose(file);
    
    puts("Input '0' untuk kembali ke dashboard\n");
    
    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 0:
        adminDashboard();
        break;
    default:
    	listprodukadmin();
        break;
    }
}

void tambahProduk() {
	clearScreen();
    puts("**************************TAMBAH PRODUK********************************\n");
    
    FILE *file = fopen(PRODUCT_DATABASE, "a+");
    
    ProductStruct produkbaru;

    int lastId;
    char buffer[256]; 
    ProductStruct readProduk;
    
    while (fgets(buffer, sizeof(buffer), file)) {
    	sscanf(buffer, "%d,%[^,],%[^,],%d,%d", &readProduk.id, readProduk.nama, readProduk.kategori, &readProduk.harga, &readProduk.stock);
        lastId = readProduk.id;
    }
    rewind(file);
    
    produkbaru.id = lastId + 1;
    
    printf("ID Produk (otomatis): %d\n", produkbaru.id);
    
    printf("\nMasukkan nama produk: ");
    fgets(produkbaru.nama, sizeof(produkbaru.nama), stdin);
    produkbaru.nama[strcspn(produkbaru.nama, "\n")] = '\0';
	
	puts("\nInput '1' untuk kategori sembako");
	puts("Input '2' untuk kategori perlengkapan mandi & mencuci");
	puts("Input '3' untuk kategori obat-obatan");
	puts("Input '4' untuk kategori makanan ringan");
	puts("Input '5' untuk kategori minuman");
	puts("Input '6' untuk kategori rokok");
	puts("Input '7' untuk kategori bumbu dapur\n");
	int inputKategori;
    printf("Input kategori produk: ");
    scanf("%d", &inputKategori);
    getchar();
    switch(inputKategori) {
    	case 1:
    		strcpy(produkbaru.kategori, "sembako");
    		break;
    	case 2:
    		strcpy(produkbaru.kategori, "perlengkapan mandi & mencuci");
    		break;
    	case 3:
    		strcpy(produkbaru.kategori, "obat-obatan");
    		break;
    	case 4:
    		strcpy(produkbaru.kategori, "makanan ringan");
    		break;
    	case 5:
    		strcpy(produkbaru.kategori, "minuman");
    		break;
    	case 6:
    		strcpy(produkbaru.kategori, "rokok");
    		break;
    	case 7:
    		strcpy(produkbaru.kategori, "bumbu dapur");
    		break;
	}
    produkbaru.kategori[strcspn(produkbaru.kategori, "\n")] = '\0';
    
    printf("\nMasukkan harga produk: ");
    scanf("%d", &produkbaru.harga);
    
    printf("\nMasukkan jumlah stok produk: ");
    scanf("%d", &produkbaru.stock);

    fprintf(file, "%d,%s,%s,%d,%d\n", produkbaru.id, produkbaru.nama, produkbaru.kategori, produkbaru.harga, produkbaru.stock);
    fclose(file);
    
    printf("\nBerhasil menambahkan produk %s\n", produkbaru.nama);

    puts("\nInput '0' untuk kembali ke dashboard");

    printf("\n");
    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();
    
    adminDashboard();
}

void editProduk() {
    clearScreen();
    puts("**************************EDIT PRODUK********************************\n");

    FILE *file = fopen(PRODUCT_DATABASE, "r");
    if (file == NULL) {
        perror("Gagal membuka file produk");
        return;
    }

    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        perror("Gagal membuka file sementara");
        fclose(file);
        return;
    }

    ProductStruct produk;
    ProductStruct produkList;
    char bufferList[256];
    
    while (fgets(bufferList, sizeof(bufferList), file))
    {
        sscanf(bufferList, "%d,%[^,],%[^,],%d,%d", &produkList.id, produkList.nama, produkList.kategori, &produkList.harga, &produkList.stock);
        printf("ID produk: %d\nNama produk: %s\nKategori produk: %s\nHarga produk: Rp%d\nStock: %d\n\n", produkList.id, produkList.nama, produkList.kategori, produkList.harga, produkList.stock);
    }
    rewind(file);
	    
	int id;
    printf("Masukkan ID produk yang ingin diedit: ");
    scanf("%d", &id);
    getchar();

	int found = 0;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d,%[^,],%[^,],%d,%d", &produk.id, produk.nama, produk.kategori, &produk.harga, &produk.stock);

        if (produk.id == id) {
            found = 1;
            printf("\nID: %d\nNama: %s\nKategori: %s\nHarga: Rp%d\nStok: %d\n", 
                   produk.id, produk.nama, produk.kategori, produk.harga, produk.stock);

            puts("\nInput '1' untuk Edit Nama Produk");
            puts("Input '2' untuk Edit Kategori");
            puts("Input '3' untuk Edit Harga");
            puts("Input '4' untuk Edit Stok");
            puts("Input '0' untuk kembali\n");

            int input;
            printf("Input: ");
            scanf("%d", &input);
            getchar();

            switch (input) {
            case 1:
                printf("\nMasukkan nama baru: ");
                fgets(produk.nama, sizeof(produk.nama), stdin);
                produk.nama[strcspn(produk.nama, "\n")] = '\0';
                break;
            case 2:
            	puts("\nInput '1' untuk kategori sembako");
				puts("Input '2' untuk kategori perlengkapan mandi & mencuci");
				puts("Input '3' untuk kategori obat-obatan");
				puts("Input '4' untuk kategori makanan ringan");
				puts("Input '5' untuk kategori minuman");
				puts("Input '6' untuk kategori rokok");
				puts("Input '7' untuk kategori bumbu dapur\n");
				int inputKategori;
			    printf("Input kategori baru: ");
			    scanf("%d", &inputKategori);
			    getchar();
			    switch(inputKategori) {
			    	case 1:
			    		strcpy(produk.kategori, "sembako");
			    		break;
			    	case 2:
			    		strcpy(produk.kategori, "perlengkapan mandi & mencuci");
			    		break;
			    	case 3:
			    		strcpy(produk.kategori, "obat-obatan");
			    		break;
			    	case 4:
			    		strcpy(produk.kategori, "makanan ringan");
			    		break;
			    	case 5:
			    		strcpy(produk.kategori, "minuman");
			    		break;
			    	case 6:
			    		strcpy(produk.kategori, "rokok");
			    		break;
			    	case 7:
			    		strcpy(produk.kategori, "bumbu dapur");
			    		break;
				}
                produk.kategori[strcspn(produk.kategori, "\n")] = '\0';
                break;
            case 3:
                printf("\nMasukkan harga baru: ");
                scanf("%d", &produk.harga);
                getchar();
                break;
            case 4:
                printf("\nMasukkan stok baru: ");
                scanf("%d", &produk.stock);
                break;
            case 0:
                fclose(file);
                fclose(tempFile);
                remove("temp.csv");
                adminDashboard();
                return;
            default:
                puts("Pilihan tidak valid.");
                fclose(file);
                fclose(tempFile);
                remove("temp.csv");
                adminDashboard();
                return;
            }
        }

        fprintf(tempFile, "%d,%s,%s,%d,%d\n", produk.id, produk.nama, produk.kategori, produk.harga, produk.stock);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        if (remove(PRODUCT_DATABASE) == 0 && rename("temp.csv", PRODUCT_DATABASE) == 0) {
            printf("\nProduk berhasil diperbarui!\n");
        } else {
            perror("Gagal memperbarui produk");
        }
    } else {
        puts("\nProduk dengan ID tersebut tidak ditemukan.");
        remove("temp.csv");
    }

    puts("\nInput '0' untuk kembali ke dashboard\n");
    
    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    adminDashboard();
}

void hapusProduk()
{
    clearScreen();
    puts("**************************HAPUS PRODUK********************************\n");

    FILE *file = fopen(PRODUCT_DATABASE, "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (!file || !tempFile)
    {
        perror("Gagal membuka file");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile); 
        return;
    }

    ProductStruct produk;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file))
    {
        sscanf(buffer, "%d,%[^,],%[^,],%d,%d", &produk.id, produk.nama, produk.kategori, &produk.harga, &produk.stock);
        printf("ID produk: %d\nNama produk: %s\nKategori produk: %s\nHarga produk: Rp%d\nStock: %d\n\n", produk.id, produk.nama, produk.kategori, produk.harga, produk.stock);
    }
	rewind(file);
	
	int id;
    printf("Masukkan ID produk yang ingin dihapus: ");
    scanf("%d", &id);
    
    int found = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        sscanf(buffer, "%d,%[^,],%[^,],%d,%d", &produk.id, produk.nama, produk.kategori, &produk.harga, &produk.stock);
        if (produk.id != id)
        {
            fprintf(tempFile, "%d,%s,%s,%d,%d\n", produk.id, produk.nama, produk.kategori, produk.harga, produk.stock);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        if (remove(PRODUCT_DATABASE) == 0 && rename("temp.csv", PRODUCT_DATABASE) == 0)
        {
            printf("\nBerhasil menghapus produk dengan ID %d\n", id);
        }
        else
        {
            perror("Gagal memperbarui database");
        }
    }
    else
    {
        printf("\nProduk dengan ID %d tidak ditemukan!\n", id);
        remove("temp.csv");
    }
    
    puts("\nInput '0' untuk kembali ke dashboard\n");
    
    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    adminDashboard();
}

void rekapPenjualan()
{
    clearScreen();
    puts("**************************REKAP PENJUALAN********************************\n");

    FILE *rekapPenjualanFile = fopen(REKAP_PENJUALAN_DATABASE, "r");
    FILE *productFile = fopen(PRODUCT_DATABASE, "r");

    if (rekapPenjualanFile == NULL || productFile == NULL)
    {
        puts("Belum ada penjualan.");
        if (rekapPenjualanFile) fclose(rekapPenjualanFile);
        if (productFile) fclose(productFile);
        int input;
        puts("\nInput '0' untuk kembali");
        printf("\nInput: ");
        scanf("%d", &input);
        getchar();
        adminDashboard();
    }

    CartDatabaseStruct penjualanEntries[25];
    int penjualanCount = 0;

    while (fscanf(rekapPenjualanFile, "%s %d", penjualanEntries[penjualanCount].email, &penjualanEntries[penjualanCount].id) != EOF)
    {
        penjualanCount++;
    }
    
    ProductStruct produkEntries[25];
    int produkCount = 0;
    char line[200];

    while (fgets(line, sizeof(line), productFile))
    {
        char *token;
        token = strtok(line, ",");
        produkEntries[produkCount].id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(produkEntries[produkCount].nama, token);

        token = strtok(NULL, ",");
        strcpy(produkEntries[produkCount].kategori, token);

        token = strtok(NULL, ",");
        produkEntries[produkCount].harga = atoi(token);

        token = strtok(NULL, ",");
        produkEntries[produkCount].stock = atoi(token);

        produkCount++;
    }

    printf("%-20s %-30s %-10s\n", "Email User", "Nama Barang", "Harga");
    printf("-------------------------------------------------------------\n");
	
    for (int i = 0; i < penjualanCount; i++)
    {
        int found = 0;

        for (int j = 0; j < produkCount; j++)
        {
            if (penjualanEntries[i].id == produkEntries[j].id)
            {
                printf("%-20s %-30s Rp%-10d\n", penjualanEntries[i].email, produkEntries[j].nama, produkEntries[j].harga);
                found = 1;
                break;
            }
        }

        if (!found)
        {
            printf("%-30s %-30s %-10s\n", penjualanEntries[i].email, "Produk tidak ditemukan", "-");
        }
    }
    
    int totalPenjualan = 0;
    for (int i = 0; i < penjualanCount; i++)
    {
        for (int j = 0; j < produkCount; j++)
        {
            if (penjualanEntries[i].id == produkEntries[j].id)
            {
                totalPenjualan += produkEntries[j].harga;
                break;
            }
        }
    }

    printf("\nTotal Penjualan: Rp%d\n", totalPenjualan);
    
    fclose(rekapPenjualanFile);
	fclose(productFile);

    puts("\nInput '0' untuk kembali\n");
    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    adminDashboard();
}
