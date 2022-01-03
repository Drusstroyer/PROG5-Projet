#ifndef __BFILE__
#define __BFILE__

#include <stdio.h>
#include <stdint.h>

typedef struct {
uint8_t donnees;
char nombre;
char mode;
char last;
FILE *fichier;
} BFILE;

/*
   bstart
   description : démarre un accès bit à bit au fichier dont le descripteur est
  		 passé en paramètre (le fichier doit avoir été préalablement
		 ouvert).
                 Pour conserver la cohérence des données, aucun accès non bit à
                 bit au même descripteur ne doit être fait jusqu'au prochain
                 bstop.
   paramètres : descripteur du fichier, le mode dans lequel le descripteur est
   		ouvert.
   valeur de retour : pointeur vers une structure BFILE allouée par bstart
                      ou NULL si une erreur est survenue
   effets de bord : aucun (outre l'allocation)
*/
BFILE *bstart(FILE *fichier, const char *mode);

/*
   bstop
   description : termine un accès bit à bit à un fichier préalablement démarré
  		 par bstart (termine les E/S en attente et libère la structure
                 BFILE).
   paramètres : pointeur vers une structure BFILE renvoyée par bstart
   valeur de retour : 0 si aucune erreur n'est survenue
   effets de bord : écrit potentiellement dans le fichier
*/
int bstop(BFILE *fichier);

/*
   bitread
   description : lit un bit dans un fichier sur lequel un accès bit à bit
                 a été préalablement démarré a l'aide de bstart.
   paramètres : pointeur vers une structure BFILE renvoyée par bstart
   valeur de retour : bit lu ou -1 si une erreur s'est produite ou si la
                      fin de fichier a été atteinte
   effets de bord : la valeur de retour dépend du contenu du fichier
                    lit potentiellement dans le fichier
*/
char bitread(BFILE *fichier);

/*
   bitwrite
   description : écrit un bit dans un fichier sur lequel un accès bit à bit
                 a été préalablement démarré à l'aide de bstart.
   paramètres : pointeur vers une structure BFILE renvoyée par bstart, bit à
                écrire
   valeur de retour : -1 si une erreur s'est produite
   effets de bord : écrit potentiellement dans le fichier
*/
int bitwrite(BFILE *fichier, char bit);

/*
   beof
   description : retourne 1 si un accès en lecture préalable a échoué pour
                 cause d'atteinte de la fin d'une séquence de bits (fin de
                 fichier ou fin de séquence codée dans le fichier), 0 sinon.
                 L'accès bit à bit doit avoir été préalablement démarré à
		 l'aide de bstart.
   paramètres : pointeur vers une structure BFILE renvoyée par bstart
   valeur de retour : 1 ou 0
   effets de bord : aucun.
*/
int beof(BFILE *fichier);

#endif
