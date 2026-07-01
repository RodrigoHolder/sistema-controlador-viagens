#include "ControladorDeTransito.h"
#include <iostream>
#include <algorithm>

// Função auxiliar (Busca em Profundidade - DFS) para encontrar caminhos com conexões
bool encontrarCaminho(Cidade* atual, Cidade* destino, const std::vector<Trajeto*>& todosTrajetos, 
                      std::vector<Cidade*>& visitados, std::vector<Trajeto*>& caminho) {
    if (atual == destino) return true;
    
    visitados.push_back(atual);
    
    for (auto t : todosTrajetos) {
        if (t->getOrigem() == atual) {
            // Evita loops (andar em círculos pelas mesmas cidades)
            if (std::find(visitados.begin(), visitados.end(), t->getDestino()) == visitados.end()) {
                caminho.push_back(t);
                if (encontrarCaminho(t->getDestino(), destino, todosTrajetos, visitados, caminho)) {
                    return true;
                }
                caminho.pop_back(); // Voltou atrás (Backtracking)
            }
        }
    }
    return false;
}

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
    if (buscarCidade(nome)) {
        std::cout << ">> Erro: Cidade ja cadastrada.\n";
        return;
    }
    cidades.push_back(new Cidade(nome));
    std::cout << ">> Cidade cadastrada com sucesso!\n";
}

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia) {
    Cidade* orig = buscarCidade(nomeOrigem);
    Cidade* dest = buscarCidade(nomeDestino);
    if (!orig || !dest) {
        std::cout << ">> Erro: Cidade de Origem ou Destino nao encontrada! Cadastre as cidades primeiro.\n";
        return;
    }
    trajetos.push_back(new Trajeto(orig, dest, tipo, distancia));
    std::cout << ">> Trajeto cadastrado com sucesso!\n";
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidad, 
                                                 int dist_descanso, int tempo_descanso, std::string nomeCidadeAtual) {
    Cidade* cid = buscarCidade(nomeCidadeAtual);
    if (!cid) {
        std::cout << ">> Erro: Cidade inicial '" << nomeCidadeAtual << "' nao existe! Cadastre a cidade primeiro.\n";
        return;
    }
    transportes.push_back(new Transporte(nome, tipo, capacidade, velocidad, dist_descanso, tempo_descanso, cid));
    std::cout << ">> Transporte cadastrado com sucesso!\n";
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string nomeCidadeAtual) {
    Cidade* cid = buscarCidade(nomeCidadeAtual);
    if (!cid) {
        std::cout << ">> Erro: Cidade atual '" << nomeCidadeAtual << "' nao existe! Cadastre a cidade primeiro.\n";
        return;
    }
    passageiros.push_back(new Passageiro(nome, cid));
    std::cout << ">> Passageiro cadastrado com sucesso!\n";
}

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, 
                                          std::string nomeOrigem, std::string nomeDestino) {
    Transporte* tr = buscarTransporte(nomeTransporte);
    Cidade* orig = buscarCidade(nomeOrigem);
    Cidade* dest = buscarCidade(nomeDestino);

    if (!tr || !orig || !dest) {
        std::cout << ">> Erro: Transporte, Origem ou Destino nao cadastrados no sistema.\n";
        return;
    }

    if (tr->getLocalAtual() != orig) {
        std::cout << ">> Erro: O transporte '" << tr->getNome() << "' esta em " << tr->getLocalAtual()->getNome() << " e nao na origem (" << orig->getNome() << ").\n";
        return;
    }

    // --- ALGORITMO DE BUSCA DE CONEXÕES REQUISITADO ---
    std::vector<Cidade*> visitados;
    std::vector<Trajeto*> caminhoGerado;
    
    if (!encontrarCaminho(orig, dest, trajetos, visitados, caminhoGerado)) {
        std::cout << ">> Erro: Nao existe nenhuma rota ou conexao disponivel de " << orig->getNome() << " para " << dest->getNome() << ".\n";
        return;
    }

    std::vector<Passageiro*> passEscolhidos;
    for (const auto& nome : nomesPassageiros) {
        Passageiro* p = buscarPassageiro(nome);
        if (p && p->getLocalAtual() == orig) {
            passEscolhidos.push_back(p);
        }
    }

    if (passEscolhidos.empty()) {
        std::cout << ">> Erro: Nenhum dos passageiros listados esta na cidade de origem.\n";
        return;
    }

    // Cria as viagens baseadas nos trechos encontrados
    std::vector<Viagem*> segmentos;
    for (auto t : caminhoGerado) {
        segmentos.push_back(new Viagem(tr, passEscolhidos, t->getOrigem(), t->getDestino(), t->getDistancia()));
    }

    // Encadeia as viagens usando o ponteiro 'proxima'
    for (size_t i = 0; i < segmentos.size() - 1; ++i) {
        segmentos[i]->setProxima(segmentos[i+1]);
    }

    // Registra todas no controlador
    for (auto seg : segmentos) {
        viagens.push_back(seg);
    }

    // Inicia apenas o primeiro trecho da conexão
    segmentos[0]->iniciarViagem();
    std::cout << ">> ROTA ENCONTRADA! Viagem com " << caminhoGerado.size() << " trecho(s) iniciada com sucesso!\n";
}

void ControladorDeTransito::avancarHoras(int horas) {
    bool algumaViagemAtiva = false;
    for (auto v : viagens) {
        if (v->isEmAndamento()) {
            algumaViagemAtiva = true;
            v->avancarHoras(horas);
        }
    }
    if (!algumaViagemAtiva) {
        std::cout << ">> Nenhuma viagem em andamento para avancar o tempo.\n";
    }
}

void ControladorDeTransito::relatarEstado() const {
    std::cout << "\n=== RELATORIO DE TRANSITO ===\n";
    std::cout << "--- Passageiros ---\n";
    for (auto p : passageiros) {
        std::cout << "- " << p->getNome() << ": " << (p->isEmTransito() ? "Em Transito" : p->getLocalAtual()->getNome()) << "\n";
    }
    std::cout << "--- Transportes ---\n";
    for (auto tr : transportes) {
        std::cout << "- " << tr->getNome() << ": " << (tr->isEmTransito() ? "Em Transito" : tr->getLocalAtual()->getNome()) << "\n";
    }
    std::cout << "--- Viagens em Andamento/Conexao ---\n";
    int ativas = 0;
    for (auto v : viagens) {
        if (v->isEmAndamento() || v->getProxima() != nullptr) {
            v->relatarEstado();
            ativas++;
        }
    }
    if (ativas == 0) std::cout << "(Nenhuma viagem ativa no momento)\n";
    std::cout << "=============================\n";
}