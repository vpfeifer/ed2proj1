#include "secind.h"
#include "listinv.h"

FILE *secInd;

int openSecIndex()
{
    if(!(secInd=fopen("secondaryIndex.txt","r+")))
    {
      if(!(secInd=fopen("secondaryIndex.txt","w+")))
        return 0;
    }
    
    return 1;
}

void closeSecIndex()
{
  fclose(secInd);
}

void insereSecundario(char *filme,unsigned int id)
{
  if(openSecIndex())
  {
    rewind(secInd);
    
    secIndex si,asi;
    
    int ax=0;
    
    while(fread(&si,sizeof(secIndex),1,secInd))
    {
      if(!strcmp(filme,si.filme))
      {
        asi=si;
        ax=1;
      }
    }
    
    if(ax==0)
    {
      fseek(secInd,0,SEEK_END);
      
      secIndex isi;
      isi.filme=filme;
      
      isi.listOffset = insereListaInvertida(id,-1);
      
      fwrite(&isi,sizeof(secIndex),1,secInd);
    }
    else
    {
      insereListaInvertida(id,asi.listOffset);
    }
    
  }
  
  closeSecIndex();
}

secIndex * buscaIndiceSecundario(char *filme)
{
  secIndex *si=NULL;
  
  if(openSecIndex())
  {           
    while(fread(si,sizeof(secIndex),1,secInd))
    {
      if(!strcmp(filme,si->filme))
          break;
    }
  
    closeSecIndex();
  }
  
  return si;
}
