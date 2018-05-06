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


void simulation_first_lecture(char* nom_fichier,
									int*p_base,char* mode_lecture)	
{
	int ok=1;
	int *p_ok=&ok;
	lecture_robots(nom_fichier,mode_lecture,p_ok);
	lecture_particules(nom_fichier,mode_lecture,p_ok);
	if(ok)
	{
		robot_collision_bot_bot(mode_lecture,p_ok);
		particule_collision_part_part(mode_lecture,p_ok);
		robot_collisions_bot_part (mode_lecture,p_ok);
		
	}
	if(!(strncmp(mode_lecture,"Draw",4)))
	{
		simulation_dessiner();
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

void simulation_developpement(int reload)
{
	static int collision =0;
	static int decomposition =0;
	// calcul de la decomposition vient avant 
	// calcul de la collsion vient avant
	static int compteur_idiot=1;
	if(compteur_idiot)
	{
		if(!(decomposition && collision))
		{
		robot_update_rayons_part();
		}
		compteur_idiot=0;
	}
	simulation_dessiner();
	if(reload<0)
	{
		compteur_idiot =1;
	}
}

void simulation_detruire()
{
	int destruction=-1;
	bot_total_destruction();
	part_total_destruction();
	particule_recherche(destruction);
	simulation_developpement(destruction);
}

void simulation_dessiner()
{
	draw_cadre();
	robot_dessin();
	particule_dessin();
}
