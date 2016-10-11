#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "internes.h"
#include "ligne.h"
#include "externes.h"


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

static void execute_ligne(ligne_analysee_t *ligne_analysee) {

	extrait_commande(ligne_analysee);

	// s'il ne s'agit pas d'une commande interne au shell,
	// la ligne est exécutée par un ou des fils
	if (! commande_interne(ligne_analysee) ) {
		// fait exécuter les commandes de la ligne par des fils
		executer_commandes(ligne_analysee);

	}

	// ménage
	*ligne_analysee->ligne='\0';
}


int main(void){

	ligne_analysee_t ligne;

	while(1) {
		affiche_invite();
		lit_ligne(&ligne);
		execute_ligne(&ligne);
	}
	
	return 0;
}