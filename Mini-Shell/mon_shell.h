#ifndef MON_SHELL_H
#define MON_SHELL_H

#include <signal.h>
#include "job.h"

// Affiche l'invite de commande
void affiche_invite(void);

// Execute une ligne de commande
int execute_ligne(ligne_analysee_t *ligne_analysee, ensemble_job_t *jobs, struct sigaction *sigact);

// Traitement des signaux
void traitement_signal(int sig);

// Initialise la gestion des signaux avec la structure sigaction
void initialiser_signaux(struct sigaction *sigact);
#endif
