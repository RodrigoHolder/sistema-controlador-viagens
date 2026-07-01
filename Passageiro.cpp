#include "Passageiro.h"

Passageiro::Passageiro(std::string nome, Cidade* localAtual) 
    : nome(nome), localAtual(localAtual), emTransito(false) {}

std::string Passageiro::getNome() const { return nome; }
Cidade* Passageiro::getLocalAtual() const { return localAtual; }
void Passageiro::setLocalAtual(Cidade* local) { localAtual = local; }
bool Passageiro::isEmTransito() const { return emTransito; }
void Passageiro::setEmTransito(bool estado) { emTransito = estado; }