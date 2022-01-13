// AED 2021/2022 - Aula Pratica 08
// Pedro Ribeiro (DCC/FCUP) [12/12/2021]

#include "funWithHashTables.h"
#include "hashTable.h"

#include <vector>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <set>

// Exemplo de função de hash para ints
unsigned FunWithHashTables::hashInt(const int& i) {
  return i;
}

// Exemplo de função de hash para strings
unsigned FunWithHashTables::hashString(const string& s) {
  hash<string> h;
  return h(s);
}

// ----------------------------------------------------------
// Exercicio 1: Tabelas de Dispersão
// ----------------------------------------------------------

// ..............................
// d) Contando diferentes somas de pares
// TODO
int FunWithHashTables::sumPairs(const vector<int>& numbers) {
    int temp = numbers.size();
    HashTable<int> sumHash(temp*temp,hashInt);
    for(size_t i = 0; i < numbers.size()-1; i++){
        for(size_t j = i+1; j < numbers.size(); j++){
            sumHash.insert(numbers[i]+numbers[j]);
        }
    }
    return sumHash.getNumActive();
}

// ----------------------------------------------------------
// Exercicio 2: Um padrão no DNA
// ----------------------------------------------------------
// TODO


int FunWithHashTables::dnaMotifs(string dna, int k, unordered_set<string>& motifs) {
    unordered_map<string, int> frequency;
    int max = 0;
    for(unsigned i = 0; i < dna.size()-k+1; i++){
        string temp = dna.substr(i,k);
        if(frequency.find(temp) == frequency.end()){
            frequency[temp] = 1;
            if(frequency[temp] > max)
                max=frequency[temp];
        }else{
            frequency[temp]++;
            if(frequency[temp] > max)
                max=frequency[temp];
        }
    }

    for(auto element: frequency) {
        if (element.second == max) {
            motifs.insert(element.first);
        }
    }

    return max;
}

// ----------------------------------------------------------
// Exercicio 3: Torre de Babel
// ----------------------------------------------------------
// TODO

vector<string> split(const string& s1){
    vector<string> result;
    auto it = s1.begin();
    string temp;
    while(it != s1.end()){
        if(isalpha(*it)) {
            temp += *it;
        }
        else if(temp.size()!=0){
            transform(temp.begin(),temp.end(), temp.begin(), [](char c){return tolower(c);});
            result.push_back(temp);
            temp = "";
        }
        it++;
    }
    if(temp.size()!=0){
        transform(temp.begin(),temp.end(), temp.begin(), [](char c){return tolower(c);});
        result.push_back(temp);
    }
    return result;
}

void FunWithHashTables::findLanguage(string text, const unordered_map<string, vector<string>>& dict, unordered_map<string, int>& answer) {
    vector<string> stringSplit = split(text);
    unordered_multimap<string, string> aux;
    set<string> auxSet(stringSplit.begin(),stringSplit.end());

    for(auto element: auxSet){
        for(auto idx: dict){
            if(find(idx.second.begin(), idx.second.end(), element) != idx.second.end()){
                aux.insert({element,idx.first});
            }
        }
    }

    for(auto element: dict){
        answer[element.first] = 0;
    }

    for(auto element: stringSplit){
        auto range = aux.equal_range(element);
        for(auto it = range.first; it != range.second;it++ ){
            answer[it->second]++;
        }
    }

}

// ----------------------------------------------------------
// Exercicio 4: Palavras Alienígenas
// ----------------------------------------------------------
// TODO
void FunWithHashTables::wordIndex(const vector<string> &words, vector<int>& answer) {

}
