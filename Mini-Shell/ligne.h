#ifndef LIGNE_H
#define LIGNE_H

#define NB_MAX_COMMANDES 3 // nb max de commandes sur une ligne
#define NB_MAX_MOTS 30     // nb max de mots pour une commande
#define NB_MAX_CAR 4096    // nb max de caractères dans une ligne

typedef struct ligne_analysee_t
{
  int    nb_fils;			           // nb de fils à créer pour la ligne reçue
  char*  commandes[NB_MAX_COMMANDES][NB_MAX_MOTS]; // contient les mots des différentes commandes
  char   ligne[NB_MAX_CAR];			   // contient la ligne d'entrée
} ligne_analysee_t;

// Lit la ligne de commande
void lit_ligne(ligne_analysee_t *ligne_analysee);

// fonction qui découpe la commande
int decoupe_commande(char **a_debut, ligne_analysee_t *ligne_analysee);

// fonction qui extrait chaque ligne de commande
int extrait_commande(ligne_analysee_t *ligne_analysee);

#endif
