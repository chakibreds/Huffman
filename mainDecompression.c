#include "decompression.h"
int main (int argc , char **argv)
{
  FILE *fichier=NULL;
  FILE *newfichier=NULL;
  if (argc<2)
  {
    printf("pas d'arguments\n");
    exit(1);
  }
  huff *huffdec = NULL;
  int *taille=malloc(sizeof(int));
  int *z=malloc(sizeof(int));
  fichier=fopen(argv[1],"r");
  if (argc == 3)
    newfichier=fopen(argv[2],"w");
  else
    newfichier = NULL;
  decodage(fichier,newfichier,z);


}
