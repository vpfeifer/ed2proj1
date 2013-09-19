#include "indice.h"

FILE *ind;

int openIndex()
{
    if(ind=fopen("index.txt","a+"))
      return 1;
    else
      return 0;
}

void closeIndex()
{
  fclose(ind);
}

void insertIndexOnFile(indice *index)
{
  if(openIndex())
  {
    fseek(ind,0,SEEK_END);
  
    fwrite(&index->id_locacao,sizeof(int),1,ind);
    
    fwrite(&index->offset,sizeof(int),1,ind);
  }
  
  closeIndex();
}

void insertIndexOnList(indice **lista,indice *index)
{
    if(*lista == NULL){
      *lista = index;
  }else{
      indice *aux;
      aux = *lista;
        
      while(aux->prox != NULL){
          aux = aux->prox;
      }
        
      aux->prox = index;
  }
}

void removeIndex(int id)
{
}

indice * findIndexByID(indice *lista,unsigned int id)
{  
   indice *index;
    
    index=lista;
    
   while (index != NULL && index->id_locacao!=id) 
      index = index->prox; 
   
   return index; 
}

void getAllIndexesOnFile(indice **lista)
{
  if(openIndex())
  { 
    fseek(ind,0,SEEK_END);
    
    int tam = ftell(ind),count=0;
    
    fseek(ind,0,SEEK_SET);
    
    while(count<tam)
    {
        indice *i=(indice *)malloc(sizeof(indice*));

        fread(&i->id_locacao,sizeof(int),1,ind);
        fread(&i->offset,sizeof(int),1,ind);
        i->prox=NULL;
        
        insertIndexOnList(lista,i);
        
        count+=8; 
    }
  }
  
  closeIndex();
}

//Retorna a quantidade de indices no arquivo de indices
int getIndexCount()
{
    //coloca cursor no fim do arquivo de indice
  fseek(ind,0,SEEK_END);
  
  //pega o numero de bytes do arquivo
  int indSize = ftell(ind);
  
  //divide pelo tamanho de indices, para saber quantos registros existem
  return indSize/sizeof(indice);
}


//Função para exibir na tela todos os indices da lista (finalidade de teste)
void printIndexes(indice *lista)
{
  while(lista!=NULL)
  {
    printf("%d %d\n",lista->id_locacao,lista->offset);
    lista = lista->prox;
  }
}
