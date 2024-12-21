#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MENU 50
#define MAX_NAME 50
#define ADMIN_PASS "admin123"

int main() {
    CafeMenu cafe;
    int makananCount = 0, minumanCount = 0, snackCount = 0;
    UserOrder userOrder = { 0 };

    historyFile = fopen("history.txt", "a");
    if (!historyFile) {
        printf("Peringatan: Tidak dapat membuka file history. Log tidak akan dicatat.\n");
    }

    loadMenuFromFile(cafe.makanan, &makananCount, "makanan.txt");
    loadMenuFromFile(cafe.minuman, &minumanCount, "minuman.txt");
    loadMenuFromFile(cafe.snack, &snackCount, "snack.txt");

    int choice;
    int sortChoice; 
    menuUtama:
    do {
        printf("\n=== Sistem Menu Cafe ===\n");
        printf("1. Masuk sebagai Admin\n");
        printf("2. Lanjut sebagai Customer\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        choice = validasiInputInt();
        system("cls");

        if (choice == 1) {
            if (adminLogin()) {
                do {
                    printf("\n=== Menu Admin ===\n");
                    printf("1. Tambah Makanan\n");
                    printf("2. Tambah Minuman\n");
                    printf("3. Tambah Snack\n");
                    printf("4. Hapus Makanan\n");
                    printf("5. Hapus Minuman\n");
                    printf("6. Hapus Snack\n");
                    printf("7. Update Stok Makanan\n");
                    printf("8. Update Stok Minuman\n");
                    printf("9. Update Stok Snack\n");
                    printf("0. Keluar dari Menu Admin\n");
                    printf("Pilihan Anda: ");
                    choice = validasiInputInt();
                    system ("cls");

                    switch (choice) {
                        case 1:
                            insertMenu(cafe.makanan, &makananCount, "makanan.txt", "Makanan");
                            break;
                        case 2:
                            insertMenu(cafe.minuman, &minumanCount, "minuman.txt", "Minuman");
                            break;
                        case 3:
                            insertMenu(cafe.snack, &snackCount, "snack.txt", "Snack");
                            break;
                        case 4:
                            deleteMenu(cafe.makanan, &makananCount, "makanan.txt", "Makanan");
                            break;
                        case 5:
                            deleteMenu(cafe.minuman, &minumanCount, "minuman.txt", "Minuman");
                            break;
                        case 6:
                            deleteMenu(cafe.snack, &snackCount, "snack.txt", "Snack");
                            break;
                        case 7:
                            updateStock(cafe.makanan, makananCount);
                            saveMenuToFile(cafe.makanan, makananCount, "makanan.txt");
                            break;
                        case 8:
                            updateStock(cafe.minuman, minumanCount);
                            saveMenuToFile(cafe.minuman, minumanCount, "minuman.txt");
                            break;
                        case 9:
                            updateStock(cafe.snack, snackCount);
                            saveMenuToFile(cafe.snack, snackCount, "snack.txt");
                            break;
                        case 0:
                            printf("Keluar dari Menu Admin.\n");
                            goto menuUtama;  
                        default:
                            printf("Pilihan tidak valid.\n");
                    }
                } while (1);
            }
        } else if (choice == 2) {
            do {
                printf("\n=== Menu User ===\n");
                printf("1. Tampilkan Menu Makanan\n");
                printf("2. Tampilkan Menu Minuman\n");
                printf("3. Tampilkan Menu Snack\n");
                printf("4. Cari Menu\n");
                printf("5. Pesan Menu\n");
                printf("6. Lihat Pesanan\n");
                printf("7. Checkout\n");
                printf("8. Pembatalan Pesaan\n");
                printf("9. Beri Rating\n");
                printf("0. Keluar dari Menu User\n");
                printf("Pilihan Anda: ");
                choice = validasiInputInt();
                system("cls");

                switch (choice) {
                    case 1:
                        printf("\nMenu Makanan:\n");
                        printf("1. Tanpa Pengurutan\n");
                        printf("2. Berdasarkan Harga\n");
                        printf("3. Berdasarkan Nama\n");
                        printf("4. Berdasarkan Rating\n");  
                        printf("Pilihan Anda: ");
                        sortChoice = validasiInputInt();
                        if (sortChoice == 2) {
                            sortMenu(cafe.makanan, makananCount, 1, 0);
                        } else if (sortChoice == 3) {
                            sortMenu(cafe.makanan, makananCount, 0, 0);
                        } else if (sortChoice == 4) {
                            sortMenu(cafe.makanan, makananCount, 0, 1); 
                        }
                        displayMenu(cafe.makanan, makananCount);
                        break;
                    case 2:
                        printf("\nMenu Minuman:\n");
                        printf("1. Tanpa Pengurutan\n");
                        printf("2. Berdasarkan Harga\n");
                        printf("3. Berdasarkan Nama\n");
                        printf("4. Berdasarkan Rating\n");
                        printf("Pilihan Anda: ");
                        sortChoice = validasiInputInt();
                        if (sortChoice == 2) {
                            sortMenu(cafe.minuman, minumanCount, 1, 0);
                        } else if (sortChoice == 3) {
                            sortMenu(cafe.minuman, minumanCount, 0, 0);
                        } else if (sortChoice == 4) {
                            sortMenu(cafe.minuman, minumanCount, 0, 1); 
                        }
                        displayMenu(cafe.minuman, minumanCount);
                        break;
                    case 3:
                        printf("\nMenu Snack:\n");
                        printf("1. Tanpa Pengurutan\n");
                        printf("2. Berdasarkan Harga\n");
                        printf("3. Berdasarkan Nama\n");
                        printf("4. Berdasarkan Rating\n");
                        printf("Pilihan Anda: ");
                        sortChoice = validasiInputInt();
                        if (sortChoice == 2) {
                            sortMenu(cafe.snack, snackCount, 1, 0);
                        } else if (sortChoice == 3) {
                            sortMenu(cafe.snack, snackCount, 0, 0);
                        } else if (sortChoice == 4) {
                            sortMenu(cafe.snack, snackCount, 0, 1);  
                        }
                        displayMenu(cafe.snack, snackCount);
                        break;

                    case 4:
                        printf("\nPilih kategori pencarian:\n");
                        printf("1. Makanan\n");
                        printf("2. Minuman\n");
                        printf("3. Snack\n");
                        printf("Pilihan Anda: ");
                        sortChoice = validasiInputInt();
                        if (sortChoice == 1) searchMenu(cafe.makanan, makananCount);
                        else if (sortChoice == 2) searchMenu(cafe.minuman, minumanCount);
                        else if (sortChoice == 3) searchMenu(cafe.snack, snackCount);
                        else printf("Pilihan tidak valid.\n");
                        break;
                    case 5:
                        printf("\nPilih kategori untuk dipesan:\n");
                        printf("1. Makanan\n");
                        printf("2. Minuman\n");
                        printf("3. Snack\n");
                        printf("Pilihan Anda: ");
                        sortChoice = validasiInputInt();
                        if (sortChoice == 1) addToOrder(cafe.makanan, makananCount, &userOrder);
                        else if (sortChoice == 2) addToOrder(cafe.minuman, minumanCount, &userOrder);
                        else if (sortChoice == 3) addToOrder(cafe.snack, snackCount, &userOrder);
                        else printf("Pilihan tidak valid.\n");
                        break;
                    case 6:
                        displayOrder(&userOrder);
                        break;
                    case 7:
                        checkout(&userOrder);
                        break;
                    case 8:
                        printf("\nPilih kategori pembatalan:\n");
                        printf("1. Makanan\n");
                        printf("2. Minuman\n");
                        printf("3. Snack\n");
                        printf("Pilihan Anda: ");
                        sortChoice = validasiInputInt();
                        if (sortChoice == 1) cancelOrder(&userOrder, cafe.makanan, makananCount);
                        else if (sortChoice == 2) cancelOrder(&userOrder, cafe.minuman, minumanCount);
                        else if (sortChoice == 3) cancelOrder(&userOrder, cafe.snack, snackCount);
                        else printf("Pilihan tidak valid.\n");
                        break;
					case 9:
                        printf("\nPilih kategori:\n");
                        printf("1. Makanan\n");
                        printf("2. Minuman\n");
                        printf("3. Snack\n");
                        printf("Pilihan Anda: ");
                        sortChoice = validasiInputInt();
                        if (sortChoice == 1) giveRating(cafe.makanan, makananCount, "Makanan");
					    else if (sortChoice == 2) giveRating(cafe.minuman, minumanCount, "Minuman");
						else if (sortChoice == 2) giveRating(cafe.snack, snackCount, "Snack");
						else printf ("Pilihan tidak valid.\n");
						break;
					case 0:
                        printf("Keluar dari Menu Customer.\n");
                        goto menuUtama; 
                        break;
                    default:
                        printf("Pilihan tidak valid.\n");
                }
            } while (1); 
        } else if (choice != 0) {
            printf("Pilihan tidak valid.\n");
        }
    } while (choice != 0); 

    if (historyFile) {
        fclose(historyFile);
    }

    return 0;

