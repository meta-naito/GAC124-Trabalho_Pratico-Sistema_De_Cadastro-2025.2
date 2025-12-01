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
#include "csv.hpp"
#include "textosInterface.hpp"
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

// Pede confirmação para o usuário com sim ou não, sobre escolha com a mensagem passada.
// Sempre exibe ao final da mensagem " (s/n)".
bool Confirmar(std::string mensagem);
// Limpa o terminal
// OBS: Só funciona em UNIX.
void Clear();
// Recolhe escolha do usuario de inteiro não assinado.
// Lida com erros causados por escolhas incorretas.
unsigned int EscolherOpcao(const bool MOSTRAR_OPCOES, const unsigned int DELAY_ESCOLHA);
// Implementação da Interface para gravar para o CSV
void OpcaoGravacao(std::string NOME_ARQUIVO, infoSatelite *&satelites,
                   const unsigned int qSatelites,
                   const unsigned int VELOCIDADE_ANIMACOES);
// Implementação da Interface para fechar o prograga.
void OpcaoSaida(infoSatelite *&satelites, const unsigned int VELOCIDADE_ANIMACOES);
// Pausa execução do codígo pelo tempo especificado. Utiliza segundos.
void Sleep(int time);

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

    bool mostrarOpcoes = true;
    while (true) {
        const unsigned int VELOCIDADE_ANIMACOES = 2;
        const unsigned int opcao = EscolherOpcao(mostrarOpcoes, VELOCIDADE_ANIMACOES);
        
        switch (opcao) {
            case 0: {
                mostrarOpcoes = !mostrarOpcoes;
                break;
            }
            case 7: {
                OpcaoGravacao(NOME_CSV, satelites, qSatelites, VELOCIDADE_ANIMACOES);
                break;
            }
            case 8: {
                OpcaoSaida(satelites, VELOCIDADE_ANIMACOES);
                break;
            }
            default: {
                std::cout << "Opção inválida :(" << std::endl;
                std::cout << "Voltando..." << std::endl;
                Sleep(VELOCIDADE_ANIMACOES);
                break;
            }
        }
    }

    return 0;
}

unsigned int EscolherOpcao(const bool MOSTRAR_OPCOES, const unsigned int DELAY_ESCOLHA) {
    bool opcaoValida = false;
    unsigned int opcao = 0;

    while (not opcaoValida) {
        Clear();
        try {
            if (MOSTRAR_OPCOES) {
                std::cout << textoOpcoes << std::endl;
            }
            std::cout << "> ";

            std::string opcaoString;
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

    return opcao;
}

bool Confirmar(std::string mensagem) {
    std::string escolha;
    std::cout << mensagem << " (s/n)" << std::endl;
    std::cin >> escolha;
    // transforma a string de escolha em minusculas
    std::transform(escolha.begin(), escolha.end(), escolha.begin(), ::tolower);

    if (escolha == "s" or escolha == "sim") {
        return true;
    }
    else {
        return false;
    }
}

void Clear() {
    int retorno = system("clear");
    if (retorno == -1) {
        std::cout << "Erro: Não foi possivel limpar o terminal" << std::endl;
    }
    else {
        return;
    }
}

void OpcaoGravacao(std::string NOME_ARQUIVO, infoSatelite *&satelites,
                   const unsigned int qSatelites,
                   const unsigned int VELOCIDADE_ANIMACOES) {
    if (Confirmar(textoConfirmarGravar)) {
        GravarAlterações(NOME_ARQUIVO, satelites, qSatelites);
        std::cout << textoGravacaoCompeta << std::endl;
    }
    else {
        std::cout << textoCancelarGravacao << std::endl;
    }
    std::cout << textoRetornoMenu << std::endl;
    Sleep(VELOCIDADE_ANIMACOES);

    return;
}

void OpcaoSaida(infoSatelite *&satelites, const unsigned int VELOCIDADE_ANIMACOES) {
    if (Confirmar(textoConfirmarSair)) {
        std::cout << "Saindo";

        for (unsigned int i = 0; i < VELOCIDADE_ANIMACOES; i++) {
            std::cout << ".";
            Sleep(1);
        }
        std::cout << std::endl;
        
        Clear();
        DescarregarCSV(satelites);
        exit(0);
    }
    else {
        std::cout << textoRetornoMenu << std::endl;
        Sleep(VELOCIDADE_ANIMACOES);
    }

    return;
}

void Sleep(int time) {
    std::cout.flush();
    std::cin.sync();
    std::this_thread::sleep_for(std::chrono::seconds(time));

    return;
}
