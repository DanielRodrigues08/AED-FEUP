/*
 * Postman.cpp
 */
#include "Postman.h"
#include "PostOffice.h"
#include <string>



unsigned Postman::idAux = 1;

Postman::Postman(): id(0) {}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

Postman::Postman(string name):name(name) {
    id = idAux;
    idAux++;
}

bool Postman::operator<(const Postman &p1) {
    vector<string> aux1;
    vector<string> aux2;
    for(auto idx: myMail)
        aux1.push_back(idx->getZipCode());
    for(auto idx: p1.getMail())
        aux2.push_back(idx->getZipCode());
    return numberDifferent(aux1) < numberDifferent(aux2);
}