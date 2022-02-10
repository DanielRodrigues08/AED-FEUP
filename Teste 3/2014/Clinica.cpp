
#include "Clinica.h"

//Animal

Animal::Animal(string umNome, string umaEspecie, int numeroConsultas):
nome(umNome), especie(umaEspecie), numConsultas(numeroConsultas)
{}

string Animal::getNome() const
{ return nome; }

string Animal::getEspecie() const
{ return especie; }

int Animal::getNumConsultas() const
{ return numConsultas; }

void Animal::incNumConsultas()
{ numConsultas++; }


// Veterinario

Veterinario::Veterinario(string umNome):nome(umNome)
{}

string Veterinario::getNome() const
{ return nome; }

list<string> Veterinario::getAnimais() const
{ return meusAnimais; }

void Veterinario::addAnimal(string umNomeAnimal)
{ meusAnimais.push_back(umNomeAnimal); }


// Consulta

Consulta::Consulta(int umaHora, int umDia, int umMes, string umNomeAnimal):
	hora(umaHora), dia(umDia), mes(umMes), nomeAnimal(umNomeAnimal)
{}

string Consulta::getNomeAnimal() const
{ return nomeAnimal; }

int Consulta::getHora() const { return hora; }
int Consulta::getDia() const { return dia; }
int Consulta::getMes() const { return mes; }


void ConsultasVet::addConsulta(const Consulta &c1)
{ minhasConsultas.insert(c1); }


//Clinica

Clinica::Clinica()
{}

list<ConsultasVet> Clinica::getConsultasDisponiveis() const
{ return consultasDisponiveis; }

hashAnimal Clinica::getAnimais() const
{ return animais; }

priority_queue<Veterinario> Clinica::getVeterinarios() const
{ return veterinarios; }

void Clinica::addConsultasDisponiveisVet(const ConsultasVet &v1)
{ consultasDisponiveis.push_front(v1); }

void Clinica::addAnimal(const Animal &a1)
{ animais.insert(a1); }

void Clinica::addVeterinario(const Veterinario &v1)
{ veterinarios.push(v1); }


ConsultasVet::ConsultasVet(string umNomeVet): nomeVeterinario(umNomeVet),
		minhasConsultas(Consulta(0,0,0))
{}


bool Consulta::operator < (const Consulta &c2) const {
	if(getMes() == c2.getMes() && getDia() == c2.getDia())
        return getHora() < c2.getHora();
    if(getMes() == getMes())
        return getDia() < c2.getDia();
    return getMes() < c2.getMes();
}

bool Veterinario::operator<(const Veterinario& v1) const
{
    if(meusAnimais.size()==v1.getAnimais().size())
        return nome > v1.getNome();
    else
        return meusAnimais.size()>v1.getAnimais().size();
}



Animal Clinica::fimConsulta(string umNomeAnimal, string umNomeEspecie) {
    for(auto element: animais){
        if(element.getNome() == umNomeAnimal){
            animais.erase(element);
            element.incNumConsultas();
            animais.insert(element);
            return  element;
        }
    }
    Animal animal(umNomeAnimal, umNomeEspecie);
    animal.incNumConsultas();
    animais.insert(animal);
    return animal;
}

int Clinica::numAnimaisEspecie(string umNomeEspecie) const {
    int counter = 0;
    for(auto element: animais){
        if(element.getEspecie() == umNomeEspecie){
            counter++;
        }
    }
    return counter;
}

Veterinario Clinica::alocaVeterinario(string umNomeAnimal) {
    Veterinario vet = veterinarios.top();
    veterinarios.pop();
    vet.addAnimal(umNomeAnimal);
    veterinarios.push(vet);
    return vet;
}

list<string> Clinica::veterinariosMaisN(int n) const {
    list<string> result;
    auto aux = veterinarios;
    while(!aux.empty()){
        if(aux.top().getAnimais().size() > n)
            result.push_front(aux.top().getNome());
        aux.pop();
    }

    return result;
}

