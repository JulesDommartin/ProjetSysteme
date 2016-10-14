#include <stdio.h>   
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "internes.h"
#include "job.h"

// Implémentation de cd
int cd(char* arg){
	// S'il n'y a pas d'argument après le cd, on revient a "HOME"
	if(arg==NULL){
		return (chdir(getenv("HOME")) == 0) ? 1 : 0;
	} else {
		// Sinon on change le repertoire pour celui passé en paramètre 
		// Si le répertoire n'existe pas on affiche une erreur
		if(chdir(arg) != 0) {
			printf("Erreur: le chemin spécifié n'existe pas.\n");
			return -1;
		}
	}
   	return 1;
}

// Implémentation de echo
int echo(char** mots){
	for (int m=1; m<NB_MOTS_MAX && mots[m]; m++)
      printf("%s ",mots[m]);
    printf("\n");
    return 1;
}

// Exécute la commande interne
int commande_interne(ligne_analysee_t* ligne_analysee) {
	if(strcmp(ligne_analysee->commandes[0][0], "cd")==0){
		return cd(ligne_analysee->commandes[0][1]);
	} else 
		if(strcmp(ligne_analysee->commandes[0][0], "echo")==0) {
			return echo(ligne_analysee->commandes[0]);
		}
		
	return 0;
}
