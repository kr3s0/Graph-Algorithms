#include <iostream>
#include<vector>
#include "GrafOperacije.h"
#include<list>

using namespace std;

void Zadatak1_Rumor(){
    int broj_ljudi;
    int broj_parova_prijatelja;
    cin>>broj_ljudi>>broj_parova_prijatelja;
    vector<int> cijene(broj_ljudi);
    for(int i=0;i<broj_ljudi;i++){
        cin>>cijene[i];
    }
    cout<<endl;
    GrafOperacije G1(broj_ljudi+1);
    G1.DodajBrojCvorova(broj_ljudi);
    int x,y;
    for(int i=0;i<broj_parova_prijatelja;i++){
        cin>>x>>y;
        G1.DodajGranu(x-1,y-1,1); //"-1"potrebno jer cvorovi idu od 0;
        G1.DodajGranu(y-1,x-1,1);
    }
    cout<<"Ukupna cijena potrebna da se prosire glasine po selu je:";
    cout<<G1.Glasine(cijene);
}

void Zadatak2_Kefa(){
    int V;
    int NajMacaka;
    cin>>V>>NajMacaka;
    vector<int> macke;
    int k;
    for(int i=0;i<V;i++){
        cin>>k;
        if(k==1){
            macke.push_back(i);
        }
    }
    GrafOperacije G1(V+1);
    G1.DodajBrojCvorova(V);
    int x,y;
    for(int i=0;i<V-1;i++){
        cin>>x>>y;
        G1.DodajGranu(x-1,y-1,1);
        G1.DodajGranu(y-1,x-1,1);
    }
    cout<<"Put kojim kefa treba ici: "<<endl;
    G1.Kefa(0,0,macke,NajMacaka);
    cout<<"Oni listovi koji su ispisati u putu iznad, su restorani u koje Kefa moze ici."<<endl;
}

void Zadatak3_NPHardProblem(){
    int n,m;
    cin>>n>>m;
    GrafOperacije G1(n+1);
    G1.DodajBrojCvorova(n);
    int x,y;
    for(int i=0;i<m;i++){
        cin>>x>>y;
        G1.DodajGranu(x-1,y-1,1);
        G1.DodajGranu(y-1,x-1,1);
    }
    try{
        G1.NPHardProblem();
    }
    catch(const char* k){
        for(int i=0;i<50;i++){
            cout<<*(k+i);
        }
    }
}

void Zadatak4_GregandGraph(){
    int V;
    cin>>V;
    GrafOperacije G1(V+1);
    G1.DodajBrojCvorova(V);
    int tezina;
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            cin>>tezina;
            G1.DodajGranu(i,j,tezina);
        }
        cout<<endl;
    }
    int zaBrisanje;
    for(int i=0;i<V;i++){
        cout<<G1.FloydWarshall()<<endl;
        cin>>zaBrisanje;
        G1.RemoveVertices(zaBrisanje);
    }
}

void Zadatak5_CycleInGraph(){
    int n,m,k;
    cin>>n>>m>>k;
    GrafOperacije G1(n+1);
    G1.DodajBrojCvorova(n);
    int a,b;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        G1.DodajGranu(a-1,b-1,1);//Korisnik unosi cvorove od 1, mi racunamo od 0;
        G1.DodajGranu(b-1,a-1,1);
    }
    G1.CycleInGraph(k);
}

int main(){


 return 0;
}

