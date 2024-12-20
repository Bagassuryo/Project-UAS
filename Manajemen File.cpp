#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MENU 50
#define MAX_NAME 50
#define ADMIN_PASS "admin123"

//program file untuk menyimpan menu kedalam file dokumen
void saveMenuToFile(Menu menu[], int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Gagal menyimpan ke file %s.\n", filename);
        return;
    }
    for (int i = 0; i < n; i++) {
      fprintf(file, "%s,%.2f,%d,%.2f,%d\n", menu[i].name, menu[i].price, menu[i].stock, menu[i].rating, menu[i].ratingCount);
    }
    fclose(file);
}

//fitur untuk memuat menu dari file dokumen
void loadMenuFromFile(Menu menu[], int *n, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    char line[100];
    *n = 0;
    while (fgets(line, sizeof(line), file)) {
       sscanf(line, "%[^,],%lf,%d,%lf,%d", menu[*n].name, &menu[*n].price, &menu[*n].stock, &menu[*n].rating, &menu[*n].ratingCount); 
        (*n)++;
    }
    fclose(file);
}

