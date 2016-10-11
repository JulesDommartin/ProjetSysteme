#ifndef EXTERNES_H
#define EXTERNES_H

#include "ligne.h"

//Exécute les commandes 
void executer_commande_dans_un_fils(int* pids, int i, ligne_analysee_t* ligne_analysee);


//Exécute les commandes externes
void executer_commandes(ligne_analysee_t* ligne_analysee);


#endif
