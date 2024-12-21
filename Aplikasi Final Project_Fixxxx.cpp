#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MENU 50
#define MAX_NAME 50
#define ADMIN_PASS "admin123"

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

void merge(Menu menu[], int left, int mid, int right, int byPrice, int byRating) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Menu leftArray[n1], rightArray[n2];

    for (int i = 0; i < n1; i++)
        leftArray[i] = menu[left + i];
    for (int i = 0; i < n2; i++)
        rightArray[i] = menu[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        int compare = 0;
        
        if (byPrice) {
            compare = leftArray[i].price < rightArray[j].price;
        } else if (byRating) {
            compare = leftArray[i].rating > rightArray[j].rating;
        } else {
            compare = strcmp(leftArray[i].name, rightArray[j].name) < 0;
        }

        if (compare) {
            menu[k++] = leftArray[i++];
        } else {
            menu[k++] = rightArray[j++];
        }
    }

    while (i < n1) {
        menu[k++] = leftArray[i++];
    }
    while (j < n2) {
        menu[k++] = rightArray[j++];
    }
}

void mergeSort(Menu menu[], int left, int right, int byPrice, int byRating) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(menu, left, mid, byPrice, byRating);
        mergeSort(menu, mid + 1, right, byPrice, byRating);

        merge(menu, left, mid, right, byPrice, byRating);
    }
}

void sortMenu(Menu menu[], int n, int byPrice, int byRating) {
    mergeSort(menu, 0, n - 1, byPrice, byRating);
    printf("Menu berhasil diurutkan.\n");
}

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

void searchMenu(Menu menu[], int n) {
    if (n == 0) {
        printf("Menu kosong.\n");
        return;
    }
    printf("Masukkan nama menu yang ingin dicari: ");
    char search[MAX_NAME];
    getchar();
    fgets(search, MAX_NAME, stdin);
    search[strcspn(search, "\n")] = '\0'; 

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcasecmp(menu[i].name, search) == 0) { 
            printf("Ditemukan: %s - Rp %.2f\n", menu[i].name, menu[i].price);
            found = 1;
        }
    }
    if (!found) {
        printf("Menu tidak ditemukan.\n");
    }
}

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

void addToOrder(Menu menu[], int menuCount, UserOrder *order) {
    if (menuCount == 0) {
        printf("Menu kosong.\n");
        return;
    }
    displayMenu(menu, menuCount);
    printf("Masukkan nomor menu yang ingin dipesan: ");
    int choice = validasiInputInt();

    if (choice < 1 || choice > menuCount) {
        printf("Pilihan tidak valid.\n");
        return;
    }

    if (menu[choice - 1].stock <= 0) {
        printf("Menu %s habis.\n", menu[choice - 1].name);
        return;
    }

    Order newOrder;
    strcpy(newOrder.name, menu[choice - 1].name);
    newOrder.price = menu[choice - 1].price;

    printf("Masukkan jumlah pesanan: ");
    newOrder.quantity = validasiInputInt();

    if (newOrder.quantity > menu[choice - 1].stock) {
        printf("Stok tidak mencukupi. Stok tersedia: %d\n", menu[choice - 1].stock);
        return;
    }

    menu[choice - 1].stock -= newOrder.quantity;
    order->orders[order->orderCount++] = newOrder;
    printf("Pesanan berhasil ditambahkan.\n");
}

void giveRating(Menu menu[], int n, const char *jenis) {
    if (n == 0) {
        printf("Menu kosong.\n");
        return;
    }

    displayMenu(menu, n);
    printf("Masukkan nomor menu yang ingin diberi rating: ");
    int choice = validasiInputInt();

    if (choice < 1 || choice > n) {
        printf("Pilihan tidak valid.\n");
        return;
    }

    printf("Rating saat ini untuk %s: %.2f (%d ulasan)\n", 
           menu[choice - 1].name, menu[choice - 1].rating, menu[choice - 1].ratingCount);
    printf("Masukkan rating baru (0.0 - 5.0): ");
    double newRating;

    do {
        newRating = validasiInputDouble();
        if (newRating < 0.0 || newRating > 5.0) {
            printf("Rating harus antara 0.0 hingga 5.0. Masukkan ulang: ");
        }
    } while (newRating < 0.0 || newRating > 5.0);

    if (menu[choice - 1].ratingCount == 0) {
        menu[choice - 1].rating = newRating;
    } else {
        menu[choice - 1].rating = 
            (menu[choice - 1].rating * menu[choice - 1].ratingCount + newRating) / 
            (menu[choice - 1].ratingCount + 1);
    }
    menu[choice - 1].ratingCount++;

    printf("Rating untuk %s berhasil diperbarui menjadi %.2f.\n", 
           menu[choice - 1].name, menu[choice - 1].rating);
           
    if (strcmp(jenis, "Makanan") == 0) {
        saveMenuToFile(menu, n, "makanan.txt");
    } else if (strcmp(jenis, "Minuman") == 0) {
        saveMenuToFile(menu, n, "minuman.txt");
    } else if (strcmp(jenis, "Snack") == 0) {
        saveMenuToFile(menu, n, "snack.txt");
    }

    printf("Data rating berhasil disimpan ke file.\n");
}

void cancelOrder(UserOrder *order, Menu menu[], int menuCount) {
    if (order->orderCount == 0) {
        printf("Tidak ada pesanan untuk dibatalkan.\n");
        return;
    }

    displayOrder(order);

    printf("Masukkan nomor pesanan yang ingin dibatalkan: ");
    int choice = validasiInputInt();

    if (choice < 1 || choice > order->orderCount) {
        printf("Pilihan tidak valid.\n");
        return;
    }

    for (int i = 0; i < menuCount; i++) {
        if (strcmp(menu[i].name, order->orders[choice - 1].name) == 0) {
            menu[i].stock += order->orders[choice - 1].quantity;
            break;
        }
    }

    for (int i = choice - 1; i < order->orderCount - 1; i++) {
        order->orders[i] = order->orders[i + 1];
    }
    order->orderCount--;

    printf("Pesanan berhasil dibatalkan.\n");
}

void displayOrder(UserOrder *order) {
    if (order->orderCount == 0) {
        printf("Tidak ada pesanan.\n");
        return;
    }
    printf("\nPesanan Anda:\n");
    for (int i = 0; i < order->orderCount; i++) {
        printf("%d. %s (Rp %.2f) x %d\n", i + 1, order->orders[i].name, order->orders[i].price, order->orders[i].quantity);
    }
}

void checkout(UserOrder *order) {
    if (order->orderCount == 0) {
        printf("Tidak ada pesanan untuk checkout.\n");
        return;
    }
    double total = 0;
    for (int i = 0; i < order->orderCount; i++) {
        total += order->orders[i].price * order->orders[i].quantity;
    }
    printf("Total yang harus dibayar: Rp %.2f\n", total);
    printf("Terima kasih atas pesanan Anda!\n");

    order->orderCount = 0; 
}

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

int selectCategory() {
    printf("Pilih kategori menu:\n");
    printf("1. Makanan\n");
    printf("2. Minuman\n");
    printf("3. Snack\n");
    printf("Pilihan Anda: ");
    return validasiInputInt();
}

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
}
