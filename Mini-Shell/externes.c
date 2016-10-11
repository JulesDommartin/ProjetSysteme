#include <stdio.h> 
#include <stdlib.h>    
#include <errno.h>     
#include <sys/wait.h>  
#include <unistd.h>
#include "externes.h"
#include "ligne.h"

void executer_commande_dans_un_fils(int* pids, int i, ligne_analysee_t* ligne_analysee) {
	
	// On crée un processus fils
	pid_t res = fork();

	// On vérifie que ça c'est bien passé
	if (res==-1) {perror("Impossible de créer le processus fils.\n"); exit(errno); }
	if(res == 0) {
		// Exécution de la commande dans le processus fils
		//ligne_analysee->commandes[num_comm][0] pointe vers le pemier carac
		int res_e=execvp(ligne_analysee->commandes[i][0],ligne_analysee->commandes[i]);
		if (res_e==-1) {
			perror("Le processus n'a pas réussi à lancer la commande");
			exit(errno);
		}
	} else {
		// Dans le processus père (mini shell) on stock le PID dans la bonne case
		pids[i] = res;
	}

}

//Exécute les commandes externes
void executer_commandes(ligne_analysee_t* ligne_analysee) {

	int pids[NB_MAX_COMMANDES + 1];

	// On execute une commande pour chaque commande de la ligne
	for (int i = 0; i < ligne_analysee->nb_fils; i++) {
		// on lance l'exécution de la commande dans un fils
		executer_commande_dans_un_fils(pids,i,ligne_analysee);
	}

	// Le waitpid permet d'attendre la fin d'une commande pour débuter la suivante
	for (int i = 0; i < ligne_analysee->nb_fils; i++) {
		// On attend la fin de la commande, dans l'ordre du lancement
		waitpid(pids[i], NULL, 0);
	}


	// on ne se sert plus de la ligne : ménage
	*ligne_analysee->ligne='\0';	
}

