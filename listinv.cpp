#include "listinv.h"
#include "locacao.h"

FILE *listinv;

int openListaInvertida()
{
    if(!(listinv=fopen("listaInvertida.txt","r+")))
    {
      if(!(listinv=fopen("listaInvertida.txt","w+")))
        return 0;
    }
    
    return 1;
}

void closeListaInvertida()
{
  fclose(listinv);
}

int insereListaInvertida(unsigned int id,int list)
{
  if(openListaInvertida())
  {
    int ret=0;
    
    if(list==-1)
    {
      fseek(listinv,0,SEEK_END);
      
      ret=ftell(listinv);
      
      listai li;
      li.id=id;
      li.prox=-1;
      
      fwrite(&li,sizeof(listai),1,listinv);
    }
    else
    {
      fseek(listinv,list,SEEK_SET);
      
      listai li;
      
      int anteriorOffset=ftell(listinv);
      
      while(fread(&li,sizeof(listai),1,listinv))
      {
        if(li.prox!=-1)
        {
          fseek(listinv,li.prox,SEEK_SET);
          int anteriorOffset=ftell(listinv);          
        }
        else
        {
          break;
        }
      }
      
      fseek(listinv,0,SEEK_END);
      
      int offsetNovo = ftell(listinv);
      
      listai nli;
      nli.id=id;
      nli.prox=-1;
            
      fwrite(&nli,sizeof(int),1,listinv);
      
      li.prox=offsetNovo;
      
      fseek(listinv,anteriorOffset,SEEK_SET);
      
      fwrite(&li,sizeof(listai),1,listinv);
    }
  
    closeListaInvertida();
  }
  
}

