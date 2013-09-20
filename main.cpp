/*
  PROJETO I - Estrutura de Dados II
  Locadora
  
  Alvaro Govone
  Vinicius Pfeifer
  
  Arquivos utilizados:
      principal.txt - Arquivo que salva os registros das locações
      index.txt - Arquivo que guarda a chave primaria(id) e o offset no arquivo principal
*/

#include <cstdlib>
#include <iostream>
#include "locacao.h"
#include "indice.h"

void menu();

int main()
{
  indice *indices = NULL;
  
  getAllIndexesOnFile(&indices);

    FILE *arq;
    
    unsigned int option = 0; //opção do usuário no menu
    
    indice *i;
    
    if(arq=fopen("principal.txt","a+"))
    {
      do
      {
        system("cls");
        
        printIndexes(indices);
        
        fflush(stdin);
        menu();
        
        printf("\n\nEscolha uma opcao : ");
        scanf("%d",&option);
        
        switch(option)
        {
          case 0:
            break;
          case 1:
            system("cls");
            
            printf("========= CADASTRO DE LOCACAO ==========\n\n");
            
            locacao l = readLocacao();
            
            saveLocacao(l,arq);
            
            //insere no indice
            i=(indice *)malloc(sizeof(indice *));
            i->id_locacao=l.id;
            i->offset=ftell(arq);
            i->prox = NULL;
            
            insertIndexOnFile(i);
            
            insertIndexOnList(&indices,i);
            
            break;
            
          default:
            printf("Opcao invalida!\n\n");
            system("PAUSE");
            break;
        }
      }while(option!=0);
      
    }
    else
    {
      printf("Erro ao abrir o arquivo!");
    }
    
    fclose(arq);
      
      return 1;
}

void menu()
{
  printf("========= LOCADORA UNESP ==========\n\n");
  printf("Menu:\n\n");
  printf("1. Cadastrar Locacao\n");
  printf("2. Alterar Locacao\n");
  printf("3. Remover Locacao\n");
  printf("4. Compactar arquivo\n");
  printf("5. Buscar pelo codigo da Locacao\n");
  printf("6. Buscar pelo nome do filme");   
}
