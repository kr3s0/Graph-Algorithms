#ifndef RED_H
#define RED_H

class Red{
    struct Cvor{
        Cvor* sljedeci;
        int vrijednost;
    public:
        Cvor(Cvor* next,int broj){
            sljedeci=next;
            vrijednost=broj;
        }
    };
    Cvor* glava;
    Cvor* rep;
    int broj_elemenata;
public:
    Red(int broj);
    bool DaLiJePrazan();
    void Dodaj(int broj);
    int Izbaci();
    void Ispisi();
};


#endif // RED_H
