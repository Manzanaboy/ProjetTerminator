#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utilitaire.h"
#include "error.h"
#include "robot.h"

void liste_afficher ( ROBOT *tete );
int main (int argc, char* argv[])
{
	if(argc !=2)
	{
		printf("erreur de lecture on pas entré de fichier \n");
		exit(0);
	}
	ROBOT *tete_liste=NULL;
	lecture_robots(&tete_liste, argv[1]);
	liste_afficher(tete_liste);
	bot_total_destruction(&tete_liste);
	tete_liste =NULL;
	return 0;
	
}
