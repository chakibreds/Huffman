#include"compression.h"
#include <string.h>

proba *tabproba(FILE *f,int *x,FILE *nf){
 	proba *tab;
 	tab=malloc(256*sizeof(proba));
	int *taille=malloc(sizeof(int));
	int chara=0;
  int nbc=0;
  *taille=0;
	//f=fopen("test.txt","r");
  if(f!=NULL){
  for(int j=0;j<256;j++)
  {
    tab[j].proba=0;

  }
chara=fgetc(f);
 while (chara!=EOF)
 {
 	int i=0;
 	while (i<*taille && tab[i].c!=chara)
  {i++;
	}
	if (i==*taille){tab[i].c=chara;tab[i].proba+=1;*taille+=1;}
	else{tab[i].proba+=1;}
  nbc+=1;
	chara=fgetc(f);
}


//nf=fopen("test.huf","w");
int nbchardiff=*taille;
unsigned char * chaine=malloc(8*sizeof(char));
FromDecimalToBin(nbchardiff,chaine,8);
unsigned char c = stringToBinary(chaine,0,8);
fprintf(nf,"%c",c);
fprintf(nf,"%c",0);
unsigned char buff1;
unsigned char buff2;
unsigned char buff3;
unsigned char buff4;
unsigned char * bin=malloc(8*sizeof(char));
unsigned char * occbin=malloc(32*sizeof(char));
for(int j=0;j<*taille;j++)
{

  FromDecimalToBin((int)tab[j].c,bin,8);

  buff1=stringToBinary(bin,0,8);
  fprintf(nf,"%c",buff1);

  FromDecimalToBin((int)tab[j].proba,occbin,32);
  buff1=stringToBinary(occbin,0,8);
  buff2=stringToBinary(occbin,8,8);
  buff3=stringToBinary(occbin,16,8);
  buff4=stringToBinary(occbin,24,8);
  /*fprintf(nf,"%c%c%c%c",buff1,buff2,buff3,buff4);
  printf("nbr occur : %f --> %s\n",tab[j].proba,occbin);*/
}

for(int j=0;j<*taille;j++)
{
	tab[j].proba=((tab[j].proba)/(nbc));
}
}
else printf("erreur d'ouverture du fichier\n");
*x=*taille;
return tab;
}


huff *intittab(FILE *f,int *y,FILE *nf)
{
//y=malloc(sizeof(int));
int *x=malloc(sizeof(int));
proba *tab=NULL;
tab=tabproba(f,x,nf);
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
huff *construct(FILE *f,int *taille,FILE *nf)
{
  huff *huffman=NULL;
  int *y=malloc(sizeof(int));
  huffman=intittab(f,y,nf);
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

  /*if(j==(*taille)-1)return 1;
  else return 5;*/
}
codage *tableau_de_codage(FILE *f,int *taille,FILE *nf)
{
  huff *huffman=NULL;

  int *taille_c=malloc(sizeof(int));
  huffman=construct(f,taille_c,nf);
  affiche_arbre(huffman,taille_c);
  codage *coder=malloc(((*taille_c+1)/2)*sizeof(codage));
  int i=0;
  while(i<*taille_c && huffman[i].fd==-1 && huffman[i].fg==-1)
  {
    int taille_code=0;
    coder[i].valeur=huffman[i].nom;
    coder[i].code=malloc(taille_code*sizeof(char));
    int j=huffman[i].pere;
    int precedent = i;
    while(j!=-1)
    {
      if(huffman[j].fg==precedent)
      {
        coder[i].code=realloc(coder[i].code,(1+taille_code)*sizeof(char));
        coder[i].code=strcat(coder[i].code,"0");
      }
      else
      {
        coder[i].code=realloc(coder[i].code,(1+taille_code)*sizeof(char));
        coder[i].code=strcat(coder[i].code,"1");
      }
      taille_code++;
      precedent=j;
      j=huffman[j].pere;
    }
    inversechaine(coder[i].code);
    i++;
  }
  *taille=(*taille_c+1)/2;
  return coder;
}
void inversechaine(char *chaine)
{
    int i,n;
    char lettre;

    n = strlen(chaine);

    for(i = 0;i <n/2;i++)
    {
        lettre = chaine[i];
        chaine[i] = chaine[n-i-1];
        chaine[n-i-1] = lettre;
    }
}
char * get_code(codage *coder,int *taille,char c)
{
  int i = 0;
  while (i<*taille && coder[i].valeur!=c)
  {
    i++;
  }
  return coder[i].code;
}
void codage_fichier(FILE *f,FILE *nf)
{
  int *taille =malloc(sizeof(int));
  int ziyada;
  unsigned char *chziyada=malloc(8*sizeof(char));
  codage *codehuff=NULL;
  codehuff=tableau_de_codage(f,taille,nf);
  afficher_tab_codage(codehuff,taille);
  //f=fopen("test.txt","r");
  fseek(f,0,SEEK_SET);

  if (f!=NULL)
  {
    char *code;
    char chara;
    unsigned char c;
    int i,j;
    unsigned char chaine[9]="22222222\0";
    chara=fgetc(f);
     while (chara!=EOF)
     {
       i=0;
       while(chaine[i]!='2')
       {
         i++;
       }
       code=get_code(codehuff,taille,chara);
       j=0;
       while(i<8 && j< strlen(code))

        {chaine[i]=code[j];
        i++;j++;
        }

        while ( (i == 8) || (j < strlen(code)))  {
          if (i == 8)// && j==strlen(get_code))
          {
            c=stringToBinary(chaine,0,8);
            fprintf(nf,"%c",c);
          //  printf("%s -- > %c\n",chaine,c);
            strcpy(chaine,"22222222\0");
            i = 0;
          }

          if(j<strlen(code))
          {
            while(i<8 && j< strlen(code)){
              chaine[i]=code[j];
              i++;
              j++;
            }

          }
        }
        chara = fgetc(f);


     }

     i=0;
     while(chaine[i]!='2')
     {
       i++;
     }
     if(i != 0)
     {ziyada = 8 - i;
     while (i < 8) {
         chaine[i] = '0';
         i++;
       }
     }
       else
       {ziyada = 0;}
       c=stringToBinary(chaine,0,8);
       fprintf(nf,"%c",c);
       //printf("%s -- > %c\n",chaine,c);

     //printf("ziyada : %d\n",ziyada );
     fseek(nf,1,SEEK_SET);
     FromDecimalToBin(ziyada,chziyada,8);
    // printf("ziyada : %s\n",chziyada);
     c = stringToBinary(chziyada,0,8);
     fprintf(nf,"%c",c);
      fseek(nf,0,SEEK_END);
      fseek(f,0,SEEK_END);
      printf("la taille originale du fichier : %ld\n",ftell(f));
      printf("la taille du fichier aprés compression : %ld\n",ftell(nf));
      printf("le gain en pourcentage : %.2f\n",(1-((float)ftell(nf)/ftell(f)))*100);
  }
  else
  printf("erreur d'ouvertuer du fichier \n");

}

void FromDecimalToBin(int chiffreDecimal,char* binaire,int nb_bits) {
	int leBinaire = 2;
	char tmp[60] = {0};
    int i = 0;
	int j=0;

    while (leBinaire <= chiffreDecimal)
        leBinaire *= 2;
    leBinaire /= 2;
    while (leBinaire != 0)
    {
        if (leBinaire <= chiffreDecimal)
        {
            tmp[i] = '1';
            chiffreDecimal -= leBinaire;
        }
        else {
            tmp[i] = '0';
        }
        ++i;
        leBinaire /= 2;
    }
    while (i < nb_bits) {
		binaire[j] = '0';
		++j;
		++i;
	}
	i = 0;
	while (j<nb_bits) {
		binaire[j] = tmp[i];
		++j;
		++i;
	}
	binaire[nb_bits] = '\0';
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
void afficher_tab_codage(codage *tab,int*taille)
{ float moy=0.0;
  int tout=0;
  printf("***affichage du tableau de codage***\n\n");
  for(int i=0;i<(*taille);i++)
  {
    if(tab[i].valeur=='\n')
    {
      printf("\\n--->%s\n",tab[i].code);
    }

  else {printf("%c-->%s\n",tab[i].valeur,tab[i].code);}
  tout+=strlen(tab[i].code);
}
moy=(float)tout/(*taille);
printf("la longueur moyenne du codage : %.2f\n",moy);
}
unsigned char stringToBinary(unsigned char * str,short int begin ,short int len)
{
    unsigned char code = 0;
    int i;
    for(i = begin; i < begin+len ; i++)
        code |= str[i] - '0' << (begin+len-1 - i);

    return code;
}
