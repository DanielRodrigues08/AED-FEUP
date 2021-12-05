/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
    double counter = 0;
    for(auto idx: accounts){
        if(idx -> getCodH() == cod1)
            counter += idx -> getWithdraw();
    }
    return counter;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
    vector<Account *> res;
    vector<BankOfficer>::iterator it = bankOfficers.begin();
    while(it != bankOfficers.end()) {
        if (it->getName() == name) {
            res = it->getAccounts();
            bankOfficers.erase(it);
            return res;
        }
        it++;
    }
    return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    vector<BankOfficer>::iterator it = bankOfficers.begin();
    while(it != bankOfficers.end()){
        if(it->getName() == name) {
            it->addAccount(ac);
            return *it;
        }
        it++;
    }
    throw NoBankOfficerException(name);
}

bool mySort(const Account* a1, const Account* a2){
    if(a1->getBalance() == a2->getBalance())
        return a1->getCodIBAN()<a2->getCodIBAN();
    return a1->getBalance()<a2->getBalance();
}

// a alterar
void Bank::sortAccounts() {
    sort(accounts.begin(), accounts.end(), mySort);
}



