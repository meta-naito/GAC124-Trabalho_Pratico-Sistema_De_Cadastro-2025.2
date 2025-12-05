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
void OpcaoBuscar(infoSatelite *satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES);
// Implementação da Interface para ordenar satélites.
void OpcaoOrdenar(infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES);
// Implementação da Interface para inserir satélites.
void OpcaoInserir(infoSatelite *&satelites, unsigned int &qSatelites, unsigned int &tamanhoVetorconst, const unsigned int TEMPO_ANIMACOES);
// Implementação da Interface para alterar satélites.
void OpcaoAlterar(infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES);
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

    infoSatelite* satelites = CarregarCSV(NOME_CSV, qSatelites, tamanhoVetor);

    Clear();
    const unsigned int DELAY = 6;
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
                OrdernarNome(satelites, qSatelites);
                EnterParaContinuar();
                break;
            }
            case 1: {
                OpcaoExibir(satelites, qSatelites, TEMPO_ANIMACOES);
                break;
            }
            case 2: {
                OpcaoBuscar(satelites, qSatelites, TEMPO_ANIMACOES);
                break;
            }
            case 3: {
                OpcaoOrdenar(satelites, qSatelites, TEMPO_ANIMACOES);
                break;
            }
            case 5: {
                OpcaoInserir(satelites, qSatelites, tamanhoVetor, TEMPO_ANIMACOES);
                break;
            }
            case 4: {
                OpcaoAlterar(satelites, qSatelites, TEMPO_ANIMACOES);
                break;
            }
            case 6: {
                OpcaoApagar(satelites, qSatelites, tamanhoVetor, TEMPO_ANIMACOES);
                break;
            }
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
    bool escolhido = false;
    while (not escolhido) {
        std::string escolha;
        std::cout << mensagem << " (s/n)" << std::endl;
        std::cin >> escolha;

        // transforma a string de escolha em minusculas
        // transform(escolha.begin(), escolha.end(), escolha.begin(), ::tolower);
        for (unsigned int i = 0; i < escolha.length(); i++) {
            escolha[i] = tolower(escolha[i]);
        }

        if (escolha == "s" or escolha == "sim") {
            escolhido = true;
            return true;
        }
        else if (escolha == "n" or escolha == "nao" or escolha == "não") {
            escolhido = true;
            return false;
        }
        else {
            std::cout << "Escolha invalida" << std::endl;
        }
    }

    return false;
}

void Clear() {
    int retorno = system("clear");
    if (retorno == -1) {
        std::cout << "Erro: Não foi possivel limpar o terminal" << std::endl;
    }

    std::cout.flush();
    return;
}

void EnterParaContinuar() {
    std::cout << "Press ENTER to continue...";
    // Discarta tudo incluindo '\n'
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Espera por '\n' pelo usuario (ENTER).
    std::string entrada;
    std::getline(std::cin, entrada);  

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
                std::cout << textoExibirUnico << std::endl;
                std::cout << "> ";

                std::string identidicadorString;
                std::cin >> identidicadorString;
                const unsigned int identificador = std::stoi(identidicadorString);

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
                return;
            }
            catch (std::out_of_range const&){
                std::cout << "Opção fora de alcance (numero grande demais)." << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }
            catch (std::exception const& erro) {
                std::cout << "Erro: " << erro.what() << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }

            break;
        }
        // Exibir alcance de satelites.
        case 2: {
            try {
                Clear();
                std::cout << textoExibirComecoAlcance << std::endl;
                std::cout << "> ";

                std::string inicioString;
                std::cin >> inicioString;
                const unsigned int inicio = std::stoi(inicioString);

                std::cout << textoExibirFinalAlcance << std::endl;
                std::cout << "> ";

                std::string fimString;
                std::cin >> fimString;
                const unsigned int fim = std::stoi(fimString);

                if (fim < inicio) {
                    throw std::out_of_range("Alcance impossivel.");
                }
                else if (inicio <= 0 or fim <= 0) {
                    throw std::out_of_range("Index inválido.");
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
                return;
            }
            catch (std::out_of_range const&){
                std::cout << "Opção fora de alcance válido." << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }
            catch (std::exception const& erro) {
                std::cout << "Erro:" << erro.what() << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }
            break;
        }
        // Exibir todos os satelites.
        case 3: {
            Clear();
            Imprimir(1, qSatelites, satelites, qSatelites);
            EnterParaContinuar();
            break;
        }
        default: {
            std::cout << "Opção inválida :(" << std::endl;
            std::cout << textoRetornoMenu << std::endl;
            Sleep(TEMPO_ANIMACOES);
            return;
            break;
        }
    }

    return;
}

void OpcaoBuscar(infoSatelite *satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES) {
    Clear();
    const unsigned int opcao = EscolherOpcao(tituloBusca, textoBuscaOpcoes, TEMPO_ANIMACOES);

    infoSatelite *aux = new infoSatelite[qSatelites];
    for (unsigned int i = 0; i < qSatelites; i++) {
        aux[i] = satelites[i];
    }

    switch (opcao) {
        // Busca por Nome
        case 1: {
            OrdernarNome(aux, qSatelites);

            std::cout << "> ";
            std::string querie;
            getline(std::cin >> std::ws, querie);

            // Adicionar busca aqui

            break;
        }
        // Busca por Pais
        case 2: {
            OrdernarPais(aux, qSatelites);

            std::cout << "> ";
            std::string querie;
            getline(std::cin >> std::ws, querie);

            // Adicionar busca aqui

            break;
        }
        // Busca por Ano de Lancamento
        case 3: {
            OrdenarAno(aux, qSatelites);

            unsigned int querie;
            try {
                std::cout << "> ";
                std::string querieString;
                getline(std::cin >> std::ws, querieString);

                querie = std::stoi(querieString);
            }
            catch (std::exception const& erro) {
                std::cout << "Erro:" << erro.what() << std::endl;
                std::cout << textoVoltandoAoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                delete[] aux;
                return;
            }

            // Adicionar busca aqui

            break;
        }
        // Busca por Funcao
        case 4: {
            OrdenarFuncao(aux, qSatelites);

            std::cout << "> ";
            std::string querie;
            getline(std::cin >> std::ws, querie);

            // Adicionar busca aqui

            break;
        }
        default: {
            std::cout << "Opção inválida :(" << std::endl;
            std::cout << textoRetornoMenu << std::endl;
            Sleep(TEMPO_ANIMACOES);
            break;
        }
    }

    delete[] aux;
    std::cin.ignore();
    EnterParaContinuar();

    return;
}

void OpcaoOrdenar(infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES) {
    Clear();
    const unsigned int opcao = EscolherOpcao(tituloOrdenar, textoOrdenarOpcoes, TEMPO_ANIMACOES);

    switch (opcao) {
        case 1: {
            OrdernarId(satelites, qSatelites);
            std::cout << textoSucessoOrdenação << std::endl;
            break;
        }
        case 2: {
            Clear();
            const int MAX_OPCOES = 4;
            bool opcoesEscolhidas = false;
            int escolhidas = 0;
            unsigned int *ordenarPor = new unsigned int[MAX_OPCOES];

            std::cout << decorador << ' ' << tituloOrdenarCampos << ' ' << decorador << std::endl;
            std::cout << textoOrdenarCampos << std::endl;
            std::cout << decoradorInferior << std::endl;;

            while ((not opcoesEscolhidas) and (escolhidas < MAX_OPCOES)) {
                try {
                    std::string opcaoString;
                    std::cout << "> ";
                    std::cin >> opcaoString;

                    unsigned int opcaoCampo = stoi(opcaoString);
                    if (opcaoCampo <= 0 or opcaoCampo > MAX_OPCOES) {
                        throw std::out_of_range("Não é uma opcão válida.");
                    }

                    ordenarPor[escolhidas] = opcaoCampo;

                    if ((escolhidas + 1 != MAX_OPCOES) and (not Confirmar("Deseja escolher mais uma opção?"))) {
                        opcoesEscolhidas = true;
                        escolhidas++;
                    }
                    else {
                        escolhidas++;
                    }
                }
                catch (std::invalid_argument const&) {
                    std::cout << "Opção deve ser um numero." << std::endl;
                    std::cout << "Ignorando." << std::endl;
                }
                catch (std::out_of_range const&){
                    std::cout << "Opção fora de alcance." << std::endl;
                    std::cout << "Ignorando." << std::endl;
                }
                catch (std::exception const&) {
                    std::cout << "Opção inválida." << std::endl;
                    std::cout << "Ignorando." << std::endl;
                }
            }

            for (int i = 0, j = escolhidas - 1; i < j; i++, j--) {
                int aux = ordenarPor[i];
                ordenarPor[i] = ordenarPor[j];
                ordenarPor[j] = aux;
            }

            for (int i = 0; i < escolhidas; i++) {
                switch (ordenarPor[i]) {
                    // Por Nome
                    case 1: {
                        OrdernarNome(satelites, qSatelites);
                        break;
                    }
                    // Por Pais
                    case 2: {
                        OrdernarPais(satelites, qSatelites);
                        break;
                    }
                    // Por Ano
                    case 3: {
                        OrdenarAno(satelites, qSatelites);
                        break;
                    }
                    // Por Funcao
                    case 4: {
                        OrdenarFuncao(satelites, qSatelites);
                        break;
                    }
                    default: {
                    std::cout << "Se vc ta lendo isso, vc consegui escolher uma opção indevida o que não devia acontecer." << std::endl;
                    std::cout << textoRetornoMenu << std::endl;
                    Sleep(TEMPO_ANIMACOES);
                    return;
                    }
                }
            }

            std::cout << textoSucessoOrdenação << std::endl;
            std::cout << textoRetornoMenu << std::endl;
            break;
        }
        default: {
            std::cout << "Opção inválida :(" << std::endl;
            std::cout << textoRetornoMenu << std::endl;
            Sleep(TEMPO_ANIMACOES);
            return;
        }
    }

    EnterParaContinuar();
    return;
}

void OpcaoAlterar(infoSatelite *&satelites, const unsigned int qSatelites, const unsigned int TEMPO_ANIMACOES) {
    Clear();
    const unsigned int opcao = EscolherOpcao(tituloAlterar, textoAlterarOpcoes, TEMPO_ANIMACOES);

    unsigned int identificador;
    try {
        std::cout << textoAlterarPedirId << std::endl;
        std::cout << "> ";

        std::string identificadorString;
        std::cin >> identificadorString;
        identificador = std::stoi(identificadorString);

        if (not ExisteId(identificador, satelites, qSatelites)) {
            std::cout << textoIdentificadorNaoExiste << std::endl;
            std::cout << textoRetornoMenu << std::endl;
            Sleep(TEMPO_ANIMACOES);
            return;
        }

        identificador = PosicaoId(identificador, satelites, qSatelites);
    }
    catch (std::invalid_argument const&) {
        std::cout << "O identificador deve ser um numero." << std::endl;
        std::cout << textoRetornoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
        return;
    }
    catch (std::out_of_range const&){
        std::cout << "Identificador fora de alcance." << std::endl;
        std::cout << textoRetornoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
        return;
    }
    catch (std::exception const& erro) {
        std::cout << "Erro: " << erro.what() << std::endl;
        std::cout << textoRetornoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
        return;
    }

    switch (opcao) {
        // Alterar nome
        case 1: {
            std::cout << "Sátelite selecionado: " << satelites[identificador].getId()
                      << " de nome \"" << satelites[identificador].getNome() << "\"." << std::endl;

            std::cout << textoPedirAlteracao << std::endl;
            std::string novoNome;
            std::cout << "> ";

            try {
                getline(std::cin >> std::ws, novoNome);

                satelites[identificador].setNome(novoNome);
                std::cout << textoAlterarSucesso << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }
            catch (std::exception const& erro) {
                std::cout << "Erro: " << erro.what() << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }

            break;
        }
        // Alterar Pais
        case 2: {
            std::cout << "Sátelite selecionado: " << satelites[identificador].getId()
                      << " de nome \"" << satelites[identificador].getNome() << "\"." << std::endl;

            std::cout << textoPedirAlteracao << std::endl;
            std::string novoPais;
            std::cout << "> ";

            try {
                getline(std::cin >> std::ws, novoPais);

                satelites[identificador].setPais(novoPais);
                std::cout << textoAlterarSucesso << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }
            catch (std::exception const& erro) {
                std::cout << "Erro: " << erro.what() << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }

            break;
        }
        // Alterar Ano
        case 3: {
            std::cout << "Sátelite selecionado: " << satelites[identificador].getId()
                      << " de nome \"" << satelites[identificador].getNome() << "\"." << std::endl;

            std::cout << textoPedirAlteracao << std::endl;
            std::string novoAnoString;
            std::cout << "> ";

            try {
                std::cin >> novoAnoString;
                const unsigned int novoAno = std::stoi(novoAnoString);

                satelites[identificador].setAno(novoAno);
                std::cout << textoAlterarSucesso << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }
            catch (std::invalid_argument const&) {
                std::cout << "O Ano deve ser um numero." << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }
            catch (std::out_of_range const&){
                std::cout << "Ano fora de alcance (muito grande, nulo ou negativo)." << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }
            catch (std::exception const& erro) {
                std::cout << "Erro: " << erro.what() << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }

            break;
        }
        // Alterar Funcao
        case 4: {
            std::cout << "Sátelite selecionado: " << satelites[identificador].getId()
                      << " de nome \"" << satelites[identificador].getNome() << "\"." << std::endl;

            std::cout << textoPedirAlteracao << std::endl;
            std::string novoFuncao;
            std::cout << "> ";

            try {
                getline(std::cin >> std::ws, novoFuncao);

                satelites[identificador].setFuncao(novoFuncao);
                std::cout << textoAlterarSucesso << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }
            catch (std::exception const& erro) {
                std::cout << "Erro: " << erro.what() << std::endl;
                std::cout << textoRetornoMenu << std::endl;
                Sleep(TEMPO_ANIMACOES);
                return;
            }
            break;
        }
        default: {
            std::cout << "Opção inválida :(" << std::endl;
            std::cout << textoRetornoMenu << std::endl;
            Sleep(TEMPO_ANIMACOES);
            break;
        }
    }

    std::string lixo;
    getline(std::cin, lixo);

    return;
}

void OpcaoInserir(infoSatelite *&satelites, unsigned int &qSatelites, unsigned int &tamanhoVetor, const unsigned int TEMPO_ANIMACOES) {
    Clear();
    std::cout << decorador << " " << tituloInserir << decorador << " " << std::endl;

    try {
        infoSatelite novoElemento;
        novoElemento.setId(0);

        std::string aux;

        std::cout << "Nome: " << "\n> ";
        getline(std::cin >> std::ws, aux);
        if(aux.empty()) {
            throw std::length_error("Nome vazio.");
        }

        novoElemento.setNome(aux);

        std::cout << "Pais: " << "\n> ";
        getline(std::cin >> std::ws, aux);
        novoElemento.setPais(aux);
        if (aux.empty()) {
            throw std::length_error("Pais vazio.");
        }

        std::cout << "Ano: " << "\n> ";
        std::cin >> aux;
        int auxAno = std::stoi(aux);
        novoElemento.setAno(auxAno);

        std::cout << "Função: " << "\n> ";;
        getline(std::cin >> std::ws, aux);
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
        return;
    }
    catch (std::out_of_range const&){
        std::cout << "Valor grande demais :(" << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
        return;
    }
    catch (std::length_error const& erro) {
        std::cout << "Tamanho incorreto: " << erro.what() << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
        return;
    }
    catch (std::exception const& erro) {
        std::cout << "Erro:" << erro.what() << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
        return;
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
        getline(std::cin >> std::ws, identificadorString);

        if (identificadorString.empty()) {
            throw std::length_error("Id não deve estar vazio.");
        }

        unsigned int identificador = std::stoi(identificadorString);
        if (ExisteId(identificador, satelites, qSatelites)) {
            RemoverElemento(identificador, satelites, qSatelites);

            const unsigned int EXCESSO = 10;
            if (tamanhoVetor > (qSatelites + EXCESSO) + 1) {
                ReduzirVetor(EXCESSO, satelites, tamanhoVetor);
            }

            std::cout << textoSucessoApagar << std::endl;
        }
        else {
            std::cout << textoIdentificadorNaoExiste << std::endl;
        }

        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
    }
    catch (std::invalid_argument const&) {
        std::cout << "Id deve ser um numero." << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
        return;
    }
    catch (std::length_error const&) {
        std::cout << "Id não deve estar vazio." << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
        return;
    }
    catch (std::exception const& erro) {
        std::cout << "Erro:" << erro.what() << std::endl;
        std::cout << textoVoltandoAoMenu << std::endl;
        Sleep(TEMPO_ANIMACOES);
        return;
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
    std::this_thread::sleep_for(std::chrono::seconds(time));

    return;
}
