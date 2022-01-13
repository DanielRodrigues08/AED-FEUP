/*
 * Dish.h
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#ifndef DISH_H_
#define DISH_H_

#include <string>

enum TypeOfDish {Plate, Dessert, Bowl};

class Dish {
	const std::string collection;
	const TypeOfDish type;
public:
	Dish(std::string c, TypeOfDish t);
	std::string getCollection() const;
	TypeOfDish getType() const;
	bool operator ==(const Dish& d) const;
};

#endif /* DISH_H_ */
/*
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {
    int counter = 0;
    for(list<Dish*>::iterator it = grouped_dishes.begin(); it != grouped_dishes.end(); it++){
        int counterTemp = 1;
        string collection = (*it)->getCollection();
        TypeOfDish type = (*it) ->getType();
        it++;
        if(it != grouped_dishes.end()) {
            while ((*it)->getCollection() == collection && (*it)->getType() == type) {
                counterTemp++;
                it++;
            }
        }
        it--;
        addDishes(counterTemp,collection,type);
        counter++;
    }
    return counter;
}*/