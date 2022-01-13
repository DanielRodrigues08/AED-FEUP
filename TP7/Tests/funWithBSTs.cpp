// AED 2021/2022 - Aula Pratica 07
// Pedro Ribeiro (DCC/FCUP) [06/12/2021]

#include <set>
#include <map>
#include <algorithm>
#include "funWithBSTs.h"
#include "bst.h"

// ----------------------------------------------------------
// Exercicio 1: Colecao de Cromos
// ----------------------------------------------------------
// TODO
int FunWithBSTs::newBag(const vector<int>& collection, const vector<int>& bag) {
    int counter = 0;
    set<int> newCollection(collection.begin(), collection.end());
    for(auto idx: bag){
        if(newCollection.insert(idx).second)
            counter++;
    }

    return counter;
}

// ----------------------------------------------------------
// Exercicio 2: Batalha de Pokemons
// ----------------------------------------------------------
// TODO

int FunWithBSTs::battle(const vector<int>& alice, const vector<int>& bruno) {
    multiset<int> aliceDeck(alice.begin(),alice.end());
    multiset<int> brunoDeck(bruno.begin(),bruno.end());
    while(!aliceDeck.empty() && !brunoDeck.empty()) {
        int aliceCard = *aliceDeck.rbegin();
        int brunoCard = *brunoDeck.rbegin();
        if (aliceCard > brunoCard) {
            brunoDeck.erase(--brunoDeck.end());
            aliceDeck.erase(--aliceDeck.end());
            aliceDeck.insert(aliceCard - brunoCard);
        } else if (aliceCard < brunoCard) {
            aliceDeck.erase(--aliceDeck.end());
            brunoDeck.erase(--brunoDeck.end());
            brunoDeck.insert(brunoCard - aliceCard);
        } else {
            aliceDeck.erase(--aliceDeck.end());
            brunoDeck.erase(--brunoDeck.end());
        }
    }

    if(!aliceDeck.empty()){
        return aliceDeck.size();
    }else if(!brunoDeck.empty()){
        return -brunoDeck.size();
    }
    return 0;
}


// ----------------------------------------------------------
// Exercicio 3: Reviews Cinematograficas
// ----------------------------------------------------------

// ..............................
// a) Contando Filmes
// TODO
int FunWithBSTs::numberMovies(const vector<pair<string, int>>& reviews) {
    set<string> movies;
    for(auto idx: reviews)
        movies.insert(idx.first);
    return movies.size();
}

// ..............................
// b) O filme com mais reviews
// TODO

bool myPred(pair<string, int> i1, pair<string, int> i2){
    return i1.second < i2.second;
}

void FunWithBSTs::moreReviews(const vector<pair<string, int>>& reviews, int& m, int& n) {
    map<string, int> movies;
    for(auto idx: reviews){
        if(movies.find(idx.first) == movies.end()){
            movies[idx.first] = 1;
        }else{
            movies[idx.first]++;
        }
    }

    m = max_element(movies.begin(),movies.end(), myPred)->second;

    n = 0;
    for(auto idx: movies)
        if(idx.second == m)
           n++;
}

// ..............................
// c) Os melhores filmes
// TODO
vector<string> FunWithBSTs::topMovies(const vector<pair<string, int>>& reviews, double k) {
    vector<string> answer;
    map<string, pair<int, int>> movies;

    for(auto idx: reviews){
        if(movies.find(idx.first) == movies.end()){
            movies[idx.first] = pair<int,int>(1, idx.second);
        }else{
            movies[idx.first].first++;
            movies[idx.first].second += idx.second;
        }
    }

    for(auto idx: movies){
        if((double) idx.second.second / idx.second.first >= k){
            answer.push_back(idx.first);
        }
    }


    return answer;
}

