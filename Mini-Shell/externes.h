#ifndef EXTERNES_H
#define EXTERNES_H

#include "ligne.h"
#include "job.h"

//Exécute les commandes 
void executer_commande_dans_un_fils(job_t* job, int numero_commande, ligne_analysee_t* ligne_analysee, struct sigaction *sigact, int is_background);


//Exécute les commandes externes
void executer_commandes(job_t* job, ligne_analysee_t* ligne_analysee, struct sigaction *sigact, int is_background);

#endif
