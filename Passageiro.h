#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <string>
#include "Cidade.h"

class Passageiro {
private:
    std::string nome;
    Cidade* localAtual;
    bool emTransito;
public:
    Passageiro(std::string nome, Cidade* localAtual);
    std::string getNome() const;
    Cidade* getLocalAtual() const;
    void setLocalAtual(Cidade* local);
    bool isEmTransito() const;
    void setEmTransito(bool estado);
};

#endif