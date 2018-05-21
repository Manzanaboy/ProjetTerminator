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

enum Power {DESTROY,CREATE};

void simulation_first_lecture(char* nom_fichier,
									int*p_base,char* mode_lecture)	
{
	int ok=CREATE;
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
			*p_base=DESTROY;
		}
	}
	else if(!(strncmp(mode_lecture,"Error",5)))
	{
		error_no_error_in_this_file();
	}
	robot_assoc_robot_part();
	
}

void simulation_mja()
{
	
	robot_assoc_robot_part();
	simulation_dessiner();
}

void simulation_detruire()
{
	bot_total_destruction();
	part_total_destruction();
}

void simulation_dessiner()
{
	draw_cadre();
	robot_dessin();
	particule_dessin();
}

void simulation_decomposition()
{
	int decomposition =0;
	decomposition = part_decomposition_start();
	if(decomposition)
	{
		simulation_mja();
	}
}

int simulation_particules()
{
	PARTICULE*courant=NULL;
	courant=particule_acces_tete();
	if(courant)
	{
		return 1;
	}
	else 
	{
		return 0;

	}
}
