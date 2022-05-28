#include <stdio.h>
#include <stdlib.h>
#define odaSayisi 100
#include <string.h>

typedef struct
{
    char *musteriAdi;
    char *musteriSoyadi;
}musteriBilgileri;

typedef struct
{
    int gun;
    int ay;
    int yil;


}tarihBilgileri;

typedef struct
{
    int kisiSayisi;
    int odaDurumu;//bos:0 yada dolu :1
    int odaNumarasi;
    double fiyatBilgisi;

    musteriBilgileri musteri;
    tarihBilgileri girisTarihi;
    tarihBilgileri cikisTarihi;

}odaBilgileri;

typedef enum
{
    musteri=0,
    personel=1
    
}yetkiSeviyeleri;

int gunFarkiHesapla(tarihBilgileri girisTarihi , tarihBilgileri cikisTarihi)//tarihfarkini onlemek icin yapilmistir.
{
    if(girisTarihi.gun>cikisTarihi.gun)
    {
        cikisTarihi.ay-=1;
        cikisTarihi.gun+=30;
    }
    if(girisTarihi.ay>cikisTarihi.ay)
    {
        cikisTarihi.yil-=1;
        cikisTarihi.ay+=12;
    }

    tarihBilgileri tarihFarki;
    tarihFarki.gun=cikisTarihi.gun-girisTarihi.gun;
    tarihFarki.ay=cikisTarihi.ay-girisTarihi.ay;
    tarihFarki.yil=cikisTarihi.yil-girisTarihi.yil;

    int gunFarki=tarihFarki.yil*365+tarihFarki.ay*30+tarihFarki.gun;

    return gunFarki;

}
double fiyatHesaplama(odaBilgileri *odalar,int sorgulanacakOda)
{
     int gunFarki=gunFarkiHesapla(odalar[sorgulanacakOda-1].girisTarihi,odalar[sorgulanacakOda-1].cikisTarihi);
     printf("\t\t\tKalacaginiz Gun Sayisi:%d\n",gunFarki);

     return gunFarki*150*odalar[sorgulanacakOda-1].kisiSayisi;

}

void revervasyonTemizle(odaBilgileri *odalar,int odaNumarasi)
{
    odalar[odaNumarasi-1].odaDurumu=0;//odayi bosalttik.

    free(odalar[odaNumarasi-1].musteri.musteriAdi);//ad ve soyad alanlari bellekte bosaltildi..
    free(odalar[odaNumarasi-1].musteri.musteriSoyadi);

    printf("\t\t\t%d Numarali Odanin Cikis/Iptal Islemi Gerceklestirildi.\n",odaNumarasi);

}

void doluOdaBilgisiYazdirma(odaBilgileri *odalar)
{
    int i;

    for(i=0;i<odaSayisi;i++)
    {
        if(odalar[i].odaDurumu==1)//odalari kontrol eder.
        {
            printf("\t\t\t********************************************\n");
            printf("\t\t\tOda Numarasi:%d\n",odalar[i].odaNumarasi);
            printf("\t\t\tMusteri Ad ve Soyadi:%s %s\n",odalar[i].musteri.musteriAdi,odalar[i].musteri.musteriSoyadi);
            printf("\t\t\tOdadaki Kisi Sayisi:%d\n",odalar[i].kisiSayisi);
            printf("\t\t\tFiyat Bilgisi:%.2lf TL\n",odalar[i].fiyatBilgisi);
            printf("\t\t\tGiris Tarihi:%d:%d:%d\n",odalar[i].girisTarihi.gun,odalar[i].girisTarihi.ay,
                   odalar[i].girisTarihi.yil);
            printf("\t\t\tCikis Tarihi:%d:%d:%d\n",odalar[i].cikisTarihi.gun,odalar[i].cikisTarihi.ay,
                   odalar[i].cikisTarihi.yil);
        }
    }
}

void yeniMusteriEkleme(odaBilgileri *odalar)
{
    int sorgulanacakOda;
    char musteriAdi[20],musteriSoyadi[20],ch;
    printf("\t\t\tLutfen Kayit Olmak Istediginiz Odayi Giriniz:");
    scanf("%d",&sorgulanacakOda);

    if(odalar[sorgulanacakOda-1].odaDurumu!=0)
    {
        printf("\n\t\t\tMaalesef Girdiginiz Oda %d:%d:%d Tarihine Kadar Doludur.\n",odalar[sorgulanacakOda-1].cikisTarihi.gun,
               odalar[sorgulanacakOda-1].cikisTarihi.ay,odalar[sorgulanacakOda-1].cikisTarihi.yil);
        return;
    }
    odalar[sorgulanacakOda-1].odaNumarasi=sorgulanacakOda;//oda numarasi atandi..

    printf("\t\t\tLutfen Ad ve Soyad Bilgilerinizi Giriniz:");
    scanf("%s%s",&musteriAdi,&musteriSoyadi);

    //musteri ad ve soyadlarina boyutlari kadar yer ayirildi..
    odalar[sorgulanacakOda-1].musteri.musteriAdi=(char *)malloc(sizeof(char)*strlen(musteriAdi)+1);
    odalar[sorgulanacakOda-1].musteri.musteriSoyadi=(char *)malloc(sizeof(char)*strlen(musteriSoyadi)+1);

    strcpy(odalar[sorgulanacakOda-1].musteri.musteriAdi,musteriAdi);
    strcpy(odalar[sorgulanacakOda-1].musteri.musteriSoyadi,musteriSoyadi);

    printf("\t\t\tLutfen Odada Kac  Kisi Olacaginizi Giriniz:");
    scanf("%d",&odalar[sorgulanacakOda-1].kisiSayisi);

    printf("\t\t\tLutfen Giris Tarihi Bilgisini (gun:ay:yil) Seklinde Giriniz:");
    scanf("%d:%d:%d",&odalar[sorgulanacakOda-1].girisTarihi.gun,&odalar[sorgulanacakOda-1].girisTarihi.ay,
          &odalar[sorgulanacakOda-1].girisTarihi.yil);

    printf("\t\t\tLutfen Cikis Tarihi Bilgisini (gun:ay:yil) Seklinde Giriniz:");
    scanf("%d:%d:%d",&odalar[sorgulanacakOda-1].cikisTarihi.gun,&odalar[sorgulanacakOda-1].cikisTarihi.ay,
          &odalar[sorgulanacakOda-1].cikisTarihi.yil);

    odalar[sorgulanacakOda-1].fiyatBilgisi=fiyatHesaplama(odalar,sorgulanacakOda);
    printf("\t\t\tOdeyeceginiz Tutar:%.2lf\n",odalar[sorgulanacakOda-1].fiyatBilgisi);

    printf("\n\t\t\tOnayliyor musunuz? (E or H)");
    fflush(stdin);

    ch=getchar();
    if(ch=='H')
    {
       revervasyonTemizle(odalar,sorgulanacakOda);
    }
    else
    {
        printf("\t\t\tKayit Basariyla Gerceklestirildi..\n");
        odalar[sorgulanacakOda-1].odaDurumu=1;//onaylanirsa odayi dolu gosteriyoruz...
    }
}

void OdaDurumuSorgusu(odaBilgileri *odalar,int odaNumarasi)
{
    if(odalar[odaNumarasi-1].odaDurumu!=0)
    {
        printf("\t\t\t%d Numarali Oda %d:%d:%d Tarihine Kadar Baskasi Adina Kayitlidir.\n",odaNumarasi,odalar[odaNumarasi-1].cikisTarihi.gun,
           odalar[odaNumarasi-1].cikisTarihi.ay,odalar[odaNumarasi-1].cikisTarihi.yil);
    }
    else
    {
        printf("\t\t\t%d Numarali Oda Su An Bos Durumdadir.\n",odaNumarasi);
       // yeniMusteriEkleme(odalar);
    }
}

void fiyatBilgisiYazdirma(odaBilgileri *odalar)
{
    int kisiSayisi;
    double toplamTutar=0.0;
    tarihBilgileri girisTarihi,cikisTarihi;
    printf("Lutfen Kac Kisi Olacaginizi Giriniz:");
    scanf("%d",&kisiSayisi);

     printf("\t\t\tLutfen Giris Tarihi Bilgisini (gun:ay:yil) Seklinde Giriniz:");
     scanf("%d:%d:%d",&girisTarihi.gun,&girisTarihi.ay,
          &girisTarihi.yil);

    printf("\t\t\tLutfen Cikis Tarihi Bilgisini (gun:ay:yil) Seklinde Giriniz:");
    scanf("%d:%d:%d",&cikisTarihi.gun,&cikisTarihi.ay,
          &cikisTarihi.yil);

    toplamTutar=gunFarkiHesapla(girisTarihi,cikisTarihi)*kisiSayisi*150;
    printf("\t\t\tOdemeniz Gereken Toplam Total Tutar:%.2lf\n",toplamTutar);

}


void yedekKayitAlma(odaBilgileri *odalar)
{
    FILE *otelKayitlari=fopen("otelKayit.txt","a");//a modu ile surekli uzerine eklenir kaybolma yasanmaz..
    int i;

    if(otelKayitlari!=NULL)
    {
        for(i=0;i<odaSayisi;i++)
        {
             if(odalar[i].odaDurumu!=0)//yani oda doluysa
             {
                   fprintf(otelKayitlari,"*********************************\n");
                   fprintf(otelKayitlari,"Oda Numarasi:%d\n",odalar[i].odaNumarasi);
                   fprintf(otelKayitlari,"Musteri Ad-Soyad:%s %s\n",odalar[i].musteri.musteriAdi,
                        odalar[i].musteri.musteriSoyadi);
                   fprintf(otelKayitlari,"Kisi Sayisi:%d\n",odalar[i].kisiSayisi);
                   fprintf(otelKayitlari,"Toplam Total Tutar:%.2lf\n",odalar[i].fiyatBilgisi);
                   fprintf(otelKayitlari,"Giris Tarihi: %d:%d:%d\n",odalar[i].girisTarihi.gun,
                           odalar[i].girisTarihi.ay,odalar[i].girisTarihi.yil);
                    fprintf(otelKayitlari,"Cikis Tarihi: %d:%d:%d\n",odalar[i].cikisTarihi.gun,
                           odalar[i].cikisTarihi.ay,odalar[i].cikisTarihi.yil);
             }
        }
    }
    else
    {
        fprintf(stderr,"\t\t\tYedekleme Yapilirken Hata Meydana Geldi..");
        exit(0);
    }

    fclose(otelKayitlari);
}

int main()
{
    int personelSifresi=543431,kullaniciGirisiSifre;
    int odaNumarasi;
    char ch;//kullanicinin basta girecegi harf icin yani menu..


    odaBilgileri *odaDizisi;//tum bilgiler burada tutulacak..
    yetkiSeviyeleri kullaniciYetkisi;

    odaDizisi=(odaBilgileri *)calloc(odaSayisi,sizeof(odaBilgileri));//dinamik sekilde olusturuldu. tüm odalar 0 verildi..
    printf("\t\t\tOTEL REZERVASYON SISTEMINE HOSGELDINIZ\t\t\t\n");
    printf("\n\t\tLutfen Burada Calisiyorsaniz Sifrenizi Giriniz:");
    scanf("%d",&kullaniciGirisiSifre);
    printf("\n");

    if(personelSifresi==kullaniciGirisiSifre)//kullanici bir personel
    {
        kullaniciYetkisi=personel;

    }
    else
    {
        printf("\t\t\tHatali Sifre Girisi Yaptiniz..."); //kullanici ,musteri.
        kullaniciYetkisi=musteri;
        printf("\n");
    }
    do
    {
        printf("\n\t\t\t[1] Musteri Kayit Ekrani :'E'\n");
        printf("\t\t\t[2] Oda Bilgisi Sorgulama Ekrani :'S'\n");
        printf("\t\t\t[3] Dolu Oda Bilgileri Goruntuleme Ekrani :'G'\n");
        printf("\t\t\t[4] Fiyat Sorgusu  Ekrani :'F'\n");
        printf("\t\t\t[5] Musteri Cikisi :'C'\n");
        printf("\t\t\t[6] Sistem Cikisi :'Q'\n");
        fflush(stdin);
        printf("\t\t\t");ch=getchar();

        switch(ch)
        {
               case 'E':
               case 'e':
                   {
                       if(kullaniciYetkisi==personel)
                       {
                           yeniMusteriEkleme(odaDizisi);
                       }
                       else
                       {
                           printf("\t\t\tBu Alan Sadece Calisanlar Tarafindan Kullanilabilir.\n");
                       }
                   }
                break;

               case 'S':
               case 's':
                   printf("\t\t\tLutfen Sorgulanacak Olan Odanin Numarasini Giriniz:");
                   scanf("%d",&odaNumarasi);
                   OdaDurumuSorgusu(odaDizisi,odaNumarasi);

                break;

               case 'G':
               case 'g':
                       if(kullaniciYetkisi==personel)
                       {
                           doluOdaBilgisiYazdirma(odaDizisi);
                       }
                       else
                       {
                           printf("\t\t\tBu Alan Sadece Calisanlar Tarafindan Kullanilabilir.\n");
                       }

                    break;

               case 'C':
               case 'c':
                       if(kullaniciYetkisi==personel)
                       {
                           printf("Cikis Yapmak Istediginiz Odanin Numarasini Giriniz:");
                           scanf("%d",&odaNumarasi);
                           revervasyonTemizle(odaDizisi,odaNumarasi);//daha once yazilan fonksiyon kullanildi.
                       }
                       else
                       {
                           printf("\t\t\tBu Alan Sadece Calisanlar Tarafindan Kullanilabilir.\n");
                       }
                    break;

               case 'F':
               case 'f':
                   fiyatBilgisiYazdirma(odaDizisi);
                    break;

               case 'Q':
               case 'q':
                   yedekKayitAlma(odaDizisi);
                    break;

               default:
                    break;
        }

    }while(ch!='Q');

    return 0;
}
