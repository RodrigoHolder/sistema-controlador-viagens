#include "Cidade.h"

Cidade::Cidade(std::string nome) : nome(nome) {}

std::string Cidade::getNome() const {
    return nome;
}