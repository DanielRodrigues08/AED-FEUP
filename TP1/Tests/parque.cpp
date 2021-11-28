#include "parque.h"
#include <vector>

using namespace std;

InfoCartao::InfoCartao(string nome,bool presente){
    this -> nome = nome;
    this -> presente = presente;
}

ParqueEstacionamento::ParqueEstacionamento(unsigned lot, unsigned nMaxCli):
        lotacao(lot), numMaximoClientes(nMaxCli)
{ vagas=lot; }


unsigned ParqueEstacionamento::getNumLugares() const{
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const{
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const{
    for(int idx = 0; idx <= clientes.size(); idx++){
        if(clientes[idx].nome == nome)
            return idx;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome){
    if(clientes.size() >= numMaximoClientes)
        return false;
    else {
        InfoCartao temp(nome, false);
        clientes.push_back(temp);
        return true;
    }
}

bool ParqueEstacionamento::entrar(const string& nome){
    if (vagas == 0)
        return false;

    for(int idx = 0; idx <= clientes.size(); idx++)
        if(clientes[idx].nome == nome) {
            if (clientes[idx].presente == true)
                return false;
            vagas -= 1;
            clientes[idx].presente = true;
            return true;
        }
}

bool ParqueEstacionamento::retiraCliente(const string & nome){
    for(int idx = 0; idx <= clientes.size(); idx++){
        if(clientes[idx].nome == nome )
            if(clientes[idx].presente == true)
                return false;
            else {
                clientes.erase(clientes.begin() + idx);
                return true;
            }
    }
    return false;
}

bool ParqueEstacionamento::sair(const string & nome){
    for(int idx = 0; idx <= clientes.size(); idx++){
        if(clientes[idx].nome == nome){
            if(clientes[idx].presente==true){
                vagas += 1;
                clientes[idx].presente= false;
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const{
    return (lotacao - vagas);
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const{
    return clientes.size();
}