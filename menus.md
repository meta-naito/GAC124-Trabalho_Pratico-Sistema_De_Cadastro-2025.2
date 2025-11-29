Olá, e seja bem-vindo(a) ao [alguma coisa sei laKKKK]

           .       .                   .       .      .     .      .
          .    .         .    .            .     ______
      .           .             .               ////////
                .    .   ________   .  .      /////////     .    .
           .            |.____.  /\        ./////////    .
    .                 .//      \/  |\     /////////
       .       .    .//          \ |  \ /////////       .     .   .
                    ||.    .    .| |  ///////// .     .
     .    .         ||           | |//`,/////                .
             .       \\        ./ //  /  \/   .
  .                    \\.___./ //\` '   ,_\     .     .
          .           .     \ //////\ , /   \                 .    .
                       .    ///////// \|  '  |    .
      .        .          ///////// .   \ _ /          .
                        /////////                              .
                 .   ./////////     .     .
         .           --------   .                  ..             .
  .               .        .         .                       .
                        ________________________
____________------------                        -------------_________

Opções:

    1. Inserir um novo satélite;
        > Gostaria de inserir um novo satélite ao banco de dados ou sobreescrever um outro satélite?
            1. Novo -> InserirElemento()
            2. Sobreescrever outro -> SobreescreverElemento()

    2. Apagar um satélite;

    3. Atualizar informação de satélite;
        > Qual informação você gostaria de alterar?
            1. Nome -> AtualizarNome()
            2. País de Origem -> AtualizarPais()
            3. Ano de lançamento -> AtualizarAno()
            4. Função -> AtualizarFuncao()
            [5. Identificador -> SobreescreverId()] //nao sei se esse necessitaKKKK

    4. Obter quantidade de registros de satélites -> ObterQuantidadeSatelites();
    
    5. Exibir satélites;
        > Gostaria de imprimir uma lista de satélites ou um único satélite?
            1. Lista de satélites;
                > Escolha o escopo da lista a ser exibida:
                    1. Todos os satélites -> Imprimir(idInicial = 0 e idFinal = qSatelites)
                    2. Personalizado -> Imprimir()
            2. Apenas um satélite -> ImprimirElemento()
    
    6. Buscar satélites;
        > Por qual campo você gostaria de pesquisar no sistema?
            1. Nome ->
            2. País de Origem -> 
            3. Ano de lançamento -> 
            4. Função ->
            5. Identificador ->
            //nao precisa de id pq acho que a pesquisa é pelo id mesmoKKK

    7. Ordenar satélites;
        > Qual campo você gostaria de ordenar o sistema?
            1. Nome ->
            2. País de Origem -> 
            3. Ano de lançamento -> 
            4. Função -> 
            5. Identificador ->
            //nao sei se vai realmente ter que ordenar por duas coisas ao mesmo tempo, mas isso vejo dps :D

    8. Gravar alterações -> GravarAlteracoes()

    9. Sair do programa -> exit(0)