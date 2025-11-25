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
    string nome;
    string paisOrigem;
    int anoLancamento;
    string funcao;
};

void RedimensionaVetor(infoSatelite *&vetor, int &tamanhoVetor);

int main(){
    //leitura do arquivo csv
    const string nomeEntrada = "db_satelites.csv";
    ifstream arquivo_csv(nomeEntrada);
    
    if (!arquivo_csv) {
        cout << "Erro: não foi possível localizar o arquivo \"" << nomeEntrada << "\" :(" << endl;
    }

    // Retira linha de comentário
    string linha;
    getline(arquivo_csv, linha);
    
    int numRegistros;
    arquivo_csv >> numRegistros;
    arquivo_csv.ignore();
    
    const int TAM_INICIAL = 40;
    int tamVetor = TAM_INICIAL;

    infoSatelite *satelites = new infoSatelite[TAM_INICIAL];
    
    char lixo;

    for (int i = 0; i < numRegistros; i++) {
        if (i + 1 > tamVetor) {
            RedimensionaVetor(satelites, tamVetor);
        }

        arquivo_csv >> satelites[i].identificador;
        // Lixo, nesse caso são as vírgulas.
        arquivo_csv >> lixo;
        
        arquivo_csv >> lixo;
        getline(arquivo_csv, satelites[i].nome, '"');
        arquivo_csv >> lixo;
        
        arquivo_csv >> lixo;
        getline(arquivo_csv, satelites[i].paisOrigem, '"');
        arquivo_csv >> lixo;
        
        arquivo_csv >> satelites[i].anoLancamento;
        arquivo_csv >> lixo >> lixo;
        
        getline(arquivo_csv, satelites[i].funcao, '"');
    }
    
    infoSatelite elemento = {};

    void InserirElemento(infoSatelite elemento, infoSatelite* satelites, int tamVetor);

    delete [] satelites;

    return 0;
}

void RedimensionaVetor(infoSatelite *&vetor, int &tamanhoVetor) {
    const int TAM_REDIMENSIONAMENTO = 10;
    const int TAM_INICIAL = tamanhoVetor;

    infoSatelite *aux = new infoSatelite[TAM_INICIAL];
    for (int i = 0; i < TAM_INICIAL; i++) {
        aux[i] = vetor[i];
    }
    delete[] vetor;

    tamanhoVetor += TAM_REDIMENSIONAMENTO;
    vetor = new infoSatelite[tamanhoVetor];
    for (int i = 0; i < TAM_INICIAL; i++) {
        vetor[i] = aux[i];
    }
    delete[] aux;

    return;
}

void InserirElemento(infoSatelite elemento, infoSatelite* satelites, int tamVetor) {
    
    return; 
}
