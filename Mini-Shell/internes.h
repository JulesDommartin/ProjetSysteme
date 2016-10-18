#ifndef INTERNES_H
#define INTERNES_H

#define NB_MOTS_MAX 20 // Limite le nombre de mots pour echo

#include "ligne.h"
#include "job.h"

// Implémentation de cd
int cd(char* arg);

// Implémentation de echo
int echo(char** mots);

// Implémentation de kill_job (on ne peut pas l'appeler 'kill' car elle existe déjà dans signal.h)
int kill_job(char* num, ensemble_job_t *jobs);

// Exécute une commande interne
int commande_interne(ligne_analysee_t* ligne_analysee, ensemble_job_t *jobs);

#endif

