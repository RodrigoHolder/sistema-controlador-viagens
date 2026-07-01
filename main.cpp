#include <iostream>
#include "ControladorDeTransito.h"

void exibirMenu() {
    std::cout << "\n--- SISTEMA CONTROLADOR DE VIAGENS ---\n";
    std::cout << "1. Cadastrar Cidade\n";
    std::cout << "2. Cadastrar Trajeto\n";
    std::cout << "3. Cadastrar Transporte\n";
    std::cout << "4. Cadastrar Passageiro\n";
    std::cout << "5. Iniciar Viagem\n";
    std::cout << "6. Avancar Horas\n";
    std::cout << "7. Relatorios e Consultas\n";
    std::cout << "0. Sair\n";
    std::cout << "Escolha uma opcao: ";
}

int main() {
    ControladorDeTransito controlador;
    int opcao = -1;

    // A MASSA DE TESTES FOI REMOVIDA DAQUI. O SISTEMA AGORA INICIA 100% LIMPO.

    while (opcao != 0) {
        exibirMenu();
        if (!(std::cin >> opcao)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Opcao invalida! Digite um numero.\n";
            continue;
        }

        if (opcao == 1) {
            std::string nome;
            std::cout << "Nome da Cidade: ";
            std::cin >> nome;
            controlador.cadastrarCidade(nome);
            std::cout << ">> Cidade cadastrada com sucesso!\n";

        } else if (opcao == 2) {
            std::string orig, dest;
            char tipo;
            int dist;
            std::cout << "Cidade Origem: "; std::cin >> orig;
            std::cout << "Cidade Destino: "; std::cin >> dest;
            std::cout << "Tipo (A/T): "; std::cin >> tipo;
            std::cout << "Distancia (Km): "; std::cin >> dist;
            
            std::cin.clear();
            std::cin.ignore(10000, '\n');

            controlador.cadastrarTrajeto(orig, dest, tipo, dist);
            std::cout << ">> Trajeto cadastrado com sucesso!\n";

        } else if (opcao == 3) {
            std::string nome, cidade;
            char tipo;
            int cap, vel, dist_d, tempo_d;
            std::cout << "Nome do Transporte: "; std::cin >> nome;
            std::cout << "Tipo (A/T): "; std::cin >> tipo;
            std::cout << "Capacidade: "; std::cin >> cap;
            std::cout << "Velocidade (Km/h): "; std::cin >> vel;
            std::cout << "Distancia entre descansos: "; std::cin >> dist_d;
            std::cout << "Tempo de descanso (h): "; std::cin >> tempo_d;
            std::cout << "Cidade Inicial (Onde ele esta agora): "; std::cin >> cidade;
            
            std::cin.clear();
            std::cin.ignore(10000, '\n');

            controlador.cadastrarTransporte(nome, tipo, cap, vel, dist_d, tempo_d, cidade);
            std::cout << ">> Transporte cadastrado com sucesso!\n";

        } else if (opcao == 4) {
            std::string nome, cidade;
            std::cout << "Nome do Passageiro: "; std::cin >> nome;
            std::cout << "Cidade Atual (Onde ele esta agora): "; std::cin >> cidade;
            controlador.cadastrarPassageiro(nome, cidade);
            std::cout << ">> Passageiro cadastrado com sucesso!\n";

        } else if (opcao == 5) {
            std::string tr, orig, dest, pass;
            std::cout << "Nome do Transporte que vai usar: "; std::cin >> tr;
            std::cout << "Cidade de Origem (Onde o transporte/passageiro estao): "; std::cin >> orig;
            std::cout << "Cidade de Destino: "; std::cin >> dest;
            std::cout << "Nome do Passageiro: "; std::cin >> pass;
            
            controlador.iniciarViagem(tr, {pass}, orig, dest);

        } else if (opcao == 6) {
            int horas;
            std::cout << "Quantidade de horas para avancar: "; std::cin >> horas;
            
            std::cin.clear();
            std::cin.ignore(10000, '\n');

            controlador.avancarHoras(horas);

        } else if (opcao == 7) {
            controlador.relatarEstado();
        }
    }

    return 0;
}