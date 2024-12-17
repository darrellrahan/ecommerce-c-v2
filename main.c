#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "produk.h"

int main(int argc, char *argv[]) {
	getJumlahProduk(&jumlahProduk);
	auth();
	
	return 0;
}
