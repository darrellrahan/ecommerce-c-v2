// Author: 241524002 / Afriza Choirie Saputra

#ifndef AUTH_H
#define AUTH_H
#include "header.h"
#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct
{
	char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char namaLengkap[50];
    char alamat[100];
    char nomorTelepon[20];	
} UserStruct; // struct untuk user

extern UserStruct currentUser; // variabel global untuk menyimpan detail user yang sedang login saat ini

void auth(); // modul untuk untuk halaman authentication, yaitu halaman yang pertama kali muncul saat program dirun
void registerUser(); // modul untuk proses register
void loginUser(); // modul untuk proses login
void hashPassword(const char *password, char *hashedPassword); // modul untuk proses hashing password
void logout(); // modul untuk proses logout

#endif
