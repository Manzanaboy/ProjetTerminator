#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utilitaire.h"
#include "error.h"
#include "constantes.h"
#include "simulation.h"
#include "robot.h"
#include "particule.h"

void simulation_mode_error(ROBOT* tete_liste_bot, char* nom_fichier,
					PARTICULE* tete_liste_part)
{
	lecture_robots(&tete_liste_bot, nom_fichier);
	liste_afficher(tete_liste_bot);
	bot_total_destruction(&tete_liste_bot);
	lecture_particules(&tete_liste_part, nom_fichier);
	liste_show(tete_liste_part);
	part_total_destruction(&tete_liste_part);
}
