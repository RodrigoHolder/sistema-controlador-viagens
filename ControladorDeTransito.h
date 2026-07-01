#ifndef CONTROLADOR_DE_TRANSITO_H
#define CONTROLADOR_DE_TRANSITO_H

#include <vector>
#include <string>
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Viagem.h"

class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Trajeto*> trajetos;
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Viagem*> viagens;

    Cidade* buscarCidade(std::string nome);
    Transporte* buscarTransporte(std::string nome);
    Passageiro* buscarPassageiro(std::string nome);

public:
    ~ControladorDeTransito();
    void cadastrarCidade(std::string nome);
    void cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia);
    void cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, 
                             int dist_descanso, int tempo_descanso, std::string nomeCidadeAtual);
    void cadastrarPassageiro(std::string nome, std::string nomeCidadeAtual);
    void iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, 
                       std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);
    void relatarEstado() const;
};

#endif