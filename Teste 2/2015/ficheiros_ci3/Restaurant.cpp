/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Restaurant.h"

using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)) {
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {
    for(unsigned i = 0; i < n; i++)
        getCleanDishStack(collection, type).push(new Dish(collection,type));
}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish* d = dirty.front();
    dirty.pop();
    drying.push_back(d);
	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */

void Restaurant::clearTable(vector<Table>::size_type idx) {
    if(idx < tables.size()) {
        vector<Dish*> aux = tables[idx].clear();
        for(auto idx: aux){
            dirty.push(idx);
        }
    }
}

/**
 * Stores in the respective clean stack all drying dishes of a given collection and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {
    int counter = 0;
    for(auto it = drying.begin(); it != drying.end(); it++){
        if((*it)->getCollection() == collection && (*it)->getType()==type){
            counter++;
            it = drying.erase(it);
            it--;
        }
    }
    if(counter != 0)
        addDishes(counter, collection, type);
}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {
    if(idx < tables.size()){
        if(!tables[idx].empty())
            throw TableNotReadyException();
        if(tables[idx].getPlaces().size() >= getCleanDishStack(collection, Plate).size())
            throw NotEnoughDishesException();

        vector<Dish*> aux;
        for(int i = 0; i < tables[idx].getPlaces().size(); i++){
            aux.push_back(getCleanDishStack(collection, Plate).top());
            getCleanDishStack(collection, Plate).pop();
        }

        tables[idx].putOn(aux);

    }

}

/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */
bool compareDishPointers(const Dish* d1, const Dish* d2){
    if(d1->getCollection() > d2->getCollection())
        return true;
    return d1->getType() == d2->getType() && d1->getCollection() == d2->getCollection();
}
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped = drying;
    dry_grouped.sort(compareDishPointers);
    drying.clear();
    return dry_grouped;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {
    int counter = 0;
    auto itList = grouped_dishes.begin();
    while(itList != grouped_dishes.end()){
        int counterTemp = 1;
        string collection = (*itList)->getCollection();
        TypeOfDish type = (*itList) ->getType();
        itList++;
        if(itList != grouped_dishes.end()){
            while ((*itList)->getCollection() == collection && (*itList) ->getType() == type && itList != grouped_dishes.end()){
                    counterTemp++;
                    itList++;
                }
            }

        addDishes(counterTemp,collection,type);
        counter++;
    }
	return counter;
}

