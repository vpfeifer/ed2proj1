#include "locacao.h"
#include "indice.h"

//Pede ao usuario para digitar uma locação e salva na struct locacao
locacao readLocacao()
{
      locacao l;

      printf("Digite o ID da locacao : ");
      scanf("%d",&l.id);
        
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
int saveLocacao(locacao l,FILE *arq)
{
  fseek(arq,0,SEEK_END);
  
  int offset = ftell(arq);
  
  //separador
  char sep = '|';
  
  //manipula locacao para escrever |filme|cliente|data de devolução  
  int t = strlen(l.filme)+strlen(l.cliente)+strlen(l.data_devolucao)+3;
  
  char buffer[t];
  
  sprintf(buffer,"|%s|%s|%s",l.filme,l.cliente,l.data_devolucao);
  
  //seleciona o tamanho = 4 bytes do id + tamanho da string manipulada anteriormente
  int size = 4 + sizeof(buffer);
  
  //escreve tamanho no arquivo
  fwrite(&size,sizeof(int),1,arq);

  //escreve o id
  fwrite(&l.id,sizeof(l.id),1,arq);
  
  //escreve |filme|cliente|data de devolução no arquivo
  fwrite(&buffer,sizeof(buffer),1,arq);

  printf("\n\nLocacao salva com sucesso!\n\n");
  
  system("PAUSE");
  
  return offset;
}
