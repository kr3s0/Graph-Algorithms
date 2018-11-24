#include "Red.h"
#include<iostream>

Red::Red(int broj){
    rep = nullptr;
    glava = new Cvor(rep,broj);
    broj_elemenata=1;
}

bool Red::DaLiJePrazan(){
    return broj_elemenata == 0;
}

void Red::Dodaj(int broj){
    if(DaLiJePrazan()){
        rep = nullptr;
        glava = new Cvor(rep,broj);
        broj_elemenata++;
    }
    else if(broj_elemenata == 1){
        rep = new Cvor(nullptr,broj);
        glava->sljedeci = rep;
        broj_elemenata++;
    }
    else{
        Cvor* novi = new Cvor(nullptr,broj);
        rep->sljedeci = novi;
        rep = novi;
        broj_elemenata++;
    }
}

int Red::Izbaci(){
    if(DaLiJePrazan()){
        return -1;
    }
    int zavracanje = glava->vrijednost;
    Cvor* zaBrisanje = glava;
    glava = glava->sljedeci;
    broj_elemenata--;
    delete zaBrisanje;
    return zavracanje;
}

void Red::Ispisi(){
    Cvor* trenutni = glava;
    while(trenutni != nullptr){
        std::cout<<trenutni->vrijednost<<" ";
        trenutni=trenutni->sljedeci;
    }
    std::cout<<std::endl;
}
