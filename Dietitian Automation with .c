#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>


typedef struct hastaBilgileri {

    char tc[11];
    char ad[20];
    char soyad[20];
    char cinsiyet;
    char dtarih[11];
    char adres[50];
    char tel[11];
    char sifre[20];
    int durum;
    char rtarih[11];
    char rsaat[6];
    int boy;
    int kilo;
    float vki;   // vucut kitle endeksi


} hasta ;


void giris()
{

  system("cls");
  printf("Giris ekrani \n");
  hasta h1;
  char tc[11];
  char sifre[20];

  printf("TC: ");
  scanf("%s",&tc);
  printf("Sifre: ");
  scanf("%s",&sifre);
  int sonuc=0;
  
  FILE *ptr = fopen("hastaKayitlari.txt","r+b");

  while( fread(&h1 , sizeof (hasta) ,1,ptr )!=NULL) 
  {
    if( strcmp(h1.tc,tc)==0 && strcmp(h1.sifre,sifre)==0 )
    {
      sonuc=1;
      break;
  }
}
fclose(ptr);
if(sonuc==0)
printf("Hatali giris islemi \n");
else
{
    printf(" %s %s Hos Geldiniz \n",h1.ad,h1.soyad);
    printf("1-Randevu Tarihi:");
    scanf("%s",&h1.rtarih);
    printf("2-Randevu Saati:");
    scanf("%s",&h1.rsaat);
    fclose(ptr);

    ptr=fopen("RandevuTalepEdenhastalar.txt","w+b");
    fwrite(&h1,sizeof(hasta),1,ptr);
    fclose(ptr);
    printf("%s Randevunu talebiniz alinmistir \n",h1.ad);
  
}

}

void yeniKayit()
{
  

    printf("Yeni kayit ekrani \n");

    hasta h1;

    printf("TC: ");
    scanf("%s",&h1.tc);
    printf("Ad: ");
    scanf("%s",&h1.ad);
    printf("Soyad: ");
    scanf("%s",&h1.soyad);
    printf("Cinsiyet: ");
    scanf("%s",&h1.cinsiyet);
    printf("Dogum tarihi: ");
    scanf("%s",&h1.dtarih);
    printf("Adres: ");
    scanf("%s",&h1.adres);
    printf("Telefon: ");
    scanf("%s",&h1.tel);
    printf("Sifre: ");
    scanf("%s",&h1.sifre);
    h1.durum= 0;
    strcpy(h1.rtarih, "0.0");
    strcpy(h1.rsaat, "0.0");
    h1.boy=0;
    h1.kilo=0;
    h1.vki=0.0;


    FILE *ptr = fopen("hastaKayitlari.txt","a+b");

    fwrite(&h1,sizeof(hasta),1,ptr);
    fclose(ptr);
    printf("Yeni Kayit basariyla tamamlandi\n");


}

void parolaHatirlatma()
{

  system("cls");
  printf("Parola  Hatirlatma ekrani \n");
  hasta h1;
  char tc[11];
  char dtarih[20];

  printf("TC: ");
  scanf("%s",&tc);
  printf("dtarihi: ");
  scanf("%s",&dtarih);
  int sonuc=0;
  
  FILE *ptr = fopen("hastaKayitlari.txt","r+b");

  while( fread(&h1 , sizeof (hasta) ,1,ptr )!=NULL) 
  {
    if( strcmp(h1.tc,tc)==0 && strcmp(h1.dtarih,dtarih)==0 )
    {
      sonuc=1;
      break;
  }
}
fclose(ptr);
if(sonuc==0)
printf(" %sve %s ile eslesen  kayit yok \n",tc,dtarih);
else
{
    printf(" %s %s sifreniz  \n",h1.ad,h1.soyad,h1.sifre);
    

}
 

}


void hastaGiris()
{
    system("cls");
    printf("Hasta girisi ekrani \n");

   int secim;
   printf("1-Giris \n");
   printf("2-Yeni Kayit \n");
   printf("3-Parola hatirlatma \n");
   printf("0-Ana Menuye don \n");
   printf("Seciminiz giriniz: ");
   scanf("%d",&secim);
    
    switch(secim)
    {
        case 1:
        giris();
        break;

        case 2:
        yeniKayit();
        break;

        case 3:
        parolaHatirlatma();
        break;

        case 0:
        main();
        break;

        default:
        printf("Hatali secim yaptiniz\n");

    }



}

void sekreter()
{

    system("cls");
    printf("Sekreter giris ekrani \n");
    hasta h1;
    int secim;
    int sayac=0;
    int sonuc=0;
  
   FILE *ptr = fopen("randevuTalepEdenhastalar.txt","r+b");
   
   while( fread(&h1 , sizeof (hasta) ,1,ptr )!=NULL) 
   {
     if(h1.durum==0)
   {
    
    sonuc=1;
    printf("%s\t%s\t%s\t%c\t%s\t%s\n",h1.tc,h1.ad,h1.soyad,h1.cinsiyet,h1.dtarih,h1.adres,h1.tel,h1.sifre,h1.rtarih,h1.rsaat);
    
    printf("1-Radenvu talebi onayla \n");
    printf("2-Randevu talebi reddet \n");
    printf("0-Ana menuye don \n");
    printf("Seciminiz giriniz: ");
    scanf("%d",&secim);
    if(secim==1)
    {
        FILE *ptr2 = fopen("randevuTalebiOnaylananHastalar.txt","a+b");
        fwrite(&h1,sizeof(hasta),1,ptr2);
        fclose(ptr2);
        printf(" %s Randevu talebi onaylandi \n",h1.ad);
    }
    
    else if (secim==2)
    {
        FILE *ptr2 = fopen("randevuTalebiReddedilenHastalar.txt","a+b");
        fwrite(&h1,sizeof(hasta),1,ptr2);
        fclose(ptr2);
        printf(" %s Randevu talebi reddedildi \n",h1.ad);

    }
    
    else 
    {
        fclose(ptr);
        break;
    }
    
    h1.durum=1;

    fseek(ptr,sayac*sizeof(hasta),SEEK_SET); // dosyayi okumaya basladigi yerden itibaren 1 kayit kadar ileri gitsin fseek ile
    fwrite(&h1,sizeof(hasta),1,ptr);  // if'e girsin veya giremsin ama bu islemi yapsin
    fclose(ptr);
    
  }
  
  sayac++;

}

fclose(ptr);
printf("Ana menuye yonlendiriliyorsunuz \n");

if(sonuc==0)
printf("bekleyen hasta yok \n");


}


void doktor()
{

    system("cls");
    printf("Diyetisyen girisi ekrani \n");
    
    hasta h1;
    int secim;
    int sayac=0;
    int sonuc=0;
    char teshis[20];
    char aciklama[100];

    FILE *ptr = fopen("randevuTalebiOnaylananHastalar.txt","r+b");
  
    while (fread(&h1 , sizeof(hasta), 1 ,ptr) !=NULL)
    {
        if(h1.durum ==0)
    {
        sonuc=1;
        printf("%s\t%s\t%s\t%c\t%s\t%s\n",h1.tc,h1.ad,h1.soyad,h1.cinsiyet,h1.dtarih,h1.adres,h1.tel,h1.sifre,h1.rtarih,h1.rsaat);

        printf("1-muayene et \n");
        printf("2-onceki kayitlara bak \n");
        printf("0-Ana menuye don \n");
        printf("Seciminiz giriniz: ");
        scanf("%d",&secim);
        break; 
    }
   
     sayac++;

    }

    if (secim==1)
    {
        printf("boy (1.84 uzunlugunda):");
        scanf("%f",&h1.boy);
        printf("kilo");
        scanf("%f",&h1.kilo);

        h1.vki=  (h1.kilo / (h1.boy*h1.boy) );

        if(h1.vki<18.5)
        strcpy( teshis , "zayif");
        else if(h1.vki>=18.5 && h1.vki<=24.9)
        strcpy( teshis , "normal");
        else if(h1.vki>=25 && h1.vki<=29.9)
        strcpy( teshis , "fazla kilolu");
        else if(h1.vki>=30 && h1.vki<=34.9)
        strcpy( teshis , "1.derece obez");
        else if(h1.vki>=35 && h1.vki<=44.9)
        strcpy( teshis , "2.derece obez");
        else if(h1.vki>=45)
        strcpy( teshis , "3.derece obez");
        else
        strcpy( teshis , "MORBİT OBEZ");


        printf("vki: %f \n",h1.vki);
        printf("teshis: %s \n",teshis);

        printf("Aciklamaniz :");
        scanf("%s",&aciklama);

        char dosyaAdi[20];
        strcpy(dosyaAdi,h1.tc);
        strcat(dosyaAdi,".txt"); // ekleme yaptik strcat ile

        FILE *ptr2 = fopen("dosyaAdi","a");

       
            fprintf(ptr2, "********************* \n") ; 
			fprintf(ptr2, "TC/Ad/Soyad          : %s\t%s\t%s\n", h1.tc, h1.ad, h1.soyad  ) ; 
			fprintf(ptr2, "Muayene tarih/saat   : %s\t%s\n", h1.rtarih, h1.rsaat  ) ; 
			fprintf(ptr2, "Boy/Kilo/ VKI        : %f\t%f\t%f\n", h1.boy, h1.kilo, h1.vki  ) ; 
			fprintf(ptr2, "Teshis               : %s\n", teshis ) ; 
			fprintf(ptr2, "Aciklama             : %s\n\n", aciklama ) ; 
       
        fclose(ptr2);
      
      h1.durum=1;
        
            fseek ( ptr, (sayac) * sizeof(hasta), SEEK_SET  ) ;					
			fwrite ( &h1, sizeof(hasta), 1, ptr ) ; 	
			fclose(ptr) ; 

            printf("muayene islemi tamalandi \n");

    }
   else if (secim==2)
   {
      printf("%s %s onceki kayitlara bakiliyor \n",h1.ad,h1.soyad);

        char dosyaAdi[20];
        strcpy(dosyaAdi,h1.tc);
        strcat(dosyaAdi,".txt"); // ekleme yaptik strcat ile

        FILE *ptr2 = fopen("dosyaAdi","r");

        if(ptr2!=NULL)
        {
            while(!feof(ptr2))
            {
                printf("%c",fgetc(ptr2));
            }
            
            fclose(ptr);
            fclose(ptr2);
        }
        else
        {
            printf(" %s %s hastasi daha once hic muayene olmamis \n",h1.ad,h1.soyad);
            fclose(ptr2);
        }
   }

   else
   fclose(ptr);   
   
}



void personelGiris()
{
    system("cls");
    printf("Personel girisi ekrani \n");
    
    char kullaniciAdi[20];
    char parola[20];

    printf("Kullanici adi: ");
    scanf("%s",&kullaniciAdi);
    printf("Parola: ");
    scanf("%s",&parola);

    if(strcmp(kullaniciAdi,"sekreter")==0 && strcmp(parola,"12345")==0)
    sekreter();
    else if(strcmp(kullaniciAdi,"doktor")==0 && strcmp(parola,"123456")==0)
    doktor();
    else
    printf("Hatali giris denemesi yaptiniz ! \n");



}


int menu ()
{   

    int secim;

    printf("\n\nDIYETISYEN OTOMASYONU\n\n");
    printf("1- Hasta Girisi\n");
    printf("2-Personel Girisi\n");
    printf("0- Cikis\n\n");
    printf("Seciminizi giriniz: ");
    scanf("%d",&secim);

    return secim;

} 

int main()

{

   int secim=menu();

   while (secim!=0)
   {
     switch(secim)
    
    {
        case 1:
        hastaGiris();
        break;

        case 2:
        personelGiris();
        break;

        case 0:
        break;

        default:
        printf("Hatali secim yaptiniz\n");
    }

    secim=menu();

   }



    return 0;
}