#include <cstdlib>
#include <iostream>

typedef struct listai
{
  int id;
  int prox;
};

int openListaInvertida();

void closeListaInvertida();

int insereListaInvertida(unsigned int id,int list);

