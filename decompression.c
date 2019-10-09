#include"decompression.h"
#include <string.h>




proba * lireEntete(FILE *f,int *taille,FILE *nf,int *ziyada)
{

  char chara;
  int nbc=0;
  char *chaine=malloc(9*sizeof(char));
  char *chaine2=malloc(9*sizeof(char));
  /*char *chaine3=malloc(8*sizeof(char));
  char *chaine4=malloc(8*sizeof(char));
  char *occur=malloc(32*sizeof(char));
  char *occur2=malloc(16*sizeof(char));
  char *occur1=malloc(16*sizeof(char));*/
  int *z=malloc(sizeof(int));

  if(f!=NULL)
  {


      chara= fgetc(f);
      chaine=charToBinary(chara);
    //  printf("la taille en chaine : %s\n",chaine);


    int t=0;
    int *x=malloc(sizeof(int));
    *taille=FromBinToDecimal(chaine,8);
  //  printf("la taille : %d\n",*taille);
    /**x=t;
    *taille=*x;*/
    proba *tab=malloc((*taille)*sizeof(proba));
    chara =fgetc(f);
    chaine=charToBinary(chara);
    *ziyada=FromBinToDecimal(chaine,8);
    /**z=t;
    *ziyada=*z;*/
    int i=0;
    while(i<*taille)
    {


        chara= fgetc(f);
        chaine=charToBinary(chara);

        tab[i].c=(char)FromBinToDecimal(chaine,8);
        //printf("le char : %c\n",tab[i].c);

        chaine2 = malloc(9*sizeof(char));
        for (int j=0;j<4;j++)
        {
          chara= fgetc(f);
          chaine=charToBinary(chara);
          chaine2=strcat(chaine2,chaine);
          //printf("%s --> %s\n",chaine,chaine2);
        }
            /*chara=fgetc(f);
            chaine=charToBinary(chara);
            printf("ch1 : %s\n",chaine);
            chara=fgetc(f);
            chaine2=charToBinary(chara);
            printf("ch2 : %s\n",chaine2);
            occur1=strcat(chaine2,chaine);
            printf("ch3 : %s\n",occur1);
            chara=fgetc(f);
            chaine3=charToBinary(chara);
            printf("ch4 : %s\n",chaine3);
            chara=fgetc(f);
            chaine4=charToBinary(chara);
            printf("ch5 : %s\n",chaine4);
            occur2=strcat(chaine3,chaine4);
            printf("ch6 : %s\n",occur2);
            occur=strcat(occur1,occur2);
            printf("ch7 : %s\n",occur);*/



          tab[i].proba=FromBinToDecimal(chaine2,32);

          nbc+=(int)tab[i].proba;
          //printf("le nbr de char : %d\n",nbc);
          i++;
    }
    for(int j=0;j<*taille;j++)
    {
      tab[j].proba=tab[j].proba/(nbc);
    }
    return tab;

  }
  else printf("erreur d'ouverture du fichier\n");

}


huff *intittab(FILE *f,int *y,FILE *nf,int *ziyada)
{
  int *x=malloc(sizeof(int));
  int *z=malloc(sizeof(int));
  proba *tab=NULL;
  tab=lireEntete(f,x,nf,z);
  *ziyada=*z;
  affiche_tab_proba(tab,x);
  *y=(*x);
  huff *huffman=malloc((*y)*sizeof(huff));
  for(int i=0;i<(*x);i++)
  {
    huffman[i].nom=tab[i].c;
    huffman[i].proba=tab[i].proba;
    huffman[i].pere=-1;
    huffman[i].fd=-1;
    huffman[i].fg=-1;
  }
  return huffman;
}


huff *construct(FILE *f,int *taille,FILE *nf,int *ziyada)
{
  huff *huffman=NULL;
  int *y=malloc(sizeof(int));
    int *z=malloc(sizeof(int));

  huffman=intittab(f,y,nf,z);
  *ziyada=*z;
  //printf("la taille : %d\n",*y);
 int *p=malloc(sizeof(int));
*p=*y;


  int a,b,k;
do {
  b=min(huffman,y,-1);
    //  printf("le i : %d\n",b);
  a=min(huffman,y,b);
    //printf("le j : %d\n",a);


      huffman=realloc(huffman,(*y+1)*sizeof(huff));
      *y=*y+1;
      k=*y-1;

      //printf("le k : %d\n",k);
      huffman[k].proba=huffman[b].proba+huffman[a].proba;
      huffman[k].pere=-1;
      huffman[k].fd=b;
      huffman[k].fg=a;
      huffman[b].pere=k;
      huffman[a].pere=k;

} while(*y<2*(*p)-1);

  //}

*taille=*y;
return huffman;
}

void affiche_tab_proba(proba *tab,int *taille)
{
  printf("***affichage du tableau des probabilités***\n\n");
  for(int i=0;i<(*taille);i++)
  {
    if(tab[i].c=='\n')
    {
      printf("\\n--->");
    }

  else printf("%c--->",tab[i].c);
  printf("%f\n",tab[i].proba );
  printf("\n\n");
}
}


void affiche_arbre(huff *tab,int *taille)
{
  printf("\n\n");
  printf("***affichage de l'arbre de huffman***\n\n");
  for(int i=0;i<(*taille);i++)
  {
    if(tab[i].nom=='\n')
    {
      printf("\\n--->");
    }

  else printf("%c--->",tab[i].nom);
  printf("%f\n",tab[i].proba );
  printf("pere--->%d\n",tab[i].pere );
  printf("filsD--->%d\n",tab[i].fd );
  printf("filsG--->%d\n",tab[i].fg );
  printf("\n\n");

}
}




int FromBinToDecimal(char* binaire,int nb_bits) {
	int decimal = 0;
	int i = nb_bits - 1;
	int k = 1;
	while(i >= 0) {
		if (binaire[i] == '1')
			decimal += k;
		k *= 2;
		--i;
	}
	return decimal;
}

int min(huff *huffman,int *taille,int differente)
{
  int temp=0;
  int j=0;
  float pp =2.0;
  while(j<(*taille) )
  {
    if((pp > huffman[j].proba)  && (huffman[j].pere == -1) && (j != differente) ) {
      pp = huffman[j].proba;
      temp = j;
    }
    j++;
  }
  if (pp == 2.0)
    temp = -1;
  return temp;
}
void decodage(FILE *f,FILE *nf,int *ziyada)
  {
    int *taille=malloc(sizeof(int));
      int *z=malloc(sizeof(int));
    huff *huffman=construct(f,taille,nf,z);
    *ziyada = *z ;
    affiche_arbre(huffman,taille);
    unsigned char * chaine=malloc(8*sizeof(char));
    char chara;
    FILE *temp = fopen(".huffmantemp","w");
    //fseek(f,0,SEEK_SET);
    chara = fgetc(f);
    int nbc=0;
    //printf("tell : %ld\n",ftell(f));
    while (feof(f) == 0)
    {
      chaine=charToBinary(chara);
      fputs(chaine,temp);
      chara=fgetc(f);
      nbc+=8;
    //  printf("OK\n");
    }
    int i=*taille-1;
    fclose(temp);
    temp = fopen(".huffmantemp","r");
    chara = fgetc(temp);
    int j=0;
    //printf("le moins : %d\n",nbc-*ziyada);
    while(chara!=EOF && j<(nbc-*ziyada))
    {
      if(chara=='0')
      {
        i=huffman[i].fg;
      }
      else
      {
        i=huffman[i].fd;
      }
      //printf("%c\n",chara);
      if(huffman[i].fg==-1 || huffman[i].fd==-1)
      { if (nf != NULL)
        fprintf(nf,"%c",huffman[i].nom );
        else {printf("%c",huffman[i].nom );}
        i=*taille-1;
      }

      chara = fgetc(temp);
      j++;
    }
    remove(".huffmantemp");
  }
  char *charToBinary(char c)
  {
    int d,compteur;
    char *Tbin;
    compteur=0;
    Tbin=malloc(9*sizeof(char));
    for (int i=7 ; i>= 0;i--)
    {
      d = c >> i;
      if(d & 1)
      Tbin[compteur] = 1 + '0';
      else
      Tbin[compteur] = 0 + '0';
      compteur ++;
    }
    Tbin[compteur] = '\0';
    return Tbin;
  }
