#include "indice.h"

FILE *ind;

int openIndex()
{
    if(!(ind=fopen("index.txt","r+")))
    {
      if(!(ind=fopen("index.txt","w+")))
        return 0;
    }
        
    //Cria cabeçalho, se não existir
    fseek(ind,0,SEEK_END);
      
    int pos = ftell(ind),nullValue=0;
      
    if(pos==0)
      fwrite(&nullValue,sizeof(int),1,ind);
    
    return 1;
}

void closeIndex()
{
  fclose(ind);
}

//Insere um indice no arquivo de indices
void insertIndexOnFile(indice *index)
{
  if(openIndex())
  {
    //Altera o cabeçalho com o contador da lista
    fseek(ind,0,SEEK_SET);
    
    int head=0;
    fread(&head,sizeof(int),1,ind);
    
    int cont=head;
    cont=cont+1;
    fseek(ind,0,SEEK_SET);
    fwrite(&cont,sizeof(int),1,ind);
    
    fflush(ind);
    
    fseek(ind,0,SEEK_SET);
    int t=0;
    fread(&t,sizeof(int),1,ind);
    printf("\n%d\n",t);
    
    //insere o indice
    fseek(ind,0,SEEK_END);
    fwrite(&index->id_locacao,sizeof(int),1,ind);
    fwrite(&index->offset,sizeof(int),1,ind);
  }
  
  closeIndex();
}

//Insere um indice na lista
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

//Procura um indice na lista de indices pelo id da Locação
indice * findIndexByID(indice *lista,int id)
{  
   indice *index;
    
    index=lista;
    
   while (index != NULL && index->id_locacao!=id) 
      index = index->prox; 
   
   return index; 
}

//Cria lista de indices a partir do arquivo de indices
void getAllIndexesOnFile(indice **lista)
{
  if(openIndex())
  { 
    int tam = getIndexCount();
    int count=0;
    
    fseek(ind,4,SEEK_SET);
    
    while(count<tam)
    {
        indice *i=(indice *)malloc(sizeof(indice));

        fread(&i->id_locacao,sizeof(int),1,ind);
        fread(&i->offset,sizeof(int),1,ind);
        i->prox=NULL;
        
        insertIndexOnList(lista,i);
        
        count++; 
    }
  }
  
  closeIndex();
}

//Retorna a quantidade de indices no arquivo de indices
int getIndexCount()
{
  //coloca cursor no cabeçalho do arquivo de indice
  fseek(ind,0,SEEK_SET);
  
  int size;
  fread(&size,sizeof(int),1,ind);
  
  return size;
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

//Remove indice do arquivo de indices
void removeIndexFromFile(indice *i,indice **lista)
{
  if(openIndex())
  {
  //zera o contador da lista
  fseek(ind,0,SEEK_SET);
  
  int cont=0;
  
  //insere os indices, menos o que foi excluido
  fseek(ind,4,SEEK_SET);
  
  while(*lista!=NULL)
  {
    if((*lista)->id_locacao!=i->id_locacao)
    {
      fwrite(&(*lista)->id_locacao,sizeof(int),1,ind);
      fwrite(&(*lista)->offset,sizeof(int),1,ind);
      cont++;
    }
    
    *lista = (*lista)->prox;
  }
  
  fseek(ind,0,SEEK_SET);
  fwrite(&cont,sizeof(int),1,ind);
  fflush(ind);
  
  int x;
  fseek(ind,0,SEEK_SET);
  fread(&x,sizeof(int),1,ind);
  printf("\n lido %d\n",x);
  }
  
  closeIndex();
}
