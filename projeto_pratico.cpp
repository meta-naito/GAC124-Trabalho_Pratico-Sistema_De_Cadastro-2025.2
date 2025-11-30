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
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct infoSatelite {
    unsigned int identificador;
    std::string nome;
    std::string paisOrigem;
    int anoLancamento;
    std::string funcao;

    // Getters

    unsigned int getId() {
        return identificador;
    }
    std::string getNome() {
        return nome;
    }
    std::string getPais() {
        return paisOrigem;
    }
    int getAno() {
        return anoLancamento;
    }
    std::string getFuncao() {
        return funcao;
    }

    // Setters

    void setId(int entradaId) {
        identificador = static_cast<unsigned int>(entradaId);
    }
    void setId(unsigned int entradaId) {
        identificador = entradaId;
    }
    void setNome(const char* entradaNome) {
        nome = std::string(entradaNome);
    }
    void setNome(std::string entradaNome) {
        nome = entradaNome;
    }
    void setPais(const char* entradaPais) {
        paisOrigem = std::string(entradaPais);
    }
    void setPais(std::string entradaPais) {
        paisOrigem = entradaPais;
    }
    void setAno(int entradaAno) {
        anoLancamento = entradaAno;
    }
    void setFuncao(const char* entradaFuncao) {
        funcao = std::string(entradaFuncao);
    }
    void setFuncao(std::string entradaFuncao) {
        funcao = entradaFuncao;
    }
};

// OBS: Funções que se referem ao vetor de satelites, quando não especificado, devem
//      assumir que o vetor de satelites não está mudando.

// Carregar informações sobre os satelites de um CSV.
infoSatelite* CarregarCSV(const std::string NOME_ARQUIVO, unsigned int &tamanhoVetor,
                          unsigned int &qSatelites);
// Verifica se um elemento com o dado identificador existe no vetor de satelites.
// Utiliza busca binária para isso.
bool ExisteId(const unsigned int identificador, infoSatelite *&satelites,
              const unsigned int qSatelites);
// Grava alterações em memória para um arquivo.
void GravarAlterações(const std::string NOME_ARQUIVO, infoSatelite *&satelites,
                      const unsigned int qSatelites);
// Imprime um alcance de elementos no terminal.
// Note: Não informa se um elemento não existe.
void Imprimir(const unsigned int idInicio, const unsigned int idFinal,
              infoSatelite *&satelites, const unsigned int qSatelites);
// Imprime um elemento no terminal.
// Note: Não informa se um elemento não existe.
void ImprimirElemento(const unsigned int identificador, infoSatelite *&satelites,
              const unsigned int qSatelites);

// Redimensiona o vetor. Altera valor do tamanho do vetor para novo tamanho.
void RedimensionaVetor(infoSatelite *&vetor, unsigned int &tamanhoVetor);
// Soobrescreve um elemento com um novo elemento. Preserva Id do elemento antigo.
void SoobscreverElemento(const unsigned int identificador, infoSatelite novoElemento,
                         infoSatelite *&satelites, const unsigned int qSatelites);

// === TODO ===

// Recebe um elemento é o insere em um vetor de satelites.
// Assume que o elemento existe.
// Assume que o vetor está ordenado.
// void InserirElemento(infoSatelite elemento, infoSatelite *&satelites,
//                      unsigned int &qSatelites);

// Deleta um elemento do vetor de satelites
// Assume que o elemento existe.
// Assume que o vetor está ordenado.
// void DeletarElemento(const unsigned int identificador, infoSatelite *&satelites,
//                      unsigned int &qSatelites);

// Implementação de merge sort
// template <typename type> void MergeSort(type *vetor, int inicioVetor, int finalVetor);

// Ordena satelties por Id
// void OrdernarId(infoSatelite *&satelites, const unsigned int qSatelites);

// Ordena satelites por Nome
// void OrdernarNome(infoSatelite *&satelites, const unsigned int qSatelites);

// Ordena satelites por Pais de Origem
// void OrdernarPais(infoSatelite *&satelites, const unsigned int qSatelites);

// Ordena satelites por Ano de Lançamento
// void OrdenarAno (infoSatelites *&satelites, const unsigned int qSalelites);

// === ---- ===

infoSatelite* CarregarCSV(const std::string NOME_ARQUIVO, unsigned int &tamanhoVetor,
                          unsigned int &qSatelites) {

    // Abre o arquivo .csv.
    std::ifstream arquivoCSV(NOME_ARQUIVO);
    if (arquivoCSV.fail()) {
        std::cout << "Erro: não foi possível localizar o arquivo \"" << NOME_ARQUIVO
                  << "\" :(" << std::endl;
    }

    // Retira linha de comentário.
    std::string comentario;
    getline(arquivoCSV, comentario);
    
    // Lê o número de satélites no topo do arquivo.
    arquivoCSV >> qSatelites;
    arquivoCSV.ignore();
    
    infoSatelite *satelites = new infoSatelite[tamanhoVetor];

    // Lixo, que nesse caso são as vírgulas.
    char lixo;

    for (unsigned int i = 0; i < qSatelites; i++) {
        arquivoCSV >> satelites[i].identificador;
        arquivoCSV >> lixo;
        
        arquivoCSV >> lixo;
        getline(arquivoCSV, satelites[i].nome, '"');
        arquivoCSV >> lixo;
        
        arquivoCSV >> lixo;
        getline(arquivoCSV, satelites[i].paisOrigem, '"');
        arquivoCSV >> lixo;
        
        arquivoCSV >> satelites[i].anoLancamento;
        arquivoCSV >> lixo >> lixo;
        
        getline(arquivoCSV, satelites[i].funcao, '"');

        // Redimensiona vetor se tamanho do vetor for exceder a sua capacidade.
        if (i + 1 >= tamanhoVetor) {
            RedimensionaVetor(satelites, tamanhoVetor);
        }
    }

    // Fecha arquivo .csv.
    arquivoCSV.close();

    return satelites;
}

bool ExisteId(const unsigned int identificador, infoSatelite *&satelites,
              const unsigned int qSatelites) {
    unsigned int esq_limite = 0;
    unsigned int dir_limite = qSatelites;
    
    // Busca binária pelo Identificador
    while (esq_limite <= dir_limite) {
        unsigned int meio = (esq_limite + dir_limite) / 2;

        if (satelites[meio].getId() == identificador) {
            return true;
        }
        else if (satelites[meio].getId() < identificador) {
            esq_limite = meio + 1;
        }
        else {
            dir_limite = meio - 1;
        }
    }

    return false;
}

void GravarAlterações(const std::string NOME_ARQUIVO, infoSatelite *&satelites,
                      const unsigned int qSatelites) {
    // Abre arquivo atual para ler o cometário
    std::ifstream antigoCSV(NOME_ARQUIVO);
    if (antigoCSV.fail()) {
        std::cout << "Erro: não foi possível localizar o arquivo \"" << NOME_ARQUIVO
                  << "\" :(" << std::endl;
    }

    std::string comentario;
    getline(antigoCSV, comentario, '\n');

    antigoCSV.close();

    // Grava Alterações em arquivo de mesmo nome;
    std::ofstream arquivoCSV(NOME_ARQUIVO);
    if (arquivoCSV.fail()) {
        std::cout << "Erro: não foi possível criar o arquivo \"" << NOME_ARQUIVO
                  << "\" :(" << std::endl;
    }

    arquivoCSV << comentario << '\n';
    arquivoCSV << qSatelites << '\n';
    for (unsigned int i = 0; i < qSatelites; i++) {
        arquivoCSV << satelites[i].identificador << ", "
                   << '\"' << satelites[i].nome << '\"' << ", "
                   << '\"' << satelites[i].paisOrigem << '\"' << ", "
                   << satelites[i].anoLancamento << ", "
                   << '\"' << satelites[i].funcao << '\"' << '\n'; 
    }
    
    arquivoCSV.close();

    return;
}

void Imprimir(const unsigned int idInicio, const unsigned int idFinal,
              infoSatelite *&satelites, const unsigned int qSatelites) {
    for (unsigned int i = 0; i < qSatelites; i++) {
        if (satelites[i].getId() >= idInicio and satelites[i].getId() <= idFinal) {
            std::cout << "> Satélite de ID " << satelites[i].getId() << " <\n"
                      << " Nome: " << satelites[i].getNome() << '\n'
                      << " Pais de origem: " << satelites[i].getPais() << '\n'
                      << " Ano Lançamento: " << satelites[i].getAno() << '\n'
                      << " Função: \n   \"" << satelites[i].getFuncao() << "\"\n"
                      << "> -------------- " << std::endl; 
        }
    }

    return;
}

// Alias de Imprimir
void ImprimirElemento(const unsigned int identificador, infoSatelite *&satelites,
                      const unsigned int qSatelites) {
    Imprimir(identificador, identificador, satelites, qSatelites);
    return;
}

void RedimensionaVetor(infoSatelite *&satelites, unsigned int &tamanhoVetor) {
    const int TAM_REDIMENSIONAMENTO = 10;
    const int TAM_INICIAL = tamanhoVetor;

    infoSatelite *aux = new infoSatelite[TAM_INICIAL];
    for (int i = 0; i < TAM_INICIAL; i++) {
        aux[i] = satelites[i];
    }
    delete[] satelites;

    tamanhoVetor += TAM_REDIMENSIONAMENTO;
    satelites = new infoSatelite[tamanhoVetor];
    for (int i = 0; i < TAM_INICIAL; i++) {
        satelites[i] = aux[i];
    }
    delete[] aux;

    return;
}

void SoobscreverElemento(const unsigned int identificador, infoSatelite novoElemento,
                         infoSatelite *&satelites, const unsigned int qSatelites) {
    novoElemento.setId(identificador);
    satelites[identificador] = novoElemento;

    return;
}

void InserirElemento(infoSatelite elemento, infoSatelite *&satelites, unsigned int &tamanhoVetor) {
    // elemento já possui todas as informacoes necessarias pra eu enfiar esse elemento em algum lugar
    // baseado noq ta escrito la em cima, o vetor necessita de estar organizado
    // ou seja, necessário que os ids estejam organizados tudo certinho pra poder inserir um novo no final
    // ou seja seja, merge sort antes pelos ids, checa se tem espaço o suficiente no vetor pra inserir um novo elemento
    // coloca o elemento com o id no final do vetor, e atualiza o numero de registros utilizando a funçao la em cima!


    return;
}

void IntercalaElementos(infoSatelite *) {

    return;
}

void OrdenaVetor() {

    return;
}
