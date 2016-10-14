#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "job.h"
#include "externes.h"

// initilialise les structures de contrôle des jobs au lancement du mini-shell
void initialiser_jobs(ensemble_job_t *jobs) {
	for (int i=0; i < NB_MAX_JOBS; i++) {
		jobs->jobs[i].nom[0]='\0';
		for (int j=0; j < NB_MAX_COMMANDES; j++) {
			jobs->jobs[i].pids[j] = -2; 
		}
	}
}

// réalise une action sur un job
void exec_job(job_t job, int signal) {
	// 
	for (int i=0; job.pids[i]!=-2; i++) {
		if (job.pids[i]!=0) {
			kill(job.pids[i], signal);
		}
	}
}


