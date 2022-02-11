
#include "Cooperativa.h"

//TODO: Implementar corretamente o construtor e inicializacao da BST!
Cooperativa::Cooperativa():vinhos(Vinho("",0))
{}

void Cooperativa::addVinicola(string umaVinicola) {
    for(auto element: vinicolas){
        if(element.getNome() == umaVinicola){
            vinicolas.erase(element);
            element.addVinho();
            vinicolas.insert(element);
            return;
        }
    }

    Vinicola vinicola(umaVinicola);
    vinicolas.insert(vinicola);
}

Vinicola Cooperativa::maisOpcoes() {
    Vinicola comp("");
    for(auto element: vinicolas) {
        if(element< comp)
            comp = element;
    }
    return comp;
}
/*
void Cooperativa::addEnologoVinicola(string umEnologo, string umaVinicola) {
    bool check = false;
    stack<Enologo> aux;
    while(!enologos.empty()){
        if(enologos.top().getNome() == umEnologo){
            auto enologo = enologos.top();
            enologo.addVinicolaInexistente(Vinicola(umaVinicola));
            enologos.pop();
            aux.push(enologo);
            check = true;
            break;
        }
        aux.push(enologos.top());
        enologos.pop();
    }
    if(!check){
        Enologo enologo(umEnologo);
        enologo.addVinicolaInexistente(Vinicola(umaVinicola));
        aux.push(enologo);
    }

    while (!aux.empty()){
        enologos.push(aux.top());
        aux.pop();
    }
}*/



bool Enologo::operator<(const Enologo &e1) const {
    return getNumVinhos() < e1.getNumVinhos();
}

bool Enologo::operator==(const Enologo &e1) const {
    return nome == e1.getNome();
}

