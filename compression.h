#ifndef COMPRESSION_H_
#define COMPRESSION_H_
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
	//une structure pour construire le tableau de codage composée de char et ça chaine en 0 et 1
	typedef struct codage codage;
	struct codage{
		char valeur;
		char *code;
	};
/* un fonction qui retourne un tableau de structure de proba
en realité cette fonction calcul le tableau de proba et ecrit l'entete dans le fichier
de compression*/
proba *tabproba(FILE *f,int *x,FILE *nf);
/*initialise l'arbre de huffman avec père -1 fg -1 fd -1*/
huff *intittab(FILE *f,int *y,FILE *nf);
/*construit l'arbre de huffman*/
huff *construct(FILE *f,int *taille,FILE *nf);
/*calcul le min dans un arbre de huffman et prends en considération n'a pas de pére et
different de DIFFERENTE passée en paramètres*/
int min(huff *huffman,int *taille,int differente);
/*calcul le tableau de codage un char avec son code*/
codage *tableau_de_codage(FILE *f,int *taille,FILE *nf);
/*inverse une chaine de char par exemple 100 devient 001*/
void inversechaine(char *chaine);
/*ecrit dans le fichier le codage binaire de chaque char*/
void codage_fichier(FILE *f,FILE *nf);
/*retourne le code du char passé en paramètres*/
char * get_code(codage *coder,int *taille,char c);
/*comme son nom l'indique d'un nombre décimal on passe à une chaine de binaire */
void FromDecimalToBin(int chiffreDecimal,char* binaire,int nb_bits);
/*de chaine vers le vrai binaire on lui donne le debut et la taille
en paramètres elle retourne un char de 8bits*/
unsigned char stringToBinary(unsigned char * str,short int begin ,short int len);
/*affiche tableau de proba*/
void affiche_tab_proba(proba *tab,int *taille);
/*affiche l'arbre de huffman*/
void affiche_arbre(huff *tab,int *taille);
/*affiche le tableau de codage */
void afficher_tab_codage(codage *codage,int*taille);



#endif
