Olá, e seja bem-vindo(a) ao [alguma coisa sei laKKKK]
                    
      .. ............--+-------+##.......                            
                                         ##.. ....-.-.-+         
                                             .#####-++++-#       
                                           ######+########+.     
                                         .##+++-#+--++-++#+++    
                                       #+##++++--+----+------+   
                              .#-+ .    ##++-+++###++++#+--.--   
                      .#-..             -#+-#--+######----.-..-  
               .+-.                     #++----#+####+--+.-....  
        .+.                             ##+-...--+###+---.-...   
..#+.                                    ##+-.....-----....+-.   
                                          ##+-...........---     
                                           .#---..........#      
                                              .###++-++#.        
                                                 #-.  .          
                                                +.   ..          
                                               -    ..           
                                             .     ..            
                                            #     ..             
                                          .+     ..              
                                         +.     .-               
                                        -       +                
                                      ..       +                 
                                     #.      .+                  
                                    -       .+                   
                                  ..       .-                    
                                 +         +                     

Opções:
    (Sempre possivel cancelar com Ctrl+C)

    1. Exibir satélites; (Exibe tbm quantidade de satélites)
        > Gostaria de imprimir uma lista de satélites ou um único satélite?
            1. Lista de satélites;
                > Escolha o escopo a ser exibido da lista: 
                    1. Todos os satélites -> Imprimir(idInicial = 0 e idFinal = qSatelites)
                    2. Personalizado -> Imprimir()
            2. Apenas um satélite -> ImprimirElemento()
        (Exibe satelite)
        Digite qualquer tecla para voltar ao menu principal. -> system("read");
        (Volta ao menu principal)

    2. Buscar satélites; (Buscar por um dado campo, retornar todas as informações)
        > Por qual campo você gostaria de pesquisar no sistema?
            1. Identificador ->
            2. Nome ->
            3. País de Origem -> 
            4. Ano de lançamento -> 
            5. Função ->
        (Se não for por Id) -> (Busca Id de satelites correspondentes)
        (Imprime satelites com Id que correspondem)
        Digite qualquer tecla para voltar ao menu principal. -> system("read");
        (Volta ao menu principal)

    3. Ordenar satélites;
        > Por identificador
            Satelites ordenados;
            Digite qualquer tecla para voltar ao menu principal. -> system("read");
            (Volta ao menu principal)
        > Por campos
            > Qual campo você gostaria de ordenar o sistema?
                1. Nome ->
                2. País de Origem -> 
                3. Ano de lançamento -> 
                4. Função -> 
            > Ordenar por campo secundario? (Diferente do primario, remover opcao ja usada)
                s/sim 
                    1. Nome ->
                    2. País de Origem -> 
                    3. Ano de lançamento -> 
                    4. Função -> 
                n/nao
                    Satelites ordenados;
                    Digite qualquer tecla para voltar ao menu principal. -> system("read");
                    (Volta ao menu principal) 
            > Ordenar por campo terceario? (Diferente do primario e secundario, remover opcões ja usadas)
                s/sim
                    1. Nome ->
                    2. País de Origem -> 
                    3. Ano de lançamento -> 
                    4. Função -> 
                    Satelites ordenados;
                    Digite qualquer tecla para voltar ao menu principal. -> system("read");
                    (Volta ao menu principal) 
                n/nao
                    Satelites ordenados;
                    Digite qualquer tecla para voltar ao menu principal. -> system("read");
                    (Volta ao menu principal) 
    
    4. Alterar informação de satélite;
        > Insera o identificador do satélite -> BuscarId()
            (Se existe)
                > Qual informação você gostaria de alterar?
                    1. Identificador (Se o novo Id já não existe) -> SobreescreverId()
                    1. Nome -> AtualizarNome()
                    2. País de Origem -> AtualizarPais()
                    3. Ano de lançamento -> AtualizarAno()
                    4. Função -> AtualizarFuncao()
                Informações alteradas!
                Digite qualquer tecla para voltar ao menu principal. -> system("read");
                (Volta ao menu principal) 
            (Se não existe)
                Satélite não encontrado.
                Digite qualquer tecla para voltar ao menu principal. -> system("read");
                (Volta ao menu principal) 

    5. Inserir um novo satélite; -> InserirElemento()
        (Aumenta automaticamente do identificador mais alto)
        Nome:
        País de Origem:
        Ano de Lançamento:
        Função:
        Satélite adicionado.
        Digite qualquer tecla para voltar ao menu principal. -> system("read");
        (Volta ao menu principal) 

    6. Apagar um satélite;
        > Insira o Id do satélite a ser apagado:
            (Caso exista)
                (Apaga satélite)
                Satélite apagado.
                Digite qualquer tecla para voltar ao menu principal. -> system("read");
                (Volta ao menu principal) 
            (Se não existe)
                Satélite não encontrado.
                Digite qualquer tecla para voltar ao menu principal. -> system("read");
                (Volta ao menu principal) 
        (Volta ao menu principal)

    7. Gravar alterações;
        > Deseja gravar as alterações realizadas para o CSV?
            s/sim -> GravarAlteracoes()
            n/nao -> Volta ao menu principal

    8. Sair do programa -> return 0;
