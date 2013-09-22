#include <cstdlib>
#include <iostream>
#include <ctype.h>

//Estrutura que representa a locação de um filme no sistema
typedef struct locacao
{
  unsigned int id;               //código da locação
  char filme[255];               //Nome do filme
  char cliente[255];             //Nome do Cliente
  char data_devolucao[15];       //Data de Devolução do filme
};

//Abre o arquivo de indice
int openLocacao();

//Fecha o arquivo de indice
void closeLocacao();

//Pede ao usuario para digitar uma locação e salva na struct locacao
locacao readLocacao();

//Exibe na tela os dados de uma locacao
void viewLocacao(locacao l);

//Grava locacao no arquivo no formato tamid|filme|cliente|devolucao
int saveLocacao(locacao l);

//Procura por uma locação no arquivo a partir do offset no arquivo
locacao findLocacaoByOffset(int offset);

//Insere um novo item na lista de espaços disponiveis do arquivo
void insertInAvailableList(int offset);
