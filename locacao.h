#include <cstdlib>
#include <iostream>
#include <ctype.h>

//Estrutura que representa a loca��o de um filme no sistema
typedef struct locacao
{
  unsigned int size;              //Tamanho em bytes da loca��o no arquivo
  unsigned int id;               //c�digo da loca��o
  char filme[255];               //Nome do filme
  char cliente[255];             //Nome do Cliente
  char data_devolucao[15];       //Data de Devolu��o do filme
};

//Abre o arquivo de indice
int openLocacao();

//Fecha o arquivo de indice
void closeLocacao();

//Pede ao usuario para digitar uma loca��o e salva na struct locacao
locacao readLocacao(int id);

//Exibe na tela os dados de uma locacao
void viewLocacao(locacao l);

//Grava locacao no arquivo no formato tamid|filme|cliente|devolucao
int saveLocacao(locacao l);

//Procura por uma loca��o no arquivo a partir do offset no arquivo
locacao findLocacaoByOffset(int offset);

//Insere um novo item na lista de espa�os disponiveis do arquivo
void insertInAvailableList(int offset);

//Atualiza loca��o no mesmo offset da antiga
void updateLocacao(int offset,int newLength,locacao l);

