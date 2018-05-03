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
 * \brief  lire le fichier, et dire s'il faut dessiner une
 * 			page blanche ou une page de dessin
 * \param 	tete_liste_bot		pointeur sur la tete de la liste 
 * 								des robots.
 * \param   mode_lecture		Error ou Draw
 * \param   nom_fichier			nom du fichier qu'on veut lire
 * \param 	tete_liste_part		pointeur sur la tete de la liste 
 * 								des particules.
 * \param 	base				pointeur qui va indiquer si la base sera
 * 								une page blanche une page de dessin
 */
void simulation_first_lecture(ROBOT** tete_liste_bot, char* nom_fichier,
		PARTICULE** tete_liste_part,int*p_base,char* mode_lecture);

/**
 * \brief  Détruire les données et mettre les pointeurs à NULL
 * \param 	tete_liste_bot		pointeur sur la tete de la liste 
 * 								des robots.
 * \param 	tete_liste_part		pointeur sur la tete de la liste 
 * 								des particules.
 */
void simulation_detruire(ROBOT** tete_liste_bot,
						PARTICULE**tete_liste_part);

/**
 * \brief  Se charger du developpement de la simulation
 * \param 	tete_liste_bot		pointeur sur la tete de la liste 
 * 								des robots.
 * \param 	tete_liste_part		pointeur sur la tete de la liste 
 * 								des particules.
 */
void simulation_developpement(ROBOT** tete_liste_bot,
					PARTICULE**tete_liste_part);
