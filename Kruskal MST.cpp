#include <iostream>
#include <iomanip>
#include <graphics.h>

#define BF 400

using namespace std;

/**GIRILEN DUGUMLERIN TIPI*/
class nokta{
public:
    char isim;
    int koorx;
    int koory;
    bool kontrol;

    nokta(){
        kontrol=false;
    }
};
nokta dugum[BF];

/**
  *GRAF KENARLARI TIPI
  */
struct kopru {
    nokta d1;
    nokta d2;
    int ara;
};
kopru yollar[BF];

/**
  *EN KISA YOLLARIN TUTULDUGU DIZI
  */
kopru kruskal[BF];

/**
  *KOMSULUK MATRISI
  */
int kommatris[40][40];

/**
  *DUGUMLERI GIR
  *MATRISE VE DUGUME AT
  *MATRISI EKRANA YAZ
  */
void dugum_gir(int d_sayisi){
    int i , j;
    int x , y;
    int matris[20][20]={};

    cout<< "degerleri 0-19 arasinda giriniz!"<< endl;
    for(i=0 ; i<d_sayisi ; i++){
        cout<< i+1<< ". dugumun koordinatlarini giriniz."<< endl;

    koorgir:
        cout<< "x'i giriniz:";
        cin>> x;
        cout<< "y'yi giriniz:";
        cin>> y;
        cout<< endl;

        if(x<0 || x>=20 || y<0 || y>=20){
            cout<< "0-19 arasi girmedin!! Tekrar giriniz."<<endl;
            goto koorgir;
        }

        for(j=0 ; j<i ; j++){
            if(x==dugum[j].koorx && y==dugum[j].koory){
                cout<< "bu noktada zaten bir dugum kayitli!!"<< endl
                    << "baska koordinat giriniz."<< endl;
                goto koorgir;
            }
        }

        matris[x][y]=1;
        dugum[i].koorx=x;
        dugum[i].koory=y;
        dugum[i].isim='A'+i;
    }

    cout<< "GIRDIGINIZ DUGUMLER :"<< endl;
    for(i=0 ; i<20 ; i++){
        for(j=0 ; j<20 ; j++){
            cout<< setw(3)<< matris[i][j];
        }
        cout<< endl;
    }
    cout<< endl<< endl;
}

/**
  *DUGUMLER ARASINDAKI MESAFEYI HESAPLA
  */
int uzaklik(int i , int j){
    int degerx;
    int degery;

    degerx=dugum[i].koorx-dugum[j].koorx;
    degery=dugum[i].koory-dugum[j].koory;

    if(degerx<0){
        degerx-=(2*degerx);
    }
    if(degery<0){
        degery-=(2*degery);
    }

    return (degerx+degery);
}

/**
  *KOMSULUK MATRISINI OLUSTUR
  *EKRANA YAZ
  */
void komsuluk(int d_sayisi){
    int i , j;

    cout<< "KOMSULUK MATRISI :"<< endl;
    for(i=0 ; i<d_sayisi ; i++){
        for(j=0 ; j<d_sayisi ; j++){
            kommatris[i][j]=uzaklik(i , j);
            cout<< setw(3)<< kommatris[i][j];
        }
        cout<< endl;
    }
    cout<< endl<< endl;
}

/**
  *DUGUMLER ARASINDAKI BUTUN KENARLARI BIR DIZIYE AT
  *UZAKLIKLARINA GORE KUCUKTEN BUYUKE SIRALA
  */
int kenarlar(int d_sayisi){

    int i , j;
    int yolsay=0;

    /**DIZIYE ATA*/
    for(i=0 ; i<d_sayisi ; i++){
        for(j=i+1 ; j<d_sayisi ; j++){
            yollar[yolsay].d1=dugum[i];
            yollar[yolsay].d2=dugum[j];
            yollar[yolsay].ara=kommatris[i][j];
            yolsay++;
        }
    }

    /**MESAFELERE GORE KUCUKTEN BUYUKE SIRALA*/
    for(i=0 ; i<yolsay-1 ; i++){
        for(j=0 ; j<yolsay-1 ; j++){
            if(yollar[j].ara>yollar[j+1].ara){
                kopru tmp=yollar[j];
                yollar[j]=yollar[j+1];
                yollar[j+1]=tmp;
            }
        }
    }


    /**EKRANA YAZ*/
    cout<< "SIRALI HALI ILE KENARLAR :"<< endl;
    for(i=0 ; i<yolsay ; i++){
        cout<< yollar[i].d1.isim<< " --> "<< yollar[i].d2.isim<< " "<< yollar[i].ara<< endl;
    }
    cout<< endl<< endl;

    return (yolsay);
}

/**
  *KRUSKAL YONTEMI ILE EN KISA YOLU BULUR
  */
void en_kisa_yol(int d_sayisi , int yolsay){

    int i , j , kr_ekle=0 ;

    for(i=0 ; i<yolsay ; i++){
         /**CEVRIM KONTROLU YAPAR*/
        char ekle_d1=yollar[i].d1.isim;
        char ekle_d2=yollar[i].d2.isim;

        for(j=0 ; j<d_sayisi ; j++){
            if(ekle_d1==dugum[j].isim){
                yollar[i].d1.kontrol=dugum[j].kontrol;
            }
            if(ekle_d2==dugum[j].isim){
                yollar[i].d2.kontrol=dugum[j].kontrol;
            }
        }

        if(yollar[i].d1.kontrol==true && yollar[i].d2.kontrol==true){
            cout<< "CEVRIM OLDU! EKLENEMEZ!"<< endl;
        }
        /**CEVRIM YOKSA KENARI EKLER*/
        else{
            cout<< "EKLENDI"<< endl;
            char d1_eklenen=yollar[i].d1.isim;
            char d2_eklenen=yollar[i].d2.isim;
            for(j=0 ; j<d_sayisi ; j++){
                if(d1_eklenen==dugum[j].isim || d2_eklenen==dugum[j].isim){
                    dugum[j].kontrol=true;
                }
            }
            kruskal[kr_ekle]=yollar[i];
            kr_ekle++;
        }
    }

    cout<< "EN KISA YOL :"<< endl;
    for(i=0 ; i<d_sayisi-1 ; i++){
        cout<< kruskal[i].d1.isim<< "---"<< kruskal[i].d2.isim<< " "<< kruskal[i].ara<< endl;
    }
}

void grafik(int d_sayisi){

    int yaricap=20;
    int i;

    for(i=0 ; i<d_sayisi ; i++){

        int c_x=(dugum[i].koorx*30)+25;
        int c_y=(dugum[i].koory*30)+25;
        char *c_i=&dugum[i].isim;

        circle(c_x , c_y , yaricap);
        outtextxy(c_x-5 , c_y-5 , c_i);
    }

    for(i=0 ; i<d_sayisi-1 ; i++){
        line(kruskal[i].d1.koorx*30+25,kruskal[i].d1.koory*30+25,kruskal[i].d2.koorx*30+25,kruskal[i].d2.koory*30+25);
        char mesafe[2];
        itoa(kruskal[i].ara, mesafe , 10);
        outtextxy((kruskal[i].d1.koorx*30+25+kruskal[i].d2.koorx*30+25)/2 , (kruskal[i].d1.koory*30+25+kruskal[i].d2.koory*30+25)/2 , mesafe);
    }
}

int main(){

    int gd=DETECT;
    int gm;
    initgraph(&gd , &gm , "C:\\TC\\BGI");

    int d_sayisi;
    int kenar_sayisi;

    cout<< "Kac dugum girilsin : ";
    cin>> d_sayisi;

    while(d_sayisi<=0 || d_sayisi>BF){
        cout<< "Yanlis deger girdin. Tekrar gir : ";
        cin>> d_sayisi;
    }

    dugum_gir(d_sayisi);
    komsuluk(d_sayisi);
    kenar_sayisi=kenarlar(d_sayisi);
    en_kisa_yol(d_sayisi , kenar_sayisi);
    grafik(d_sayisi);

    getch();
    closegraph();

    return 0;
}
