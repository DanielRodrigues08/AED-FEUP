/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>



PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name) {
    vector<Mail *> res;
    for(int idx = 0; idx <= postmen.size(); idx++){
        if(postmen[idx].getName() == name) {
            res = postmen[idx].getMail();
            postmen.erase(postmen.begin() + idx);
            return res;
        }
    }
    return res;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {
    vector<Mail *> res;

    balance = 0;
    for(auto idx: mailToSend) {
        balance += idx->getPrice();
        if (idx->getZipCode() >= firstZipCode && idx->getZipCode() <= lastZipCode)
            mailToDeliver.push_back(idx);
        else
            res.push_back(idx);
    }
    mailToSend.clear();

    return res;
}

Postman PostOffice::addMailToPostman(Mail *m, string name) {
    Postman p1;
    for(auto idx: postmen) {
        if (idx.getName() == name) {
            idx.addMail(m);
            p1 = idx;
            return p1;
        }
    }
    throw NoPostmanException(name);
    return p1;
}
