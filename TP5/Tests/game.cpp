#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

unsigned int Game::numberOfWords(string phrase) {
  if ( phrase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = phrase.find(' ');
  while (pos != string::npos) {
    phrase = phrase.substr(pos+1);
    pos = phrase.find(' ');
    n++;
  }
  return n;
}

Game::Game() {
	this->kids.clear();
}

Game::Game(list<Kid>& l2) {
	this->kids = l2;
}

//-----------------------------------------------------------------

// TODO
void Game::addKid(const Kid k1) {
    kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const {
    return kids;
}

// TODO
void Game::setKids(const list<Kid>& l1) {
    for(auto idx: l1)
        kids.push_back(idx);
}

// TODO
Kid Game::loseGame(string phrase) {
    list<Kid> kidsV2 = kids;
    while (kidsV2.size() != 1) {
        int counter = numberOfWords(phrase);
        while (counter != 1) {
            Kid temp = kidsV2.front();
            kidsV2.pop_front();
            kidsV2.push_back(temp);
            counter--;
        }
        kidsV2.erase(kidsV2.begin());
    }
    return *kidsV2.begin();
}

// TODO
list<Kid> Game::removeOlder(unsigned id) {
    queue<Kid> aux;
    list<Kid> result;
    for(auto idx: kids)
        aux.push(idx);
    kids.clear();

    while(!aux.empty()){
        if(aux.front().getAge()>id)
            result.push_back(aux.front());
        else
            kids.push_back(aux.front());
        aux.pop();
    }

    return result;
}

// TODO
queue<Kid> Game::rearrange() {
    queue<Kid> men;
    queue<Kid> women;
    for(auto idx: kids){
        if(idx.getSex() == 'm')
            men.push(idx);
        else
            women.push(idx);
    }
    kids.clear();
    if(women.size() < men.size()){
        int temp = men.size() / women.size();
        while(women.size() > 0 && men.size()>=temp){
            kids.push_back(women.front());
            women.pop();
            int counter = temp;
            while(counter != 0){
                kids.push_back(men.front());
                men.pop();
                counter--;
            }
        }
    }else {
        int temp = women.size() / men.size();
        while (men.size() > 0 && women.size() >= temp) {
            int counter = temp;
            while (counter != 1) {
                kids.push_back(women.front());
                women.pop();
                counter--;
            }
            kids.push_back(men.front());
            men.pop();
        }
    }
    queue<Kid> result;
    while(women.size()!=0){
        result.push(women.front());
        women.pop();
    }
    while(men.size()!=0){
        result.push(men.front());
        men.pop();
    }
    return result;
}

// TODO
bool Game::operator==(Game& g2) {
	if(kids.size() != g2.getKids().size())
        return false;
    list<Kid>::iterator it1 = kids.begin();
    list<Kid>::iterator it2 = g2.getKids().begin();
    while(it1 != kids.end()) {
        if (!(*it1 == *it2))
            return false;
        it1++;
        it2++;
    }
    return true;
}

// TODO
list<Kid> Game::shuffle() const {
    list<Kid> result;
    list<Kid> aux = kids;
    while(result.size()!=kids.size()){
        list<Kid>::iterator it = aux.begin();
        int temp = rand() % aux.size();
        advance(it,temp);
        result.push_back(*it);
        aux.remove(*it);
    }
    return result;
}


