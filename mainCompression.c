#include "compression.h"
int main (int argc , char **argv)
{
/*  //printf("chakib");
  FILE *fichier=NULL;
  FILE *newfichier = NULL;
  proba *tableau;
  int *x=malloc(sizeof(int));
  tableau=tabproba(fichier,x,newfichier);
  for(int i=0;i<(*x);i++)
  {
  printf("%c--->",tableau[i].c) ;
  printf("%f\n",tableau[i].proba );
}
 huff *huffman=NULL;
  int *y=malloc(sizeof(int));
  //printf("chakib");
  huffman=intittab(fichier,y,newfichier);
  //printf("chakib");

  for(int i=0;i<(*y);i++)
  {
  printf("%c--->",huffman[i].nom) ;
  printf("%f\n",huffman[i].proba );
  printf("pere--->%d\n",huffman[i].pere );
  printf("filsD--->%d\n",huffman[i].fd );
  printf("filsG--->%d\n",huffman[i].fg );
  printf("\n\n");
}

huff *hufftest=NULL;
int *z=malloc(sizeof(int));
hufftest=consruct(fichier,z,newfichier);
for(int i=0;i<(*z);i++)
{
  printf("%d) \n",i);
printf("%c--->",hufftest[i].nom) ;
printf("%f\n",hufftest[i].proba );
printf("pere--->%d\n",hufftest[i].pere );
printf("filsD--->%d\n",hufftest[i].fd );
printf("filsG--->%d\n",hufftest[i].fg );
printf("\n\n");
}
printf("\n");

/*double c,d;
d=0.0007;c=0.0007;
if(c<=d)
{
  printf("return 1\n");
}
else printf("return 0\n");*/

/*int *taille =malloc(sizeof(int));
codage *codehuff=NULL;
codehuff=tableau_de_codage(fichier,taille,newfichier);
for(int i = 0;i<*taille;i++)
{
  printf("%c-->%s\n",codehuff[i].valeur,codehuff[i].code);
}
FILE *nf=NULL;
codage_fichier(fichier,newfichier);*/
FILE *fichier=NULL;
FILE *newfichier=NULL;
if (argc<3)
{
  printf("pas d'arguments");
  exit(1);
}
fichier=fopen(argv[1],"r");
newfichier=fopen(argv[2],"w");
codage_fichier(fichier,newfichier);


}
