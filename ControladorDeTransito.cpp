#include "ControladorDeTransito.h"
#include <iostream>
#include <algorithm>

ControladorDeTransito::~ControladorDeTransito() {
    for (auto c : cidades) delete c;
    for (auto t : trajetos) delete t;
    for (auto tr : transportes) delete tr;
    for (auto p : passageiros) delete p;
    for (auto v : viagens) delete v;
}

Cidade* ControladorDeTransito::buscarCidade(std::string nome) {
    for (auto c : cidades) if (c->getNome() == nome) return c;
    return nullptr;
}

Transporte* ControladorDeTransito::buscarTransporte(std::string nome) {
    for (auto tr : transportes) if (tr->getNome() == nome) return tr;
    return nullptr;
}

Passageiro* ControladorDeTransito::buscarPassageiro(std::string nome) {
    for (auto p : passageiros) if (p->getNome() == nome) return p;
    return nullptr;
}

void ControladorDeTransito::cadastrarCidade(std::string nome) {
    if (buscarCidade(nome)) return;
    cidades.push_back(new Cidade(nome));
}

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia) {
    Cidade* orig = buscarCidade(nomeOrigem);
    Cidade* dest = buscarCidade(nomeDestino);
    if (orig && dest) {
        trajetos.push_back(new Trajeto(orig, dest, tipo, distancia));
    }
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, 
                                                 int dist_descanso, int tempo_descanso, std::string nomeCidadeAtual) {
    Cidade* cid = buscarCidade(nomeCidadeAtual);
    if (cid) {
        transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, dist_descanso, tempo_descanso, cid));
    }
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string nomeCidadeAtual) {
    Cidade* cid = buscarCidade(nomeCidadeAtual);
    if (cid) {
        passageiros.push_back(new Passageiro(nome, cid));
    }
}

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, 
                                          std::string nomeOrigem, std::string nomeDestino) {
    Transporte* tr = buscarTransporte(nomeTransporte);
    Cidade* orig = buscarCidade(nomeOrigem);
    Cidade* dest = buscarCidade(nomeDestino);

    if (!tr || !orig || !dest) {
        std::cout << "Erro: Entidades nao encontradas.\n";
        return;
    }

    if (tr->getLocalAtual() != orig) {
        std::cout << "Erro: O transporte nao esta na cidade de origem.\n";
        return;
    }

    std::vector<Passageiro*> passEscolhidos;
    for (const auto& nome : nomesPassageiros) {
        Passageiro* p = buscarPassageiro(nome);
        if (p && p->getLocalAtual() == orig) {
            passEscolhidos.push_back(p);
        }
    }

    Viagem* novaViagem = new Viagem(tr, passEscolhidos, orig, dest);
    novaViagem->iniciarViagem();
    viagens.push_back(novaViagem);
    std::cout << "Viagem de " << orig->getNome() << " para " << dest->getNome() << " iniciada com sucesso!\n";
}

void ControladorDeTransito::avancarHoras(int horas) {
    for (auto v : viagens) {
        if (v->isEmAndamento()) {
            v->avancarHoras(horas);
        }
    }
}

void ControladorDeTransito::relatarEstado() const {
    std::cout << "\n=== RELATORIO DE TRANSITO ===\n";
    std::cout << "--- Passageiros ---\n";
    for (auto p : passageiros) {
        std::cout << "- " << p->getNome() << ": " << (p->isEmTransito() ? "Em Trânsito" : p->getLocalAtual()->getNome()) << "\n";
    }
    std::cout << "--- Transportes ---\n";
    for (auto tr : transportes) {
        std::cout << "- " << tr->getNome() << ": " << (tr->isEmTransito() ? "Em Trânsito" : tr->getLocalAtual()->getNome()) << "\n";
    }
    std::cout << "--- Viagens em Andamento ---\n";
    for (auto v : viagens) {
        v->relatarEstado();
    }
    std::cout << "=============================\n";
}