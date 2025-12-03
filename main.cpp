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

// Pede confirmação para o usuário com sim ou não, sobre escolha com a mensagem passada.
// Sempre exibe ao final da mensagem " (s/n)".
bool Confirmar(std::string mensagem);
// Limpa o terminal
// OBS: Só funciona em UNIX.
void Clear();
// Espera até que o usuário digite digite alguma coisa para continuar a execução.
void EnterParaContinuar();
// Exibe texto de opcoes + eecolhe escolha do usuario de inteiro não assinado.
// Lida com erros causados por escolhas incorretas.
unsigned int EscolherOpcao(const std::string TITULO, const std::string OPCOES, const unsigned int TEMPO_ANIMACOES);
// Implementação da Interface para exibir satélites.
void OpcaoExibir(infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES);
// Implementação da Interface para buscar satélites.
void OpcaoBuscar(infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES);
// Implementação da Interface para inserir satèlites.
void OpcaoInserir(infoSatelite *&satelites, unsigned int &qSatelites, unsigned int &tamanhoVetorconst, const unsigned int TEMPO_ANIMACOES);
// Implementação da Interface para deletar satélites.
void OpcaoApagar(infoSatelite *&satelites, unsigned int &qSatelites, unsigned int &tamanhoVetor, const unsigned int TEMPO_ANIMACOES);
// Implementação da Interface para gravar para o CSV
void OpcaoGravacao(std::string NOME_ARQUIVO, infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES);
// Implementação da Interface para fechar o prograga.
void OpcaoSaida(infoSatelite *&satelites, const unsigned int TEMPO_ANIMACOES);
// Pausa execução do codígo pelo tempo especificado. Utiliza segundos.
void Sleep(int time);

int main() {
    extern const std::string textoInicio;
    extern const std::string sateliteASCII;
    extern const std::string textoOpcoes;
    
    const std::string NOME_CSV = "db_satelites.csv";
    const unsigned int TAM_INICIAL = 40;
    unsigned int tamanhoVetor = TAM_INICIAL;
    unsigned int qSatelites = 0;

    infoSatelite* satelites = CarregarCSV(NOME_CSV, tamanhoVetor, qSatelites);

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
        const unsigned int TEMPO_ANIMACOES = 2;
        const unsigned int opcao = EscolherOpcao(tituloMenu, textoOpcoesMenu, TEMPO_ANIMACOES);
        
        switch (opcao) {
            // 0 -> CASO DE TESTES
            case 0: {
                std::cout << MaiorId(satelites, qSatelites) << std::endl;
                EnterParaContinuar();
                break;
            }
            case 1: {
                OpcaoExibir(satelites, qSatelites, TEMPO_ANIMACOES);
                break;
            case 2:
                OpcaoBuscar();
                break;
            case 5:
                OpcaoInserir(satelites, qSatelites, tamanhoVetor, TEMPO_ANIMACOES);
                break;
            }
            case 6:
                OpcaoApagar(satelites, qSatelites, tamanhoVetor, TEMPO_ANIMACOES);
                break;
            case 7: {
                OpcaoGravacao(NOME_CSV, satelites, qSatelites, TEMPO_ANIMACOES);
                break;
            }
            case 8: {
                OpcaoSaida(satelites, TEMPO_ANIMACOES);
                break;
            }
            default: {
                std::cout << "Opção inválida :(" << std::endl;
                std::cout << textoVoltando << std::endl;
                Sleep(TEMPO_ANIMACOES);
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

void EnterParaContinuar() {
    std::cin.ignore();
    std::cout << "Digite Enter para continuar." << std::endl;
    std::cin.get();

    return;
}

unsigned int EscolherOpcao(const std::string TITULO, const std::string OPCOES, const unsigned int TEMPO_ANIMACOES) {
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
            std::cout << "Opção deve ser um numero." << std::endl;
            std::cout << textoVoltando << std::endl;
            Sleep(TEMPO_ANIMACOES);
        }
        catch (std::out_of_range const&){
            std::cout << "Opção fora de alcance (numero grande demais)." << std::endl;
            std::cout << textoVoltando << std::endl;
            Sleep(TEMPO_ANIMACOES);
        }
        catch (std::exception const&) {
            std::cout << "Opção inválida." << std::endl;
            std::cout << textoVoltando << std::endl;
            Sleep(TEMPO_ANIMACOES);
        }
    }

    return opcao;
}

void OpcaoExibir(infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES) {
    Clear();
    const unsigned int opcao = EscolherOpcao(tituloExibir, textoExibirOpcoes, TEMPO_ANIMACOES);

    switch (opcao) {
        // Exibir um satelite.
        case 1: {
            try {
                Clear();
                std::cout << "Digite o identificador do satélite a ser exibido" << std::endl;
                std::cout << "> ";

                std::string identidicadorString;
                std::cin >> identidicadorString;
                const unsigned int identificador = stoi(identidicadorString);

                if (ExisteId(identificador, satelites, qSatelites)) {
                    std::cout << std::endl;
                    ImprimirElemento(identificador, satelites, qSatelites);
                }
                else {
                    std::cout << textoIdentificadorNaoExiste << std::endl;
                }

                EnterParaContinuar();
            }
            catch (std::invalid_argument const&) {
                std::cout << "Opção deve ser um numero." << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
            }
            catch (std::out_of_range const&){
                std::cout << "Opção fora de alcance (numero grande demais)." << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
            }
            catch (std::exception const& erro) {
                std::cout << "Erro: " << erro.what() << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
            }

            break;
        }
        // Exibir alcance de satelites.
        case 2: {
            try {
                Clear();
                std::cout << "Note: Se um Id não existir ele sera pulado." << std::endl;
                std::cout << "Digite o identificador no começo do alcance a ser exibido" << std::endl;
                std::cout << "> ";

                std::string inicioString;
                std::cin >> inicioString;
                const unsigned int inicio = stoi(inicioString);

                std::cout << "Digite o identificador no final do alcance a ser exibido" << std::endl;
                std::cout << "> ";

                std::string fimString;
                std::cin >> fimString;
                const unsigned int fim = stoi(fimString);

                if (fim < inicio) {
                    throw std::out_of_range("Alcance impossivel.");
                }

                Clear();
                Imprimir(inicio, fim, satelites, qSatelites);
                std::cout << std::endl;

                EnterParaContinuar();
            }
            catch (std::invalid_argument const&) {
                std::cout << "Opção deve ser um numero." << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
            }
            catch (std::out_of_range const&){
                std::cout << "Opção fora de alcance válido." << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
            }
            catch (std::exception const& erro) {
                std::cout << "Erro:" << erro.what() << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
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
            std::cout << textoRetornoMenu << std::endl;
            Sleep(TEMPO_ANIMACOES);
            break;
        }
    }

    return;
}

void OpcaoBuscar(infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES) {
    

    return;
}

void OpcaoInserir(infoSatelite *&satelites, unsigned int &qSatelites, unsigned int &tamanhoVetor, const unsigned int TEMPO_ANIMACOES) {
    Clear();
    std::cout << decorador << " " << tituloInserir << decorador << " " << std::endl;

    try {
        infoSatelite novoElemento;
        novoElemento.setId(0);

        std::string aux;

        std::cin.ignore();
        std::cout << "Nome: " << "\n> ";
        getline(std::cin, aux);
        if(aux.empty()) {
            throw std::length_error("Nome vazio.");
        }

        novoElemento.setNome(aux);

        std::cout << "Pais: " << "\n> ";
        getline(std::cin, aux);
        novoElemento.setPais(aux);
        if(aux.empty()) {
            throw std::length_error("Pais vazio.");
        }

        std::cout << "Ano: " << "\n> ";
        std::cin >> aux;
        std::cin.ignore();
        int auxAno = stoi(aux);
        novoElemento.setAno(auxAno);

        std::cout << "Função: " << "\n> ";;
        getline(std::cin, aux);
        novoElemento.setFuncao(aux);
        if(aux.empty()) {
            throw std::length_error("Função vazia.");
        }

        InserirElemento(novoElemento, satelites, qSatelites, tamanhoVetor);
    }
    catch (std::invalid_argument const&) {
        std::cout << "Ano deve ser um numero." << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
    }
    catch (std::out_of_range const&){
        std::cout << "Valor grande demais :(" << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
    }
    catch (std::length_error const& erro) {
        std::cout << "Tamanho incorreto: " << erro.what() << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
    }
    catch (std::exception const& erro) {
        std::cout << "Erro:" << erro.what() << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
    }

    return;
}

void OpcaoApagar(infoSatelite *&satelites, unsigned int &qSatelites, unsigned int &tamanhoVetor, const unsigned int TEMPO_ANIMACOES) {
    Clear();
    std::cout << decorador << " " << tituloApagar << decorador << " " << std::endl;

    try {
        std::cout << "Identificador a ser deletado: " << std::endl;
        std::cout << "> ";
        std::string identificadorString;
        std::cin.ignore();
        getline(std::cin, identificadorString);

        if (identificadorString.empty()) {
            throw std::length_error("Id não deve estar vazio.");
        }

        unsigned int identificador = stoi(identificadorString);
        if (ExisteId(identificador, satelites, qSatelites)) {
            RemoverElemento(identificador, satelites, qSatelites);
            std::cout << textoSucessoApagar << std::endl;
            EnterParaContinuar();
        }
        else {
            std::cout << textoIdentificadorNaoExiste << std::endl;
            Sleep(TEMPO_ANIMACOES);
            std::cout << textoVoltandoAoMenu << std::endl;
        }
    }
    catch (std::invalid_argument const&) {
        std::cout << "Id deve ser um numero." << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
    }
    catch (std::length_error const&) {
        std::cout << "Id não deve estar vazio." << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
    }
    catch (std::exception const& erro) {
        std::cout << "Erro:" << erro.what() << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
    }

    return;
}

void OpcaoGravacao(std::string NOME_ARQUIVO, infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES) {
    if (Confirmar(textoConfirmarGravar)) {
        GravarAlterações(NOME_ARQUIVO, satelites, qSatelites);
        std::cout << textoGravacaoCompeta << std::endl;
    }
    else {
        std::cout << textoCancelarGravacao << std::endl;
    }
    std::cout << textoRetornoMenu << std::endl;
    Sleep(TEMPO_ANIMACOES);

    return;
}

void OpcaoSaida(infoSatelite *&satelites, const unsigned int TEMPO_ANIMACOES) {
    if (Confirmar(textoConfirmarSair)) {
        std::cout << "Saindo";

        for (unsigned int i = 0; i < TEMPO_ANIMACOES; i++) {
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
        Sleep(TEMPO_ANIMACOES);
    }

    return;
}

void Sleep(int time) {
    std::cout.flush();
    std::cin.sync();
    std::this_thread::sleep_for(std::chrono::seconds(time));

    return;
}
