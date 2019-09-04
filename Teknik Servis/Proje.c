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


struct genel_bilgi //Girilcek Bilgilerin Tutulduðu Yapý
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


	
void urun_ekle()  //Ürünlerin Bilgilerinin Veri Tabanýna Eklendiði Fonksiyon
{
	
	printf(">ÜRÜN EKLEME\n_______________\n");	


	FILE *dosya,*id; 
	dosya=fopen("database.txt","a+");  //database açmak için
	id=fopen("identity.txt","a+");
	
	if(dosya==NULL || id == NULL) 
	{
		printf("Veritabaný açýlamadý veya bulunamadý. Lütfen veritabanýnýzý kontrol edin. Ana menüye dönülüyor...");
		sleep(3);
		clrscr();
		return ;
	}

	char *identity;		int sayi_id; 
	fscanf(id,"%s",identity);	
	sayi_id=atoi(identity);	sayi_id++; //string ifadeyi int e çevirip 1 arttýrýr
	fclose(id);
	
	id=fopen("identity.txt","w"); 
	fprintf(id,"%d",sayi_id);
	fclose(id);
	
	

	///////ÜRÜN GÝRÝÞLERÝ
	
	printf("\n-Ürün Sahibinin;\n");
	printf("Kiþi Numarasý: %d\n",sayi_id); 
	printf("Adý Soyadý:");			gets(yeni.musteri_ad);			
	printf("Telefon Numarasý:");	gets(yeni.musteri_numara);
	printf("Mail Adresi:");			gets(yeni.musteri_mail);
	printf("Adresi:");				gets(yeni.musteri_adres);
	
	printf("\n-Ürünün;\n"); 
	printf("Seri Numarasý: ");							gets(yeni.urun_serino);
	printf("Marka/Model: ");							gets(yeni.urun_markamodel);	
	printf("Cihaz Türü: ");								gets(yeni.urun_tur);	
	printf("Görülen Arýzalar: ");						gets(yeni.urun_ariza);	
	printf("Cihaz Yanýnada Býrakýlan Aksesuarlar: ");	gets(yeni.urun_aksesuar);	
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
	
	
	//dosya kapatma komutlarý
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
		printf("Veritabanýna Ulasilamiyor...\n\n");
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
				printf("Ürün Teslim Edildi\n");
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
	
	printf("Silinecek Kiþinin Numarasýný Giriniz : ");
	scanf("%s",&kelime);	_flushall();
	if(aranan==NULL || gecicidosya ==NULL)
	{ 
		printf("Veritabanýna Ulaþýlamýyor...\n\n");
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
				printf("Silme iþlemi baþarýyla gerçekleþtirildi.\n");
								
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
	printf("Sorgulanacak Kisinin;\n1)Kisi Numarasý ile Sorgulama\n2)Telefon Numarasý ile Sorgulama\n3)Ana Menuye Donmek Icin...\n\nIslem Seciniz:");
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
		printf("Yanlýs Giris Yaptiniz...\n\n");
		return;
	}
	
	
		
	FILE *aranan=fopen("database.txt","r");
	
	if(aranan==NULL)
	{ 
		printf("Veritabanýna Ulasilamiyor...\n\n");
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
	arama=fopen("database.txt","r"); //Dosyayý okumak için açar.
	char line[sizeof(yeni)];		//line deðiþkeninin boyutunu yeni isimli struct ýn boyutuna eþitler.
	
	
	if(arama==NULL) 
	{
		clrscr();
		printf("Veritabaný açýlamadý. Lütfen veritabanýnýzý kontrol edin. Ana menüye dönülüyor...");
		
		return ;
	}
	
	printf(">ÜRÜN LÝSTELEME\n_______________\n\n");
	printf("1) Tüm Ürünleri Listele\n2) Yapým Aþamasýnda Olanlarý Listele\n3) Teslim Edilen Ürünleri Listele\nÝþlem Seçiniz : ");
	int giris;
	_flushall();
	scanf("%d",&giris);
	_flushall(); 
	printf("\n");
	
	char *idler,*ad,*tel,*mail,*adres,*serino,*marka,*tur,*ariza,*aks,*teslimalan,*durum;
	printf("%-6s%-25s %-15s %-40s %-15s\n","Id","Ad Soyad","Tel. Numarasý","Mail Adresi","Cihaz Durumu");
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


void giris_ekrani() //Ana Ekraný Gösterir
{

	gonder:
	printf("\t\t\t\t\t -TEKNÝK SERVÝSE HOÞGELDÝNÝZ-\n");
	printf("--Ýþlemleri Seçiniz--\n1)Yeni Ürün Ekleme\n2)Ürün Listeleme\n3)Ürün Sorgulama\n4)Ürün Silme\n5)Ürün Teslim etme\n6)Cikis\n");
	
	int giris;
	printf("\nÝþleminiz->");
	scanf("%d",&giris);
	_flushall(); //GETS ile girilen karakter dizisini giris e atadý
	
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
				printf("Çýkýs yapýlýyor.");
				sleep(1);
				return;
				exit(0);	
		}
	}
	else 
	{
		clrscr();
		printf("YANLIÞ GÝRÝÞ!!!\n\n");
		goto gonder;
	}
	 
	
}


int main(int argc, char **argv)
{

	setlocale(LC_ALL, "Turkish"); //Türkçe Dil 
	giris_ekrani();

	return 0;
}
