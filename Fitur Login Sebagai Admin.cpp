#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MENU 50
#define MAX_NAME 50
#define ADMIN_PASS "admin123"

// Untuk struct menu, cafe menu, order, dan user order
typedef struct {
    char name[MAX_NAME];
    double price;
    int stock;
    double rating;
    int ratingCount;
} Menu;

typedef struct {
    Menu makanan[MAX_MENU];
    Menu minuman[MAX_MENU];
    Menu snack[MAX_MENU];
} CafeMenu;

typedef struct {
    char name[MAX_NAME];
    double price;
    int quantity;
} Order;

typedef struct {
    Order orders[MAX_MENU];
    int orderCount;
} UserOrder;

//untuk tampilan menunya
void displayMenu(Menu menu[], int n) {
    if (n == 0) {
        printf("Menu kosong.\n");
        return;
    }
    printf("\n|%-5s| %-30s | %-10s | %-5s | %-10s\n", "No", "Nama Menu", "Harga", "Stok", "Rating");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("|%-5d| %-30s | Rp %-9.2f | %-5d | %-9.2f\n", i + 1, menu[i].name, menu[i].price, menu[i].stock, menu[i].rating);
    }
}

//fitur untuk tambah menu
void insertMenu(Menu menu[], int *n, const char *filename, const char *jenis) {
    if (*n >= MAX_MENU) {
        printf("Menu %s penuh.\n", jenis);
        return;
    }
    Menu newMenu;
    printf("Masukkan nama %s: ", jenis);
    getchar(); 
    fgets(newMenu.name, MAX_NAME, stdin);
    newMenu.name[strcspn(newMenu.name, "\n")] = '\0';
    printf("Masukkan harga %s: ", jenis);
    newMenu.price = validasiInputDouble();
    printf("Masukkan stock menu baru: ");
    newMenu.stock = validasiInputDouble();

    menu[*n] = newMenu;
    (*n)++;
    saveMenuToFile(menu, *n, filename);
    printf("%s berhasil ditambahkan.\n", jenis);
}

//fitur untuk menghapus menu 
void deleteMenu(Menu menu[], int *n, const char *filename, const char *jenis) {
    if (*n == 0) {
        printf("Menu %s kosong.\n", jenis);
        return;
    }
    displayMenu(menu, *n);
    printf("Masukkan nomor %s yang ingin dihapus: ", jenis);
    int choice = validasiInputInt();

    if (choice < 1 || choice > *n) {
        printf("Pilihan tidak valid.\n");
        return;
    }

    for (int i = choice - 1; i < *n - 1; i++) {
        menu[i] = menu[i + 1];
    }
    (*n)--;
    saveMenuToFile(menu, *n, filename);
    printf("%s berhasil dihapus.\n", jenis);
}

//fitur untuk menambah stock dari menu makanan, minuman, dan snack
void updateStock(Menu menu[], int n) {
    if (n == 0) {
        printf("Menu kosong.\n");
        return;
    }
    displayMenu(menu, n);
    printf("Masukkan nomor menu yang ingin diatur stoknya: ");
    int choice = validasiInputInt();

    if (choice < 1 || choice > n) {
        printf("Pilihan tidak valid.\n");
        return;
    }

    printf("Stok saat ini: %d\n", menu[choice - 1].stock);
    printf("Masukkan stok baru: ");
    int newStock = validasiInputInt();

    if (newStock < 0) {
        printf("Stok tidak boleh negatif.\n");
        return;
    }

    menu[choice - 1].stock = newStock;
    printf("Stok untuk %s berhasil diperbarui menjadi %d.\n", menu[choice - 1].name, newStock);
}
