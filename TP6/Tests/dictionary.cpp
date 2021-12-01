#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"

using namespace std;

WordMean::WordMean(string w, string m): word(w), meaning(m) {}

string WordMean::getWord() const {
    return word;
}

bool WordMean::operator<(const WordMean &w1) const{
    return word < w1.getWord();
}

bool WordMean::operator==(const WordMean &w1) const {
    return word==w1.getWord();
}

ostream& operator<<(ostream& os, const WordMean& w1){
    os << w1.getWord() << endl << w1.getMeaning() << endl;
    return os;
}

string WordMean::getMeaning() const {
    return meaning;
}

void WordMean::setMeaning(string m) {
    meaning = m;
}

void WordMean::setWord(string w) {
    word = w;
}

BST<WordMean> Dictionary::getWords() const {
	return words;
}



// ---------------------------------------------

//TODO
void Dictionary::readFile(ifstream &f) {
    string wordTemp, meaningTemp;
    while(getline(f,wordTemp)){
        getline(f, meaningTemp);
        words.insert(WordMean(wordTemp,meaningTemp));
    }
}

//TODO
string Dictionary::consult(string word1, WordMean& previous, WordMean& next) const {
    const WordMean empty("","");
    auto val = words.find(WordMean(word1,""));
    BSTItrIn<WordMean> it(words);
    if(val == empty){
        while(!it.isAtEnd() && it.retrieve().getWord() < word1){
            previous.setWord(it.retrieve().getWord());
            previous.setMeaning(it.retrieve().getMeaning());
            it.advance();
        }
        if(!it.isAtEnd()){
            next.setWord(it.retrieve().getWord());
            next.setMeaning(it.retrieve().getMeaning());
        }
        return "word not found";
    }else{
        return val.getMeaning();
    }
}

//TODO
bool Dictionary::update(string word1, string mean1) {
    return true;
}

//TODO
void Dictionary::print() const {
    words.printTree();
}
