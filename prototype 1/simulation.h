/*!
 \file simulation.h
 \brief Module qui gère le traitement d'un fichier en fonction du mode
		que l'on veut.
 \author Jose Antonio Simon Greminger
		 Damian Perez Grether
		 Selina Bothner
 \version 3.01
 \date 21 avril 2018
 */

#include "robot.h"
#include "particule.h"

/**
 * \brief  lire le fichier en mode Error
 * \param 	tete_liste_bot		pointeur sur la tete de la liste 
 * 								des robots.
 * \param   nom_fichier			nom du fichier qu'on veut lire
 * \param 	tete_liste_part		pointeur sur la tete de la liste 
 * 								des particules.
 */
void simulation_mode_error(ROBOT* tete_liste_bot, char* nom_fichier,
					PARTICULE* tete_liste_part);

/**
 * \brief  lire le fichier en mode Draw, et dire s'il faut dessiner une
 * 			page blanche ou une page de dessin
 * \param 	tete_liste_bot		pointeur sur la tete de la liste 
 * 								des robots.
 * \param   nom_fichier			nom du fichier qu'on veut lire
 * \param 	tete_liste_part		pointeur sur la tete de la liste 
 * 								des particules.
 * \param 	base				pointeur qui va indiquer si la base sera
 * 								une page blanche une page de dessin
 */
void simulation_mode_draw(ROBOT* tete_liste_bot, char* nom_fichier,
					PARTICULE* tete_liste_part, int*p_base);
