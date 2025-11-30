/******************************************************************
|																  |
| Projeto Prático - Sistema de Cadastro em Arquivos com Ordenação |
|																  |
| Nomes: . Arthur Fazzio Mendes                              	  |
|        . Lívia Rezende Masson                                   |
|                                                                 |
| Tema: Satélites                                                 |
|                                                                 |
*******************************************************************/
#include "projeto_pratico.cpp"
#include "textosInterface.hpp"
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <thread>

void Clear();
void Sleep(int time);
void Sair();

int main() {
    extern const std::string textoInicio;
    extern const std::string sateliteASCII;
    extern const std::string textoOpcoes;
    
    const std::string NOME_CSV = "db_satelites.csv";
    const unsigned int TAM_INICIAL = 40;
    unsigned int tamVetor = TAM_INICIAL;
    unsigned int qSatelites = 0;

    infoSatelite* satelites = CarregarCSV(NOME_CSV, tamVetor, qSatelites);

    Clear();
    const unsigned int DELAY = 3;
    std::cout << textoInicio << '\n' << std::endl;
    std::cout << sateliteASCII << std::endl;

    std::cout << "Entrando em: ";
    for (unsigned int i = 0; i < DELAY; i++) {
        std::cout << DELAY - i << ".. ";
        Sleep(1);
    }
    std::cout << std::endl;

    while (true) {
        const unsigned int DELAY_ESCOLHA = 3;

        bool opcaoValida = false;
        unsigned int opcao;

        while (not opcaoValida) {
             Clear();

            try {
                std::string opcaoString;
                std::cout << textoOpcoes << std::endl;
                std::cout << "> "; 
                std::cin >> opcaoString;

                opcao = stoi(opcaoString);
                opcaoValida = true;
            }
            catch (std::invalid_argument const&) {
                std::cout << "Opção deve ser um numero." << std::endl;
                std::cout << "Voltando..." << std::endl;
                Sleep(DELAY_ESCOLHA);
            }
            catch (std::out_of_range const&){
                std::cout << "Opção fora de alcance (numero grande demais)." << std::endl;
                std::cout << "Voltando..." << std::endl;
                Sleep(DELAY_ESCOLHA);
            }
        }

        switch (opcao) {
            case 8: {
                Sair();
                break;
            }
            default: {
                std::cout << "Opção não implementada :(" << std::endl;
                std::cout << "Voltando..." << std::endl;
                Sleep(DELAY_ESCOLHA);
                break;
            }
        }
    }

    return 0;
}

void Sair() {
    const unsigned int DELAY_SAIDA = 3;
    std::string escolha;
    std::cout << "Deseja mesmo sair? (s/n)" << std::endl;
    std::cin >> escolha;
    // transforma a string de escolha em minusculas
    std::transform(escolha.begin(), escolha.end(), escolha.begin(), ::tolower);

    if (escolha == "s" or escolha == "sim") {
        std::cout << "Saindo";

        for (unsigned int i = 0; i < DELAY_SAIDA; i++) {
            std::cout << ".";
            Sleep(1);
        }
        std::cout << std::endl;
        
        Clear();
        exit(0);
    }
    else if (escolha == "n" or escolha == "não" or escolha == "nao") {
        std::cout << "Retornando ao menu principal." << std::endl;
        Sleep(DELAY_SAIDA);
    }

    return;
}

void Clear() {
    int retorno = system("clear");
    if (retorno == -1) {
        std::cout << "Erro: Não foi possivel limpar o terminal" << std::endl;
    }
    return;
}

void Sleep(int time) {
    std::cout.flush();
    std::cin.sync();
    std::this_thread::sleep_for(std::chrono::seconds(time));
    return;
}
