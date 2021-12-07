/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"
#include <algorithm>

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* s, string e, unsigned c) {
    Expertize notFound("",0);
    Expertize search = getExpertize(e, c);
    if(search == notFound)
        search = Expertize(e,c);
    else
        expertizes.remove(search);

    search.addConsultant(s);
    expertizes.insert(search);

}


vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	Expertize notFound("",0);
    Expertize search = expertizes.find(Expertize(project->getExpertize(),project->getCost()));
    for(auto idx: search.getConsultants()){
        if(idx->getCurrentProject() == "")
            temp.push_back(idx);
    }
	return temp;
}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	if(student->getCurrentProject() != "")
	    return false;
    if(project->getConsultant() != nullptr)
        return false;
    vector<Student*> temp = getCandidateStudents(project);
    auto it = find(temp.begin(),temp.end(), student);
    if(it == temp.end())
        return false;
    project->setConsultant(student);
    student->addProject(project->getTitle());
    return true;
}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	//TODO:

}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	//TODO

}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	//TODO:

}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
	//TODO:
	return 0;

}





















