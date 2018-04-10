#include "utilitaire.h"
#include "error.h"
#include "constantes.h"
#include "simulation.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if(argc !=3)
	{
		printf("erreur de lecture, entrées des fichiers \n");
		printf("exectubale suivi du mode et enfin le fichier a lire\n");
		exit(0);
	}
	ROBOT *tete_liste_bot=NULL;
	PARTICULE* tete_liste_part=NULL;
	simulation_mode_error(tete_liste_bot, argv[2], tete_liste_part);
	tete_liste_bot =NULL;
	tete_liste_part=NULL;
	return 0;
}
