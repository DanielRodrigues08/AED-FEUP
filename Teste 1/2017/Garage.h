/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>
using namespace std;
template <class Vehicle>
class Garage {
	std::vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

class NoSuchBrandException {
    string brand;
public:
    NoSuchBrandException(string brand): brand(brand) { }
    string getBrand(){return brand;}
};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
std::vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}

template<class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle) {
    if(vehicles.size() >= capacity)
        return false;
    typename vector<Vehicle *>::const_iterator it = vehicles.begin();
    while (it != vehicles.end()){
        if(*(*it) == *vehicle)
            return false;
        it++;
    }
    vehicles.push_back(vehicle);
    return true;
}

template<class Vehicle>
bool mySort(Vehicle* v1, Vehicle* v2){
    if(v1->getBrand() == v2->getBrand())
        return v1->getPrice() > v2->getPrice();
    return v1->getBrand() < v2->getBrand();
}


template<class Vehicle>
void Garage<Vehicle>::sortVehicles() {
    sort(vehicles.begin(),vehicles.end(),mySort<Vehicle>);
}

template<class Vehicle>
Vehicle* Garage<Vehicle>::removeVehicle(std::string brand, std::string model){
    Vehicle* removed;
    typename  vector<Vehicle *>::iterator it = vehicles.begin();
    while (it != vehicles.end()){
        if((*it)->getBrand() == brand && (*it)->getModel() == model){
            removed = *it;
            vehicles.erase(it);
            return removed;
        }
        it++;
    }
    throw NoSuchVehicleException();
}

template<class Vehicle>
float Garage<Vehicle>::avgPrice(std::string brand) const {
    int sum = 0, counter = 0;
    typename  vector<Vehicle *>::const_iterator it = vehicles.begin();
    while (it != vehicles.end()){
        if((*it)->getBrand() == brand){
            sum += (*it)->getPrice();
            counter++;
        }
        it++;
    }
    if(counter==0)
        throw NoSuchBrandException(brand);
    else
        return sum/(float)counter;
}


#endif /* SRC_GARAGE_H_ */
