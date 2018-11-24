#include "GrafOperacije.h"
#include<iostream>
#include<queue>
#include<vector>
#include<unordered_set>
#include<stack>
#include<climits>

using namespace std;

void GrafOperacije::Sirina(int c){
    queue<int> Red;
    Red.push(c);
    Oznaci(c,Posjecen);
    while(!Red.empty()){
        int trenutni = Red.front();
        Red.pop();
        cout<<"->"<<trenutni;
        for(int i = PrviSusjed(trenutni);i<DajBrojCvorova();i = SljedeciSusjed(trenutni,i)){
            if(DajOznaku(i)==Neposjecen){
                Oznaci(i,Posjecen);
                Red.push(i);
            }
        }
    }
}

void GrafOperacije::Dubina(int c){
    cout<<"->"<<c;
    Oznaci(c,Posjecen);
    for(int i=PrviSusjed(c);i<DajBrojCvorova();i=SljedeciSusjed(c,i)){
        if(DajOznaku(i)==Neposjecen){
            Dubina(i);
        }
    }
}

void GrafOperacije::PotpunaDubina(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    for(int i=0;i<DajBrojCvorova();i++){
        if(DajOznaku(i)==Neposjecen){
            Dubina(i);
        }
    }
}

void GrafOperacije::PotpunaSirina(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    for(int i=0;i<DajBrojCvorova();i++){
        if(DajOznaku(i)==Neposjecen){
            Sirina(i);
        }
    }
}

void GrafOperacije::IspisiKomponentePovezanosti(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    int broj = 1;
    for(int i=0;i<DajBrojCvorova();i++){
        if(DajOznaku(i)==Neposjecen){
            cout<<broj<<".komponenta povezanosti:"<<endl;
            Dubina(i);
            cout<<endl;
            broj++;
        }
    }
}

bool GrafOperacije::PostojiPut(int v1,int v2){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    int counter = 0;
    queue<int> Red;
    Red.push(v1);
    Oznaci(v1,Posjecen);
    while(!Red.empty()){
        int trenutni = Red.front();
        Red.pop();
        if(trenutni == v2){
            cout<<counter;
            cout<<endl;
            return true;
        }
        for(int i = PrviSusjed(trenutni);i<DajBrojCvorova();i = SljedeciSusjed(trenutni,i)){
            if(DajOznaku(i)==Neposjecen){
                Oznaci(i,Posjecen);
                counter++;
                Red.push(i);
            }
        }
    }
    cout<<counter;
    cout<<endl;
    return false;
}

bool GrafOperacije::Povezan(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    int broj = 0;
    for(int i=0;i<DajBrojCvorova();i++){
        if(DajOznaku(i)==Neposjecen){
            Dubina(i);
            broj++;
        }
    }
    if(broj != 1){
        return false;
    }
    return true;
}

bool GrafOperacije::NeusmjereniCiklus(int v1,int roditelj){
    Oznaci(v1,Posjecen);
    for(int i=PrviSusjed(v1);i<DajBrojCvorova();i=SljedeciSusjed(v1,i)){
        if(DajOznaku(i)==Neposjecen){
            if(NeusmjereniCiklus(i,v1)){
                return true;
            }
        }
        else if(i!=roditelj){
            return true;
        }
    }
    return false;
}

bool GrafOperacije::NeusmjereniCiklican(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    for(int i=0;i<DajBrojCvorova();i++){
        if(DajOznaku(i)==Neposjecen){
            if(NeusmjereniCiklus(i,-1)){
                return true;
            }
        }
    }
    return false;
}

//Prvo pozvati OznaciSve();
bool GrafOperacije::IspisiPut(int v1,int v2){
    bool rez;
    Oznaci(v1,Posjecen);
    for(int i=PrviSusjed(v1);i<DajBrojCvorova();i=SljedeciSusjed(v1,i)){
        if(DajOznaku(i)==Neposjecen){
            rez = IspisiPut(i,v2);
            if(rez){
                break;
            }
        }
    }
    if(v1 == v2 or rez){
        cout<<"->"<<v1;
        return true;
    }
    else{
        return false;
    }
}

void GrafOperacije::OznaciSve(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
}

void GrafOperacije::Kefa(int prvi,int counter,vector<int> &macke,int NajMacaka){
    bool ima_ga = false;
    /*
    Ili da koristimo pair<int,bool> gdje bi int bio index vrha , a bool vrijednost da li dati vrh ima macku ili ne.
    Tada bi blok ispod postao jednostavno: if prvi.second then counter + = 1 ,else counter = 0;
    */
    for(int i=0;i<macke.size();i++){
        if(macke[i]==prvi){
            counter++;
            ima_ga=true;
            break;
        }
    }
    if(!ima_ga){
        counter=0;
    }
    Oznaci(prvi,Posjecen);
    if(counter > NajMacaka){
        return;
    }
    for(int i = PrviSusjed(prvi);i<DajBrojCvorova();i=SljedeciSusjed(prvi,i)){
        if(DajOznaku(i)==Neposjecen){
            Kefa(i,counter,macke,NajMacaka);
        }
    }
    if(counter <= NajMacaka){
        cout<<prvi<<" ";
    }
}

//https://codeforces.com/problemset/problem/687/A
//dokaz da se ovaj problem može svesti na ispitivanje bipartitivnosti tj ekvivalencija <=>;
/*

*/
bool GrafOperacije::Bipartitivan(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    vector<int> boje(DajBrojCvorova());
    for(int i=1;i<boje.size();i++){
        boje[i]=0;
    }
    return PrivatniBipartitiv(0,boje,2);
}

void GrafOperacije::NPHardProblem(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    for(int i=0;i<DajBrojCvorova();i++){
        if(DajOznaku(i)==Neposjecen){
            vector<int> boje(DajBrojCvorova());
            for(int j=1;j<boje.size();j++){
                boje[j]=0;
            }
            if(PrivatniBipartitiv(i,boje,2)){
                int counter1=0;
                int counter2=0;
                vector<int> prvi,drugi;
                for(int k=0;k<boje.size();k++){
                    if(boje[k]==1){
                        counter1++;
                        prvi.push_back(k);
                    }
                    else{
                        counter2++;
                        drugi.push_back(k);
                    }
                }
                cout<<counter1<<endl;
                for(int k=0;k<prvi.size();k++){
                    cout<<prvi[k]<<" ";
                }
                cout<<endl;
                cout<<counter2<<endl;
                for(int k=0;k<drugi.size();k++){
                    cout<<drugi[k]<<" ";
                }
                cout<<endl;
            }
        }
    }
}

bool GrafOperacije::PrivatniBipartitiv(int v,vector<int> &boje,int prosla){
    int trenutna = 1;
    if(prosla == 1){
        trenutna=2;
    }
    for(int i=PrviSusjed(v);i<DajBrojCvorova();i=SljedeciSusjed(v,i)){
        if(boje[i]==trenutna){
            return false;
        }
    }
    boje[v]=trenutna;
    Oznaci(v,Posjecen);
    for(int i=PrviSusjed(v);i<DajBrojCvorova();i=SljedeciSusjed(v,i)){
        if(DajOznaku(i)==Neposjecen){
            if(!PrivatniBipartitiv(i,boje,trenutna)){
                return false;
            }
        }
    }
    return true;
}

bool GrafOperacije::UsmjereniCiklican(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    unordered_set<int> hes;
    return UsmjereniCiklus(0,hes);
}

bool GrafOperacije::UsmjereniCiklus(int v,unordered_set<int>& hes){
    if(hes.find(v)==hes.end()){
        hes.insert(v);
    }
    else{
        return true;
    }
    Oznaci(v,Posjecen);
    for(int i=PrviSusjed(v);i<DajBrojCvorova();i=SljedeciSusjed(v,i)){
        if(DajOznaku(i)==Neposjecen){
            if(UsmjereniCiklus(i,hes)){
                return true;
            }
        }
        else{
            return UsmjereniCiklus(i,hes);
        }
    }
    hes.erase(v);
    return false;
}

int GrafOperacije::DuzinaPuta(int v1,int v2){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    int counter = 0;
    queue<int> Red;
    Red.push(v1);
    Oznaci(v1,Posjecen);
    while(!Red.empty()){
        int trenutni = Red.front();
        Red.pop();
        if(trenutni == v2){
            return counter;
        }
        for(int i = PrviSusjed(trenutni);i<DajBrojCvorova();i = SljedeciSusjed(trenutni,i)){
            if(DajOznaku(i)==Neposjecen){
                Oznaci(i,Posjecen);
                counter++;
                Red.push(i);
            }
        }
    }
    return counter;
}

int GrafOperacije::Diametar(){
    int najduzi = 0;
    for(int i=0;i<DajBrojCvorova();i++){
        for(int j=i+1;j<DajBrojCvorova();j++){
            int trenutni = DuzinaPuta(i,j);
            if(trenutni > najduzi){
                najduzi = trenutni;
            }
        }
    }
    return najduzi;
}

void GrafOperacije::TopoloskoSortiranje(){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    stack<int> TS;
    for(int i=0;i<DajBrojCvorova();i++){
        if(DajOznaku(i)==Neposjecen){
            PrivatnoTopoloskoSortiranje(i,TS);
        }
    }
    while(!TS.empty()){
        cout<<TS.top()<<" ";
        TS.pop();
    }
    cout<<endl;
}

void GrafOperacije::PrivatnoTopoloskoSortiranje(int v,stack<int>& TS){
    Oznaci(v,Posjecen);
    for(int i = PrviSusjed(v);i<DajBrojCvorova();i=SljedeciSusjed(v,i)){
        if(DajOznaku(i)==Neposjecen){
            PrivatnoTopoloskoSortiranje(i,TS);
        }
    }
    TS.push(v);
}

int MinKey(int keys[],bool notyetMST[],int V){
    int mini = 100;
    int min_index;
    for(int i=0;i<V;i++){
        if(notyetMST[i]==true and keys[i]<mini){
            mini = keys[i];
            min_index = i;
        }
    }
    return min_index;
}

void GrafOperacije::MinimalSpanningTree(){
    int MST_inprogress[DajBrojCvorova()];
    int keys[DajBrojCvorova()];
    bool notyetMST[DajBrojCvorova()];//Za sve one koji jos nisu u MST-u drzimo true, ako udju u MST postaju false
    for(int i=0;i<DajBrojCvorova();i++){
        keys[i]=100;
        notyetMST[i]=true;
    }
    keys[0]=0;
    MST_inprogress[0]=-1;
    for(int i=0;i<DajBrojCvorova()-1;i++){
        int next = MinKey(keys,notyetMST,DajBrojCvorova());
        notyetMST[next]=false;
        for(int k = PrviSusjed(next);k<DajBrojCvorova();k=SljedeciSusjed(next,k)){
            if(DajTezinu(next,k) and notyetMST[k]==true and DajTezinu(next,k)<keys[k]){
                MST_inprogress[k]=next;
                keys[k]=DajTezinu(next,k);
            }
        }
    }
    for(int i = 1;i<DajBrojCvorova();i++){
        cout<<MST_inprogress[i]<<" "<<i<<" "<<DajTezinu(i,MST_inprogress[i])<<" ";
    }
    cout<<endl;
}

void GrafOperacije::GreedyBojenje(){
    int colored_vertices[DajBrojCvorova()];
    bool available_color[DajBrojCvorova()];
    colored_vertices[0]=0;
    available_color[0]=true;
    for(int i=1;i<DajBrojCvorova();i++){
        colored_vertices[i]=-1;
        available_color[i]=true;
    }
    for(int i=1;i<DajBrojCvorova();i++){
        for(int j=PrviSusjed(i);j<DajBrojCvorova();j=SljedeciSusjed(i,j)){
            if(colored_vertices[j]!=-1){
                available_color[colored_vertices[j]]=false;
            }
        }
        for(int j=0;j<DajBrojCvorova();j++){
            if(available_color[j]==true){
                colored_vertices[i]=j;
                break;
            }
        }
        for(int j=PrviSusjed(i);j<DajBrojCvorova();j=SljedeciSusjed(i,j)){
            if(colored_vertices[j]!=-1){
                available_color[colored_vertices[j]]=true;
            }
        }
    }
    for(int i=0;i<DajBrojCvorova();i++){
        cout<<i<<" je boje "<<colored_vertices[i]<<" "<<endl;
    }
}

int GrafOperacije::Glasine(vector<int>& c){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    int rezultat = 0;
    for(int i=0;i<DajBrojCvorova();i++){
        if(DajOznaku(i)==Neposjecen){
            int counter = 100;
            rezultat += PrivatniGlasine(i,counter,c);
        }
    }
    return rezultat;
}

int GrafOperacije::PrivatniGlasine(int v,int& counter,vector<int>& c){
    Oznaci(v,Posjecen);
    if(counter > c[v]){
        counter = c[v];
    }
    for(int i=PrviSusjed(v);i<DajBrojCvorova();i=SljedeciSusjed(v,i)){
        if(DajOznaku(i)==Neposjecen){
            PrivatniGlasine(i,counter,c);
        }
    }
    return counter;
}

void GrafOperacije::DijkstraShortestPath(int pocetak){
    int* udaljenosti = new int[DajBrojCvorova()];
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
        udaljenosti[i]=100;
    }
    udaljenosti[pocetak]=0;
    for(int i=0;i<DajBrojCvorova();i++){
        int trenutni = DijkstraShortestPathPrivate(udaljenosti);
        Oznaci(trenutni,Posjecen);
        for(int j=PrviSusjed(trenutni);j<DajBrojCvorova();j=SljedeciSusjed(trenutni,j)){
            if(!DajOznaku(j) and udaljenosti[j]>udaljenosti[trenutni]+DajTezinu(trenutni,j)){
                udaljenosti[j]=udaljenosti[trenutni]+DajTezinu(trenutni,j);
            }
        }
    }
    for(int i=0;i<DajBrojCvorova();i++){
        cout<<"Udaljenost cvora "<<i<<" od "<<pocetak<<" je "<<udaljenosti[i]<<endl;
    }
}


int GrafOperacije::DijkstraShortestPathPrivate(int* udaljenosti){
    int min_index;
    int minimal_vrijednost = 100;
    for(int i=0;i<DajBrojCvorova();i++){
        if(!DajOznaku(i) and udaljenosti[i]<=minimal_vrijednost){
            min_index=i;
            minimal_vrijednost=udaljenosti[i];
        }
    }
    return min_index;
}

int GrafOperacije::FloydWarshall(){ //https://codeforces.com/problemset/problem/295/B
    int** Udaljenosti = new int*[DajBrojCvorova()];
    for(int i=0;i<DajBrojCvorova();i++){
        Udaljenosti[i] = new int[DajBrojCvorova()];
    }
    for(int i=0;i<DajBrojCvorova();i++){
        for(int j=0;j<DajBrojCvorova();j++){
            if(j==i){
                Udaljenosti[i][j]=0; //Udaljenosti[i][i]
            }
            else{
                if(DajTezinu(i,j)==0){
                    Udaljenosti[i][j]=100; //Teorijski bi trebali koristiti INT_MAX
                }
                else{
                    Udaljenosti[i][j]=DajTezinu(i,j);
                }
            }
        }
    }
    for(int i=0;i<DajBrojCvorova();i++){
        for(int j=0;j<DajBrojCvorova();j++){
            for(int k=0;k<DajBrojCvorova();k++){
                if(Udaljenosti[j][k]>Udaljenosti[j][i]+Udaljenosti[i][k]){
                    Udaljenosti[j][k]=Udaljenosti[j][i]+Udaljenosti[i][k];
                }
            }
        }
    }
    int ukupna_suma = 0;
    for(int i=0;i<DajBrojCvorova();i++){
        for(int j=0;j<DajBrojCvorova();j++){
            if(Udaljenosti[i][j]!=100){
                ukupna_suma+=Udaljenosti[i][j];
            }
        }
    }
    for(int i=0;i<DajBrojCvorova();i++){
        delete [] Udaljenosti[i];
    }
    delete [] Udaljenosti;
    return ukupna_suma;
}

void GrafOperacije::RemoveVertices(int v){
    for(int j=0;j<DajBrojCvorova();j++){
        BrisiGranu(v,j);
        BrisiGranu(j,v);
    }
}

void GrafOperacije::CycleInGraph(int k){
    for(int i=0;i<DajBrojCvorova();i++){
        Oznaci(i,Neposjecen);
    }
    for(int i=0;i<DajBrojCvorova()-k;i++){
        if(CycleInGraphPrivate(k,i,i)){
            return;
        }
        Oznaci(i,Posjecen);
    }
}

bool GrafOperacije::CycleInGraphPrivate(int k,int v,int pocetak){
    Oznaci(v,Posjecen);
    if(k==0){
        Oznaci(v,Neposjecen);
        if(DajTezinu(pocetak,v)){
            int i=0;
            while(DajOznaku(i)){
                cout<<i<<" ";
                i++;
            }
            cout<<v<<" "<<pocetak<<endl;
            return true;
        }
        else{
            return false;
        }
    }
    for(int i=0;i<DajBrojCvorova();i++){
        if(!DajOznaku(i) and DajTezinu(v,i)){
            if(CycleInGraphPrivate(k-1,i,pocetak)){
                return true;
            }
        }
    }
    Oznaci(v,Neposjecen);
    return false;
}
