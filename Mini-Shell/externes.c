#include <stdio.h> 
#include <stdlib.h>    
#include <errno.h>     
#include <sys/wait.h>  
#include <unistd.h>
#include <string.h>

#include "job.h"
#include "externes.h"
#include "ligne.h"

void executer_commande_dans_un_fils(job_t* job, int numero_commande, ligne_analysee_t* ligne_analysee) {
	
	// On regarde s'il faut un tube pour la sortie et/out l'entrée
	// Il faut que le numero de commande ne soit pas le dernier et qu'il y ai au moins 2 commandes
	int out = numero_commande < ligne_analysee->nb_fils-1 && ligne_analysee->nb_fils >=2;
	int in = numero_commande > 0;
	
	if(out) {
		if(pipe(job->tubes[numero_commande]) == -1) {
    		perror("Erreur création du tube\n");
    		exit(errno);
    	}
	}
	
	// On crée un processus fils
	pid_t res = fork();

	// On vérifie que ça c'est bien passé
	if (res==-1) {
		perror("Impossible de créer le processus fils\n");
		exit(errno);
	}
	if(res == 0) {
		// Exécution de la commande dans le processus fils
		// S'il faut un tube pour la sortie
		if(out) {
			// On redirige la sortie
			dup2(job->tubes[numero_commande][1], 1);
			// On ferme l'entrée
			close(job->tubes[numero_commande][0]);
		}
		// S'il faut un tube pour l'entrée
		if(in) {
			// On redirige l'entrée
			dup2(job->tubes[numero_commande-1][0], 0);
			// On ferma la sortie
			close(job->tubes[numero_commande-1][1]);
		}
		int res_e=execvp(ligne_analysee->commandes[numero_commande][0],ligne_analysee->commandes[numero_commande]);
		if (res_e==-1) {
			perror("Le processus n'a pas réussi à lancer la commande");
			exit(errno);
		}
	} else {
		// Dans le processus père (mini shell) on stock le PID
		job->pids[numero_commande] = res;
	}
	
	// On ferme tous les tubes
	for (int i=0; i<numero_commande; i++) {
		close(job->tubes[i][0]);
		close(job->tubes[i][1]);
	}
}

//Exécute les commandes externes
void executer_commandes(job_t* job, ligne_analysee_t* ligne_analysee) {

	strcpy(job->nom,ligne_analysee->ligne);

	// On execute une commande pour chaque commande de la ligne
	for (int i = 0; i < ligne_analysee->nb_fils; i++) {
		// on lance l'exécution de la commande dans un fils
		executer_commande_dans_un_fils(job,i,ligne_analysee);
	}

	// Le waitpid permet d'attendre la fin d'une commande pour débuter la suivante
	for (int i = 0; i < ligne_analysee->nb_fils; i++) {
		// On attend la fin de la commande, dans l'ordre du lancement
		waitpid(job->pids[i], NULL, 0);
	}

	// on ne se sert plus de la ligne : ménage
	*ligne_analysee->ligne='\0';	
}

