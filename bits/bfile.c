#include "bit_operations.h"
#include "bfile.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define DELIMITEUR '@'
#define READ 0
#define WRITE 1

#ifdef FIN_DYNAMIQUE
int ecrire_fin(FILE *fichier, int nombre, uint8_t octet) {
	int resultat = EOF;

	if ((nombre >= 0) && (nombre <= 8)) {
		/* protocole de fin (directive de taille restante) */
		resultat = fputc(DELIMITEUR,fichier);
		if (resultat != EOF)
			fputc(nombre+'0',fichier);
		if ((nombre > 0) && (resultat != EOF))
			fputc(octet, fichier);
	} else
		/* Sinon bug, écrire fin écrit un sous ensemble de bits d'un octet */
		assert(0);
	return resultat;
}

char lire_octet(FILE *fichier, uint8_t *octet) {
	char nombre = 8;
	int resultat;
       
	resultat = fgetc(fichier);
	if (resultat == EOF)
		/* Bug, la fin devrait être marquée par une directive */
		assert(0);
	/* Decodage du protocole de trames */
	if (resultat == DELIMITEUR) {
		resultat = fgetc(fichier);
		if (resultat == EOF)
			/* Bug, une directive fait deux caractères */
			assert(0);
		if (resultat == DELIMITEUR) {
			*octet = resultat;
		} else {
			resultat -= '0';
			if ((resultat >= 0) && (resultat <= 8)) {
				nombre = resultat;
				resultat = fgetc(fichier);
				if (resultat == EOF)
					/* Bug, il manque les données de fin */
					assert(0);
				*octet = resultat;
			} else
				/* Bug si resultat n'est pas entre 1 et 8 */
				assert(0);
		}
	} else
		*octet = resultat;
	return nombre;
}

int ecrire_octet(FILE *fichier, uint8_t octet) {
	int resultat; 

	/* gestion du protocole des directives */
	if (octet == DELIMITEUR) {
		resultat = fputc(DELIMITEUR, fichier);
		if (resultat == EOF)
			/* Erreur d'ecriture */
			return resultat;
	} 
	resultat = fputc(octet, fichier);
	return resultat;
}
#else
int ecrire_fin(FILE *fichier, int nombre, uint8_t octet) {
	if (nombre > 0)
		return fputc(octet, fichier);
	else
		return octet;
}

char lire_octet(FILE *fichier, uint8_t *octet) {
	int resultat;
       
	resultat = fgetc(fichier);
	if (resultat == EOF)
		return -1;
	else {
		*octet = resultat;
		return 8;
	}
}

int ecrire_octet(FILE *fichier, uint8_t octet) {
	return fputc(octet, fichier);
}
#endif

BFILE *bstart(FILE *fichier, const char *mode) {
	BFILE *resultat;

	resultat = (BFILE *) malloc(sizeof(BFILE));
	if (resultat == NULL)
		return NULL;
	resultat->fichier = fichier;
	if (strcmp(mode,"r") == 0) {
		resultat->mode = READ;
		resultat->last = 0;
		resultat->nombre = 0;
	} else
		if (strcmp(mode,"w") == 0) {
			resultat->mode = WRITE;
			resultat->nombre = 0;
		} else {
			assert(0);
		}
	return resultat;
}

int bstop(BFILE *fichier) {
	int resultat=0;

	if (fichier->mode == WRITE) {
		resultat = ecrire_fin(fichier->fichier, fichier->nombre, fichier->donnees);
	}
	free(fichier);
 
	return resultat;
}
	
char bitread(BFILE *fichier) {
	assert(fichier->mode == READ);
	/* On remplit le buffer si necessaire */
	if (fichier->nombre < 1) {
		if (!fichier->last) {
			fichier->nombre = lire_octet(fichier->fichier, &fichier->donnees);
			fichier->last = (fichier->nombre < 8);
		} else
			fichier->nombre = -1;
		if (fichier->nombre < 1)
			return -1;
	}
	/* Si on arrive jusqu'ici, c'est qu'il y a encore des donnees */
	fichier->nombre--;
	return get_bit(fichier->donnees, fichier->nombre);
}

int bitwrite(BFILE *fichier, char bit) {
	int resultat = 0;

	assert(fichier->mode == WRITE);
	fichier->nombre++;
	fichier->donnees = fichier->donnees << 1;
	switch (bit) {
		case 0:
			fichier->donnees = clr_bit(fichier->donnees, 0);
			break;
		case 1:
			fichier->donnees = set_bit(fichier->donnees, 0);
			break;
		default:
			/* Bug, un bit est soit 0, soit 1 */
			assert(0);
	}
	if (fichier->nombre == 8) {
		resultat = ecrire_octet(fichier->fichier, fichier->donnees);
		fichier->nombre = 0;
	}
	return resultat;
}

int beof(BFILE *fichier)
{
	return (fichier->nombre < 0);
}
