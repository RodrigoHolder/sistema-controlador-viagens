#include "Viagem.h"
#include <iostream>
#include <cmath>

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distancia)
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino), 
      proxima(nullptr), horasEmTransito(0), emAndamento(false) {
    
    // Agora usa a distancia real do trajeto!
    double tempoViagemPuro = (double)distancia / transporte->getVelocidade();
    int paradas = distancia / transporte->getDistanciaEntreDescansos();
    if (distancia % transporte->getDistanciaEntreDescansos() == 0 && paradas > 0) paradas--;
    
    horasTotaisNecessarias = std::ceil(tempoViagemPuro) + (paradas * transporte->getTempoDescanso());
}

void Viagem::iniciarViagem() {
    emAndamento = true;
    transporte->setEmTransito(true);
    transporte->setLocalAtual(nullptr);
    for (auto p : passageiros) {
        p->setEmTransito(true);
        p->setLocalAtual(nullptr);
    }
}

void Viagem::avancarHoras(int horas) {
    if (!emAndamento) return;
    horasEmTransito += horas;
    if (horasEmTransito >= horasTotaisNecessarias) {
        emAndamento = false;
        // Se houver uma próxima conexão, as entidades continuam em trânsito
        if (proxima == nullptr) {
            transporte->setEmTransito(false);
            transporte->setLocalAtual(destino);
            for (auto p : passageiros) {
                p->setEmTransito(false);
                p->setLocalAtual(destino);
            }
            std::cout << ">> Viagem finalizada! Chegada a cidade de " << destino->getNome() << "\n";
        } else {
            std::cout << ">> Conexao intermediaria concluida em " << destino->getNome() << ". Aguardando proximo trecho.\n";
        }
    }
}

void Viagem::relatarEstado() const {
    std::cout << "Trecho: " << origem->getNome() << " -> " << destino->getNome() 
              << " | Status: " << (emAndamento ? "Em andamento" : "Aguardando/Finalizado")
              << " (" << horasEmTransito << "/" << horasTotaisNecessarias << "h)\n";
}

bool Viagem::isEmAndamento() const { return emAndamento; }
void Viagem::setProxima(Viagem* prox) { proxima = prox; }
Viagem* Viagem::getProxima() const { return proxima; }
Cidade* Viagem::getDestino() const { return destino; }
Transporte* Viagem::getTransporte() const { return transporte; }
std::vector<Passageiro*> Viagem::getPassageiros() const { return passageiros; }