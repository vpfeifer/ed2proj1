#include "locacao.h"
#include "indice.h"

FILE *arq;

int openLocacao()
{
    if(!(arq=fopen("principal.txt","r+")))
    {
      if(!(arq=fopen("principal.txt","w+")))
        return 0;
    } 
      //Insere Cabeçalho inicial se não existir
      fseek(arq,0,SEEK_END);
      
      int pos = ftell(arq),nullValue=-1;
      
      if(pos==0)
        fwrite(&nullValue,sizeof(int),1,arq);
      
      return 1;
}

void closeLocacao()
{
  fclose(arq);
}

//Pede ao usuario para digitar uma locação e salva na struct locacao
locacao readLocacao(int id)
{
      locacao l;
        
      l.id=id;
        
      printf("\n");
      
      printf("Digite o nome do filme : ");
      fflush(stdin);
      gets(l.filme);

      printf("\n");
      
      printf("Digite o nome do cliente : ");
      gets(l.cliente);
      
      printf("\n");
      
      printf("Digite a data de devolucao : ");
      gets(l.data_devolucao);
      
      return l;
}

//Exibe na tela os dados de uma locacao
void viewLocacao(locacao l)
{
  printf("\n\n");
  
  printf("========== Locacao ==========\n\n");
  
  printf("ID : %d\n\nNome do filme : %s\n\nNome do cliente : %s\n\nData de devolucao : %s\n\n",l.id,l.filme,l.cliente,l.data_devolucao);

  printf("===================================");
  
  printf("\n\n");
}

//Grava locacao no arquivo no formato tamid|filme|cliente|devolucao
int saveLocacao(locacao l)
{
  fseek(arq,0,SEEK_END);
  
  int offset=ftell(arq);
  
  //separador
  char sep = '|';
  
  //manipula locacao para escrever |filme|cliente|data de devolução  
  int t = strlen(l.filme)+strlen(l.cliente)+strlen(l.data_devolucao)+3;
  
  char buffer[t];
  
  sprintf(buffer,"|%s|%s|%s",l.filme,l.cliente,l.data_devolucao);
  
  //seleciona o tamanho = 4 bytes do id + tamanho da string manipulada anteriormente
  int size = 4 + sizeof(buffer);
  
  //verifica se tem espaço na lista de disponiveis
  fseek(arq,0,SEEK_SET);//coloca o ponteiro no inicio do arquivo
  
  int prox=0,tam=0,oAnt=ftell(arq);
  
  //Lê o offset do primeiro item
  fread(&prox,sizeof(int),1,arq);
  
  if(prox!=-1)
  {
    //Coloca o ponteiro do arquivo na posição do primeiro elemento da lista
    fseek(arq,prox,SEEK_SET);
  
    //Procura por um espaço disponivel para o registro
    while(prox!=-1)
    {
      //Le o tamanho do espaço disponível
      fread(&tam,sizeof(int),1,arq);
      
      //Se couber no espaço
      if(size<=tam)
      {
        //Guarda onde deve ser salvo o novo registro
        offset=ftell(arq)-4;
        
        //Le o proximo
        fseek(arq,1,SEEK_CUR);
        fread(&prox,sizeof(int),1,arq);
        
        //Escreve o proximo no anterior para remover, o espaço que não está mais disponivel
        fseek(arq,oAnt,SEEK_SET);
        fwrite(&prox,sizeof(int),1,arq);
        
        prox=-1;
      }
      else
      {
        //Salva o offset do atual como anterior
        oAnt=prox;
        
        //Le o proximo
        fseek(arq,1,SEEK_CUR);
        fread(&prox,sizeof(int),1,arq);
      }
    }
  }
  
  //Coloca o ponteiro onde o registro será inserido
  fseek(arq,offset,SEEK_SET);
  
  //escreve tamanho no arquivo
  fwrite(&size,sizeof(int),1,arq);

  //escreve o id
  fwrite(&l.id,sizeof(l.id),1,arq);
  
  //escreve |filme|cliente|data de devolução no arquivo
  fwrite(&buffer,sizeof(buffer),1,arq);

  fflush(arq);
  
  return offset;
}

locacao findLocacaoByOffset(int offset)
{
  //Posiciona o ponteiro do arquivo para começar a ler
  fseek(arq,offset,SEEK_SET);
  
  //Lê o tamanho do registro
  int tam;            
  fread(&tam,sizeof(int),1,arq);
  
  //Lê o id da Locação
  int id;
  fread(&id,sizeof(int),1,arq);
  
  //Lê as strings do registro            
  char buffer[tam-4];
  fread(&buffer,sizeof(char),tam,arq);
  
  char * pch;
  char * arr[4];
  int i=1;
  
  pch = strtok (buffer,"|");
  arr[0] = pch;
  
  while (pch != NULL)
  {
    //printf ("%s\n",pch);
    pch = strtok (NULL, "|");
    arr[i]=pch;
    i++;
  }
  
  //Cria o objeto para retornar
  locacao l;
  
  l.id = id;
  strcpy(l.filme,arr[0]);
  strcpy(l.cliente,arr[1]);
  strcpy(l.data_devolucao,arr[2]);
  
  return l;
}

void insertInAvailableList(int offset)
{
  //coloca o ponteiro no cabeçalho do arquivo
  fseek(arq,0,SEEK_SET);
  
  //le o cabeçalho
  int prox;
  fread(&prox,sizeof(int),1,arq);
  
  //escreve o offset do novo primeiro elemento da lista de disponiveis
  fseek(arq,0,SEEK_SET);
  fwrite(&offset,sizeof(int),1,arq);
  
  //escreve <tamanho do registro>#<proximo elemento da lista>
  fseek(arq,offset+5,SEEK_SET);
  
  char sep='#';
  fwrite(&sep,sizeof(char),1,arq);
  
  fwrite(&prox,sizeof(int),1,arq);
  
  fflush(arq);
}

void updateLocacao(int offset,int newLength,locacao l)
{
                  fseek(arq,offset,SEEK_SET);
                
                fwrite(&newLength,sizeof(int),1,arq);
              
                fwrite(&l.id,sizeof(int),1,arq);
                
                char buffer[newLength-4];
                
                sprintf(buffer,"|%s|%s|%s",l.filme,l.cliente,l.data_devolucao);
                
                fwrite(&buffer,sizeof(buffer),1,arq);
}
