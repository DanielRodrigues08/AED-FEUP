#include "Escritorio.h"
#include <iostream>
#include <algorithm>
using namespace std;
//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }



//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }



//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }



//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}



//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

int Escritorio::numImpressorasSemResponsavel() const {
    int counter = 0;
    for(auto idxImpressoras: impressoras){
        bool res = false;
        for(auto idxFuncionario: funcionarios){
            for(auto idxImpressoras2: idxFuncionario.getImpressoras())
                if(idxImpressoras->getCodigo() == idxImpressoras2->getCodigo()){
                    res=true;
                    break;
                }
            if(res)
                break;
        }
        if(!res)
            counter++;
    }

    return counter;
}

vector<Impressora*> Escritorio::retiraImpressoras(int ano1){
    vector<Impressora*> result;
    auto it = impressoras.begin();
    while (it != impressoras.end()){
        if((*it)->getAno()<ano1){
            result.push_back(*it);
            it = impressoras.erase(it);
        }
        else
            it++;
    }
    return result;
}

bool  ImpressoraPB::imprime(Documento doc1) {
    if(numPagImprimir < doc1.getNumPaginas())
        return false;
    numPagImprimir -= doc1.getNumPaginas();
    docsImpressos.push_back(doc1);
    return true;
}

bool ImpressoraCores::imprime(Documento doc1) {
    if(numPagImprimirAmarelo < doc1.getPercentagemAmarelo()*doc1.getNumPaginas() || numPagImprimirPreto < doc1.getPercentagemPreto()*doc1.getNumPaginas())
        return false;
    docsImpressos.push_back(doc1);
    numPagImprimirAmarelo -= doc1.getPercentagemAmarelo()*doc1.getNumPaginas();
    numPagImprimirPreto -= doc1.getPercentagemPreto()*doc1.getNumPaginas();
    return true;
}

Impressora* Escritorio::imprimeDoc(Documento doc1) const {
    Impressora* notFound = new ImpressoraPB("inexistente",0,0);
    for(auto idx: impressoras){
        if(idx->imprime(doc1))
            return idx;
    }
    return notFound;
}

vector<Impressora*> Escritorio::tonerBaixo() const {
    vector<Impressora*> result;
    for(auto idx: impressoras){
        if(idx->lowToner())
            result.push_back(idx);
    }
    return result;
}

Documento Documento::operator+(const Documento &rhs) const {
    int nPag = numPaginas + rhs.numPaginas;
    float pP = (pPreto * numPaginas + rhs.pPreto * rhs.numPaginas) / nPag;
    float pA = (pAmarelo * numPaginas + rhs.pAmarelo * rhs.numPaginas) / nPag;

    return Documento(nPag, pP, pA);
}

string Escritorio::operator()(string cod) const {
    for(auto idx: funcionarios){
        for(auto idx2: idx.getImpressoras())
            if(idx2->getCodigo() == cod)
                return idx.getCodigo();
    }
    return "nulo";
}