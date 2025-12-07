# Introdução

O relatório que se segue tem o propósito de demonstrar, de forma clara e objetiva, os resultados, análises e conclusões obtidos ao longo do desenvolvimento do trabalho prático da matéria de Introdução aos Algoritmos (GAC124), feito por Arthur Fazzio Mendes e Lívia Rezende Masson (10B).

A elaboração deste documento visa detalhar os métodos adotados para a implementação do sistema de cadastro com o tema "Satélites" feito pelo grupo, explicando em conjunto a lógica total do programa, assim como identificar os aspectos mais relevantes no desenvolvimento do prejeto, incluindo os erros e acertos da dupla durante o processo de programação.

# Banco de dados

O arquivo __"db_satelites.csv"__ (abreviação/adaptação de DataBase Satélites) inclui as informações de cada satélite colocado pelo grupo, totalizando 55.

A primeira linha do arquivo contém as informações de cada campo utilizado para identificar um elemento, sendo eles:

- Identificador,
- Nome,
- País de Origem,
- Ano de Lançamento,
- Função.

A segunda linha contém a quantidade total de satélites no arquivo, sendo sujeito a mudanças no período em que o programa esteja rodando.

Cada campo é separado por vírgulas, como é costume para um arquivo CSV. Para as variáveis que podem possuir vírgulas em sua composição, são utilizadas aspas para serem computadas como um único campo.

A inserção de elementos para o arquivo foi, de certa forma, feita gradualmente. Para uniformização de grande parte dos elementos, foram utilizados bancos de dados existentes de satélites em órbita ativos.

Mesmo assim, alguns dos satélites não se encaixam nessa categoria. Eles aindam continuam no arquivo ou por serem satélites facilmente reconhecíveis e significativos para o progresso da humanidade, ou por ser o único satélite natural de nosso planeta, sendo ele a Lua.

Mais informações sobre a especificação de cada campo e como esse arquivo é lido pelo programa estarão logo abaixo.

# Estruturas do código

As estruturas que serão descritas a seguir são as incluídas no arquivo "csv_utils.hpp", seguindo a ordem em que estão inclusas.

No caso de variáveis que usam _std::_ para serem identificadas, elas não serão inclusas na descrição, salvo em casos onde elas estão incluídas em um trecho de código a ser explicado. 

Além disso, para algumas funções serão incluídos comentários sobre o desenvolvimento das mesmas, se durante a duração do projeto houveram mudanças significativas em sua lógica.

## `struct infoSatelite`

O registro `infoSatelite` possui 5 campos que englobam as informações de um satélite, sendo eles:
    
```
unsigned int identificador;
string nome;
string paisOrigem;
int anoLancamento;
string funcao;
```

#### unsigned int `identificador`:
Variável do tipo int não assinado, que armazena o Id de um satélite.

Único para cada satélite no banco de dados, e não permutável. Ou seja, caso aconteça a exclusão de um satélite, por exemplo, o identificador do mesmo não poderá ser reutilizado.
    
Previamente, o identificador era uma variável do tipo int, mas o grupo optou pela mudança para unsigned int pois não seriam utilizados identificadores negativos.

#### string `nome`:
Variável do tipo string, que armazena o nome completo de um satélite, junto com sua abreviação (quando necessário).

#### string `paisOrigem`:
Variável do tipo string, que armazena o país de origem de um satélite.

É considerado país de origem aquele que controla o satélite, não o país na qual o satélite foi lançado à órbita. Portanto, é possível que um satélite possua mais de um país de origem, considerando o caso de múltiplos países monitorando um mesmo satélite.
Nesse caso, ficará explícito os donos de cada satélite.

No caso especial da Lua, foi escolhido que o "país de origem" dela fosse Theia, nome dado ao planeta que, baseado na hipótese do Grande Impacto, colidiu com a Terra e deu origem à Lua.

#### int `anoLancamento`:
Variável do tipo int, que armazena o ano em que um satélite foi lançado a órbita.

No caso especial da Lua, foi escolhido que o ano de lançamento dela seria igual ao máximo que um inteiro em um processador de 32-bits consegue armazenar, tanto por ser relativamente próximo à idade estimada do nosso satélite, quanto pelo fato de que algumas funções utilizadas no código retornam o número zero (a outra possibilidade de ano de lançamento pensada pelo grupo).

#### string `funcao`:
Variável do tipo string, que armazena a função de um satélite.

Durante o processo de inserção de elementos no arquivo CSV, houve uma mudança do propósito de uma função de satélite. Para explicar melhor, foi percebido que o que foi colocado como "função" de um satélite era nada mais que comentários e/ou curiosidades sobre o mesmo.
Como isso foi apenas notado muito tarde no desenvolvimento do projeto, foi então decidido pelo grupo que esses comentários sobre um satélite serviriam como sua função, já que também serve para explicar o porquê de um dado satélite existir.

## `infoSatelite* CarregarCSV()`

```
infoSatelite* CarregarCSV(const string NOME_ARQUIVO, unsigned int &tamanhoVetor, unsigned int &qSatelites)
```

A função `CarregarCSV()` tem o objetivo de fazer a leitura do arquivo que contém o banco de dados __"db_satelites.csv"__. 

Ela retorna um ponteiro para o vetor de registro _infoSatelite_, de nome `satelites`, e possui como parâmetros: 
    
- Uma string constante que denomina o nome do arquivo,
- O tamanho total do vetor de registro, que é uma variável do tipo int não assinado, com valor inicial 40,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado, com valor inicial 0.

Ambos o tamanho do vetor e a quantidade de satélites são passados por referência para serem mudados dentro da função.

Primeiramente, é utilizado um objeto _"ifstream"_ para abrir o arquivo __"db_satelites.csv"__. Logo abaixo, é checado se esse arquivo existe. Caso não exista, é exibido uma mensagem de erro no terminal, e não é possível implementar o resto das funções do programa.

Feita a checagem, é lido então a primeira linha do arquivo, que serve de comentário para a identificação dos campos. Como essa identificação serve apenas para o entendimento dos argumentos do arquivo CSV, ela não será utilizada durante o programa.

Após essa leitura, são lidos para a variável _qSatelites_ a quantidade de satélites presentes no banco de dados, utilizando _"cin >>"_. Finalmente, é criado dinamicamente um vetor de registros _infoSatelite_, com tamanho inicial igual a variável _tamanhoVetor_.

As informações de cada satélite são lidas respeitando a segunte ordem de variáveis:

    - identificador,
    - nome,
    - paisOrigem,
    - anoLancamento,
    - funcao.

A função utiliza um loop _for()_ com o índice _i_, e condição de parada sendo se _i_ é igual ou maior a _qSatelites_, com _i_ incrementando em um a cada loop.

Para as variáveis que possuem aspas (ou seja, que são strings), é utilizado _getline()_ para a leitura em cada campo, sendo a condição de parada as aspas finais da string. Logo após, usamos a variável _lixo_ para descartar as vírgulas que separam cada variável no arquivo.

Para as outras variáveis, é utilizado apenas o operador >>, já que não é necessário a atribuição de espaços nessas variáveis. Sempre também é descartado as vírgulas utilizando _lixo_.

Por fim, é feito uma checagem se o tamanho do índice _i_ mais um é maior ou igual a _tamanhoVetor_. Caso seja, indica que é necessário redimensionar o vetor, utilizando função própria para isso, que será explicada a frente.

Após a leitura de uma linha completa, esse código irá se repetir até que sejam lidos todos os satélites presentes no arquivo. Saindo do _for()_, o arquivo __"db_satelites.csv"__ então é fechado.

## `void RedimensionaVetor()`

```
void RedimensionaVetor(infoSatelite *&vetor, unsigned int &tamanhoVetor)
```

O procedimento `RedimensionaVetor()` tem o objetivo de aumentar a capacidade total do vetor de registros _infoSatelite_, permitindo com que novos satélites sejam adicionados sem a perca de dados prévios.

Como o procedimento é do tipo __void__, a função não retorna nenhum valor, e possui como parâmetros:

- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- O tamanho total do vetor, que é uma variável do tipo int não assinado.

Ambas as variáveis são passadas por referência, já que ambas serão modificadas no decorrer da função.

É utilizado uma variável constante _TAM _ REDIMENSIONAMENTO_, de valor 10, para o aumento em cada redimensionamento do vetor.

Então, é criado um vetor de registros _infoSatelite_ auxiliar, com o tamanho inicial do vetor armazenado em uma variável auxiliar _TAM _ INICIAL_.

Usando um loop _for()_, os dados do vetor original `satelites` são copiados para esse vetor auxiliar, terminando quando o índice ser igual ou maior que _TAM _ INICIAL_. Logo após, o vetor _satelites_ é apagado da memória.

Então, _tamanhoVetor_ é aumentado em _TAM _ REDIMENSIONAMENTO_ (ou seja, _tamanhoVetor_ é agora 10 unidades maior do que antes). A função depois faz com que o ponteiro `satelites` aponte para uma nova área de memória, de tamanho ajustado _tamanhoVetor_.

Por fim, utilizando outro loop _for()_, os dados do vetor auxiliar são copiados para o novo vetor `satelites`, terminando quando o índice novamente for igual ou maior a _TAM _ INICIAL_. Depois, o vetor auxiliar é apagado da memória.

## `void ReduzirVetor()`

```
void ReduzirVetor(unsigned int qReducao, infoSatelite *&satelites, unsigned int &tamanhoVetor)
```

O procedimento `ReduzirVetor()` tem como objetivo reduzir o tamanho total do vetor, fazendo com que o mesmo não ocupe espaço desnecessário em memória.

Como o procedimento é do tipo __void__, a função não retorna nenhum valor, e possui como parâmetros:

- A quantidade em que o vetor de registros deve ser diminuído, sendo uma variável do tipo int não assinado,
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- O tamanho total do vetor, que é uma variável do tipo int não assinado.

Ambos o vetor de registros e o tamanho do vetor são passadas por referência, já que ambos serão modificadas no decorrer da função.

A lógica desse procedimento é quase idêntica a de RedimensionaVetor(), apenas diferindo em que, nessa função, o vetor auxiliar possui tamanho de variável _NOVO _ TAMANHO_, que é calculada pela diferença entre _tamanhoVetor_ e _qReducao_.

## `void Imprimir()`

```
void Imprimir(const unsigned int idInicio, const unsigned int idFinal, infoSatelite *satelites, const unsigned int qSatelites)
```

O procedimento `Imprimir()` tem como objetivo exibir, na tela do usuário, os elementos no intervalo que o usuário pedir.

Como o procedimento é do tipo __void__, a função não retorna nenhum valor, e possui como parâmetros:

- O identificador do primeiro elemento a ser exibido, sendo uma variável do tipo int não assinado,
- O identificador do último elemento a ser exibido, sendo uma variável do tipo int não assinado,
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado constante.

O procedimento utiliza um loop _for()_ com um índice _i_, e condição de parada sendo se _i_ é igual ou maior a _qSatelites_, com _i_ incrementando em um a cada loop.

Dentro dessa repetição, é checado se o identificador do satélite na posição _i_ é maior ou igual a _idInicio_, e menor ou igual a _idFinal_. Caso seja, esse satélite é exibido na tela.

Após encontrar um satélite com um identificador no escopo informado, esse trecho de código irá se repetir até que todos os satélites serem exibidos.

## `void ImprimirElemento()`

```
ImprimirElemento(const unsigned int identificador, infoSatelite *satelites, const unsigned int qSatelites)
```

O procedimento `ImprimirElemento()` tem como objetivo exibir na tela do usuário apenas um satélite do vetor de registros. Foi criada para fins práticos, já que ela é apenas um alias de `Imprimir()`.

Como o procedimento é do tipo __void__, a função não retorna nenhum valor, e possui como parâmetros:

- O identificador do elemento a ser exibido, sendo uma variável do tipo int não assinado,
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado constante.

Essa função chama apenas o procedimento `Imprimir()`, com o parâmetro _idInicial_ e _idFinal_ sendo a variável _identificador_. Ou seja, é impresso apenas um único elemento com o identificador pedido.

## Ordenação de elementos

Os procedimentos de ordenação foram feitos utilizando a lógica do Merge Sort recursivo, pelo fato desse método de ordenação ser éstavel. Ou seja, ele preserva a ordem original de elementos iguais após a ordenação.

Esse aspecto do Merge Sort é beneficial para a implementação usada, já que se o vetor dor ordenado por dois campos distintos, a ordem de elementos relativos será mantida.

Inicialmente, foi feito duas funções __template__ de tipo __void__: uma para a intercalação de elementos necessária para o Merge Sort, e outra que é o Merge Sort em si. Ambas as inicializações podem ser vistas abaixo: 

```
- template <typename tipoDado> void IntercalaElementos(tipoDado *vetor, int inicioVetor, int meioVetor, int finalVetor)
- template <typename tipoDado> void MergeSort(tipoDado *vetor, int inicioVetor, int finalVetor)
```

O tipo _tipoDado_ era dependente de qual campo do vetor de registros era para ser ordenado. Exemplificando, se era necessário ordenar o vetor pelo ano de lançamento (uma variável de tipo int), _tipoDado_ seria igual a int, e a chamada seria algo como:

```
IntercalaElementos<int>(int *vetor, ...)
```

Essas funções tanto auxiliaram a modularização do código, já que não era estritamente necessário criar uma vertente de Merge Sort para cada variável, quanto pioraram na manutenção do mesmo, pois não era possível passar como parâmetro todo o vetor de satélites.

Então, era necessário criar um vetor auxiliar do mesmo tipo que a variável a ser ordenada, copiar os dados do campo do vetor de registros a ser ordenado para esse vetor auxiliar, ordená-lo, e por fim organizar o vetor original usando o auxiliar como molde.

Como pode ser visto, essa implementação trouxe muitos problemas, sendo o principal deles a inconfiabilidade dos elementos do vetor original estarem nos lugares certos após a ordenação. Esse fator foi mais observado na função `OrdenarPais()` em sua forma original, já que em grande parte dos casos, os países de origem não eram ordenados corretamente, justamente pela necessidade do vetor auxiliar.

Então, após a percepção desse erro por parte do grupo, foi decidido apenas fazer uma função de intercalação, Merge Sort e ordenação para cada campo do registro, como será explicado abaixo.

### `void IntercalaELementos()`

```
void IntercalaElementosId(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor)

void IntercalaElementosNome(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor)

void IntercalaElementosPais(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor)

void IntercalaElementosAno(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor)

void IntercalaElementosFuncao(infoSatelite *vetor, int inicioVetor, int meioVetor, int finalVetor)
```
Os procedimentos descritos acima tem como objetivo intercalar os elementos para a função `MergeSort()`.

Como essas funções são do tipo __void__, elas não retornam nenhum valor, e tem como parâmetros:

- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A posição inicial do vetor, que é uma variável do tipo int,
- A posição do meio do vetor, que é uma variável do tipo int,
- A última posição do vetor, que é uma variável do tipo int.

A intercalação faz com que os elementos de dois subvetores distintos - sendo o primeiro vetor de tamanho [_inicioVetor_, _meioVetor_], e o segundo de tamanho [_meioVetor_ + 1, _finalVetor_] - sejam organizados de forma que os elementos desses vetores estejam ordenados crescentemente.

### `void MergeSort()`

```
void MergeSortId(infoSatelite *vetor, int inicioVetor, int finalVetor)

void MergeSortNome(infoSatelite *vetor, int inicioVetor, int finalVetor)

void MergeSortPais(infoSatelite *vetor, int inicioVetor, int finalVetor)

void MergeSortAno(infoSatelite *vetor, int inicioVetor, int finalVetor)

void MergeSortFuncao(infoSatelite *vetor, int inicioVetor, int finalVetor)
```

Os procedimentos descritos acima tem como objetivo ordenar os elementos utilizando Merge Sort.

Como essas funções são do tipo __void__, elas não retornam nenhum valor, e tem como parâmetros:

- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A posição inicial do vetor, que é uma variável do tipo int,
- A última posição do vetor, que é uma variável do tipo int.

É criado uma variável _meioVetor_ que, fazendo uma média entre _inicioVetor_ e _finalVetor_, calcula o meio do vetor para `IntercalaElementos()`.

O conceito de Merge Sort é aplicar recursivamente a divisão do vetor original em metades até que cada metade possua um único elemento. Após essa divisão, os elementos são intercalados utilizando `IntercalaElementos()`.

### `void Ordenar()`

```
void OrdenarId(infoSatelite *&satelites, const unsigned int qSatelites)

void OrdenarNome(infoSatelite *&satelites, const unsigned int qSatelites)

void OrdenarPais(infoSatelite *&satelites, const unsigned int qSatelites)

void OrdenarAno(infoSatelite *&satelites, const unsigned int qSatelites)

void OrdenarFuncao(infoSatelite *&satelites, const unsigned int qSatelites)
```
Os procedimentos descritos acima tem como objetivo ordenar os elementos do vetor de registros.

Como essas funções são do tipo __void__, elas não retornam nenhum valor, e tem como parâmetros:

- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado constante.

Esses procedimentos apenas chamam a função `MergeSort()` correspondente, deixando assim mais fácil as chamadas.

## Busca de elementos

### `bool ExisteId()`

```
bool ExisteId(const unsigned int identificador, infoSatelite *&satelites, const unsigned int qSatelites);
```
 
A função `ExisteId()` tem como objetivo informar se um identificador existe no vetor de satélites, uma vez que não existe garantia de que os índices do vetor correspondem com os identificadores dos satélites, ou até que os identificadores estejam em ordem. 

Para isso, ela realiza busca binária no vetor até encontrar o elemento.

Seus parâmetros são:

- Um identificador para ser localizado, do tipo int não assinado,
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado constante.

Utilizando a lógica de busca binária iterativa, a função percorre o vetor de registros satélite por satélite, verificando se o identificador existe em algum satélite. Caso exista um elemento com o identificador fornecido ela retorna o valor booleano _true_. Do contrário, a função retorna _false_.

### `unsigned int MaiorId()`

```
unsigned int MaiorId(infoSatelite *&satelites, unsigned int qSatelites)
```

A função`MaiorId()` tem como objetivo encontrar o maior identificador que existe dentro do satélite, servindo como uma função auxiliar para `InserirElemento()` (que será explicada a frente) conseguir adicionar um novo elemento cujo identificador não está ocupado.

Seus parâmetros são:
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado constante.

A variável _maiorId_ é inicializada como o identificador do primeiro elemento do vetor de registros.

Utilizando um loop _for()_, o vetor de registros é percorrido até encontrar um identificador maior do que o armazenado por _maiorId_. Caso isso aconteça, _maiorId_ receberá o identificador maior.

Ao final da função, é devolvido o maior identificador encontrado no vetor de registros.

### `void BuscarNome()`, `void BuscarPais()` e `void BuscarAno()`

```
void BuscarNome(const std::string NOME_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites);

void BuscarPais(const std::string PAIS_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites);

void BuscarAno(const int ANO_PROCURADO, infoSatelite *&satelites, const unsigned int qSatelites);
```

Os procedimentos `BuscarNome()`, `BuscarPais()` e `BuscarAno()` tem como objetivo buscar, no vetor de registros, elementos que correspondem ao que o usuário pedir, exibindo os elementos na tela.

Todos esses procedimentos são capazes de diferenciar maiúsculas de minúsculas, e letras acentuadas de não acentuadas. Além disso, assumem que o vetor que ela busca os elementos está ordenado por nome.

Todos os procedimentos tem como parâmetros:
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado constante.

Para fazer a busca, `BuscarNome()` e `BuscarPais()` necessitam de:

- Uma palavra/trecho que denomina o que está sendo procurado, sendo ele uma variável do tipo string constante.

E `BuscarAno` necessita de:

- O ano que está sendo procurado, sendo ele uma variável do tipo inteiro constante.

Todas as funções, de maneira semelhante, percorrem o vetor realizando busca binária iterativa. Caso seja achado alguma correspondência, é verificado com dois loops _while()_ se existem outros elementos que também correspondem à pesquisa.

O primeiro loop busca se existem correspondências em posições acima/a esquerda da posição em que foi encontrado o elemento. Caso possua, a variável _comecoImpri_ (inicializada com a posião em que o elemento foi primeiramente encontrado) é decrementada em um cada vez que são achados outros elementos.

Já o segundo utiliza a mesma lógica do primeiro, mas busca correspondências abaixo/a direita da posição em que foi encontrado o elemento. Nesse caso, a variável _finalImpri_ (também inicializada com a posição do primeiro elemento) é incrementada em um.

Como essas funções são do tipo __void__, elas não retornam nenhum valor, apenas escrevem para a saída padrão os elementos que correspondem a busca, utilizando `ImprimirElemento()` em um loop _for()_, com início em _comecoImpri_ e final em _finalImpr_ Caso nenhuma das duas variáveis forem alteradas, será exibido apenas o elemento encontrado inicialmente.

### `void BuscarFuncao()`

```
void BuscarFuncao(std::string FUNCAO_PROCURADA, infoSatelite *&satelites, const unsigned int qSatelites);
```

O procedimento `BuscarFuncao()` tem como objetivo buscar, no vetor de registros, elementos que correspondem a função que está sendo pesquisada no vetor de registros, ou que contém uma substring correspondente, exibindo os elementos na tela.

Todos esses procedimentos são capazes de diferenciar maiúsculas de minúsculas, e letras acentuadas de não acentuadas. Além disso, assumem que o vetor que ela busca os elementos está ordenado por nome.

São utilizados como parâmetros:
- Uma string com a função a ser procurada.
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado constante.

A função percorre o vetor realizando a busca na função de cada satélite e imprimindo todos os elementos com uma substring ou string correspondente a busca. De maneira sucinta, a lógica dessa função é idêntica as funções acima de busca.

Como a função é do tipo __void__, ela não retorna nenhum valor, e apenas escreve para a saída padrão os elementos que correspondem a busca usando `ImprimirElemento()`.

## `void SobrescreverElemento()`

```
void SobrescreverElemento(const unsigned int identificador, infoSatelite novoElemento, infoSatelite *&satelites, const unsigned int qSatelites);

```
Esse procedimento tem como objetivo sobreescrever um satélite com outro, preservando o identificador.

Como essa função é do tipo __void__, ela não retorna nenhum valor, e tem como parâmetros:

- O identificador do elemento a ser reescrito, que é uma variável do tipo int não assinado constante,
- O elemento que vai ser sobreposto ao antigo, que é uma variável do tipo infoSatélite,
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado constante.

O identificador do elemento antigo é atribuído ao campo de _novoElemento_, e logo após, o elemento é sobrescrito pelo novo elemento,

## `void InserirElemento()`

```
void InserirElemento(infoSatelite novoElemento, infoSatelite *&satelites, unsigned int &qSatelites, unsigned int &tamanhoVetor)
```

Esse procedimento tem como objetivo inserir um novo satélite ao vetor de registros.

Como essaa função é do tipo __void__, ela não retorna nenhum valor, e tem como parâmetros:

- O elemento a ser inserido, que é uma variável do tipo infoSatélite,
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado constante.

É criado uma variável _novaQuantidade_, que recebe o valor _qSatélites_ mais 1, indicando a nova adição oo vetor. Logo após, é criado um novo identificador, utilizando a função `MaiorId()` e incrementando em um esse valor.

Depois, é verificado se é possível inserir um novo elemento ao vetor. Caso não seja, o vetor é redimensioado utilizando `RedimensionaVetor()`.

Por fim, o identificador criado anteriormente é atribuído ao campo do novo elemento, o novo elemento é inserido no vetor, e é incrementado em um _qSatelites_. 

## `void RemoverElemento()`

```
void RemoverElemento(unsigned int identificador, infoSatelite *&satelites, unsigned int &qSatelites);
```

Esse procedimento tem como objetivo remover um satélite do vetor de registros.

Como essa função é do tipo __void__, ela não retorna nenhum valor, e tem como parâmetros:

- O identificador do elemento a ser removido, que é uma variável do tipo int não assinado constante,
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite,
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado constante.

A função utiliza um loop _for()_, percorrendo o vetor de registros até achar o elemento com o identificador correspondente. 

Quando ele é achado, outro loop _for()_ é ativado, com o índice _j_ igual ao índice do elemento a ser removido. Nisso, todos os elementos à direita do índice _j_ são passados em uma unidade a esquerda, essencialmente sobrescrevendo o elemento a ser removido.

## `void GravarAlterações()`

```
void GravarAlterações(const std::string NOME_ARQUIVO, infoSatelite *&satelites, const unsigned int qSatelites);

```

Esse procedimento tem como objetivo salvar as alterações feitas no vetor de registros ao longo do programa no arquivo CSV.

Como essa função é do tipo __void__, ela não retorna nenhum valor, e tem como parâmetros:

- Uma string constante que denomina o nome do arquivo,
- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite.
- A quantidade total de satélites no banco de dados, que é uma variável do tipo int não assinado.

Primeiramente, é lido a primeira linha do CSV original, que é o comentário para a identificação dos campos, também checando se o arquivo existe. Caso não exista, é exibido uma mensagem de erro no terminal.

Logo após, é utilizado o objeto _ofstream_ para escrever as alterações no arquivo __"db_satelites.csv"__. É então escrito novamente o comentário, a quantidade total de satélites no vetor e, utilizando um loop _for()_, os campos de cada satélite,

## `void DeletarSalvo()`

```
void DeletarSalvo(infoSatelite *&satelites)
```

Esse procedimento tem como objetivo não permitir que as alterações feitas no vetor de registros ao longo do programa sejam salvos no arquivo CSV.

Como essa função é do tipo __void__, ela não retorna nenhum valor, e tem como parâmetro:

- O ponteiro para o vetor de registros, que é uma variável do tipo infoSatelite.

Essa função então apenas apaga da memória o vetor de resgistros.