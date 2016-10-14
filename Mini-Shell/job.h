#ifndef JOB_H
#define JOB_H

#define NB_MAX_JOBS 1

#include "ligne.h"


// Structure job 
typedef struct job_t
{
  char   nom[NB_MAX_CAR];             // ligne de commandes
  pid_t  pids[NB_MAX_COMMANDES+1];    // pids des fils exécutant chaque commande
  int tubes[NB_MAX_COMMANDES-1][2];   // pids[i]==-2 si le job n'a pas de pème fils
                                      // pids[i]==0 si le pème fils s'est terminé
                                      // le job est en cours d'exécution si pids[0]!=-2
} job_t;

// Structure qui contient un ensemble de jobs
typedef struct ensemble_job_t
{
  job_t  jobs[NB_MAX_JOBS];
} ensemble_job_t;


// initilialise les structures de contrôle des jobs au lancement du mini-shell
void initialiser_jobs(ensemble_job_t *jobs);

// réalise une action sur un job
void exec_job(job_t job, int signal);

#endif
