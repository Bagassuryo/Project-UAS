#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MENU 50
#define MAX_NAME 50
#define ADMIN_PASS "admin123"

//prototype fungsi, digunakan untuk memberi tahu compiler tentang keberadaan fungsi sebelum digunakan
FILE *historyFile;

double validasiInputDouble();
int validasiInputInt();
void displayMenu(Menu menu[], int n);
void sortMenu(Menu menu[], int n, int byPrice, int byRating);
void insertMenu(Menu menu[], int *n, const char *filename, const char *jenis);
void deleteMenu(Menu menu[], int *n, const char *filename, const char *jenis);
void searchMenu(Menu menu[], int n);
void updateStock(Menu menu[], int n);
void addToOrder(Menu menu[], int menuCount, UserOrder *order);
void displayOrder(UserOrder *order);
void checkout(UserOrder *order);
void saveOrderToHistory(UserOrder *order);
void saveMenuToFile(Menu menu[], int n, const char *filename);
void loadMenuFromFile(Menu menu[], int *n, const char *filename);
int adminLogin();
int selectCategory();


double validasiInputDouble() {
    double value;
    while (scanf("%lf", &value) != 1 || value < 0) {
        printf("Input tidak valid. Masukkan angka positif: ");
        while (getchar() != '\n');
    }
    return value;
}

int validasiInputInt() {
    int value;
    while (scanf("%d", &value) != 1 || value < 0) {
        printf("Input tidak valid. Masukkan angka positif: ");
        while (getchar() != '\n');
    }
    return value;
}

int adminLogin() {
    char password[50];
    printf("Masukkan password admin: ");
    scanf("%s", password);
    if (strcmp(password, ADMIN_PASS) == 0) {
        printf("Login berhasil.\n");
        return 1;
    } else {
        printf("Password salah.\n");
        return 0;
    }
}
