/*
 * PostOffice.h
 */

#ifndef SRC_POSTOFFICE_H_
#define SRC_POSTOFFICE_H_

#include "Mail.h"
#include "Postman.h"
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
unsigned int numberDifferent (const vector<T> & v1){
    vector<T> aux = v1;
    sort(aux.begin(),aux.end());
    return  unique(aux.begin(),aux.end()) - aux.begin();
}

class NoPostmanException
{
    string name;
public:
    NoPostmanException(string name){this -> name = name;}
    string getName() const {return name; }
};

class PostOffice {
	vector<Mail *> mailToSend;
	vector<Mail *> mailToDeliver;
	vector<Postman> postmen;
	string firstZipCode, lastZipCode;
public:
	PostOffice();
	PostOffice(string firstZCode, string lastZCode);
	void addMailToSend(Mail *m);
	void addMailToDeliver(Mail *m);
	void addPostman(const Postman &p);
	vector<Mail *> getMailToSend() const;
	vector<Mail *> getMailToDeliver() const;
	vector<Postman> getPostman() const;
	//-------
	vector<Mail *> removePostman(string name);
	vector<Mail *> endOfDay(unsigned int &balance);
	Postman addMailToPostman(Mail *m, string name);
};

#endif /* SRC_POSTOFFICE_H_ */
