/*
 * Bank.h
 */

#ifndef SRC_BANK_H_
#define SRC_BANK_H_

#include "Account.h"
#include <vector>

#include "BankOfficer.h"


class Bank {
	vector<Account *> accounts;
	vector<BankOfficer> bankOfficers;
public:
	Bank();
	void addAccount(Account *a);
	void addBankOfficer(BankOfficer b);
	vector<BankOfficer> getBankOfficers() const;
	vector<Account *> getAccounts() const;

	//-------
	double getWithdraw(string cod1) const;
	vector<Account *> removeBankOfficer(string name);
	const BankOfficer& addAccountToBankOfficer(Account *ac, string name);
	void sortAccounts();
};

template<class T>
bool inVector(const vector<T>& aux, const T& element){
    for(auto idx: aux)
        if(idx == element)
            return true;
    return false;
}

template <class T>
unsigned int numberDifferent(const vector<T>& v1){
    vector<T> aux;
    for(auto idx: v1){
        if(!inVector(aux, idx)){
            aux.push_back(idx);
        }
    }
    return aux.size();
}

class NoBankOfficerException {
    string name;
public:
    NoBankOfficerException(const string &name) {this->name = name;}
    string getName() {return name;}
};


#endif /* SRC_BANK_H_ */
