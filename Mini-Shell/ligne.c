#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ligne.h"
#include "mon_shell.h"

void lit_ligne(ligne_analysee_t *ligne_analysee)
{
	// lecture de la ligne de commande
	while (!fgets(ligne_analysee->ligne,sizeof(ligne_analysee->ligne)-1,stdin)) {
		// si Ctrl-d est tapé, alors on sort du mini-shell
		if (feof(stdin)) {
			printf("\n");
			exit(0);
		}
	} 
}

int decoupe_commande(char **a_debut, ligne_analysee_t *ligne_analysee){
	int i;
	// début de la commande à découper
	char *debut = *a_debut;
	
	if (strlen(debut) == 1) {
		return -1;
	} else {
		
		while (*debut && isspace(*debut)) debut++;

		for (i=0; i<NB_MAX_MOTS-1 ;i++) {
			// fin de ligne 
			if (!*debut)
			  break;

			// pipe inattendu 
			if (*debut=='|') {
			 printf("Erreur : caractère | inattendu\n"); 
			 exit(EXIT_FAILURE);
			}

			// stocke le début du mot numéro i
			ligne_analysee->commandes[ligne_analysee->nb_fils][i]=debut;

			// cherche la fin du mot
			while (*debut && !isspace(*debut) && *debut != '|') debut++;

			// entre deux arguments
			if (*debut && isspace(*debut)) {
			  	*debut='\0';
			  	debut++;
			 	while (*debut && isspace(*debut)) debut++;
			}

			// entre deux commandes
			if (*debut == '|') {
			  	*debut='\0';
			  	debut++; i++;
			 	break;
			}

		}
	
		*a_debut = debut;

		//  NULL pour execvp 
		ligne_analysee->commandes[ligne_analysee->nb_fils][i] = NULL;

		// test pour & (background)
		if (i>0 && strcmp("&",ligne_analysee->commandes[ligne_analysee->nb_fils][i-1])==0)
		{
		 ligne_analysee->commandes[ligne_analysee->nb_fils][i-1] = NULL;
		}
		return 1;
	}
}

int extrait_commande(ligne_analysee_t *ligne_analysee) {
	char* debut = ligne_analysee->ligne;

	ligne_analysee->nb_fils=0;
	while (ligne_analysee->nb_fils<NB_MAX_COMMANDES && *debut) {
		if (decoupe_commande(&debut,ligne_analysee) == -1) {
			return -1;
		}
		ligne_analysee->nb_fils++;
	}
	return 0;
}
