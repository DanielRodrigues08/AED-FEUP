/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>


Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    unsigned counter = 0;
	auto it = doctors.begin();
    while(it != doctors.end()){
        if(it->getMedicalSpecialty() == medicalSpecialty)
            counter += it->getPatients().size();
        it++;
    }
	return counter;

}

bool mySort(const Doctor& d1, const Doctor& d2){
    if(d1.getPatients().size() == d2.getPatients().size() && d1.getMedicalSpecialty() == d2.getMedicalSpecialty())
        return d1.getCode() < d2.getCode();
    if(d1.getPatients().size() == d2.getPatients().size())
        return d1.getMedicalSpecialty() < d2.getMedicalSpecialty();
    return d1.getPatients().size() < d2.getPatients().size();
}

void Hospital::sortDoctors() {
	doctors.sort(mySort);

}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	unsigned counter = 0;
    auto it = doctors.begin();
    while(it != doctors.end()){
        if(it->getMedicalSpecialty() == medicalSpecialty1)
            counter++;
        it++;
    }
    if(counter >= 3)
        return false;
    doctors.push_back(Doctor(codM1, medicalSpecialty1));
	return true;

}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
    queue<Patient> p1;
    auto it = doctors.begin();
    while(it != doctors.end()){
        if(it->getCode() == codM1){
            p1 = it->getPatients();
            doctors.erase(it);
            return p1;
        }
        it++;
    }
	throw DoctorInexistent();
}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
	vector<Doctor*> aux;
    auto it = doctors.begin();
    while(it != doctors.end()){
        if(it->getMedicalSpecialty() == medicalSpecialty1){
            if(aux.size() == 0)
                aux.push_back(&(*it));
            else{
                if(it -> getPatients().size() < aux[0]->getPatients().size())
                    aux[0] = &(*it);
            }
        }
        it++;
    }
    if(aux.size() == 0)
        return false;
    aux[0]->addPatient(Patient(cod1,medicalSpecialty1));
	return true;

}



void Hospital::processPatient(unsigned codM1) {
    for(auto it = doctors.begin(); it != doctors.end(); it++){
        if(it->getCode() == codM1 && it->getPatients().size()>0){
            bool check = true;
            Patient p1 = it->removeNextPatient();
            auto it_1 = letterTray.begin();
            for(auto it_1 = letterTray.begin(); it_1 != letterTray.end(); it_1++){
                if(it_1->size() < trayCapacity){
                    it_1->push(p1);
                    check = false;
                    break;
                }
            }
            if(check){
                stack<Patient> temp;
                temp.push(p1);
                letterTray.push_back(temp);
                break;
            }
        }
    }

}


unsigned Hospital::removePatients(unsigned codP1) {
	unsigned counter = 0;
    for(auto it = letterTray.begin(); it != letterTray.end(); it++){
        if(it->top().getCode() == codP1){
            it->pop();
            counter++;
            if(it->empty())
                it = letterTray.erase(it)--;
        }
    }
	return counter;

}



