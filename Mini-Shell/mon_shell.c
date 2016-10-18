#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "internes.h"
#include "ligne.h"
#include "externes.h"
#include "job.h"
#include "mon_shell.h"



// A envoyer à Philippe.Bidimger@imag.fr
// Sujet: [MIAGE]Gueze/Dommartin
// Avant jeudi 20 octobre 23h59

static ensemble_job_t jobs;

// Affiche l'invite de commande
void affiche_invite(void) {
	char* rep_courant;
	rep_courant = get_current_dir_name();
	if( rep_courant != NULL ) {
		printf("%s", rep_courant);
	} else {
		printf("Répertoire inconnu");
	}

	printf("> ");
	fflush(stdout);
}

// Execute une ligne de commande
int execute_ligne(ligne_analysee_t *ligne_analysee, ensemble_job_t *jobs, struct sigaction *sigact) {
	int is_background = 0;
	if ((is_background = extrait_commande(ligne_analysee)) == -1) {
		return -1;
	} else {
		
		// S'il ne s'agit pas d'une commande interne au shell,
		// La ligne est exécutée par un ou des fils
		if (! commande_interne(ligne_analysee, jobs) ) {
			job_t *job = jobs->jobs;
		
			// Suspension des signaux
			sigact->sa_handler = SIG_IGN;
			sigaction(SIGINT, sigact, NULL);
			// Exécute les commandes de la ligne par des fils
			executer_commandes(job, ligne_analysee, sigact, is_background);
			// Rétablissement des signaux
			initialiser_signaux(sigact);
		}
		
		
		// ménage
		*ligne_analysee->ligne='\0';
		return 0;
	}
}

// Traitement des signaux
void traitement_signal(int sig) {
	switch(sig) {
		//
		case SIGINT:
			printf("\n");
			affiche_invite();
			break;
		default:
			printf("Signal non traité");
	}
}

// Initialise la gestion des signaux
void initialiser_signaux(struct sigaction *sigact) {
	sigact->sa_flags=0;
	sigemptyset(&sigact->sa_mask);
	
	sigact->sa_handler = traitement_signal;
	
	sigaction(SIGINT, sigact, NULL);
}

int main(void){

	struct sigaction sigact;
	ligne_analysee_t ligne;
	
	initialiser_jobs(&jobs);
	initialiser_signaux(&sigact);

	while(1) {
		affiche_invite();
		lit_ligne(&ligne);
		execute_ligne(&ligne, &jobs, &sigact);
	}
	
	return 0;
}
