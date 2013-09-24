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
    
  unsigned int option = 0,aux=0;
    
  indice *i;
    
    if(openLocacao())
    {
      do
      {
        system("cls");
        
        printIndexes(indices);
        
        menu();
        
        printf("\n\nEscolha uma opcao : ");
        scanf("%d",&option);
        
        system("cls");
                    
        switch(option)
        {
          case 0:
            break;
          case 1:
            
            printf("========= CADASTRO DE LOCACAO ==========\n");
            
            printf("\nDigite o codigo da locacao : ");
            scanf("%d",&aux);
            
            i = findIndexByID(indices,aux);
            
            if(i!=NULL)
              printf("\n\nCodigo ja existe!\n\n");
            else
            {
              locacao l = readLocacao(aux);
            
              aux = saveLocacao(l);
            
              //insere no indice
              i=(indice *)malloc(sizeof(indice));
              i->id_locacao=l.id;
              i->offset=aux;
              i->prox = NULL;
            
              insertIndexOnFile(i);
            
              insertIndexOnList(&indices,i);
            
              printf("\n\nLocacao salva com sucesso!\n\n");
            }
            break;
          
          case 2:
            
            printf("========= ALTERAR LOCACAO ==========\n\n");
            
            printf("Digite o ID da locacao que deseja alterar : ");
            scanf("%d",&aux);
            
            
            i = findIndexByID(indices,aux);
            
            if(i==NULL)
              printf("\n\nLocacao nao encontrada\n\n!");
            else
            { 
              locacao l = findLocacaoByOffset(i->offset);
              
              int oldLength = 7+strlen(l.filme)+strlen(l.cliente)+strlen(l.data_devolucao);
              
              printf("\n\n1. Filme\n");
              printf("2. Cliente\n");
              printf("3. Data de Devolucao\n");  
              
              printf("\n\nEscolha o campo que deseja alterar: ");
              
              scanf("%d",&aux);
              
              char newValue[255];
              printf("\n\nDigite o novo valor: ");
              fflush(stdin);
              gets(newValue);
              
              switch(aux)
              {
                case 1:
                  strcpy(l.filme,newValue);
                  break;
                case 2: 
                  strcpy(l.cliente,newValue);
                  break;
                case 3:
                  strcpy(l.data_devolucao,newValue);
                  break;
              }
              
              int newLength = 7+strlen(l.filme)+strlen(l.cliente)+strlen(l.data_devolucao);
              
              if(newLength<=oldLength)
              {
                //insere no mesmo lugar
                updateLocacao(i->offset,newLength,l);
              }
              else
              {
               //exclui e insere denovo
                
              insertInAvailableList(i->offset);

              removeIndexFromFile(i,&indices);
              
              indices=NULL;
              
              getAllIndexesOnFile(&indices);
              
              aux = saveLocacao(l);
            
              i=(indice *)malloc(sizeof(indice));
              i->id_locacao=l.id;
              i->offset=aux;
              i->prox = NULL;
            
              insertIndexOnFile(i);
            
              insertIndexOnList(&indices,i);
              }
            }
          
            printf("\nLocacao alterada com sucesso!\n");
          
          break;
          
          case 3:
            
            printf("========= REMOVER LOCACAO ==========\n\n");
            
            printf("Digite o ID da locacao que deseja remover : ");
            scanf("%d",&aux);
            
            
            i = findIndexByID(indices,aux);
            
            if(i==NULL)
              printf("\n\nLocacao nao encontrada\n\n!");
            else
            { 
              insertInAvailableList(i->offset);

              removeIndexFromFile(i,&indices);
              
              indices=NULL;
              
              getAllIndexesOnFile(&indices);
            }
           
           printf("\nLocacao removida com sucesso!\n");
           
          break;
          
          case 4:
            
              printf("========= COMPACTAÇÃO DO ARQUIVO ==========\n\n");
            
              printf("Em construção...\n\n");
              
              //compactar();
          
          break;  
                    
          case 5:
            
            printf("========= BUSCAR LOCACAO POR ID ==========\n\n");
            
            printf("Digite o ID da locacao que deseja buscar : ");
            scanf("%d",&aux);
            
            i = findIndexByID(indices,aux);
            
            if(i==NULL)
              printf("\n\nLocacao nao encontrada\n\n!");
            else
            { 
              locacao l = findLocacaoByOffset(i->offset);
              
              viewLocacao(l);  
            }
            
            break;
          
          case 6:
              
              printf("========= BUSCAR LOCACAO PELO FILME ==========\n\n");
            
              printf("Em construção...");
          
          break;  
          
          default:
            printf("Opcao invalida!\n\n");
            break;
        }
        
        if(option!=0)
          system("PAUSE");
      }while(option!=0);
      
    }
    else
    {
      printf("Erro ao abrir o arquivo!");
    }
    
    closeLocacao();
    
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
  printf("6. Buscar pelo nome do filme\n");
  printf("0. Sair");   
}
