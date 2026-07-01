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
        
        if (proxima == nullptr) {
            // Se for o ÚLTIMO trecho de todos, finalmente move as entidades para o destino final
            transporte->setEmTransito(false);
            transporte->setLocalAtual(destino);
            for (auto p : passageiros) {
                p->setEmTransito(false);
                p->setLocalAtual(destino);
            }
            std::cout << ">> VIAGEM TOTAL FINALIZADA! Chegada a cidade de " << destino->getNome() << "\n";
        } else {
            // Se houver uma conexão seguinte, ativa-a imediatamente!
            std::cout << ">> Conexao em " << destino->getNome() << " concluida. Iniciando proximo trecho...\n";
            
            proxima->iniciarViagem();
            
            // Se sobrarem horas deste avanço, repassa-as para o próximo trecho
            int sobra = horasEmTransito - horasTotaisNecessarias;
            if (sobra > 0) {
                proxima->avancarHoras(sobra);
            }
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