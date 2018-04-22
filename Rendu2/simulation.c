/*!
 \file simulation.c
 \brief Module qui gère le traitement d'un fichier en fonction du mode
		que l'on veut.
 \author Jose Antonio Simon Greminger
		 Damian Perez Grether
		 Selina Bothner
 \version 3.01
 \date 21 avril 2018
 */

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
#include "draw.h"

void simulation_mode_error(ROBOT* tete_liste_bot, char* nom_fichier,
							PARTICULE* tete_liste_part)
{
	char mode_lecture[5] = "Error";
	int ok=1;
	int *p_ok=&ok;

	lecture_robots(&tete_liste_bot, nom_fichier,mode_lecture,p_ok);
	lecture_particules(&tete_liste_part, nom_fichier,
							mode_lecture,p_ok);
	robot_collision_bot_bot(tete_liste_bot,mode_lecture,p_ok);
	particule_collision_part_part(tete_liste_part,mode_lecture,p_ok);
	robot_collisions_bot_part (tete_liste_bot,tete_liste_part,
								mode_lecture,p_ok);
	error_no_error_in_this_file();
	bot_total_destruction(&tete_liste_bot);
	part_total_destruction(&tete_liste_part);
}

void simulation_mode_draw(ROBOT* tete_liste_bot, char* nom_fichier,
							PARTICULE* tete_liste_part,int*p_base)
{
	char mode_lecture[4] = "Draw";
	int ok=1;
	int *p_ok = &ok;

	lecture_robots(&tete_liste_bot, nom_fichier,mode_lecture,p_ok);
	lecture_particules(&tete_liste_part, nom_fichier,
							mode_lecture,p_ok);
	robot_collision_bot_bot(tete_liste_bot,mode_lecture,p_ok);
	particule_collision_part_part(tete_liste_part,mode_lecture,p_ok);
	robot_collisions_bot_part (tete_liste_bot,tete_liste_part,
									mode_lecture,p_ok);
	robot_dessin(tete_liste_bot);
	particule_dessin(tete_liste_part);
	
	bot_total_destruction(&tete_liste_bot);
	part_total_destruction(&tete_liste_part);
	
	if(!ok)
	{
		*p_base=0;
	}
}
