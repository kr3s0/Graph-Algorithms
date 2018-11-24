#include "MSGraf.h"

MSGraf::MSGraf(int maxV){
    maxBrojCvorova = maxV;
    BrojCvorova = 0;
    BrojGrana = 0;
    Oznaka = new bool[maxV];
    for(int i=0;i<maxV;i++){
        Oznaka[i] = Neposjecen;
    }
    Matrica = new int*[maxV];
    for(int i=0;i<maxV;i++){
        Matrica[i]=new int[maxV];
    }
    for(int i=0;i<maxBrojCvorova;i++){
        for(int j=0;j<maxBrojCvorova;j++){
            Matrica[i][j]=0;
        }
    }
}

MSGraf::~MSGraf(){
    delete [] Oznaka;
    for(int i=0;i<maxBrojCvorova;i++){
        delete [] Matrica[i];
    }
    delete [] Matrica;
}

void MSGraf::DodajGranu(int v1,int v2,int w){
    if(v1<0 or v1>=BrojCvorova or v2<0 or v2>=BrojCvorova){//Inace treba stajati or w<=0, ali zbog potreba Floyd Algoritma
        throw "Cvorovi koje ste unijeli nisu uredu, ili tezina grane nije pozitivna!\n";//koji radi i sa neg. granam, uklonit cemo to
    }
    if(Matrica[v1][v2] == 0){
        BrojGrana++;
    }
    Matrica[v1][v2] = w;
}

void MSGraf::DodajBrojCvorova(int n){
    if(n > maxBrojCvorova){
        throw "Ne mozete dodati toliko cvorova!";
    }
    BrojCvorova = n;
}

void MSGraf::BrisiGranu(int v1,int v2){
    if(v1<0 or v1>=BrojCvorova or v2<0 or v2>=BrojCvorova){
        throw "Cvorovi koje ste unijeli nisu uredu!\n";
    }
    if(Matrica[v1][v2] == 1){
        BrojGrana--;
    }
    Matrica[v1][v2] = 0;
}

void MSGraf::BrisiSveGrane(){
    for(int i=0;i<BrojCvorova;i++){
        for(int j=0;j<BrojCvorova;j++){
            Matrica[i][j] = 0;
        }
    }
    BrojGrana = 0;
}

int MSGraf::DajTezinu(int v1,int v2){
    if(v1<0 or v1>=BrojCvorova or v2<0 or v2>=BrojCvorova){
        throw "Cvorovi koje ste unijeli nisu uredu!\n";
    }
    return Matrica[v1][v2];
}

bool MSGraf::DajOznaku(int v1){
    if(v1<0 or v1>=BrojCvorova){
        throw "Cvor koji ste unijeli nije uredu1!";
    }
    return Oznaka[v1];
}

void MSGraf::Oznaci(int v1,bool k){
    if(v1<0 or v1>=BrojCvorova){
        throw "Cvor koji ste unijeli nije uredu3!";
    }
    Oznaka[v1] = k;
}

int MSGraf::PrviSusjed(int v1){
    if(v1<0 or v1>=BrojCvorova){
        throw "Cvor koji ste unijeli nije uredu2!";
    }
    for(int i=0;i<BrojCvorova;i++){
        if(Matrica[v1][i]!=0){
            return i;
        }
    }
    return BrojCvorova;
}

int MSGraf::SljedeciSusjed(int v1,int v2){
    if(v1<0 or v1>=BrojCvorova or v2<0 or v2>=BrojCvorova){
        throw "Cvor koji ste unijeli nije uredu!";
    }
    for(int i=v2+1;i<BrojCvorova;i++){
        if(Matrica[v1][i] != 0){
            return i;
        }
    }
    return BrojCvorova;
}

void MSGraf::OznaciSve(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
}

