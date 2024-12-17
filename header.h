#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h> 
#endif 
#define USER_DATABASE "user_database.dat"
#define CART_DATABASE "cart_database.txt"
#define PRODUCT_DATABASE "product_database.txt"
#define REKAP_PENJUALAN_DATABASE "rekap_penjualan_database.txt"

#endif
