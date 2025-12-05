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
#include <map>
#include <fstream>
#include <string>

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

// >===== INICIALIZAÇÃO DE FUNÇÕES =====<

// (OBS: Funções que se referem ao vetor de satélites, quando não especificado, devem
//  assumir que o vetor de satélites não está mudando.)

// Carregar informações sobre os satélites de um arquivo CSV.
infoSatelite* CarregarCSV(const std::string NOME_ARQUIVO, unsigned int &tamanhoVetor, unsigned int &qSatelites);

// Redimensiona o vetor, alterando o valor do tamanho do vetor para o novo tamanho.
void RedimensionaVetor(infoSatelite *&vetor, unsigned int &tamanhoVetor);

// >===== IMPRESSÃO DE ELEMENTOS DO BANCO DE DADOS =====<

// Imprime um alcance de elementos no terminal.
// Nota: Não informa se um elemento não existe.
void Imprimir(const unsigned int idInicio, const unsigned int idFinal, infoSatelite *&satelites, const unsigned int qSatelites);

// Imprime um elemento no terminal.
// Nota: Não informa se um elemento não existe.
void ImprimirElemento(const unsigned int identificador, infoSatelite *&satelites, const unsigned int qSatelites);

// >===== ORDENAÇÃO DE ELEMENTOS NO BANCO DE DADOS =====<

// Função template para implementação do Merge Sort.
// Pode ser utilizada para unsigned int, int, e string.
template <typename tipoDado> void MergeSort(tipoDado *vetor, int inicioVetor, int finalVetor);

// Função template para intercalação de elementos necessário para Merge Sort.
template <typename tipoDado> void IntercalaElementos(tipoDado *vetor, int inicioVetor, int meioVetor, int finalVetor);

// Ordena satélites por Id.
void OrdernarId(infoSatelite *&satelites, const unsigned int qSatelites);

// Ordena satélites por nome.
void OrdernarNome(infoSatelite *&satelites, const unsigned int qSatelites);

// Ordena satélites por país de origem.
void OrdernarPais(infoSatelite *&satelites, const unsigned int qSatelites);

// Ordena satélites por ano de lançamento.
void OrdenarAno(infoSatelite *&satelites, const unsigned int qSalelites);

// Ordena satélites por função.
void OrdenarFuncao(infoSatelite *&satelites, const unsigned int qSatelites);

// >===== BUSCA DE ELEMENTOS NO BANCO DE DADOS =====<

// Verifica se um elemento com o dado identificador existe no vetor de satélites, utilizando busca binária.
bool ExisteId(const unsigned int identificador, infoSatelite *&satelites, const unsigned int qSatelites);

// Busca, no vetor de satélites, o nome de um determinado satélite, imprimindo o elemento correspondente.
void BuscarNome(const std::string nomeProcurado, infoSatelite *satelites, const unsigned int qSatelites);

// Busca, no vetor de satélites, o país de origem de um determinado satélite, imprimindo o elemento correspondente.
void BuscarPais(const std::string paisProcurado, infoSatelite *satelites, const unsigned int qSatelites);

// Busca, no vetor de satélites, o ano de lançamento de um determinado satélite, imprimindo o elemento correspondente.
void BuscarAno(const int ANO_PROCURADO, infoSatelite *satelites, const unsigned int qSatelites);

// Busca, no vetor de satélites, a função de um determinado satélite, imprimindo o elemento correspondente.
void BuscarFuncao(const std::string funcaoProcurada, infoSatelite *satelites, const unsigned int qSatelites);

// Busca, no vetor de satélites, satélites correspondentes a um trecho digitado pelo usuário e os imprime.
void BuscarParte(const std::string trecho, infoSatelite *satelites, const unsigned int qSatelites);

// Converte um dado texto para letras maiúsculas, auxiliando na busca.
std::string ConverterMaiusculo(std::string texto);

// Converte um dado texto para uma versão sem acentuação, auxiliando na busca.
std::string RemoverAcentuacao(std::string texto);

// >===== ALTERAÇÃO DE DADOS DOS ELEMENTOS NO BANCO DE DADOS =====<

// Soobrescreve um elemento com um novo elemento. Preserva o Id do elemento antigo.
void SobrescreverElemento(const unsigned int identificador, infoSatelite novoElemento,infoSatelite *&satelites, const unsigned int qSatelites);

// Recebe um elemento e o insere no vetor de satélites.
// Nota: Assume que o elemento existe, e que o vetor está ordenado.
void InserirElemento(infoSatelite novoElemento, infoSatelite *&satelites, unsigned int &qSatelites, unsigned int &tamanhoVetor);

// Remove um elemento do vetor de satélites
// Nota: Assume que o elemento existe, e que o vetor está ordenado.
void RemoverElemento(unsigned int identificador, infoSatelite *&satelites, unsigned int &qSatelites);

// Grava alterações em memória para um arquivo.
void GravarAlterações(const std::string NOME_ARQUIVO, infoSatelite *&satelites, const unsigned int qSatelites);

// === ---- ===

int main(){
    const std::string NOME_CSV = "db_satelites.csv";
    const unsigned int TAM_INICIAL = 40;
    unsigned int tamVetor = TAM_INICIAL;
    unsigned int qSatelites = 0;

    infoSatelite* satelites = CarregarCSV(NOME_CSV, tamVetor, qSatelites);

    // teste de busca por nome !!
    std::string nomeProcura;
    int anoProcura;

    // OrdernarPais(satelites, qSatelites);
    // GravarAlterações(NOME_CSV, satelites, qSatelites);
    // std::cin >> anoProcura;
    // OrdernarId(satelites, qSatelites);
    // GravarAlterações(NOME_CSV, satelites, qSatelites);

    std::cout << "Digite um nome de satélite a ser buscado: \n";
    getline(std::cin, nomeProcura);
    //std::cin >> anoProcura;


    BuscarPais(nomeProcura, satelites, qSatelites);
    //std::cout << "\ntudo certo!\n";

    return 0;
}

infoSatelite* CarregarCSV(const std::string NOME_ARQUIVO, unsigned int &tamanhoVetor, unsigned int &qSatelites) {

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

void Imprimir(const unsigned int idInicio, const unsigned int idFinal, infoSatelite *&satelites, const unsigned int qSatelites) {
    for (unsigned int i = 0; i < qSatelites; i++) {
        if (satelites[i].getId() >= idInicio and satelites[i].getId() <= idFinal) {
            std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << '\n'
                      << "| Satélite de ID     | " << satelites[i].getId() << '\n'
                      << "| Nome               | " << satelites[i].getNome() << '\n'
                      << "| País de origem     | " << satelites[i].getPais() << '\n'
                      << "| Ano de Lançamento  | " << satelites[i].getAno() << '\n'
                      << "| Função:\n   \"" << satelites[i].getFuncao() << '\"' << std::endl; 
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

template <typename tipoDado> void MergeSort(tipoDado *vetor, int inicioVetor, int finalVetor) {
    int meioVetor;

    if (inicioVetor < finalVetor) {
        meioVetor = (inicioVetor + finalVetor) / 2;
        MergeSort(vetor, inicioVetor, meioVetor);
        MergeSort(vetor, meioVetor + 1, finalVetor);
        IntercalaElementos(vetor, inicioVetor, meioVetor, finalVetor);
    }

    return;
}

template <typename tipoDado> void IntercalaElementos(tipoDado *vetor, int inicioVetor, int meioVetor, int finalVetor) {
    // posMeio é um nome ruim pra isso, pensa num melhor!!!
    int posInicio = inicioVetor, posMeio = meioVetor + 1;
    int tamVetor = finalVetor - inicioVetor + 1;

    tipoDado *vetTemporario = new tipoDado[tamVetor];
    
    //Intercalação dos vetores
    for (int i = 0; i < tamVetor; i++) {
        if (posInicio <= meioVetor and posMeio <= finalVetor) {
            if (vetor[posInicio] < vetor[posMeio]) {
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

void OrdernarId(infoSatelite *&satelites, const unsigned int qSatelites) {
    // Criação de um vetor temporário para ordenar os elementos da função chamada.
    // OBS: Para todos as funções de ordenação a lógica de criar um vetor temporário é a mesma.
    //      Portanto, as outras funções não irão ter comentários auxliares.
    unsigned int *temp = new unsigned int[qSatelites];

    for (unsigned int i = 0; i < qSatelites; i++) {
        temp[i] = satelites[i].getId();
    }

    MergeSort<unsigned int>(temp, 0, qSatelites - 1);
    
    // Cria um registro auxiliar para poder ordenar o vetor de satélites em si.
    // OBS: Para todas as funções de ordenação a lógica de criar um registro auxiliar é a mesma.
    //      Portanto, as outras funções não irão ter comentários auxliares.
    infoSatelite aux;

    for (unsigned int i = 0; i < qSatelites; i++) {
        for (unsigned int j = 0; j < qSatelites; j++) {
            if (temp[i] == satelites[j].getId()) {
                aux = satelites[i];
                satelites[i] = satelites[j];
                satelites[j] = aux;
            }
        }
    }
    delete [] temp;

    return;
}

void OrdernarNome(infoSatelite *&satelites, const unsigned int qSatelites) {
    std::string *temp = new std::string[qSatelites];

    for (unsigned int i = 0; i < qSatelites; i++) {
        temp[i] = satelites[i].getNome();
    }

    MergeSort<std::string>(temp, 0, qSatelites - 1);

    infoSatelite aux;

    for (unsigned int i = 0; i < qSatelites; i++) {
        for (unsigned int j = 0; j < qSatelites; j++) {
            if (temp[i] == satelites[j].getNome()) {
                aux = satelites[i];
                satelites[i] = satelites[j];
                satelites[j] = aux;
            }
        }
    }
    delete [] temp;

    return;
}

void OrdernarPais(infoSatelite *&satelites, const unsigned int qSatelites) {
    std::string *temp = new std::string[qSatelites];

    for (unsigned int i = 0; i < qSatelites; i++) {
        temp[i] = satelites[i].getPais();
    }

    MergeSort<std::string>(temp, 0, qSatelites - 1);

    infoSatelite aux;

    for (unsigned int i = 0; i < qSatelites; i++) {
        for (unsigned int j = 0; j < qSatelites; j++) {
            if (temp[i] == satelites[j].getPais()) {
                aux = satelites[i];
                satelites[i] = satelites[j];
                satelites[j] = aux;
            }
        }
    }
    delete [] temp;

    return;
}

void OrdenarAno(infoSatelite *&satelites, const unsigned int qSatelites) {
    int *temp = new int[qSatelites];

    for (unsigned int i = 0; i < qSatelites; i++) {
        temp[i] = satelites[i].getAno();
    }

    MergeSort<int>(temp, 0, qSatelites - 1);

    infoSatelite aux;

    for (unsigned int i = 0; i < qSatelites; i++) {
        for (unsigned int j = 0; j < qSatelites; j++) {
            if (temp[i] == satelites[j].getAno()) {
                aux = satelites[i];
                satelites[i] = satelites[j];
                satelites[j] = aux;
            }
        }
    }
    delete [] temp;
    
    return;
}

void OrdenarFuncao(infoSatelite *&satelites, const unsigned int qSatelites) {
    std::string *temp = new std::string[qSatelites];

    for (unsigned int i = 0; i < qSatelites; i++) {
        temp[i] = satelites[i].getFuncao();
    }

    MergeSort<std::string>(temp, 0, qSatelites - 1);

    infoSatelite aux;

    for (unsigned int i = 0; i < qSatelites; i++) {
        for (unsigned int j = 0; j < qSatelites; j++) {
            if (temp[i] == satelites[j].getFuncao()) {
                aux = satelites[i];
                satelites[i] = satelites[j];
                satelites[j] = aux;
            }
        }
    }
    delete [] temp;

    return;
}

bool ExisteId(const unsigned int identificador, infoSatelite *&satelites, const unsigned int qSatelites) {
    unsigned int esq_limite = 0;
    unsigned int dir_limite = qSatelites;
    
    // Busca binária pelo Identificador.
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

void BuscarNome(std::string nomeProcurado, infoSatelite *satelites, const unsigned int qSatelites) {
    nomeProcurado = ConverterMaiusculo(nomeProcurado);
    
    // Criacão de um vetor temporário para poder ordená-lo sem perder a ordenação original do vetor de satélites.
    infoSatelite *vetOrdenado = new infoSatelite[qSatelites];

    for (unsigned int i = 0; i < qSatelites; i++) {
        vetOrdenado[i] = satelites[i];
    }
    OrdernarNome(vetOrdenado, qSatelites);

    unsigned int posInicial = 0, posFinal = qSatelites;
    bool achou = false;

    // Busca pelo nome correspondente.
    while (posInicial < posFinal) {
        unsigned int meio = (posInicial + posFinal) / 2;
        std::string auxMaiuscula = ConverterMaiusculo(vetOrdenado[meio].getNome());

        if (auxMaiuscula == nomeProcurado) {
            ImprimirElemento(vetOrdenado[meio].getId(), satelites, qSatelites);
            achou = true;

            // Aumenta posInicial para sair do while.
            posInicial = posFinal + 1;
        }

        else {
            if (nomeProcurado > auxMaiuscula) {
                posInicial = meio + 1;
            }
            else {
                posFinal = meio - 1;
            }
        }
    }

    if (!achou) {
        std::cout << "Não foi possível encontrar um satélite que contém esse ano de lançamento.\n";
    }

    delete [] vetOrdenado;

    return;
}

void BuscarPais(std::string paisProcurado, infoSatelite *satelites, const unsigned int qSatelites) {
    paisProcurado = ConverterMaiusculo(paisProcurado);
    
    // Criacão de um vetor temporário para poder ordená-lo sem perder a ordenação original do vetor de satélites.
    infoSatelite *vetOrdenado = new infoSatelite[qSatelites];

    for (unsigned int i = 0; i < qSatelites; i++) {
        vetOrdenado[i] = satelites[i];
    }
    OrdernarPais(vetOrdenado, qSatelites);
    GravarAlterações("teste.txt", vetOrdenado, qSatelites);
    
    unsigned int posInicial = 0, posFinal = qSatelites;
    bool achou = false;

    while (posInicial <= posFinal) {
        unsigned int meio = (posInicial + posFinal) / 2;
        std::string auxMaiuscula = ConverterMaiusculo(vetOrdenado[meio].getPais());

        if (auxMaiuscula == paisProcurado) {
            ImprimirElemento(vetOrdenado[meio].getId(), satelites, qSatelites);
            achou = true;
            
            while (vetOrdenado[meio + 1].getPais() == paisProcurado) {
                meio++;
                ImprimirElemento(vetOrdenado[meio].getId(), satelites, qSatelites);
            }
            
            // Aumenta posInicial para sair do while.
            posInicial = posFinal + 1;
        }

        else {
            if (paisProcurado > auxMaiuscula) {
                posInicial = meio + 1;
            }
            else {
                posFinal = meio - 1;
            }
        }
    }
    
    if (!achou) {
        std::cout << "Não foi possível encontrar um satélite que contém esse país de origem.\n";
    }

    delete [] vetOrdenado;

    return;
}

void BuscarAno(const int ANO_PROCURADO, infoSatelite *satelites, const unsigned int qSatelites) {
    // Criacão de um vetor temporário para poder ordená-lo sem perder a ordenação original do vetor de satélites.
    infoSatelite *vetOrdenado = new infoSatelite[qSatelites];

    for (unsigned int i = 0; i < qSatelites; i++) {
        vetOrdenado[i] = satelites[i];
    }
    OrdenarAno(vetOrdenado, qSatelites);
    
    unsigned int posInicial = 0, posFinal = qSatelites;
    bool achou = false;

    while (posInicial <= posFinal) {
        unsigned int meio = (posInicial + posFinal) / 2;

        if (vetOrdenado[meio].getAno() == ANO_PROCURADO) {
            ImprimirElemento(vetOrdenado[meio].getId(), satelites, qSatelites);
            achou = true;

            // Encontra outras instâncias de satélites que possuem o mesmo ano de lançamento.
            while (vetOrdenado[meio + 1].getAno() == ANO_PROCURADO) {
                meio++;
                ImprimirElemento(vetOrdenado[meio].getId(), satelites, qSatelites);
            }

            // Aumenta posInicial para sair do while.
            posInicial = posFinal + 1;
        }

        else {
            if (ANO_PROCURADO > vetOrdenado[meio].getAno()) {
                posInicial = meio + 1;
            }
            else {
                posFinal = meio - 1;
            }
        }
    }

    if (!achou) {
        std::cout << "Não foi possível encontrar um satélite que contém esse ano de lançamento.\n";
    }

    delete [] vetOrdenado;

    return;
}

void BuscarFuncao(std::string funcaoProcurada, infoSatelite *satelites, const unsigned int qSatelites) {
    funcaoProcurada = ConverterMaiusculo(funcaoProcurada);
    
    // Criacão de um vetor temporário para poder ordená-lo sem perder a ordenação original do vetor de satélites.
    infoSatelite *vetOrdenado = new infoSatelite[qSatelites];

    for (unsigned int i = 0; i < qSatelites; i++) {
        vetOrdenado[i] = satelites[i];
    }
    OrdenarFuncao(vetOrdenado, qSatelites);
    
    unsigned int posInicial = 0, posFinal = qSatelites;
    bool achou = false;

    while (posInicial <= posFinal) {
        unsigned int meio = (posInicial + posFinal) / 2;
        std::string auxMaiuscula = ConverterMaiusculo(vetOrdenado[meio].getFuncao());

        if (auxMaiuscula== funcaoProcurada) {
            ImprimirElemento(vetOrdenado[meio].getId(), satelites, qSatelites);
            achou = true;

            // Aumenta posInicial para sair do while.
            posInicial = posFinal + 1;
        }

        else {
            if (funcaoProcurada > auxMaiuscula) {
                posInicial = meio + 1;
            }
            else {
                posFinal = meio - 1;
            }
        }
    }

    if (!achou) {
        std::cout << "Não foi possível encontrar um satélite que contém essa função.\n";
    }
    
    delete [] vetOrdenado;

    return;
}

void BuscarParte(std::string trecho, infoSatelite *satelites, const unsigned int qSatelites) {
    trecho = ConverterMaiusculo(trecho);
    
    // Criacão de um vetor temporário para poder ordená-lo sem perder a ordenação original do vetor de satélites.
    infoSatelite *vetOrdenado = new infoSatelite[qSatelites];

    for (unsigned int i = 0; i < qSatelites; i++) {
        vetOrdenado[i] = satelites[i];
    }
    OrdernarId(vetOrdenado, qSatelites);

    bool achou = false;
    for (unsigned int i = 0; i < qSatelites; i++) {
        std::string auxMaiuscula = ConverterMaiusculo(vetOrdenado[i].getFuncao());

        if (auxMaiuscula.find(trecho) < auxMaiuscula.size()) {
            ImprimirElemento(vetOrdenado[i].getId(), satelites, qSatelites);
            achou = true;
        }
    }

    if (!achou) {
        std::cout << "Não foi possível encontrar um satélite que contém esse trecho.\n";
    }

    delete [] vetOrdenado;

    return;
}

std::string ConverterMaiusculo(std::string texto) {
    std::string textoMaiusculo;
        
    // Fazer com que o o trecho de uma função do satélite na posição meio seja maiúscula para fazer as comparações de buscas corretas,
    // sem a necessidade do usuário digitar o texto corretamente.
    for (long unsigned int i = 0; i < size(texto); i++) {
            textoMaiusculo += toupper(texto[i]);
    }
    
    return textoMaiusculo;
}

std::string RemoverAcentuacao(std::string texto) {
    const std::map<std::string, std::string> MAPA_ACENTUACAO = {
        // Mapa das letras minúsculas.
        {"á", "a"}, {"à", "a"}, {"ã", "a"}, {"â", "a"},
        {"é", "e"}, {"ẽ", "e"}, {"ê","e"},
        {"í", "i"}, {"ì", "i"},
        {"ó", "o"}, {"õ", "o"},
        {"ú", "u"}, {"ç", "c"},

        // Mapa das letras maiúsuclas.
        {"Á", "A"}, {"À", "A"}, {"Ã", "A"}, {"Â", "A"},
        {"É", "E"}, {"Ẽ", "E"}, {"Ê","E"},
        {"Í", "I"}, {"Ì", "I"},
        {"Ó", "O"}, {"Õ", "O"},
        {"Ú", "U"}, {"Ç", "C"}
    };
    
    std::string textoDesacentuado = texto;

    for (auto &letra : texto) {
    }

    return textoDesacentuado;
}

void SobrescreverElemento(const unsigned int identificador, infoSatelite novoElemento, infoSatelite *&satelites, const unsigned int qSatelites) {
    novoElemento.setId(identificador);
    satelites[identificador] = novoElemento;

    return;
}

// ERRADO!!!!!
void InserirElemento(infoSatelite novoElemento, infoSatelite *&satelites, unsigned int &qSatelites, unsigned int &tamanhoVetor) {
    unsigned int idNovo = qSatelites + 1;
    
    // Checa se é possível inserir um novo elemento no vetor.
    if (idNovo > tamanhoVetor) {
        RedimensionaVetor(satelites, tamanhoVetor);
    }

    else {
        novoElemento.setId(idNovo);
        satelites[qSatelites] = novoElemento;
        qSatelites++;
    }

    return;
}

void RemoverElemento(unsigned int identificador, infoSatelite *&satelites, unsigned int &qSatelites) {
    for (unsigned int i = 0; i < qSatelites; i++) {
        if (identificador == satelites[i].getId()) {
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
