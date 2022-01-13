/*
 * pizzeria.cpp
 *
 *  Created on: 25 Oct 2015
 *      Author: RRossetti
 */

#include "pizzeria.h"
#include <algorithm>

/*
 * CLASS MENU
 */
int Menu::idAux = 1;

Menu::Menu() {
    id = 0;
	name = "";
	likes = 0;
}

Menu::Menu(int id1, string n1, vector<string> is1, int lks1) {
	id = id1;
	name = n1;
	ingredients = is1;
	likes = lks1;
}

int Menu::getId() const { return id; }
void Menu::setId(int id1) { id = id1; }
string Menu::getName() const { return name; }
void Menu::setName(string n1) { name = n1; }
vector<string> Menu::getIngredients() const { return ingredients; }




/*
 * CLASS CUSTOMER
 */

Customer::Customer(int nif1, string n1) {
	nif = nif1;
	name = n1;
}

int Customer::getNIF() const {
	return nif;
}

string Customer::getName() const {
	return name;
}


/*
 * CLASS PIZZERIA
 */

Pizzeria::Pizzeria() { }

Pizzeria::Pizzeria(vector<Menu> ms1) {
	menus = ms1;
}

vector<Menu> Pizzeria::getMenus() const { return menus; }

vector<Customer*> Pizzeria::getCustomers() const { return customers; }

int Pizzeria::addCustomer(Customer* c1) {
	customers.push_back(c1);
	return customers.size();
}


Menu::Menu(string n1, vector<string> is1): name(n1), ingredients(is1){
    id = idAux;
    idAux++;
}

void Menu::setIngredients(const vector<string> &is1) {
    vector<string> aux;
    aux.insert(aux.end(), ingredients.begin(),ingredients.end());
    aux.insert(aux.end(),is1.begin(),is1.end());
    if (isSet(aux)) ingredients = aux;
    else throw Menu::ExceptionIngredientsRepeated();
}

vector<Menu> Pizzeria::optionsWithinIngredientLimits(int i1, int i2) const{
    vector<Menu> result;
    if(i1<1 || i2 < 1 || i1>i2)
        throw Pizzeria::ExceptionInvalidIngredientLimits();
    else{
        for(auto idx: menus){
            if(idx.getIngredients().size() >= i1 && idx.getIngredients().size() <= i2)
                result.push_back(idx);
        }
    }
    return result;
}

bool mySort(const Menu& m1, const Menu& m2){
    if(m1.getLikes() == m2.getLikes())
        return m1.getName() < m2.getName();
    return m1.getLikes() > m2.getLikes();
}

vector<Menu> Pizzeria::popularityRank() const {
    vector<Menu> aux = menus;
    sort(aux.begin(),aux.end(),mySort);
    return aux;
}

Customer* Pizzeria::chefCustomer() {
    float max = -1;
    Customer* result;
    for(auto idx: customers) {
        int counterMenu = 0;
        int counterLikes = 0;
        float ratio;
        for (auto idx_1: menus){
            if(idx_1.getName() == idx->getName()){
                counterMenu++;
                counterLikes += idx_1.getLikes();
            }
        }
        ratio = (counterLikes * 1.0)/counterMenu;
        if(ratio >= max) {
            result = idx;
            max = ratio;
        }

    }
    return result;
}

Menu& Pizzeria::removeIngredient(vector<string> is1, string i1){
    Menu* aux;
    bool check = true;

    for(auto idx: menus){
        if(idx.getIngredients() == is1){
            aux = &idx;
            check = false;
            break;
            cout << "TESTE " << endl;
        }
    }
    if(check)
        throw ExceptionInexistentMenu();
    /*
    check = true;

    vector<string> temp = aux->getIngredients();
    for(auto it = temp.begin(); it != temp.end(); it++){
        if(*it == i1){
            check = false;
            //temp.erase(it);
            break;
        }
    }*/

    if(check)
        throw Menu::ExceptionIngredientNotPresent(i1);

    //aux->setIngredients(temp);
    return *aux;
}