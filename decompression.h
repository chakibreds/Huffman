#ifndef DECOMPRESSION_H_
#define DECOMPRESSION_H_
#include <stdio.h>
#include<stdlib.h>
//une structure composée de un char et une probabilité pour construire le tableau de proba
typedef struct proba proba ;
struct proba{
	char c;
	double proba;
};
//une structure pour construire l'arbre de huffman
typedef struct huff huff;
struct huff {
	char nom;
	int pere,fd,fg;
	double proba;
};
/*lit l'entete et retourne le tableau de proba de chaque char */
proba * lireEntete(FILE *f,int *taille,FILE *nf,int *ziyada);
/*intialise le tableau de huffman avec pere -1 fd -1 fg -1*/
huff *intittab(FILE *f,int *y,FILE *nf,int *ziyada);
/*construit l'arbre de huffman*/
huff *construct(FILE *f,int *taille,FILE *nf,int *ziyada);
/*affiche tableau de proba*/
void affiche_tab_proba(proba *tab,int *taille);
/*affiche l'arbre de huffman*/
void affiche_arbre(huff *tab,int *taille);
/*comme son nom l'indique de chaine de binaire vers un int */
int FromBinToDecimal(char* binaire,int nb_bits);
/*calcul le tableau de codage un char avec son code*/
int min(huff *huffman,int *taille,int i);
/*decompressse et ecrit dans le fichier le meme contenu que
 le fichier avant la compression */
void decodage(FILE *f,FILE *nf,int *ziyada);
/*de char vers une chaine des 0 et des 1*/
char *charToBinary(char c);
#endif
