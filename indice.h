#include <cstdlib>
#include <iostream>

//Struct para controlar o indice na memória
typedef struct indice
{
  int id_locacao;
  int offset;
  struct indice *prox;
};

//Abre o arquivo de indice
int openIndex();

//Fecha o arquivo de indice
void closeIndex();

//Insere um novo indice no arquivo
void insertIndexOnFile(indice *index);

//Insere um novo indice na lista de indices
void insertIndexOnList(indice **lista,indice *index);

//Função para buscar elementos na lista de Indices
indice * findIndexByID(indice *lista,int id);

//Retorna um array com todos os indices
void getAllIndexesOnFile(indice **lista);

//Retorna a quantidade de indices no arquivo de indices
int getIndexCount();

//Função para exibir na tela todos os indices da lista (finalidade de teste)
void printIndexes(indice *lista);

//Remove indice do arquivo de indices
void removeIndexFromFile(indice *i,indice **lista);

//zera o contador de indice
void emptyIndex();


//Recria o arquivo
void recreateIndex();
