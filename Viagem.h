#ifndef VIAGEM_H
#define VIAGEM_H

#include <vector>
#include "Transporte.h"
#include "Passageiro.h"
#include "Cidade.h"

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    Viagem* proxima;
    int horasEmTransito;
    int horasTotaisNecessarias;
    bool emAndamento;
public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);
    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado() const;
    bool isEmAndamento() const;
    void setProxima(Viagem* prox);
    Viagem* getProxima() const;
    Cidade* getDestino() const;
    Transporte* getTransporte() const;
    std::vector<Passageiro*> getPassageiros() const;
};

#endif