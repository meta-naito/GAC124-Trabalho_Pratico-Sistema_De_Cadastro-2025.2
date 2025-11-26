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

// Carregar informações sobre os satelites de um CSV.
infoSatelite* CarregarCSV(const std::string NOME_ARQUIVO, unsigned int &tamanhoVetor,
                          unsigned int &qSatelites);
// Imprime um alcance de elementos no terminal.
// Note: Não informa se um elemento não existe.
void Imprimir(unsigned int idInicio, unsigned int idFinal, infoSatelite* satelites,
              const unsigned int qSatelites);
// Imprime um elemento no terminal.
// Note: Não informa se um elemento não existe.
void ImprimirElemento(const unsigned int identificador, infoSatelite* satelites,
              const unsigned int qSatelites);
// Redimensiona o vetor. Altera valor do tamanho do vetor para novo tamanho.
void RedimensionaVetor(infoSatelite *&vetor, unsigned int &tamanhoVetor);

// === TODO ===

// Soobrescre um elemento com um novo elemento
void SobreescreverElemento(unsigned int identificador, infoSatelite novoElemento);
// Recebe um elemento é o insere em um vetor de satelites.
// Assume que o vetor está ordenado e que não esta mudando durante a inserção.
// Atuzaliza tamanho do vetor
void InserirElemento(infoSatelite elemento, infoSatelite *&satelites, unsigned int &tamanhoVetor);

// Obtem numero de registros no CSV
unsigned int ObterQuantidadeSatelites(const std::string NOME_ARQUIVO);
// Atualiza numero de registros no CSV
void AtualizarNumeroSatelites(const std::string NOME_ARQUIVO, unsigned int novoValor);

// Buscar em memoria pelo id especificado é o imprime
void BuscarId();
// Sobreescreve o id de algum elemento. Ou seja o substituido, preservando o elemento.
void SobreescreverId();

// Atualiza o nome de um elemento pelo Id;
void AtualizarNome();

// Atualiza o pais de um elemento pelo Id;
void AtualizarPais();

// Atualiza o ano de um elemento pelo Id;
void AtualizarAno();

// Atualiza a função de um elemento pelo Id.
void AtualizarFuncao();

// Grava alterações em memória para um arquivo.
void GravarAlterações(const std::string NOME_ARQUIVO, infoSatelite *vetor, unsigned int qSatelites);

// === ---- ===

int main(){
    const std::string NOME_CSV = "db_satelites.csv";
    const unsigned int TAM_INICIAL = 40;
    unsigned int tamVetor = TAM_INICIAL;
    unsigned int qSatelites = 0;

    infoSatelite* satelites = CarregarCSV(NOME_CSV, tamVetor, qSatelites);

    std::cout << satelites[2].getId() << " " << satelites[2].getNome() << std::endl;
    std::cout << qSatelites << std::endl;

    Imprimir(3, 6, satelites, qSatelites);

    return 0;
}

infoSatelite* CarregarCSV(const std::string NOME_ARQUIVO, unsigned int &tamanhoVetor,
                          unsigned int &qSatelites) {
    // Abre CSV
    std::ifstream arquivoCSV(NOME_ARQUIVO);
    if (!arquivoCSV) {
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

void ImprimirElemento(const unsigned int identificador, infoSatelite* satelites,
                      const unsigned int qSatelites) {
    for (unsigned int i = 0; i < qSatelites; i++) {
        if (identificador == satelites[i].getId()) {
            std::cout << "> Satélite de ID " << satelites[i].getId() << " <\n"
                      << " Nome: " << satelites[i].getNome() << "\n"
                      << " Pais de origem: " << satelites[i].getPais() << "\n"
                      << " Ano Lançamento: " << satelites[i].getAno() << "\n"
                      << " Função: \n   \"" << satelites[i].getFuncao() << "\"\n"
                      << "> -------------- " << std::endl; 
        }
    }

    return;
}

void Imprimir(unsigned int idInicio, unsigned int idFinal, infoSatelite* satelites,
              const unsigned int qSatelites) {
    for (unsigned int i = 0; i < qSatelites; i++) {
        if (i >= idInicio and i <= idFinal) {
            std::cout << "> Satélite de ID " << satelites[i].getId() << " <\n"
                      << " Nome: " << satelites[i].getNome() << "\n"
                      << " Pais de origem: " << satelites[i].getPais() << "\n"
                      << " Ano Lançamento: " << satelites[i].getAno() << "\n"
                      << " Função: \n   \"" << satelites[i].getFuncao() << "\"\n"
                      << "> -------------- " << std::endl; 
        }
    }

    return;
}
