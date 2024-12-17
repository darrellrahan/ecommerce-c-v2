// Author: 241524002 / Afriza Choirie Saputra

#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "others.h"
#include "dashboard.h"
#include "admin.h"

UserStruct currentUser;

void auth()
{
    clearScreen();
    puts("**************************GUDANG GARAM JAYA********************************\n");
    puts("Input '1' untuk Register");
    puts("Input '2' untuk Login\n");

    int input;
    printf("Input: ");
    scanf("%d", &input);
    getchar();

    switch (input)
    {
    case 1:
        registerUser();
        break;
    case 2:
        loginUser();
        break;
    default:
        auth();
        break;
    }
}

void registerUser()
{
    clearScreen();
    puts("**************************REGISTER********************************\n");

    FILE *file = fopen(USER_DATABASE, "ab");
    
    UserStruct user;

    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char namaLengkap[50];
    char alamat[100];
    char nomorTelepon[20];

    printf("Masukkan email (tidak boleh ada spasi): ");
    scanf("%s", email);
    printf("Masukkan password (tidak boleh ada spasi): ");
    scanf("%s", password);
    getchar();
    printf("Masukkan nama lengkap: ");
    fgets(namaLengkap, 50, stdin);
    printf("Masukkan alamat: ");
    fgets(alamat, 100, stdin);
    printf("Masukkan nomor telepon: ");
    fgets(nomorTelepon, 20, stdin);
    
    char hashedPassword[33];
    hashPassword(password, hashedPassword);
    
    strcpy(user.email, email);
	strcpy(user.password, hashedPassword);
	strcpy(user.namaLengkap, namaLengkap);
	strcpy(user.alamat, alamat);
	strcpy(user.nomorTelepon, nomorTelepon);

	fwrite(&user, sizeof(UserStruct), 1, file);
    fclose(file);

    loginUser();
}

void loginUser()
{
    clearScreen();
    puts("**************************LOGIN********************************\n");

    FILE *file = fopen(USER_DATABASE, "rb");
    
    UserStruct user;
    
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int loginSuccess = 0;

    printf("Masukkan email (tidak boleh ada spasi): ");
    scanf("%s", email);
    printf("Masukkan password (tidak boleh ada spasi): ");
    scanf("%s", password);
    getchar();
    
    char hashedPassword[33];
    hashPassword(password, hashedPassword);
    
    if (strcmp(email, "admin@mail.com") == 0 && strcmp(password, "admin123") == 0)
    {
        printf("\nLogin berhasil sebagai admin.\n");
        adminDashboard(); 
        return;
    }

	while (fread(&user, sizeof(UserStruct), 1, file)) {
        if (strcmp(email, user.email) == 0 && strcmp(hashedPassword, user.password) == 0) {
        	currentUser = user;
            loginSuccess = 1;
            break;
        }
    }

    fclose(file);

    if (loginSuccess)
    {
        dashboard();
    }
    else
    {
        puts("\nEmail atau Password salah.");
        puts("Input '1' untuk coba lagi");
        puts("Input '2' untuk kembali\n");
        int input;
        printf("Input: ");
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            loginUser();
            break;
        case 2:
            auth();
            break;
        default:
        	auth();
            break;
        }
    }
}

void hashPassword(const char *password, char *hashedPassword) {
	int length = strlen(password);
    for (int i = 0; i < 32; i++) {
        hashedPassword[i] = (password[i % length] ^ (i + 1)) % 94 + 33;
    }
    hashedPassword[32] = '\0';
}

void logout()
{
	strcpy(currentUser.email, "");
	strcpy(currentUser.password, "");
	strcpy(currentUser.namaLengkap, "");
	strcpy(currentUser.alamat, "");
	strcpy(currentUser.nomorTelepon, "");
	
    auth();
}

