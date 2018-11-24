#ifndef GRAFOPERACIJE_H
#define GRAFOPERACIJE_H
#include "MSGraf.h"
#include<vector>
#include<unordered_set>
#include<stack>

using namespace std;

class GrafOperacije : public MSGraf {
    static const bool Posjecen = true;
    static const bool Neposjecen = false;
    void Sirina (int);
    void Dubina (int);
    bool NeusmjereniCiklus(int,int);
    bool PrivatniBipartitiv(int,vector<int>&,int);
    bool UsmjereniCiklus(int,unordered_set<int>&);
    void PrivatnoTopoloskoSortiranje(int,stack<int>&);
    int PrivatniGlasine(int v,int& najmanji,vector<int>& c);
    int DijkstraShortestPathPrivate(int*);
    bool CycleInGraphPrivate(int,int,int);
public:
    GrafOperacije(int n) : MSGraf(n){}
    void PotpunaSirina();
    void PotpunaDubina();
    void IspisiKomponentePovezanosti();
    bool PostojiPut(int,int);
    bool Povezan();
    bool NeusmjereniCiklican();
    bool IspisiPut(int,int);
    void Kefa(int prvi,int counter,vector<int> &macke,int NajMacaka);//Zadatak sa CodeForce-a; Da li na putu od root-a do krajnjeg cvora postoji n ili više prepreka uzastopnih
    void OznaciSve();
    bool Bipartitivan(); //;Zadatak sa codeforcea za projekat https://codeforces.com/problemset/problem/687/A, dokaz na implementaciji
    bool UsmjereniCiklican();
    int DuzinaPuta(int,int);
    int Diametar();
    void TopoloskoSortiranje();
    void MinimalSpanningTree();
    void GreedyBojenje();
    int Glasine(vector<int>&);//Zadatak sa CodeForce-a ; https://codeforces.com/problemset/problem/893/C
    void DijkstraShortestPath(int);
    int FloydWarshall();//CodeForce
    void RemoveVertices(int);//CodeForce
    void NPHardProblem();//CodeForce
    void CycleInGraph(int);//CodeForce
};

#endif // GRAFOPERACIJE_H
