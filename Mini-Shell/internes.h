#ifndef INTERNES_H
#define INTERNES_H

#define NB_MOTS_MAX 20 // Limite le nombre de mots pour echo

#include "ligne.h"

// Implémentation de cd
int cd(char* arg);

// Implémentation de echo
int echo(char** mots);

// Exécute une commande interne
int commande_interne(ligne_analysee_t* ligne_analysee);

#endif

