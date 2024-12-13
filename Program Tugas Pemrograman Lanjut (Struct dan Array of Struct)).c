#include <stdio.h>
#include <string.h>

typedef struct{
	int nrp; 
	int umur;
	char nama[30]; 
	char alamat[20]; 
	char jenisKelamin[10];
}Data;

int main (){
	Data data[3];
	
	data[0].nrp = 01;
	strcpy(data[0].nama, "Bagas");
	strcpy(data[0].alamat, "Lamongan");
	strcpy(data[0].jenisKelamin, "Laki-laki");
	data[0].umur = 2005;
	
	data[1].nrp = 02;
	strcpy(data[1].nama, "Suryo");
	strcpy(data[1].alamat, "Lumajang");
	strcpy(data[1].jenisKelamin, "Laki-laki");
	data[1].umur = 2006;
	
	data[2].nrp = 01;
	strcpy(data[2].nama, "Putri");
	strcpy(data[2].alamat, "Surabaya");
	strcpy(data[2].jenisKelamin, "Perempuan");
	data[2].umur = 2003;
	
int i;
for (i = 0; i < 3; i++){
	ptintf ("Siapa yang sakit? Apakah sudah pernah berkunjung? :");
	printf ("Nrp : %d", data[i].nrp);
	printf ("Nama Pasien: %s", data[i].nama);
	printf ("Jenis Kelamin Pasien: %s", data[i].jenisKelamin);
	printf ("Alamat Pasien: %s", data[i].alamat);
	printf ("Umur Pasien: %d", data[i].umur);	
	}
	
	return 0;	
}
