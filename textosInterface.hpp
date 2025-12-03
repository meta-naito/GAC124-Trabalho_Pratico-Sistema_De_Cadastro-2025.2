#include <string>

// Texto utilidades & geral
const std::string decorador = "=-=";
const std::string decoradorInferior = "=-=-=-=-=-=-=-=-=";
const std::string decoradorLongo = "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
const std::string textoRetornoMenu = "Retornando ao menu principal.";
const std::string textoIdentificadorNaoExiste = "Identificador não existe na base de dados.";

// Texto Início
const std::string textoInicio = "Olá, e seja bem vindo! ao sistema de cadastro em arquivos com tema de satélites.";
const std::string sateliteASCII = 
"      .. ............--+-------+##.......                        \n"
"                                         ##.. ....-.-.-+         \n"
"                                             .#####-++++-#       \n"
"                                           ######+########+.     \n"
"                                         .##+++-#+--++-++#+++    \n"
"                                       #+##++++--+----+------+   \n"
"                              .#-+ .    ##++-+++###++++#+--.--   \n"
"                      .#-..             -#+-#--+######----.-..-  \n"
"               .+-.                     #++----#+####+--+.-....  \n"
"        .+.                             ##+-...--+###+---.-...   \n"
"..#+.                                    ##+-.....-----....+-.   \n"
"                                          ##+-...........---     \n"
"                                           .#---..........#      \n"
"                                              .###++-++#.        \n"
"                                                 #-.  .          \n"
"                                                +.   ..          \n"
"                                               -    ..           \n"
"                                             .     ..            \n"
"                                            #     ..             \n"
"                                          .+     ..              \n"
"                                         +.     .-               \n"
"                                        -       +                \n"
"                                      ..       +                 \n"
"                                     #.      .+                  \n"
"                                    -       .+                   \n"
"                                  ..       .-                    \n"
"                                 +         +                     ";

// Texto da opção de exibir.
const std::string tituloExibir = "Exibir satélites.";
const std::string textoExibirOpcoes =
"Gostaria de imprimir uma lista de satélites ou um único satélite?\n"
"   1. Unico satélite.\n"
"   2. Alcance de satélites.\n"
"   3. Todos os satélites.";

// Texto da opção de buscar.
const std::string tituloBusca = "Buscar satélites.";

// Texto da opção de ordenar.
const std::string tituloOrdenar = "Ordenar satélites.";

// Texto da opção de alterar.
const std::string tituloAlterar = "Alterar informações de um satélite.";

// Texto da opção de inserir.
const std::string tituloInserir = "Inserir novo satélite.";

// Texto da opção de apagar.
const std::string tituloApagar = "Apagar um satélite.";
const std::string textoSucessoApagar = "Satélite apagado.";

// Texto da opção de gravar.
const std::string tituloGravar = "Gravar alterações.";
const std::string textoConfirmarGravar = "Deseja gravar as alterações para o CSV?";
const std::string textoGravacaoCompeta = "Gravação concluida!";
const std::string textoCancelarGravacao = "Gravação cancelada.";

// Texto da opção de sair.
const std::string tituloSair = "Sair do programa.";
const std::string textoConfirmarSair = "Deseja mesmo sair? (Alterações não gravadas não são salvas)";

// Texto menu

const std::string textoVoltando= "Voltando...";
const std::string textoVoltandoAoMenu = "Voltando ao menu principal...";
const std::string tituloMenu = "Opções";
const std::string textoOpcoesMenu = 
"0. TESTES.\n"
"1. " + tituloExibir + '\n' +
"2. " + tituloBusca + '\n' +
"3. " + tituloOrdenar + '\n' +
"4. " + tituloAlterar + '\n' +
"5. " + tituloInserir + '\n' +
"6. " + tituloApagar + '\n' +
"7. " + tituloGravar + '\n' +
"8. " + tituloSair;
