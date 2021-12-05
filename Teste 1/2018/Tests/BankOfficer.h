/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>

class BankOfficer {
    static unsigned int idxAux;
    unsigned int id;
	string name;
	vector<Account *> myAccounts;
public:
    static unsigned int idAux;
	BankOfficer();
	void setName(string nm);
	void addAccount(Account *a);
	void addAccount(vector<Account *> accounts);
	string getName() const;
	vector<Account *> getAccounts() const;
	unsigned int getID() const;
    bool operator>(const BankOfficer& of1);

	//-------
	BankOfficer(string nm);
	vector<Account *> removeBankOfficer(string name);
};



#endif /* SRC_BANKOFFICER_H_ */
