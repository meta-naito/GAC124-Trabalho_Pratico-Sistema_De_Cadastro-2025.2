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
// void InserirElemento(infoSatelite elemento, infoSatelite *&satelites, unsigned int &qSatelites);

// Deleta um elemento do vetor de satelites
// Assume que o elemento existe.
// Assume que o vetor está ordenado.
// void DeletarElemento(const unsigned int identificador, infoSatelite *&satelites, unsigned int &qSatelites);

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

int main(){
    const std::string NOME_CSV = "db_satelites.csv";
    const unsigned int TAM_INICIAL = 40;
    unsigned int tamVetor = TAM_INICIAL;
    unsigned int qSatelites = 0;

    infoSatelite* satelites = CarregarCSV(NOME_CSV, tamVetor, qSatelites);
    
    std::cout << ExisteId(2, satelites, qSatelites) << std::endl;
    std::cout << ExisteId(6, satelites, qSatelites) << std::endl;

    GravarAlterações(NOME_CSV, satelites, qSatelites);

    return 0;
}

infoSatelite* CarregarCSV(const std::string NOME_ARQUIVO, unsigned int &tamanhoVetor,
                          unsigned int &qSatelites) {
    // Abre CSV
    std::ifstream arquivoCSV(NOME_ARQUIVO);
    if (arquivoCSV.fail()) {
        std::cout << "Erro: não foi possível localizar o arquivo \"" << NOME_ARQUIVO
                  << "\" :(" << std::endl;
    }

    // Retira linha de comentário.
    std::string comentario;
    getline(arquivoCSV, comentario);
    
    // Le numero de satelites no topo.
    arquivoCSV >> qSatelites;
    arquivoCSV.ignore();
    
    infoSatelite *satelites = new infoSatelite[tamanhoVetor];

    // Lixo, nesse caso são as vírgulas.
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

    // Fecha CSV
    arquivoCSV.close();

    return satelites;
}

bool ExisteId(const unsigned int identificador, infoSatelite *&satelites,
              const unsigned int qSatelites) {
    unsigned int esq_limite = 0;
    unsigned int dir_limite = qSatelites - 1;
    
    // Busca binária pelo Identificador
    while (esq_limite <= dir_limite) {
        unsigned int meio = (esq_limite + dir_limite) / 2;

        if (satelites[meio].getId() == identificador) {
            return true;
        }

        if (satelites[meio].getId() < identificador) {
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
