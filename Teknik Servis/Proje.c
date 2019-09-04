#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <dos.h>


void clrscr() //Ekran Silme Fonksiyonu
{
    system("@cls||clear");
}


struct genel_bilgi //Girilcek Bilgilerin Tutuldu�u Yap�
{	
	char musteri_sayi[50];
	char musteri_ad[30];
	char musteri_numara[12];
	char musteri_mail[30];
	char musteri_adres[100];
	
	char urun_serino[15];
	char urun_markamodel[50];
	char urun_tur[20];
	char urun_ariza[500];
	char urun_aksesuar[100];
	char urun_gelistarihi[25];
	char urun_teslimalan[30];
	char urun_durum[50];
}yeni,gecici;


	
void urun_ekle()  //�r�nlerin Bilgilerinin Veri Taban�na Eklendi�i Fonksiyon
{
	
	printf(">�R�N EKLEME\n_______________\n");	


	FILE *dosya,*id; 
	dosya=fopen("database.txt","a+");  //database a�mak i�in
	id=fopen("identity.txt","a+");
	
	if(dosya==NULL || id == NULL) 
	{
		printf("Veritaban� a��lamad� veya bulunamad�. L�tfen veritaban�n�z� kontrol edin. Ana men�ye d�n�l�yor...");
		sleep(3);
		clrscr();
		return ;
	}

	char *identity;		int sayi_id; 
	fscanf(id,"%s",identity);	
	sayi_id=atoi(identity);	sayi_id++; //string ifadeyi int e �evirip 1 artt�r�r
	fclose(id);
	
	id=fopen("identity.txt","w"); 
	fprintf(id,"%d",sayi_id);
	fclose(id);
	
	

	///////�R�N G�R��LER�
	
	printf("\n-�r�n Sahibinin;\n");
	printf("Ki�i Numaras�: %d\n",sayi_id); 
	printf("Ad� Soyad�:");			gets(yeni.musteri_ad);			
	printf("Telefon Numaras�:");	gets(yeni.musteri_numara);
	printf("Mail Adresi:");			gets(yeni.musteri_mail);
	printf("Adresi:");				gets(yeni.musteri_adres);
	
	printf("\n-�r�n�n;\n"); 
	printf("Seri Numaras�: ");							gets(yeni.urun_serino);
	printf("Marka/Model: ");							gets(yeni.urun_markamodel);	
	printf("Cihaz T�r�: ");								gets(yeni.urun_tur);	
	printf("G�r�len Ar�zalar: ");						gets(yeni.urun_ariza);	
	printf("Cihaz Yan�nada B�rak�lan Aksesuarlar: ");	gets(yeni.urun_aksesuar);	
	printf("Teslim Alan: ");							gets(yeni.urun_teslimalan);	
	
	
	fprintf(dosya,"%d\t",sayi_id);
	fprintf(dosya,"%s\t",yeni.musteri_ad);
	fprintf(dosya,"%s\t",yeni.musteri_numara);
	fprintf(dosya,"%s\t",yeni.musteri_mail);
	fprintf(dosya,"%s\t",yeni.musteri_adres);
	
	fprintf(dosya,"%s\t",yeni.urun_serino);
	fprintf(dosya,"%s\t",yeni.urun_markamodel);
	fprintf(dosya,"%s\t",yeni.urun_tur);
	fprintf(dosya,"%s\t",yeni.urun_ariza);
	fprintf(dosya,"%s\t",yeni.urun_aksesuar);
	fprintf(dosya,"%s\t",yeni.urun_teslimalan);
	fprintf(dosya,"%s\n","Yapim Asamasinda");
	
	
	//dosya kapatma komutlar�
	if(fclose(dosya)==0)
	{
		fclose(dosya);
		fclose(id);
	}
	printf("Urun Ekleme Basari Ile Gerceklesti...\n\n");
}


void urun_teslim()
{
	
	char kelime[10];
	int sayac=0;
	FILE *aranan=fopen("database.txt","a+");
	FILE *gecicidosya=fopen("database2.txt","a+");
	
	printf("Teslim Edilecek Kisinin Numarasini : ");
	scanf("%s",&kelime);	_flushall();
	if(aranan==NULL || gecicidosya ==NULL)
	{ 
		printf("Veritaban�na Ulasilamiyor...\n\n");
		return ;
	}
	
	char line[sizeof(gecici)];	
	char *idler,*ad,*tel,*mail,*adres,*serino,*marka,*tur,*ariza,*aks,*teslimalan,*durum;
	while(fgets(line,sizeof(line),aranan))
	{	
				idler=strtok(line,"\t");
				ad=strtok(NULL,"\t");
				tel=strtok(NULL,"\t");
				mail=strtok(NULL,"\t");
				adres=strtok(NULL,"\t");
				serino=strtok(NULL,"\t");
				marka=strtok(NULL,"\t");
				tur=strtok(NULL,"\t");
				ariza=strtok(NULL,"\t");
				aks=strtok(NULL,"\t");
				teslimalan=strtok(NULL,"\t");
				durum=strtok(NULL,"\t");
								
			if(strcmp(idler,kelime)==0)
			{
				sayac++;
				fprintf(gecicidosya,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s",idler,ad,tel,mail,adres,serino,marka,tur,ariza,aks,teslimalan,"Teslim Edildi");
				printf("�r�n Teslim Edildi\n");
			}
			else
			{
				
					fprintf(gecicidosya,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s",idler,ad,tel,mail,adres,serino,marka,tur,ariza,aks,teslimalan,durum);
			
			}
		
	}
		if(sayac==0)
		{
			printf("%s numarali kisi bulunamadi.\n\n",kelime);
		}
		
		fclose(aranan);
		fclose(gecicidosya);
		
		remove("database.txt");
		rename("database2.txt","database.txt");
		
		
		
}
void urun_sil()
{
	char kelime[10];
	int sayac=0;
	FILE *aranan=fopen("database.txt","a+");
	FILE *gecicidosya=fopen("database2.txt","a+");
	
	printf("Silinecek Ki�inin Numaras�n� Giriniz : ");
	scanf("%s",&kelime);	_flushall();
	if(aranan==NULL || gecicidosya ==NULL)
	{ 
		printf("Veritaban�na Ula��lam�yor...\n\n");
		return ;
	}
	
	char line[sizeof(gecici)];	
	char *idler,*ad,*tel,*mail,*adres,*serino,*marka,*tur,*ariza,*aks,*teslimalan,*durum;
	while(fgets(line,sizeof(line),aranan))
	{	
				idler=strtok(line,"\t");
				ad=strtok(NULL,"\t");
				tel=strtok(NULL,"\t");
				mail=strtok(NULL,"\t");
				adres=strtok(NULL,"\t");
				serino=strtok(NULL,"\t");
				marka=strtok(NULL,"\t");
				tur=strtok(NULL,"\t");
				ariza=strtok(NULL,"\t");
				aks=strtok(NULL,"\t");
				teslimalan=strtok(NULL,"\t");
				durum=strtok(NULL,"\t");
				printf("Silme i�lemi ba�ar�yla ger�ekle�tirildi.\n");
								
			if(strcmp(idler,kelime)==0)
			{
				sayac++;
			}
			else
			{
				
					fprintf(gecicidosya,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s",idler,ad,tel,mail,adres,serino,marka,tur,ariza,aks,teslimalan,durum);
			
			}
		
	}
		if(sayac==0)
		{
			printf("%s numarali kisi bulunamadi.\n\n",kelime);
		}
		
		fclose(aranan);
		fclose(gecicidosya);
		
		remove("database.txt");
		rename("database2.txt","database.txt");
		
		
		
}

void urun_sorgula()
{	
	_flushall();
	char giris[10],kelime[15];
	printf("Sorgulanacak Kisinin;\n1)Kisi Numaras� ile Sorgulama\n2)Telefon Numaras� ile Sorgulama\n3)Ana Menuye Donmek Icin...\n\nIslem Seciniz:");
	scanf("%s",&giris);	_flushall();
	
	clrscr();
	if(strcmp(giris,"1")==0)
	{
		printf("\nKisi Numarasini Giriniz : "); scanf("%s",kelime);_flushall();
	}
	else if(strcmp(giris,"2")==0)
	{
			printf("\nTelefon Numarasini Giriniz : "); scanf("%s",kelime);_flushall();
	}
	
	else if(strcmp(giris,"3")==0) return;
	
	else
	{
		printf("Yanl�s Giris Yaptiniz...\n\n");
		return;
	}
	
	
		
	FILE *aranan=fopen("database.txt","r");
	
	if(aranan==NULL)
	{ 
		printf("Veritaban�na Ulasilamiyor...\n\n");
		return ;
	}
	
	char line[sizeof(gecici)];	
	char *idler,*ad,*tel,*mail,*adres,*serino,*marka,*tur,*ariza,*aks,*teslimalan,*durum;
	
	while(fgets(line,sizeof(line),aranan))
			{
				idler=strtok(line,"\t");
				ad=strtok(NULL,"\t");
				tel=strtok(NULL,"\t");
				mail=strtok(NULL,"\t");
				adres=strtok(NULL,"\t");
				serino=strtok(NULL,"\t");
				marka=strtok(NULL,"\t");
				tur=strtok(NULL,"\t");
				ariza=strtok(NULL,"\t");
				aks=strtok(NULL,"\t");
				teslimalan=strtok(NULL,"\t");
				durum=strtok(NULL,"\t");
				if(strcmp(giris,"1")==0)
				{
					if(strcmp(idler,kelime)==0)
					{
					printf("Bulunan Kisinin ve Cihazin Bilgileri;\nId : %s\nAd Soyad : %s\nTelefon : %s\nMail : %s\nAdres : %s\nSeri No : %s\nMarka\Model : %s\nCihaz Turu : %s\nAriza : %s\nYaninda Birakilan Aksesuarlar : %s\nTeslim Alan : %s\nCihaz Durumu : %s\n",idler,ad,tel,mail,adres,serino,marka,tur,ariza,aks,teslimalan,durum);
					break;
					}
				}
				else if(strcmp(giris,"2")==0)
				{
					
					if(strcmp(tel,kelime)==0)
					{
					
					printf("Bulunan Kisinin ve Cihazin Bilgileri;\nId : %s\nAd Soyad : %s\nTelefon : %s\nMail : %s\nAdres : %s\nSeri No : %s\nMarka\Model : %s\nCihaz Turu : %s\nAriza : %s\nYaninda Birakilan Aksesuarlar : %s\nTeslim Alan : %s\nCihaz Durumu : %s\n",idler,ad,tel,mail,adres,serino,marka,tur,ariza,aks,teslimalan,durum);
					break;
					}
				}
			}
			
			if(		(strcmp(idler,kelime)!=0)	&&		strcmp(tel,kelime)!=0)
			{
				
				printf("Aranan Kisi Bulunamadi.Lutfen Girdiginiz Bilgilerin Dogrulugundan Emin Olunuz...\n\n");
				fclose(aranan);
				return;
			}
			fclose(aranan);
}


void urun_listele()
{
	FILE *arama;
	arama=fopen("database.txt","r"); //Dosyay� okumak i�in a�ar.
	char line[sizeof(yeni)];		//line de�i�keninin boyutunu yeni isimli struct �n boyutuna e�itler.
	
	
	if(arama==NULL) 
	{
		clrscr();
		printf("Veritaban� a��lamad�. L�tfen veritaban�n�z� kontrol edin. Ana men�ye d�n�l�yor...");
		
		return ;
	}
	
	printf(">�R�N L�STELEME\n_______________\n\n");
	printf("1) T�m �r�nleri Listele\n2) Yap�m A�amas�nda Olanlar� Listele\n3) Teslim Edilen �r�nleri Listele\n��lem Se�iniz : ");
	int giris;
	_flushall();
	scanf("%d",&giris);
	_flushall(); 
	printf("\n");
	
	char *idler,*ad,*tel,*mail,*adres,*serino,*marka,*tur,*ariza,*aks,*teslimalan,*durum;
	printf("%-6s%-25s %-15s %-40s %-15s\n","Id","Ad Soyad","Tel. Numaras�","Mail Adresi","Cihaz Durumu");
	printf("________________________________________________________________________________________________________\n\n");
	
	
	switch(giris)
	{
			
		case 1:
		
			while(fgets(line,sizeof(line),arama))
			{
				idler=strtok(line,"\t");
				ad=strtok(NULL,"\t");
				tel=strtok(NULL,"\t");
				mail=strtok(NULL,"\t");
				adres=strtok(NULL,"\t");
				serino=strtok(NULL,"\t");
				marka=strtok(NULL,"\t");
				tur=strtok(NULL,"\t");
				ariza=strtok(NULL,"\t");
				aks=strtok(NULL,"\t");
				teslimalan=strtok(NULL,"\t");
				durum=strtok(NULL,"\t");
				
				printf("%-6s%-25s %-15s %-40s %-15s\n",idler,ad,tel,mail,durum);
			}
			case 2:
			while(fgets(line,sizeof(line),arama))
			{
				idler=strtok(line,"\t");
				ad=strtok(NULL,"\t");
				tel=strtok(NULL,"\t");
				mail=strtok(NULL,"\t");
				adres=strtok(NULL,"\t");
				serino=strtok(NULL,"\t");
				marka=strtok(NULL,"\t");
				tur=strtok(NULL,"\t");
				ariza=strtok(NULL,"\t");
				aks=strtok(NULL,"\t");
				teslimalan=strtok(NULL,"\t");
				durum=strtok(NULL,"\t");
				if(strcmp(durum,"Yapim Asamasinda\n")==0)
				{
					printf("%-6s%-25s %-15s %-40s %-15s\n",idler,ad,tel,mail,durum);
				}
			}
			
			case 3:
				while(fgets(line,sizeof(line),arama))
			{
				idler=strtok(line,"\t");
				ad=strtok(NULL,"\t");
				tel=strtok(NULL,"\t");
				mail=strtok(NULL,"\t");
				adres=strtok(NULL,"\t");
				serino=strtok(NULL,"\t");
				marka=strtok(NULL,"\t");
				tur=strtok(NULL,"\t");
				ariza=strtok(NULL,"\t");
				aks=strtok(NULL,"\t");
				teslimalan=strtok(NULL,"\t");
				durum=strtok(NULL,"\t");
				if(strcmp(durum,"Yapim Asamasinda\n")!=0)
				{
					printf("%-6s%-25s %-15s %-40s %-15s\n",idler,ad,tel,mail,durum);
				}
			}
				
	}
	
	fclose(arama);
	_flushall();
	return;		
}


void giris_ekrani() //Ana Ekran� G�sterir
{

	gonder:
	printf("\t\t\t\t\t -TEKN�K SERV�SE HO�GELD�N�Z-\n");
	printf("--��lemleri Se�iniz--\n1)Yeni �r�n Ekleme\n2)�r�n Listeleme\n3)�r�n Sorgulama\n4)�r�n Silme\n5)�r�n Teslim etme\n6)Cikis\n");
	
	int giris;
	printf("\n��leminiz->");
	scanf("%d",&giris);
	_flushall(); //GETS ile girilen karakter dizisini giris e atad�
	
	if( giris==1 || giris==2 || giris==3 || giris==4 || giris==5 || giris==6 )
	{
		switch (giris)
		{
			case 1:
				clrscr();
				urun_ekle();
				goto gonder;
			case 2:
				clrscr();
				urun_listele();
				goto gonder;
			case 3:
				clrscr();
				urun_sorgula();
				goto gonder;
			case 4:
				clrscr();
				urun_sil();
				goto gonder;
			case 5:
				clrscr();
				urun_teslim();
				goto gonder;
			case 6:
				printf("��k�s yap�l�yor.");
				sleep(1);
				return;
				exit(0);	
		}
	}
	else 
	{
		clrscr();
		printf("YANLI� G�R��!!!\n\n");
		goto gonder;
	}
	 
	
}


int main(int argc, char **argv)
{

	setlocale(LC_ALL, "Turkish"); //T�rk�e Dil 
	giris_ekrani();

	return 0;
}
