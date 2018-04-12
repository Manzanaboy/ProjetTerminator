#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utilitaire.h"
#include "error.h"
#include "robot.h"

int main (int argc, char* argv[])
{
	if(argc !=3)
	{
		printf("erreur de lecture, entrées des fichiers \n");
		printf("exectubale suivi du mode et enfin le fichier a lire\n");
		exit(0);
	}
	ROBOT *tete_liste=NULL;
	lecture_robots(&tete_liste, argv[2]);
	liste_afficher(tete_liste);
	bot_total_destruction(&tete_liste);
	tete_liste =NULL;
	return 0;
	
}

