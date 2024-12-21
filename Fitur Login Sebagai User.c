#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MENU 50
#define MAX_NAME 50
#define ADMIN_PASS "admin123"

//fitur untuk memesan makanan
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

//fitur untuk melakukan sorting (Metode Merge Sort)
void merge(Menu menu[], int left, int mid, int right, int byPrice, int byRating) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Menu leftArray[n1], rightArray[n2];
	
	int i, j;
    for (i = 0; i < n1; i++)
        leftArray[i] = menu[left + i];
    for (i = 0; i < n2; i++)
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

//fitur untuk melakukan pencarian (Metode Sequential Seacrh)
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
	
	int i;
    int found = 0;
    for (i = 0; i < n; i++) {
        if (strcasecmp(menu[i].name, search) == 0) { 
            printf("Ditemukan: %s - Rp %.2f\n", menu[i].name, menu[i].price);
            found = 1;
        }
    }
    if (!found) {
        printf("Menu tidak ditemukan.\n");
    }
}

//fitur untuk memberi rating pada menu
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

//fitur pembatalan pesanan menu
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
	
	int i;
    for (i = 0; i < menuCount; i++) {
        if (strcmp(menu[i].name, order->orders[choice - 1].name) == 0) {
            menu[i].stock += order->orders[choice - 1].quantity;
            break;
        }
    }

    for (i = choice - 1; i < order->orderCount - 1; i++) {
        order->orders[i] = order->orders[i + 1];
    }
    order->orderCount--;

    printf("Pesanan berhasil dibatalkan.\n");
}

//fitur untuk melihat pesanan yang sudah dipesan
void displayOrder(UserOrder *order) {
    if (order->orderCount == 0) {
        printf("Tidak ada pesanan.\n");
        return;
    }
    printf("\nPesanan Anda:\n");
    
	int i;
	for (int i = 0; i < order->orderCount; i++) {
        printf("%d. %s (Rp %.2f) x %d\n", i + 1, order->orders[i].name, order->orders[i].price, order->orders[i].quantity);
    }
}

//fungsi melakukan checkout
void checkout(UserOrder *order) {
    if (order->orderCount == 0) {
        printf("Tidak ada pesanan untuk checkout.\n");
        return;
    }
    int i;
	double total = 0;
    for (i = 0; i < order->orderCount; i++) {
        total += order->orders[i].price * order->orders[i].quantity;
    }
    printf("Total yang harus dibayar: Rp %.2f\n", total);
    printf("Terima kasih atas pesanan Anda!\n");

    order->orderCount = 0; 
    saveOrderToHistory(order);
}

