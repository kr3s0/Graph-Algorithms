#ifndef MSGRAF_H
#define MSGRAF_H

class MSGraf{
    int maxBrojCvorova;
    int BrojCvorova,BrojGrana;
    int** Matrica;
    bool* Oznaka;
    static const bool Posjecen = true;
    static const bool Neposjecen = false;
public:
    MSGraf (int maxV);
    ~MSGraf();
    void DodajGranu(int,int,int);
    void DodajBrojCvorova(int);
    inline int DajBrojCvorova(){return BrojCvorova;}
    inline int DajBrojGrana(){return BrojGrana;}
    void BrisiGranu(int,int);
    void BrisiSveGrane();
    int DajTezinu(int,int);
    bool DajOznaku(int);
    void Oznaci(int,bool);
    int PrviSusjed(int);
    int SljedeciSusjed(int,int);
    void OznaciSve();
};
#endif // MSGRAF_H
