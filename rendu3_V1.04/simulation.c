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

static ROBOT* tete_liste_bot=NULL;
static PARTICULE* tete_liste_part=NULL;

void simulation_first_lecture(char* nom_fichier,
									int*p_base,char* mode_lecture)	
{
	int ok=1;
	int *p_ok=&ok;
	lecture_robots(&tete_liste_bot,nom_fichier,mode_lecture,
																p_ok);
	lecture_particules(&tete_liste_part, nom_fichier,
										mode_lecture,p_ok);
	if(ok)
	{
		robot_collision_bot_bot(tete_liste_bot,mode_lecture,p_ok);
		particule_collision_part_part(tete_liste_part,mode_lecture,p_ok);
		robot_collisions_bot_part (tete_liste_bot,tete_liste_part,
												mode_lecture,p_ok);
		
	}
	if(!(strncmp(mode_lecture,"Draw",4)))
	{
		robot_dessin(tete_liste_bot);
		particule_dessin(tete_liste_part);
		if(!ok)
		{
			*p_base=0;
		}
	}
	else if(!(strncmp(mode_lecture,"Error",5)))
	{
		error_no_error_in_this_file();
	}
	
}

void simulation_developpement()
{
	static int compteur_idiot=1;
	if(compteur_idiot !=0)
	{
		printf("fonction developpement à developper  in File %s avec amour Jose \n",__FILE__);
		compteur_idiot=0;
	}
	robot_dessin(tete_liste_bot);
	particule_dessin(tete_liste_part);
}

void simulation_detruire()
{
	bot_total_destruction(&tete_liste_bot);
	part_total_destruction(&tete_liste_part);
	tete_liste_bot=NULL;
	tete_liste_part=NULL;
	
}
