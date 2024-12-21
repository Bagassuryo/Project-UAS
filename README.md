#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
Header library untuk: 
•	Stdio.h merupakan header untuk operasi input dan output standar.
•	String.h merupakan header untuk memanipulasi string seperti strcpy, strcmp, strcat, dan lain-lain.
•	Stdlib.h merupakan header untuk fungsi utilitas seperti alokasi memori, konversi data, dan keluar dari program.
•	Ctype.h merupakan header untuk memeriksa dan memanipulasi karakter. 
 
#define MAX_MENU 50
#define MAX_NAME 50
#define ADMIN_PASS "admin123"
•	Define max menu digunakan untuk membatasi jumlah menu maksimal 50 item.
•	Define max name digunakan untuk membatasi jumlah nama menu maksimal 50 karakter.
•	Define admin pass digunakan untuk definisi kata sandi saat akan melakukan login sebagai admin.
 
typedef struct {
    char name[MAX_NAME];
    double price;
    int stock;
    double rating;
    int ratingCount;
} Menu;
Deklarasi struct bernama Menu yang berisi:
•	name bertipe string Panjang 50 karakter.
•	price bertipe double.
•	stock bertipe integer.
•	rating bertipe double.
•	ratingCount bertipe integer.
 
typedef struct {
    Menu makanan[MAX_MENU];
    Menu minuman[MAX_MENU];
    Menu snack[MAX_MENU];
} CafeMenu;
Deklarasi struct bernama CafeMenu untuk deklarasi menu dalam cafe yang berisi:
•	menu makanan.
•	menu minuman.
•	menu snack.
 
typedef struct {
    char name[MAX_NAME];
    double price;
    int quantity;
} Order;
Deklarasi struct bernama Order untuk pesan menu dalam cafe yang berisi:
•	name bertipe string maksimal 50 karakter.
•	price bertipe double.
•	quantity bertipe integer.
 
typedef struct {
    Order orders[MAX_MENU];
    int orderCount;
} UserOrder;
Deklarasi struct bernama UserOrder untuk deklarasi pesanan yang berisi:
•	orders dengan tipe data order maksimal 50 item.
•	orderCount bertipe data integer.
 
FILE *historyFile;
•	Berfungsi sebagai pointer ke file historyFile yang digunakan untuk menyimpan Riwayat pesanan. 
 
double validasiInputDouble();
int validasiInputInt(); 
void displayMenu(Menu menu[], int n); 
void sortMenu(Menu menu[], int n, int byPrice, int byRating); 
void insertMenu(Menu menu[], int *n, const char *filename, const char *jenis); 
void deleteMenu(Menu menu[], int *n, const char *filename, const char *jenis); 
void searchMenu(Menu menu[], int n); 
void updateStock(Menu menu[], int n);.
void addToOrder(Menu menu[], int menuCount, UserOrder *order); 
void displayOrder(UserOrder *order); 
void checkout(UserOrder *order); 
void saveOrderToHistory(UserOrder *order); 
void saveMenuToFile(Menu menu[], int n, const char *filename); 
void loadMenuFromFile(Menu menu[], int *n, const char *filename); 
int adminLogin(); 
int selectCategory();
•	Deklarasi fungsi / prototipe fungsi diatas digunakan untuk memberitahu compiler keberadaan fungsi sebelum digunakan. 

double validasiInputDouble() {
    double value;
    while (scanf("%lf", &value) != 1 || value < 0) {
        printf("Input tidak valid. Masukkan angka positif: ");
        while (getchar() != '\n');
    }
    return value;
}
•	Fungsi ini digunakan untuk validasi input agar bertipe double dan bernilai positif. 
•	Double value merupakan deklarasi untuk menyimpan input bertipe double.
•	Scanf disini akan membaca inputan dari penggua dengan tipe double (Angka Desimal) dan menyimpannya di dalam value.
•	Jika inputan berupa char atau bilangan negatif, maka pengguna akan diminta menginputkan angka positif.
•	Return akan mengembalikan nilai ke fungsi. 
 
int validasiInputInt() {
    int value;
    while (scanf("%d", &value) != 1 || value < 0) {
        printf("Input tidak valid. Masukkan angka positif: ");
        while (getchar() != '\n');
    }
    return value;
}
•	Logika dalam fungsi ini tidak jauh dari berbeda dengan fungsi validasiInputDouble, hanya saja disini fungsi ini digunakan untuk melakukan validasi pada input bertipe integer.
 
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
•	Fungsi ini digunakan untuk menampilkan menu yang ada di cafe dengan parameter struct menu dan juga jumlah menu.
•	Melakukan pengecekan jika menu kosong, maka program akan mencetak “Menu kosong” dan menghentikan eksekusi.
•	Sebaliknya, jika terdapat menu program akan mencetak header tabel dan juga melakukan looping untuk mengiterasi setiap menu yang ada di dalam array Menu[].


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
•	Ini adalah fungsi sorting yang menggunakan metode Merge Sort.
•	Ada tiga bagian dalam metode sort ini, yaitu merge, mergeSort, dan sortMenu.
•	Merge adalah bagian untuk menggabungkan dua subarray yang telah dipisah agar menjadi terurut. Pada fungsi ini, akan ada tiga pilihan sorting, yaitu sorting berdasarkan harga (price), rating, serta nama
•	MergeSort adalah bagian kedua, ini adalah algoritma rekursif yang membagi array menjadi lebih kecil. Kemudian fungsi merge akan dipanggil untuk urutan menggabungkan urutan yang benar.
•	SortMenu hanya memanggil fungsi mergeSort dengan parameter menu, n (jumlah menu), byPrice, dan byRating

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
•	Fungsi ini digunakan untuk menambah menu dengan parameter array menu, pointer n, nama filename tempat menu akan disimpan, serta jenis file.
•	Pertama program akan memeriksa apakah menu sudah penuh, jika iya program akan mencetak “Menu sudah penuh” dan menghentikan eksekusi.
•	Fgets digunakan untuk meminta inputan pengguna hingga MAX_NAME, lalu program akan meminta memasukkan harga dengan validasiDouble agar inputan hanya bisa bertipe double positif, lalu juga stock dengan validasiInt.
•	Program kemudian akan menyimpan menu yang sudah ditambahkan kedalam file.
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

•	Fungsi ini digunakan untuk menghapus menu dengan menampilkan displayMenu dan memilih menu apa yang akan di hapus.
•	Pertama program akan apakah menu kosong atau tidak, jika iya program akan mencetak “Menu Kosong” dan menghentikan eksekusi.
•	Program akan meminta inputan nomor mana yang akan dihapus dengan validasiInt agar nilai yang dimasukkan bertipe integer positif.
•	Fungsi looping disini digunakan untuk menggeser elemen di dalam array setelah dilakukan penghapusan.
•	Program ini kemudian akan menyimpan menu yang dihapus di dalam file.

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
•	Ini adalah fungsi search dengan menggunakan metode sequential search.
•	Pertama program akan melakukan pengecekan, apakah menu kosong apa tidak, jika iya program akan mencetak “Menu Kosong” dan menghentikan eksekusi.
•	Variable found yang dideklarasikan digunakan sebagai indikator untuk melakukan pencarian. 
•	Lopping dilakukan untuk memeriksa menu yang sesuai dalam array Menu. Strcasecmp digunakan untuk membandingkan dua string 
•	Setelah menu ditemukan, mengatur found ke 1.
•	Jika found masih bernilai 0, maka menu tidak di temukan.

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
•	Fungsi ini digunakan untuk melakukan update stock menu.
•	Jika n bernilai 0 maka akan menampilkan menu kosong dan keluar dari fungsi.
•	DisplayMenu digunakan untuk menampilkan daftar menu dengan stoknya. 
•	Program akan meminta untuk memasukkan nomor menu yang ingin diubah, jika input bernilai lebih kecil dari 0 atau lebih besar dari jumlah menu maka akan menampilkan pilihan tidak valid dan mengembalikan fungsi.
•	Jika input valid maka program akan mencetak stok menu saat ini dan diminta untuk memasukkan stok baru, ketika nilai yang dimasukkan negatif maka akan menampilkan pesan dan akan keluar dari fungsi.
•	Jika semua kondisi terpenuhi maka program akan menampilkan stok untuk menu berhasil diperbarui.
 
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
•	Fungsi ini digunakan untuk menambah menu kedalam pesanan dengan parameter array menu, menuCount, dan pointer user.
•	Program akan mengecek apakah menu kosong apa tidak.
•	Program kemudian menampilkan daftar menu dengan memanggil displayMenu.
•	Lalu pengguna akan diminta memasukkan input dan melakukan validasi dengan validasiInt untuk memastikan input yang dimasukkan valid.
•	Terdapat percabangan untuk memastikan inputan pengguna berada dalam rentang menu yang ada dan juga jika stock menu kosong program akan mencetak “Menu Habis”
•	Order newOrder digunakan untuk menyalin data item ke pesanan baru.
•	Inputan jumlah pesanan dengan validasiInt agar inputan dari pengguna valid.
•	Fungsi percabangan digunakan untuk memastikan apabila jumlah stock yang dipesan tidak melebihi jumlah stock yang ada.
•	Mengurangi jumlah stock yang ada dan menambah jumlah pesanan pada code order  -->orderCount++
 
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
•	Fungsi ini digunakan untuk memberikan rating pada menu dengan parameter array menu, n, dan pointer ke jenis menu.
•	Jika n bernilai 0 maka menampilkan menu kosong dan akan mengembalikan fungsi.
•	DisplayMenu digunakan untuk menampilkan daftar menu. 
•	Program akan meminta untuk memasukkan nomor menu yang ingin ditampilkan, lalu dengan ValidasiInputInt akan memastikan apakah input sesuai atau tidak. 
•	Jika input bernilai lebih kecil dari 0 atau lebih besar dari jumlah menu maka akan menampilkan pilihan tidak valid dan mengembalikan fungsi. Jika semua kondisi terpenuhi maka akan menampilkan rating dan ulasan pada menu.
•	Fungsi ini juga dapat melakukan perubahan pada rating dengan rentang nilai double 0.0 hingga 0.5, jika input tidak valid maka akan dilakukan pengulangan input hingga valid.
•	Jika sebelumnya pada menu tidak terdapat rating maka rating akan memperbarui berdasarkan masukan baru. Jika sebelumnya sudah ada rating pada menu maka akan menghitung rata-ratanya.
•	Setelah rating berhasil diperbarui maka akan menampilkan pesan rating berhasil diperbarui.
•	Jika proses penambahan rating selesai maka akan menyimpan perubahan pada file yang sesuai pada menu yang baru diubah. 
 
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
•	Ini adalah fungsi yang digunakan untuk membatalkan pemesanan dengan parameter pointer pesanan, array menu, dan juga jumlah menu.
•	Program akan memeriksa dari orderCount untuk melihat apakah ada menu yang dipesan.
•	Tampilan pesanan akan muncul dengan memanggil displayOrder.
•	Program meminta inputan dari pengguna dan melakukan validasi.
•	Percabangan dilakukan untuk melakukan validasi pada pada nomor pesanan.
•	Looping kemudian dilakukan untuk mengembalikan stock makanan dengan menggunakan string strcmp, jika menu sama maka program akan mengembalikan jumlah menu yang dibatalkan kedalam stock menu.
•	Looping kedua dilakukan untuk menghapus menu yang sudah dibatalkan sebelumnya dari daftar.
 
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
•	Fungsi ini digunakan untuk menampilkan daftar pesanan pengguna dengan parameter UserOrder *order. Dimana order adalah pointer ke struktur UserOrder yang menyimpan informasi pesanan pengguna.
•	Fungsi ini akan menganalisa atau mengecek apakah orderCount adalah 0, yang berarti tidak ada pesanan.
•	Jika tidak ada pesanan, menampilkan pesan "Tidak ada pesanan" dan mengakhiri fungsi.
•	Jika ada pesanan, menampilkan daftar pesanan dengan format: <nomor>. <nama_item> (Rp <harga>) x <jumlah>
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
•	Fungsi ini digunakan untuk melakukan proses checkout pesanan. Dengan parameter UserOrder *order. Dimana order adalah pointer ke struktur UserOrder.
•	Fungsi ini akan mengecek atau menganalisa apakah orderCount adalah 0. Jika benar, menampilkan pesan "Tidak ada pesanan untuk checkout" dan mengakhiri fungsi.
•	Jika ada pesanan, akan dihitung total harga semua pesanan.
•	Menampilkan total yang harus dibayar dengan format:Total yang harus dibayar: Rp <total>
•	Menampilkan pesan "Terima kasih atas pesanan Anda!"
•	Mengosongkan daftar pesanan dengan mengatur orderCount menjadi 0.

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
•	Fungsi ini digunakan untuk menyimpan data menu ke dalam file. Dengan parameter Menu menu[ ] merupakan array struktur Menu yang berisi informasi tentang item menu, int n jumlah item dalam menu, dan const char *filename adalah nama file tempat data menu akan disimpan.
•	Fungsi ini akan membuka file untuk ditulis (w mode). Lalu Mengecek apakah file berhasil dibuka. 
•	Jika tidak, menampilkan pesan error dan mengakhiri fungsi. Menuliskan setiap item menu ke dalam file dengan format: <nama_item>,<harga>,<stok>,<rating>,<jumlah_rating> 
•	Terkahir akan menyimpan dan menutup file.

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
•	Fungsi ini digunakan untuk memuat data menu dari file. Dengan parameter Menu menu[] merupakan array struktur Menu yang akan diisi dengan data dari file, int *n adalah pointer ke integer yang akan menyimpan jumlah item dalam menu setelah dimuat, dan const char *filename adalah nama file tempat data menu disimpan.
•	Fungsi ini akan membuka file untuk dibaca (r mode). Lalu mengecek apakah file berhasil dibuka. 
•	Jika tidak, menampilkan pesan error dan mengakhiri fungsi. 
•	Jika file berhasil dibuka maka program akan membaca setiap baris dalam file dan mem-parsing data ke dalam struktur Menu. 
•	Setleha itu akan mengisi array Menu dan mengupdate jumlah item (*n). 
•	Jika sudah selesai maka fungsi akan menutup file.
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
•	Fungsi untuk login admin yang bertipe data integer.
•	Deklarasi password maksimal 50 karakter.
•	Menampilkan perintah untuk memasukkan password, lalu input akan di scan. Jika password yang diisi benar maka akan mencetak login berhasil dan mengembalikan fungsi 1.
•	Jika input password salah maka akan mencetak password salah dan mengembalikan fungsi.
 
int selectCategory() {
    printf("Pilih kategori menu:\n");
    printf("1. Makanan\n");
    printf("2. Minuman\n");
    printf("3. Snack\n");
    printf("Pilihan Anda: ");
    return validasiInputInt();
}
•	Fungsi integer untuk memilih kategori. 
•	Mencetak pilihan kategori menu seperti makanan, minuman, dan snack.
•	Mencetak pilihan user.
•	Menegmbalikan nilai dengan memvalidasi input user.
 
int main() {
CafeMenu cafe;
int makananCount = 0, minumanCount = 0, snackCount = 0;
UserOrder userOrder = { 0 };
•	Fungsi utama program untuk menjalankan aplikasi menu dan pemesanan cafe dan menangani menu admin serta customer.
•	Deklarasi CafeMenu cafe untuk menyimpan daftar menu.
•	makananCount = 0, minumanCount = 0, snackCount = 0 untuk menghitung jumlah menu masing-masing dan diinisialisasi 0.
•	UserOrder untuk menyimpan pesanan pengguna.
 
historyFile = fopen("history.txt", "a");
if (!historyFile) {
   printf("Peringatan: Tidak dapat membuka file history. Log tidak akan dicatat.\n");
    }
•	Fungsi untuk membuka file history dalam mode a (append) bertujuan untuk mencatat riwayat aktivitas.
•	Jika file gagal dibuka makan akan mencetak kalimat tidak dapat membuka file history.
 
loadMenuFromFile(cafe.makanan, &makananCount, "makanan.txt");
loadMenuFromFile(cafe.minuman, &minumanCount, "minuman.txt");
loadMenuFromFile(cafe.snack, &snackCount, "snack.txt");
•	Fungsi load menu bertujuan untuk membaca item masing-masing menu dari file external dengan jenis txt yang kemudian disimpan dalam variabel cafeMenfu.
 
int choice;
int sortChoice; 
•	variabel untuk menyimpan pilihan.
•	Variabel untuk menyimpan pilihan pengurutan dan kategori.
 
menuUtama:
•	Merupakan label goto untuk mengarahkan eksekusi program ke bagian tertentu. MenuUtama merupakan label penanda posisi, sehingga saat mencapai goto maka program akan langsung mengembalikan ke posisi menuUtama.

do {
 printf("\n=== Sistem Menu Cafe ===\n");
 printf("1. Masuk sebagai Admin\n");
 printf("2. Lanjut sebagai Customer\n");
 printf("0. Keluar\n");
 printf("Pilihan Anda: ");
 choice = validasiInputInt();
 system("cls");
•	Tampilan awal saat program dijalankan.
•	Menampilkan pilihan kepada user ingin masuk sebagai admin atau customer.
•	Setelah pilihan dimasukkan akan memvalidasi input.
 
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
•	Jika pada tampilan menu utama memillih admin / 1 maka tampilan menu akan berubah. 
•	Pada menu ini program akan menampilkan kepada user untuk memasukkan password, jika password salah maka akan mengembalikan program.
•	Jika password benar makan menu admin akan menampilkan tambah menu, hapus menu, dan update stok menu. Kemudian input admin akan divalidasi.
•	Menu admin akan menampilkan pilihan untuk tambah item menu, hapus item menu, dan update stok item.
 
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
•	Switch case untuk pilhan input admin.
•	Case 1 sampai 3 digunakan untuk menambahkan item baru ke menu.
•	Case 4 sampai 6 digunakan untuk menghapus item pada menu. 
•	Case 7 sampai 9 digunakan untuk memperbarui stok setiap item pada menu.
•	Ketika admin sudah melakukan perubahan dan keluar dari program, maka otomatis menyimpan semua perubahan ke file dengan fungsi saveMenuToFile. 
•	Jika user admin memilih case 0 maka akan mengembalikan tampilan ke tampilan awal menu cafe.

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
•	Jika pada tampilan menu utama memillih customer / 2 maka tampilan menu akan berubah. 
•	Menu user akan menampilkan tampilan menu, cari menu, pesan menu, lihat pesanan, checkout, dan pembatalan pesanan.
•	Pada menu ini user juga dapat memberikan rating untuk setiap item pada daftar menu.
 
switch (choice) {
    case 1:
           printf("\nMenu Makanan:\n");
           printf("1. Tanpa Pengurutan\n");
           printf("2. Berdasarkan Harga\n");
           printf("3. Berdasarkan Nama\n");
           printf("4. Berdasarkan Rating\n");  
           Printf("Pilihan Anda: ");
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
•	Case pertama digunakan untuk menampilkan menu makanan dengan memilih pengurutan berdasarkan harga, nama atau rating.
•	Program kemudian memanggil function sort menu dengan parameter yang ada sebelumnya.
•	Setelah kita memilih sorting dari ke empat pilihan diatas, maka program akan memanggil function dsiplayMenu untuk menampilkan daftar menu yang sudah di urutkan.

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
•	Menggunakan logika yang sama dengan case 1, ini digunakan untuk melakukan sorting dan menampilkan menu untuk minuman.

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
•	Untuk case ini juga memiliki logika yang sama dengan case 1 dan case 2.
•	Case ini akan menampilkan daftar menu snack dengan pengurutan yang di inputan user
 
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
•	Case 4 akan muncul saat user memasukkan inputan 4 untuk fitur cari menu.
•	Program akan meminta input penggua untuk kategori makanan, minuman, dan snack.
•	Fungsi seacrh kemduian akan dipanggil pada percabangan pilihan 1, 2, ataupun 3.
•	Jika user memberikan inputan selain 3 pilihan diatas maka program akan mencetak “Pilihan tidak valid.”

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
•	Case kelima adalah penjelasan saat user memberi inputan pesan makanan.
•	Ada tiga kategori yang muncul saat akan memesan menu.
•	Program kemudian memanggil fungsi addToOrder yang sudah di buat sebelumnya.
•	Program akan mencetak “Pilihan tidak valid” jika user memasukkan angka lain selain ketiga kategori diatas.

    case 6:
           displayOrder(&userOrder);
           break;
•	Menampilkan menu yang sudah dipesan dengan memanggil fungsi displayOrder.


    case 7:
           checkout(&userOrder);
           break;
•	Program untuk melakukan checkout pada makanan yang sudah dipesan sebelumnya.
•	Fungsi ini memanggil fungsi checkout dnegan parameter userOrder.

    case 8:
           printf("\nPilih kategori pembatalan:\n");
           printf("1. Makanan\n");
           printf("2. Minuman\n");
           printf("3. Snack\n");
           printf("Pilihan Anda: ");
           sortChoice = validasiInputInt();
 if (sortChoice == 1) cancelOrder(&userOrder,cafe.makanan,makananCount);
 else if (sortChoice == 2) cancelOrder(&userOrder,cafe.minuman,minumanCount);
 else if (sortChoice == 3) cancelOrder(&userOrder,cafe.snack,snackCount);
           else printf("Pilihan tidak valid.\n");
           break;
•	Case ini digunakan saat user memilih fitur pembatalan pesanan.
•	Program memanggil fungsi cancelOrder yang sudah dibuat dengan parameter userOrder, array menu, dan menuCount.

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
•	Case 9 digunakan saat user memilih beri rating pada menu yang sudah dipesan. 
•	Ada 3 kategori yang bisa dipilih oleh user, program kemudian memanggil fungsi giveRating untuk memasukkan rating dari user kedalam file eksternal yang ada.

    case 0:
           printf("Keluar dari Menu Customer.\n");
           goto menuUtama; 
           break;
•	Jika user memasukkan inputan ke-0, maka program akan seketika membawa user ke menu utama, dimana ada pilihan login sebagai admin, lanjut sebagai customer, dan keluar.


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
•	Program akan menutup file History yang sudah dibuka di awal dengan perintah fclose.

    }
 
    return 0;
}

