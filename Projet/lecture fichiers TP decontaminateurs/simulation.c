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
	lecture_particules(&tete_liste_part, nom_fichier);
	robot_collision_bot_bot(tete_liste_bot);
	particule_collision_part_part(tete_liste_part);
	liste_afficher(tete_liste_bot);
	liste_show(tete_liste_part);
	bot_total_destruction(&tete_liste_bot);
	part_total_destruction(&tete_liste_part);
}
