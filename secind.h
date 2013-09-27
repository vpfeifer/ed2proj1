#include <cstdlib>
#include <iostream>

typedef struct secIndex
{ 
  char *filme;
  int listOffset;
};

int openSecIndex();

void closeSecIndex();

void insereSecundario(char *filme,unsigned int id);

secIndex * buscaIndiceSecundario(char *filme);
