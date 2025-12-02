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
#include "csv_utils.hpp"
#include "textosInterface.hpp"
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

// Pede confirmação para o usuário com 'sim' ou 'não', sobre escolha com a mensagem passada.
// Sempre exibe ao final da mensagem "(s/n)".
bool Confirmar(std::string mensagem);

// Limpa o terminal
// OBS: Só funciona em UNIX.
void Clear();

// Espera até que o usuário digite algo para continuar a execução do programa.
void EnterParaContinuar();

// Exibe texto de opções + escolhe alternativa do usuário de inteiro não assinado/inteiro positivo.
// Lida com erros causados por escolhas incorretas.
unsigned int EscolherOpcao(const std::string TITULO, const std::string OPCOES, const unsigned int DELAY_ESCOLHA);

// Implementação da Interface para exibir satélites.
void OpcaoExibir(infoSatelite *&satelites, unsigned int qSatelites, const int VELOCIDADE_ANIMACOES);

// Implementação da Interface para gravar para o arquivo CSV.
void OpcaoGravacao(std::string NOME_ARQUIVO, infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int VELOCIDADE_ANIMACOES);

// Implementação da Interface para fechar o programa.
void OpcaoSaida(infoSatelite *&satelites, const unsigned int VELOCIDADE_ANIMACOES);

// Pausa execução do código pelo tempo especificado. Utiliza segundos como medição de tempo.
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

    while (true) {
        const unsigned int VELOCIDADE_ANIMACOES = 2;
        const unsigned int opcao = EscolherOpcao(tituloMenu, textoOpcoesMenu, VELOCIDADE_ANIMACOES);
        
        switch (opcao) {
            // 0 -> CASO DE TESTES
            case 0: {
                std::cout << MaiorId(satelites, qSatelites) << std::endl;
                EnterParaContinuar();
                break;
            }
            case 1: {
                OpcaoExibir(satelites, qSatelites, VELOCIDADE_ANIMACOES);
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

bool Confirmar(std::string mensagem) {
    std::string escolha;
    std::cout << mensagem << " (s/n)" << std::endl;
    std::cin >> escolha;
    // transforma a string de escolha em letras minúsculas.
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
        std::cout << "Erro: Não foi possivel limpar o terminal." << std::endl;
    }
    else {
        return;
    }
}

void EnterParaContinuar() {
    std::cin.ignore();
    std::cout << "Digite Enter para continuar." << std::endl;
    std::cin.get();

    return;
}

unsigned int EscolherOpcao(const std::string TITULO, const std::string OPCOES, const unsigned int DELAY_ESCOLHA) {
    bool opcaoValida = false;
    unsigned int opcao = 0;

    while (not opcaoValida) {
        Clear();
        try {
            std::cout << decorador << ' ' << TITULO << ' ' << decorador << std::endl;
            std::cout << OPCOES << std::endl;
            std::cout << decoradorInferior << std::endl;;
            std::cout << "> ";

            std::string opcaoString;
            std::cin >> opcaoString;

            opcao = stoi(opcaoString);
            opcaoValida = true;
        }
        catch (std::invalid_argument const&) {
            std::cout << "Opção deve ser um número." << std::endl;
            std::cout << "Voltando..." << std::endl;
            Sleep(DELAY_ESCOLHA);
        }
        catch (std::out_of_range const&){
            std::cout << "Opção fora de alcance (número grande demais)." << std::endl;
            std::cout << "Voltando..." << std::endl;
            Sleep(DELAY_ESCOLHA);
        }
        catch (std::exception const&) {
            std::cout << "Opção inválida." << std::endl;
            std::cout << "Voltando ao menu principal..." << std::endl;
            Sleep(DELAY_ESCOLHA);
        }
    }

    return opcao;
}

void OpcaoExibir(infoSatelite *&satelites, unsigned int qSatelites, const int VELOCIDADE_ANIMACOES) {
    Clear();
    const unsigned int opcao = EscolherOpcao(tituloExibir, textoExibirOpcoes, VELOCIDADE_ANIMACOES);

    switch (opcao) {
        // Exibir um satélite.
        case 1: {
            try {
                Clear();
                std::cout << "Digite o identificador do satélite a ser exibido:" << std::endl;
                std::cout << "> ";

                std::string identidicadorString;
                std::cin >> identidicadorString;
                const unsigned int identificador = stoi(identidicadorString);

                if (ExisteId(identificador, satelites, qSatelites)) {
                    std::cout << std::endl;
                    ImprimirElemento(identificador, satelites, qSatelites);
                    std::cout << std::endl;
                }
                else {
                    std::cout << "Esse identificador não pertence a nenhum satélite." << std::endl;
                }

                EnterParaContinuar();
            }
            catch (std::invalid_argument const&) {
                std::cout << "Opção deve ser um número." << std::endl;
                std::cout << "Voltando ao menu principal..." << std::endl;
                Sleep(VELOCIDADE_ANIMACOES);
            }
            catch (std::out_of_range const&){
                std::cout << "Opção fora de alcance (número grande demais)." << std::endl;
                std::cout << "Voltando ao menu principal..." << std::endl;
                Sleep(VELOCIDADE_ANIMACOES);
            }
            catch (std::exception const&) {
                std::cout << "Opção inválida." << std::endl;
                std::cout << "Voltando ao menu principal..." << std::endl;
                Sleep(VELOCIDADE_ANIMACOES);
            }

            break;
        }
        // Exibir alcance de satelites.
        case 2: {
            try {
                Clear();
                std::cout << "Observação: Se um identificador não existir, ele será pulado." << std::endl;
                std::cout << "Digite o identificador no começo do alcance a ser exibido:" << std::endl;
                std::cout << "> ";

                std::string inicioString;
                std::cin >> inicioString;
                const unsigned int inicio = stoi(inicioString);

                std::cout << "Digite o identificador no final do alcance a ser exibido:" << std::endl;
                std::cout << "> ";

                std::string fimString;
                std::cin >> fimString;
                const unsigned int fim = stoi(fimString);

                if (fim <= inicio) {
                    throw std::out_of_range("Alcance impossível.");
                }

                Clear();
                Imprimir(inicio, fim, satelites, qSatelites);

                EnterParaContinuar();
            }
            catch (std::invalid_argument const&) {
                std::cout << "Opção deve ser um número." << std::endl;
                std::cout << "Voltando ao menu principal..." << std::endl;
                Sleep(VELOCIDADE_ANIMACOES);
            }
            catch (std::out_of_range const&){
                std::cout << "Opção fora de alcance válido." << std::endl;
                std::cout << "Voltando ao menu principal..." << std::endl;
                Sleep(VELOCIDADE_ANIMACOES);
            }
            catch (std::exception const&) {
                std::cout << "Opção inválida." << std::endl;
                std::cout << "Voltando ao menu principal..." << std::endl;
                Sleep(VELOCIDADE_ANIMACOES);
            }

            break;
        }
        // Exibir todos os satelites.
        case 3: {
            Clear();
            Imprimir(0, qSatelites, satelites, qSatelites);
            EnterParaContinuar();
            break;
        }
        default: {
            std::cout << "Opção inválida :(" << std::endl;
            std::cout << "Voltando ao menu..." << std::endl;
            Sleep(VELOCIDADE_ANIMACOES);
            break;
        }
    }

    return;
}

void OpcaoGravacao(std::string NOME_ARQUIVO, infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int VELOCIDADE_ANIMACOES) {
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
        DeletarSalvo(satelites);
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
