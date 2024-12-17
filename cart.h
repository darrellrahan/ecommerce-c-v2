// Author: 241524006 / Darrell Rafa Raihan

#ifndef CART_H
#define CART_H
#include "header.h"
#include "auth.h"
#include "produk.h"

typedef struct
{
    char email[MAX_EMAIL_LENGTH]; // user email associated with the product id
    int id; // the product id
} CartDatabaseStruct; // struct untuk keranjang

void addToCart(int id, char nama[]); // modul untuk menambahkan produk ke keranjang
void getCart(ProductStruct outputCart[], CartDatabaseStruct cartDatabase[]); // modul untuk fetch data terbaru dari database keranjang
void checkout(int totalHarga); // modul untuk checkout produk
void deleteProductFromCart(); // modul untuk hapus produk dari keranjang

#endif
