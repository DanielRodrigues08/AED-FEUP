/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {

}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
    vector<Book*> temp;
    for(BSTItrIn<BookCatalogItem> it(catalogItems); !it.isAtEnd(); it.advance()){
        if(it.retrieve() == BookCatalogItem(book->getTitle(),book->getAuthor(),0)){
            for(auto elem: it.retrieve().getItems()){
                if(elem->getReader() == nullptr){
                    temp.push_back(elem);
                }
            }
        }
    }
    return temp;
}


bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	auto aux = getAvailableItems(book);
    if(aux.empty()) return false;
    aux[0]->setReader(reader);
    reader->addReading(aux[0]->getTitle(),aux[0]->getAuthor());
	return true;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
    userRecords.insert(UserRecord(user));
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
    UserRecord temp = UserRecord(user);
    userRecords.erase(temp);
    temp.setEMail(newEMail);
    userRecords.insert(temp);
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
    for(const auto& element: candidates){
        if(element.numReadings() >= min)
            readerCandidates.push(element);
    }
}

int ReadingClub::awardReaderChampion(User& champion) {
    if(readerCandidates.empty()) return 0;
    if(readerCandidates.size() == 1){
        champion = readerCandidates.top();
        return 1;
    }

    auto aux = readerCandidates;
    User user1 = aux.top();
    aux.pop();
    User user2 = aux.top();

    if(user1.numReadings() == user2.numReadings())
        return 0;

    champion = user1;
	return readerCandidates.size();
}
























