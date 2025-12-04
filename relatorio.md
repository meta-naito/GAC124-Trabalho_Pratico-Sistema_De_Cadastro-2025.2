## struct infoSatelite

### Atributos:

O registro infoSatelite possui 5 campos que englobam as informações de um satélite, sendo eles:
    
    unsigned int identificador;
    string nome;
    string paisOrigem;
    int anoLancamento;
    string funcao;

#### unsigned int identificador:
Variável do tipo int não assinado, que armazena o Id de um satélite.
Único para cada satélite no banco de dados, e não permutável. Ou seja, caso aconteça a exclusão de um satélite, por exemplo, o identificador do mesmo não poderá ser reutilizado.
    
    Previamente, o identificador era uma variável do tipo int, mas o grupo optou pela mudança para unsigned int pois não seriam utilizados identificadores negativos.

#### string nome:
Variável do tipo string, que armazena o nome completo de um satélite, junto com sua abreviação (quando necessário).

#### string paisOrigem:
Variável do tipo string, que armazena o país de origem de um satélite.
É considerado país de origem aquele que controla o satélite, não o país da onde o satélite foi lançado à órbita. Portanto, é possível que um satélite possua mais de um país de origem, considerando o caso de múltiplos países monitorando um mesmo satélite.
Nesse caso, ficará explícito os donos de cada satélite.

#### int anoLancamento:
Variável do tipo int, que armazena o ano em que um satélite foi lançado a órbita.

    No caso especial da Lua, único satélite natural do banco de dados, foi escolhido que o ano de lançamento dela seria igual a zero.

#### string funcao:
Variável do tipo string, que armazena a função de um satélite.
[eu to percebendo que estamos usando a funcao errado!!!!!!!!!!!! suicidio, arruma dps e conversa com a athena oliver pls]

### Métodos:

Além dos atributos do registro, existe também algumas funções e procedimentos, sendo elas:

#### unsigned int getId():
