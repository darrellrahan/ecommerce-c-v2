// Author: 241524028 / Roufiel Hadi

#include <stdio.h>
#include <stdlib.h>
#include "akun.h"
#include "auth.h"
#include "others.h"
#include "dashboard.h"

void infoAkun() {
	clearScreen();
    puts("**************************INFO AKUN********************************\n");
    printf("Email         : %s\n", currentUser.email);
    printf("Nama Lengkap  : %s", currentUser.namaLengkap);
    printf("Alamat        : %s", currentUser.alamat);
    printf("Nomor Telepon : %s", currentUser.nomorTelepon);

    puts("\nInput '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();
    
    switch (input)
    {
	    case 0:
	        akun();
	        break;
	    default:
	    	infoAkun();
	        break;
    }
}

void editAkun() {
	clearScreen();
    puts("**************************EDIT AKUN********************************\n");
    printf("Nama Lengkap  : %s", currentUser.namaLengkap);
    printf("Alamat        : %s", currentUser.alamat);
    printf("Nomor Telepon : %s", currentUser.nomorTelepon);
    
    puts("\nInput '1' untuk Edit Nama Lengkap");
    puts("Input '2' untuk Edit Alamat");
    puts("Input '3' untuk Edit Nomor Telepon");
    puts("Input '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();
    
    UserStruct tempUser;
    FILE *file;
    file = fopen(USER_DATABASE, "rb+");
    if (file == NULL) {
        file = fopen(USER_DATABASE, "wb+");
        if (file == NULL) {
            printf("\nGagal membuka atau membuat file untuk pembaruan kata sandi.\n");
            return;
        }
    }
    
    char newValue[100];

    switch (input)
    {
    case 1:
    	printf("\nMasukkan nama lengkap baru: ");
        fgets(newValue, sizeof(newValue), stdin);
        strcpy(currentUser.namaLengkap, newValue);
        while (fread(&tempUser, sizeof(UserStruct), 1, file)) {
	        if (strcmp(tempUser.email, currentUser.email) == 0) {
	            fseek(file, -sizeof(UserStruct), SEEK_CUR);  
	            fwrite(&currentUser, sizeof(UserStruct), 1, file);  
	            break;
	        }
	    }
    	fclose(file);
        editAkun();
        break;
    case 2:
    	printf("\nMasukkan alamat baru: ");
        fgets(newValue, sizeof(newValue), stdin);
        strcpy(currentUser.alamat, newValue);
        while (fread(&tempUser, sizeof(UserStruct), 1, file)) {
	        if (strcmp(tempUser.email, currentUser.email) == 0) {
	            fseek(file, -sizeof(UserStruct), SEEK_CUR);  
	            fwrite(&currentUser, sizeof(UserStruct), 1, file);  
	            break;
	        }
	    }
    	fclose(file);
        editAkun();
        break;
    case 3:
    	printf("\nMasukkan nomor telepon baru: ");
        fgets(newValue, sizeof(newValue), stdin);
        strcpy(currentUser.nomorTelepon, newValue);
        while (fread(&tempUser, sizeof(UserStruct), 1, file)) {
	        if (strcmp(tempUser.email, currentUser.email) == 0) {
	            fseek(file, -sizeof(UserStruct), SEEK_CUR);  
	            fwrite(&currentUser, sizeof(UserStruct), 1, file);  
	            break;
	        }
	    }
    	fclose(file);
        editAkun();
        break;
    case 0:
        akun();
        break;
    default:
    	editAkun();
        break;
    }
}

void gantiPassword() {
	clearScreen();
	puts("**************************GANTI PASSWORD********************************\n");
	
	char currentPassword[100], newPassword[100], confirmPassword[100], hashedPassword[33];
    FILE *file;
    UserStruct tempUser;
    int found = 0;
    
    printf("Masukkan password saat ini: ");
    scanf("%s", currentPassword);
    
    hashPassword(currentPassword, hashedPassword);
    
    if (strcmp(hashedPassword, currentUser.password) != 0) {
        printf("\nKata sandi salah!\n");
        
        puts("\nInput '1' untuk coba lagi");
        puts("Input '0' untuk kembali\n");

	    int input;
	    printf("Input: ");
	    scanf("%d", &input);
	    getchar();
	
	    switch (input)
	    {
	    case 1:
	    	gantiPassword();
	    case 0:
	        akun();
	        break;
	    default:
	    	akun();
	        break;
	    }
    }

    printf("Masukkan password baru: ");
    scanf("%s", newPassword);
    printf("Konfirmasi password baru: ");
    scanf("%s", confirmPassword);

    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("\nKata sandi tidak cocok!\n");
        
        puts("\nInput '1' untuk coba lagi");
        puts("Input '0' untuk kembali\n");

	    int input;
	    printf("Input: ");
	    scanf("%d", &input);
	    getchar();
	
	    switch (input)
	    {
	    case 1:
	    	gantiPassword();
	    case 0:
	        akun();
	        break;
	    default:
	    	akun();
	        break;
	    }
    } else {
        hashPassword(newPassword, currentUser.password);

        file = fopen(USER_DATABASE, "rb+");
        if (file == NULL) {
            file = fopen(USER_DATABASE, "wb+"); 
            if (file == NULL) {
                printf("\nGagal membuka atau membuat file untuk pembaruan kata sandi.\n");
                return;
            }
        }

        while (fread(&tempUser, sizeof(UserStruct), 1, file)) {
            if (strcmp(tempUser.email, currentUser.email) == 0) {
                fseek(file, -sizeof(UserStruct), SEEK_CUR);  
                fwrite(&currentUser, sizeof(UserStruct), 1, file);  
                found = 1;
                break;
            }
        }

        fclose(file);

        if (found) {
            printf("\nKata sandi berhasil diubah!\n");
        } else {
            printf("\nPengguna tidak ditemukan!\n");
        }
    }
    
    puts("\nInput '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    akun();
}

void infoAplikasi()
{
    clearScreen();
    puts("**************************INFO APLIKASI********************************\n");
    puts("Nama Aplikasi         : WARUNG GUDANG GARAM JAYA!");
    puts("Deskripsi Aplikasi    : Platform e-commerce untuk toko kelontong WARUNG GUDANG GARAM JAYA!");
    puts("Versi Aplikasi        : 1.0");

    puts("\nInput '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
	    case 0:
	        akun();
	        break;
	    default:
	    	infoAplikasi();
	        break;
    }
}

void pusatBantuan()
{
    clearScreen();
    puts("**************************PUSAT BANTUAN********************************\n");
    puts("Email         : cs@gudanggaramjaya.com");
    puts("Nomor Telepon : 021-120");
    puts("SMS           : 021120");
    puts("Website       : www.warungmadura.com/help");

    puts("\nInput '0' untuk kembali\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
	    case 0:
	        akun();
	        break;
	    default:
	    	pusatBantuan();
	        break;
    }
}

