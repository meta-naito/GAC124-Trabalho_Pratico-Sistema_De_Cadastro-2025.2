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

struct infoSatelite {
    unsigned int identificador;
    std::string nome;
    std::string paisOrigem;
    int anoLancamento;
    std::string funcao;
};

// >===== INICIALIZAÇÃO DE FUNÇÕES =====<

// (OBS: Funções que se referem ao vetor de satélites, quando não especificado, devem
//  assumir que o vetor de satelites não está mudando.)

// Carregar informações sobre os satélites de um arquivo CSV.
infoSatelite* CarregarCSV(const std::string NOME_ARQUIVO, unsigned int &qSatelites, unsigned int &tamanhoVetor);

// Redimensiona o vetor, alterando o valor do tamanho do vetor para o novo tamanho.
void RedimensionaVetor(infoSatelite *&vetor, unsigned int &tamanhoVetor);

// Reduz o vetor, elimina elementos com indice mais alto.
void ReduzirVetor(unsigned int qReducao, infoSatelite *&satelites, unsigned int &tamanhoVetor);

// >===== IMPRESSÃO DE ELEMENTOS DO BANCO DE DADOS =====<

// Imprime um alcance de elementos no terminal.
// Nota: Não informa se um elemento não existe.
void Imprimir(const unsigned int idInicio, const unsigned int idFinal,
              infoSatelite *&satelites, const unsigned int qSatelites);

// Imprime um elemento no terminal.
// Nota: Não informa se um elemento não existe.
void ImprimirElemento(const unsigned int identificador, infoSatelite *&satelites,
                      const unsigned int qSatelites);

// >===== ORDENAÇÃO DE ELEMENTOS NO BANCO DE DADOS =====<

// Intercalacao por identificador.
void IntercalaElementosId(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor);
// Merge Sort por identificador.
void MergeSortId(infoSatelite *&vetor, int inicioVetor, int finalVetor);
// Ordena satélites por identificador.
void OrdernarId(infoSatelite *&satelites, const unsigned int qSatelites);

// Intercalacao por nome do satélite.
void IntercalaElementosNome(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor);
// Merge Sort por nome do satélite.
void MergeSortNome(infoSatelite *&vetor, int inicioVetor, int finalVetor);
// Ordena satélites por nome do satélite.
void OrdernarNome(infoSatelite *&satelites, const unsigned int qSatelites);

// Intercalacao por pais de origem.
void IntercalaElementosPais(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor);
// Merge Sort por pais de origem.
void MergeSortPais(infoSatelite *&vetor, int inicioVetor, int finalVetor);
// Ordena satélites por país de origem.
void OrdernarPais(infoSatelite *&satelites, const unsigned int qSatelites);

// Intercalacao por ano de lançamento.
void IntercalaElementosAno(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor);
// Merge Sort por ano de lançamento
void MergeSortAno(infoSatelite *&vetor, int inicioVetor, int finalVetor);
// Ordena satélites por ano de lançamento.
void OrdenarAno(infoSatelite *&satelites, const unsigned int qSatelites);

// Intercalacao por função do satélite.
void IntercalaElementosFuncao(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor);
// Merge Sort por função do satélite.
void MergeSortFuncao(infoSatelite *&vetor, int inicioVetor, int finalVetor);
// Ordena satélites por função.
void OrdenarFuncao(infoSatelite *&satelites, const unsigned int qSatelites);

// >===== BUSCA DE ELEMENTOS NO BANCO DE DADOS =====<

// Verifica se um elemento com o dado identificador existe no vetor de satélites, utilizando busca binária.
bool ExisteId(const unsigned int identificador, infoSatelite *&satelites,
              const unsigned int qSatelites);

// Retorna qual é o maior Id presente no CSV.
unsigned int MaiorId(infoSatelite *&satelites, unsigned int qSatelites);

// Busca a posição no vetor de satélites no banco de dados, pelo identificador.
// Nota: Assume que o vetor está ordenado e que o elemento existe.
// Essa função NÃO checa se o elemento existe.
unsigned int PosicaoId(const unsigned int ID_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites);

// Busca, no banco de dados, o nome de um determinado satélite, retornando o Id do elemento correspondente.
// Nota: Assume que o vetor está ordenado pelo identificador.
void BuscarNome(const std::string NOME_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites);

// Busca, no banco de dados, o país de origem de um determinado satélite, retornando o Id do elemento correspondente.
// Nota: Assume que o vetor está ordenado pelo identificador.
void BuscarPais(const std::string PAIS_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites);

// Busca, no banco de dados, o ano de lançamento de um determinado satélite, retornando o Id do elemento correspondente.
// Nota: Assume que o vetor está ordenado pelo identificador.
void BuscarAno(const int ANO_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites);

// Busca, no banco de dados, a função de um determinado satélite, retornando o Id do elemento correspondente.
// Nota: Assume que o vetor está ordenado pelo identificador.
void BuscarFuncao(std::string FUNCAO_PROCURADA, infoSatelite *&satelites, const unsigned int qSatelites);

// >===== ALTERAÇÃO DE DADOS DOS ELEMENTOS NO BANCO DE DADOS =====<

// Soobrescreve um elemento com um novo elemento. Preserva Id do elemento antigo.
void SobrescreverElemento(const unsigned int identificador, infoSatelite novoElemento,
                          infoSatelite *&satelites, const unsigned int qSatelites);

// Recebe um elemento e o insere no vetor de satélites.
// Nota: Assume que o elemento existe, e que o vetor está ordenado.
void InserirElemento(infoSatelite novoElemento, infoSatelite *&satelites,
                     unsigned int &qSatelites, unsigned int &tamanhoVetor);

// Remove um elemento do vetor de satélites
// Nota: Assume que o elemento existe, e que o vetor está ordenado.
void RemoverElemento(unsigned int identificador, infoSatelite *&satelites,
                     unsigned int &qSatelites);

// Grava alterações em memória para um arquivo.
void GravarAlterações(const std::string NOME_ARQUIVO, infoSatelite *&satelites,
                      const unsigned int qSatelites);

// Deleta o vetor de satelites nao salvando as alterações
void DeletarSalvo(infoSatelite *&satelites);

infoSatelite* CarregarCSV(const std::string NOME_ARQUIVO, unsigned int &qSatelites, unsigned int &tamanhoVetor) {

    // Abre o arquivo .csv.
    std::ifstream arquivoCSV(NOME_ARQUIVO);
    if (arquivoCSV.fail()) {
        std::cout << "Erro: não foi possível localizar o arquivo \"" << NOME_ARQUIVO << "\" :(" << std::endl;
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

    // Ordenar os satélites por identificador
    // OrdernarId(satelites, qSatelites);

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

void ReduzirVetor(unsigned int qReducao, infoSatelite *&satelites, unsigned int &tamanhoVetor) {
    const int NOVO_TAMANHO = tamanhoVetor - qReducao;

    infoSatelite *aux = new infoSatelite[NOVO_TAMANHO];
    for (int i = 0; i < NOVO_TAMANHO; i++) {
        aux[i] = satelites[i];
    }
    delete[] satelites;

    tamanhoVetor -= qReducao;
    satelites = new infoSatelite[NOVO_TAMANHO];
    for (int i = 0; i < NOVO_TAMANHO; i++) {
        satelites[i] = aux[i];
    }
    delete[] aux;

    return;
}

void Imprimir(const unsigned int idInicio, const unsigned int idFinal, infoSatelite *&satelites, const unsigned int qSatelites) {
    for (unsigned int i = 0; i < qSatelites; i++) {
        if (satelites[i].identificador >= idInicio and satelites[i].identificador <= idFinal) {
            std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << '\n'
                      << "| Satélite de ID     | " << satelites[i].identificador << '\n'
                      << "| Nome               | " << satelites[i].nome << '\n'
                      << "| País de origem     | " << satelites[i].paisOrigem << '\n'
                      << "| Ano de Lançamento  | " << satelites[i].anoLancamento << '\n'
                      << "| Função:\n\"" << satelites[i].funcao << '\"' << std::endl; 
        }
    }
    std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;

    return;
}

// Alias de Imprimir().
void ImprimirElemento(const unsigned int identificador, infoSatelite *&satelites, const unsigned int qSatelites) {
    Imprimir(identificador, identificador, satelites, qSatelites);
    
    return;
}

void IntercalaElementosId(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor) {
    int posInicio = inicioVetor, posMeio = meioVetor + 1;
    int tamVetor = finalVetor - inicioVetor + 1;

    infoSatelite *vetTemporario = new infoSatelite[tamVetor];
    
    //Intercalação dos vetores
    for (int i = 0; i < tamVetor; i++) {
        if (posInicio <= meioVetor and posMeio <= finalVetor) {
            if (vetor[posInicio].identificador < vetor[posMeio].identificador) {
                vetTemporario[i] = vetor[posInicio];
                posInicio++;
            }
            else {
                vetTemporario[i] = vetor[posMeio];
                posMeio++;
            }
        }
        else if (posInicio > meioVetor) {
            vetTemporario[i] = vetor[posMeio];
            posMeio++;
        }
        else {
            vetTemporario[i] = vetor[posInicio];
            posInicio++;
        }
    }

    for (int i = 0; i < tamVetor; i++) {
        vetor[inicioVetor + i] = vetTemporario[i];
    }

    delete [] vetTemporario;

    return;
}

void MergeSortId(infoSatelite *&vetor, int inicioVetor, int finalVetor) {
    int meioVetor;

    if (inicioVetor < finalVetor) {
        meioVetor = (inicioVetor + finalVetor) / 2;
        MergeSortId(vetor, inicioVetor, meioVetor);
        MergeSortId(vetor, meioVetor + 1, finalVetor);
        IntercalaElementosId(vetor, inicioVetor, meioVetor, finalVetor);
    }

    return;
}

void OrdernarId(infoSatelite *&satelites, const unsigned int qSatelites) {
    MergeSortId(satelites, 0, qSatelites - 1);

    return;
}

void IntercalaElementosNome(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor) {
    int posInicio = inicioVetor, posMeio = meioVetor + 1;
    int tamVetor = finalVetor - inicioVetor + 1;

    infoSatelite *vetTemporario = new infoSatelite[tamVetor];
    
    //Intercalação dos vetores
    for (int i = 0; i < tamVetor; i++) {
        if (posInicio <= meioVetor and posMeio <= finalVetor) {
            if (vetor[posInicio].nome < vetor[posMeio].nome) {
                vetTemporario[i] = vetor[posInicio];
                posInicio++;
            }
            else {
                vetTemporario[i] = vetor[posMeio];
                posMeio++;
            }
        }
        else if (posInicio > meioVetor) {
            vetTemporario[i] = vetor[posMeio];
            posMeio++;
        }
        else {
            vetTemporario[i] = vetor[posInicio];
            posInicio++;
        }
    }

    for (int i = 0; i < tamVetor; i++) {
        vetor[inicioVetor + i] = vetTemporario[i];
    }

    delete [] vetTemporario;
    
    return;
}

void MergeSortNome(infoSatelite *&vetor, int inicioVetor, int finalVetor) {
    int meioVetor;

    if (inicioVetor < finalVetor) {
        meioVetor = (inicioVetor + finalVetor) / 2;
        MergeSortNome(vetor, inicioVetor, meioVetor);
        MergeSortNome(vetor, meioVetor + 1, finalVetor);
        IntercalaElementosNome(vetor, inicioVetor, meioVetor, finalVetor);
    }

    return;
}

void OrdernarNome(infoSatelite *&satelites, const unsigned int qSatelites) {
    MergeSortNome(satelites, 0, qSatelites - 1);

    return;
}

void IntercalaElementosPais(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor) {
    int posInicio = inicioVetor, posMeio = meioVetor + 1;
    int tamVetor = finalVetor - inicioVetor + 1;

    infoSatelite *vetTemporario = new infoSatelite[tamVetor];
    
    //Intercalação dos vetores
    for (int i = 0; i < tamVetor; i++) {
        if (posInicio <= meioVetor and posMeio <= finalVetor) {
            if (vetor[posInicio].paisOrigem < vetor[posMeio].paisOrigem) {
                vetTemporario[i] = vetor[posInicio];
                posInicio++;
            }
            else {
                vetTemporario[i] = vetor[posMeio];
                posMeio++;
            }
        }
        else if (posInicio > meioVetor) {
            vetTemporario[i] = vetor[posMeio];
            posMeio++;
        }
        else {
            vetTemporario[i] = vetor[posInicio];
            posInicio++;
        }
    }

    for (int i = 0; i < tamVetor; i++) {
        vetor[inicioVetor + i] = vetTemporario[i];
    }

    delete [] vetTemporario;
    
    return;
}

void MergeSortPais(infoSatelite *&vetor, int inicioVetor, int finalVetor) {
    int meioVetor;

    if (inicioVetor < finalVetor) {
        meioVetor = (inicioVetor + finalVetor) / 2;
        MergeSortPais(vetor, inicioVetor, meioVetor);
        MergeSortPais(vetor, meioVetor + 1, finalVetor);
        IntercalaElementosPais(vetor, inicioVetor, meioVetor, finalVetor);
    }

    return;
}

void OrdernarPais(infoSatelite *&satelites, const unsigned int qSatelites) {
    MergeSortPais(satelites, 0, qSatelites - 1);

    return;
}

void IntercalaElementosAno(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor) {
    int posInicio = inicioVetor, posMeio = meioVetor + 1;
    int tamVetor = finalVetor - inicioVetor + 1;

    infoSatelite *vetTemporario = new infoSatelite[tamVetor];
    
    //Intercalação dos vetores
    for (int i = 0; i < tamVetor; i++) {
        if (posInicio <= meioVetor and posMeio <= finalVetor) {
            if (vetor[posInicio].anoLancamento < vetor[posMeio].anoLancamento) {
                vetTemporario[i] = vetor[posInicio];
                posInicio++;
            }
            else {
                vetTemporario[i] = vetor[posMeio];
                posMeio++;
            }
        }
        else if (posInicio > meioVetor) {
            vetTemporario[i] = vetor[posMeio];
            posMeio++;
        }
        else {
            vetTemporario[i] = vetor[posInicio];
            posInicio++;
        }
    }

    for (int i = 0; i < tamVetor; i++) {
        vetor[inicioVetor + i] = vetTemporario[i];
    }

    delete [] vetTemporario;
    
    return;
}

void MergeSortAno(infoSatelite *&vetor, int inicioVetor, int finalVetor) {
    int meioVetor;

    if (inicioVetor < finalVetor) {
        meioVetor = (inicioVetor + finalVetor) / 2;
        MergeSortAno(vetor, inicioVetor, meioVetor);
        MergeSortAno(vetor, meioVetor + 1, finalVetor);
        IntercalaElementosAno(vetor, inicioVetor, meioVetor, finalVetor);
    }

    return;
}

void OrdenarAno(infoSatelite *&satelites, const unsigned int qSatelites) {
    MergeSortAno(satelites, 0, qSatelites - 1);

    return;
}

void IntercalaElementosFuncao(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor) {
    int posInicio = inicioVetor, posMeio = meioVetor + 1;
    int tamVetor = finalVetor - inicioVetor + 1;

    infoSatelite *vetTemporario = new infoSatelite[tamVetor];
    
    //Intercalação dos vetores
    for (int i = 0; i < tamVetor; i++) {
        if (posInicio <= meioVetor and posMeio <= finalVetor) {
            if (vetor[posInicio].funcao < vetor[posMeio].funcao) {
                vetTemporario[i] = vetor[posInicio];
                posInicio++;
            }
            else {
                vetTemporario[i] = vetor[posMeio];
                posMeio++;
            }
        }
        else if (posInicio > meioVetor) {
            vetTemporario[i] = vetor[posMeio];
            posMeio++;
        }
        else {
            vetTemporario[i] = vetor[posInicio];
            posInicio++;
        }
    }

    for (int i = 0; i < tamVetor; i++) {
        vetor[inicioVetor + i] = vetTemporario[i];
    }

    delete [] vetTemporario;
    
    return;
}

void MergeSortFuncao(infoSatelite *&vetor, int inicioVetor, int finalVetor) {
    int meioVetor;

    if (inicioVetor < finalVetor) {
        meioVetor = (inicioVetor + finalVetor) / 2;
        MergeSortFuncao(vetor, inicioVetor, meioVetor);
        MergeSortFuncao(vetor, meioVetor + 1, finalVetor);
        IntercalaElementosFuncao(vetor, inicioVetor, meioVetor, finalVetor);
    }

    return;
}

void OrdenarFuncao(infoSatelite *&satelites, const unsigned int qSatelites) {
    MergeSortFuncao(satelites, 0, qSatelites - 1);

    return;
}

bool ExisteId(const unsigned int identificador, infoSatelite *&satelites, const unsigned int qSatelites) {
    unsigned int esq_limite = 0;
    unsigned int dir_limite = qSatelites;
    
    // Busca binária pelo Identificador.
    while (esq_limite <= dir_limite) {
        unsigned int meio = (esq_limite + dir_limite) / 2;

        if (satelites[meio].identificador == identificador) {
            return true;
        }
        else if (satelites[meio].identificador < identificador) {
            esq_limite = meio + 1;
        }
        else {
            dir_limite = meio - 1;
        }
    }

    return false;
}

unsigned int MaiorId(infoSatelite *&satelites, unsigned int qSatelites) {
    if (qSatelites == 0) {
        return 0;
    }

    unsigned int maiorId = satelites[0].identificador;
    
    for (unsigned int i = 0; i < qSatelites; i++) {
        if (satelites[i].identificador > maiorId) {
            maiorId = satelites[i].identificador;
        }
    }

    return maiorId;
}

unsigned int PosicaoId(const unsigned int ID_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites) {
    unsigned int posInicial = 0;
    unsigned int posFinal = qSatelites;

    while (posInicial <= posFinal) {
        unsigned int meio = (posInicial + posFinal) / 2;

        if (satelites[meio].identificador == ID_PROCURADO) {
            return meio;
        }

        else {
            if (ID_PROCURADO > satelites[meio].identificador) {
                posInicial = meio + 1;
            }
            else {
                posFinal = meio - 1;
            }
        }
    }

    // Assume que o elemento existe por isso retorna 0 caso não ache ele.
    return 0;
}

void BuscarNome(const std::string NOME_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites) {
    unsigned int posInicial = 0;
    unsigned int posFinal = qSatelites - 1;

    while (posInicial <= posFinal) {
        unsigned int meio = (posInicial + posFinal) / 2;

        if (satelites[meio].nome == NOME_PROCURADO) {
            unsigned int comecoImpri = meio;
            unsigned int finalImpri = meio;

            while (comecoImpri > 0 and satelites[comecoImpri - 1].nome == NOME_PROCURADO) {
                comecoImpri--;
            }

            while (finalImpri + 1 < qSatelites and satelites[finalImpri + 1].nome == NOME_PROCURADO) {
                finalImpri++;
            }

            for (unsigned int i = comecoImpri; i <= finalImpri; i++) {
                ImprimirElemento(satelites[i].identificador, satelites, qSatelites);
            }
            return;
        }

        else {
            if (NOME_PROCURADO > satelites[meio].nome) {
                posInicial = meio + 1;
            }
            else {
                if (meio == 0) {
                    return;
                }
                posFinal = meio - 1;
            }
        }
    }

    return;
}

void BuscarPais(const std::string PAIS_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites) {
    std::cout << PAIS_PROCURADO << std::endl;

    unsigned int posInicial = 0;
    unsigned int posFinal = qSatelites - 1;

    while (posInicial <= posFinal) {
        unsigned int meio = (posInicial + posFinal) / 2;

        if (satelites[meio].paisOrigem == PAIS_PROCURADO) {

            unsigned int comecoImpri = meio;
            unsigned int finalImpri = meio;

            while (comecoImpri > 0 and satelites[comecoImpri - 1].paisOrigem == PAIS_PROCURADO) {
                comecoImpri--;
            }

            while (finalImpri + 1 < qSatelites and satelites[finalImpri + 1].paisOrigem == PAIS_PROCURADO) {
                finalImpri++;
            }

            for (unsigned int i = comecoImpri; i <= finalImpri; i++) {;
                ImprimirElemento(satelites[i].identificador, satelites, qSatelites);
            }
            return;
        }

        else {
            if (PAIS_PROCURADO > satelites[meio].paisOrigem) {
                posInicial = meio + 1;
            }
            else {
                if (meio == 0) {
                    return;
                }
                posFinal = meio - 1;
            }
        }
    }

    return;
}

void BuscarAno(const int ANO_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites) {
    unsigned int posInicial = 0;
    unsigned int posFinal = qSatelites - 1;

    while (posInicial <= posFinal) {
        unsigned int meio = (posInicial + posFinal) / 2;

        if (satelites[meio].anoLancamento == ANO_PROCURADO) {
            unsigned int comecoImpri = meio;
            unsigned int finalImpri = meio;

            while (comecoImpri > 0 and satelites[comecoImpri - 1].anoLancamento == ANO_PROCURADO) {
                comecoImpri--;
            }

            while (finalImpri + 1 < qSatelites and satelites[finalImpri + 1].anoLancamento == ANO_PROCURADO) {
                finalImpri++;
            }

            for (unsigned int i = comecoImpri; i <= finalImpri; i++) {
                ImprimirElemento(satelites[i].identificador, satelites, qSatelites);
            }
            return;
        }

        else {
            if (ANO_PROCURADO > satelites[meio].anoLancamento) {
                posInicial = meio + 1;
            }
            else {
                if (meio == 0) {
                    return;
                }
                posFinal = meio - 1;
            }
        }
    }

    return;
}

void BuscarFuncao(std::string FUNCAO_PROCURADA, infoSatelite *&satelites, const unsigned int qSatelites) {
    unsigned int posInicial = 0;
    unsigned int posFinal = qSatelites - 1;

    while (posInicial <= posFinal) {
        unsigned int meio = (posInicial + posFinal) / 2;

    if (satelites[meio].funcao == FUNCAO_PROCURADA) {
            unsigned int comecoImpri = meio;
            unsigned int finalImpri = meio;

            while (comecoImpri > 0 and satelites[comecoImpri - 1].funcao == FUNCAO_PROCURADA) {
                comecoImpri--;
            }

            while (finalImpri + 1 < qSatelites and satelites[finalImpri + 1].funcao == FUNCAO_PROCURADA) {
                finalImpri++;
            }

            for (unsigned int i = comecoImpri; i <= finalImpri; i++) {
                ImprimirElemento(satelites[i].identificador, satelites, qSatelites);
            }
            return;
        }

        else {
            if (FUNCAO_PROCURADA > satelites[meio].funcao) {
                posInicial = meio + 1;
            }
            else {
                if (meio == 0) {
                    return;
                }
                posFinal = meio - 1;
            }
        }
    }

    return;
}

void SobrescreverElemento(const unsigned int identificador, infoSatelite novoElemento, infoSatelite *&satelites, const unsigned int qSatelites) {
    novoElemento.identificador = identificador;
    satelites[identificador] = novoElemento;

    return;
}

void InserirElemento(infoSatelite novoElemento, infoSatelite *&satelites, unsigned int &qSatelites, unsigned int &tamanhoVetor) {
    unsigned int novaQuantidade = qSatelites + 1;
    unsigned int novoId = MaiorId(satelites, qSatelites) + 1;

    // Checa se é necessario redimensionar o vetor.
    if (novaQuantidade > tamanhoVetor) {
        RedimensionaVetor(satelites, tamanhoVetor);
    }

    novoElemento.identificador = novoId;
    satelites[qSatelites] = novoElemento;
    qSatelites++;

    return;
}

void RemoverElemento(unsigned int identificador, infoSatelite *&satelites, unsigned int &qSatelites) {
    for (unsigned int i = 0; i < qSatelites; i++) {
        if (identificador == satelites[i].identificador) {
            qSatelites--;

            // Move todos os elementos a direita do elemento a ser removido para a esquerda.
            for (unsigned int j = i; j < qSatelites; j++) {
                satelites[j] = satelites[j + 1];
            }
        }
    }

    return;
}

void GravarAlterações(const std::string NOME_ARQUIVO, infoSatelite *&satelites, const unsigned int qSatelites) {
    // Abre arquivo atual para ler o cometário.
    std::ifstream antigoCSV(NOME_ARQUIVO);
    if (antigoCSV.fail()) {
        std::cout << "Erro: não foi possível localizar o arquivo \"" << NOME_ARQUIVO << "\" :(" << std::endl;
    }

    std::string comentario;
    getline(antigoCSV, comentario, '\n');

    antigoCSV.close();

    // Grava Alterações em arquivo de mesmo nome;
    std::ofstream arquivoCSV(NOME_ARQUIVO);
    if (arquivoCSV.fail()) {
        std::cout << "Erro: não foi possível criar o arquivo \"" << NOME_ARQUIVO << "\" :(" << std::endl;
    }

    arquivoCSV << comentario << '\n';
    arquivoCSV << qSatelites << '\n';
    for (unsigned int i = 0; i < qSatelites; i++) {
        if (satelites[i].identificador != 0) {
            arquivoCSV << satelites[i].identificador << ", "
                    << '\"' << satelites[i].nome << '\"' << ", "
                    << '\"' << satelites[i].paisOrigem << '\"' << ", "
                    << satelites[i].anoLancamento << ", "
                    << '\"' << satelites[i].funcao << '\"' << '\n'; 
        }
    }
    
    arquivoCSV.close();

    return;
}

void DeletarSalvo(infoSatelite *&satelites) {
    delete [] satelites;

    return;
}
