#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "Kart.h"

using namespace std;

vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}

bool mySort(CKart& k1, CKart& k2){
    return k1.getNumero() < k2.getNumero();
}

//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts()
{
	vector<CKart> vord;
    for(auto idx: pistasG){
        vord.insert(vord.end(), idx.getFrotaActual().begin(), idx.getFrotaActual().end());
    }
    sort(vord.begin(),vord.end(),mySort);
	return vord;
    
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    int counter = 0;
    for(auto idx: pistasG){
        for(auto idx_1: idx.getKartsAvariados())
            if(idx_1.getCilindrada() == cilind) counter += 1;
    }
    return counter;
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
	int counter = 0;
    for(auto& x: frotaKartsPista) {
        if (counter == numeroKarts)
            return true;
        if (x.getCilindrada() == cilind && !(x.getAvariado())) {
            kartsLinhaPartida.push(x);
            counter++;
        }
    }
    return false;
}


//Exercicio 1 d) 
int CPista::inicioCorrida()
{
	while(!kartsLinhaPartida.empty()){
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }
    return kartsEmProva.size();
}

