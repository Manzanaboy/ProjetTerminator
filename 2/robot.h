/*!
 \file robot.c
 \brief Module qui gère l'automate de lecture pour lire les robots
		Il les sauvegarde dasn le tas sous forme de liste chaînée
		* et les détruit quand on a en a plus besoin.
		* Pendant la lecture il s'occupe de vérifier chaque type
		* erreur quand peut avoir.
		* Il permet aussi de dessiner les robots en décomposant
		* la strcuture. 
 \author Jose Antonio Simon Greminger
		 Damian Perez Grether
		 Selina Bothner
 \version 3.01
 \date 21 avril 2018
 */
 
#include "particule.h"
#ifndef ROBOT_H

	typedef struct robot ROBOT;
	
	/**
	 * \brief automate de lecture des fichiers
	 * \param tete_liste	 L'adresse d'un pointeur de type ROBOT qui 
	 * 						pointe sur un pointeur tete de liste.
	 * \param nom_fichier 	 le nom du fichier qu'on veut lire
	 */ 
	void lecture_robots(char* nom_fichier, char*mode_lecture,int*p_ok);
	
	/**
	 * \brief eliminer un robot de la liste. 
	 * \param p_tete 	adresse du pointeur qui pointeur sur 
	 * 					le début de la liste
	 * \param el 		adresse du robot que l'on 
	 * 					cherche à eliminer.
	 */
	void bot_destruction ( ROBOT *el);
	
	/**
	 * \brief eliminer la liste de robots. 
	 * \param tete_liste 	adresse du pointeur qui pointe sur 
	 * 						le début de la liste
	 */
	void bot_total_destruction ();
	
	/**
	 * \brief ajouter un robot dans la liste chaînée
	 * \param p_tete 	adresse du pointeur qui pointeur sur 
	 * 					le début de la liste
	 */
	ROBOT * liste_ajouter ();
	
	/**
	 * \brief comparer le nombre de robots qui sont décrits dans
	 * 		 le fichier au nombre de robot qu'on est censé avoir.
	 * 		Si ça ne joue pas et qu'on est en mode error, il faut 
	 * 		    arrêter le programme.Si c'est en mode Draw, il faut 
	 * 			juste signaler que la simulation n'est pas ok. 
	 * 		
	 * \param nbbot_att		nombre de robots qu'on est censé avoir.
	 * \param nbbot_recu	nombre de robots décrits.
	 * \param ligne			numeor de la ligne du "FIN_LISTE".
	 * \param mode_lecture  mode de lecture error ou draw
	 * \param p_ok  		pointeur sur la variable qui indique si la
	 * 						simulation est ok ou ko.
	 */
	void analyse_nbrbot (int nbbot_att,int nbbot_recu
						,unsigned int line,char*mode_lecture, int*p_ok);
	
	/**
	 * \brief analyser si l'angle du robot se trouve dans le bon 
	 * 		  domaine de définition.
	 * 		  Si ça ne joue pas et qu'on est en mode error, il faut 
	 * 		    arrêter le programme.Si c'est en mode Draw, il faut 
	 * 			juste signaler que la simulation n'est pas ok. 
	 * \param alpha			angle du robot.
	 * \param mode_lecture  mode de lecture error ou draw
	 * \param p_ok  		pointeur sur la variable qui indique si la
	 * 						simulation est ok ou ko.
	 */
	void analyse_angle_bot (double alpha,char*mode_lecture, int*p_ok);
	
	/**
	 * \brief analyse s'il y a eu collision entre les robots.
	 * 			Si ça ne joue pas et qu'on est en mode error, il faut 
	 * 		    arrêter le programme.Si c'est en mode Draw, il faut 
	 * 			juste signaler que la simulation n'est pas ok. 
	 * \param tete_liste_bot 	adresse du pointeur qui pointeur sur 
	 * 							le début de la liste des robots.
	 * \param mode_lecture  mode de lecture error ou draw
	 * \param p_ok  		pointeur sur la variable qui indique si la
	 * 						simulation est ok ou ko.
	 */
	void robot_collision_bot_bot(char*mode_lecture, int*p_ok);
	
	/**
	 * \brief analyse s'il y a eu collision entre les robots et les 
	 * 		particules.
	 * 		Si ça ne joue pas et qu'on est en mode error, il faut 
	 * 		 	arrêter le programme.Si c'est en mode Draw, il faut 
	 * 			juste signaler que la simulation n'est pas ok. 
	 * \param tete_liste_bot 	adresse du pointeur qui pointeur sur 
	 * 							le début de la liste des robots.
	 * \param tete_liste_aprt 	adresse du pointeur qui pointeur sur 
	 * 							le début de la liste des particules.
	 * \param mode_lecture  mode de lecture error ou draw
	 * \param p_ok  		pointeur sur la variable qui indique si la
	 * 						simulation est ok ou ko.
	 */
	void robot_collisions_bot_part (char*mode_lecture, int*p_ok);
	
	/**
	 * \brief dessiner toutes les particules. 
	 * \param tete_liste	adresse du pointeur qui pointer sur 
	 * 						le début de la liste des robots
	 */
	void robot_dessin();
	
	/**
	 * \brief retranscrire les données des champs d'un robots dans 
	 * 			des variables locales.
	 * \param courant 		robot dont on veut extraire les données 
	 * 						des champs
	 * \param p_pos_x		pointeur sur une coordonnée horizontale 
	 * 						du centre du robot. 
	 *\param p_pos_y		pointeur sur une coordonnée verticale
	 * 						du centre du robot.
	 * \param p_angle 		pointeur sur une variable de l'angle.
	 */
	void robot_get_values(ROBOT*courant,double*p_pos_x,double*p_pos_y,
							double*p_angle);
	/**
	 * \brief afficher dans le terminal les données des robots.
	 * \param p_tete 	adresse du pointeur qui pointe sur 
	 * 					le début de la liste des robots.
	 */
	void liste_afficher ();
	
	void robot_assoc_robot_part();
	
	void robot_nearest(int tab_part[],int nb_part);
	/**
	 * \brief sauvegarde les données des robots dans le fichier 
	 * 		indiqué en parametre.
	 * \param fichier_save	le nom du fichier ou l'on sauvegarde les
	 * 			donnes.
	 */
	int robot_sauver(char* fichier_save);
	
	int robot_calcul_temps(double part_x, double part_y);
	
	void robot_ciblage(int num_bot,double part_x,double part_y,
							PARTICULE*courant);
	
	int robot_part_elimine(S2D corps,S2D cible);
	
	double robot_calcul_delta_angle(S2D corps,S2D cible);
	
	void robot_next_part(ROBOT**courant,int*p_particule_elimine,
						int*p_arret,int*p_suite);
	/**
	 * \brief 
	 */

	/**
	 * \brief gere le deplacment des robots et l'elimination des 
	 * 		particules. Renvoie vraie s'il y a eu elimination.
	 */

	int robot_deplacer();
	
	/**
	 * \brief 	verifie si la position de la souris touche un robot
	 * 		et selectionne ce robot.
	 * \param x La position selon x de la souris
	 * \param y La position selon y de la souris
	 */
	int robot_selection(float x, float y);

	/**
	 * \brief	verifie que tous les robots soient deselectionnés
	 * 		et les deselectionne dans le cas contraire.
	 */
	void robot_deselection();
/**
	 * \brief 	permet de passer les vitesses donnés en mode manuel
	 * 		pour les fonctions de deplacement des robots.
	 * \param rot	vit de rotation donnée
	 * \param tran	vit de translation donnée
	 */
	void robot_vitesse(float rot, float tran);

	/**
	 * \brief 	assure la rotation du robot donné en argument
	 * \param courant	L'addresse du robot
	 */
	double robot_rotaion(ROBOT *courant);
	
	/**
	 * \brief 	assure la translation d'un robot en verifiant les
	 * 		collisions avec les autres robots et particules. Renvoie 
	 * 		le numero de la particule touchee s'il y a eu collision.
	 * \param courant	l'addresse du robot
	 * \param tran		la distance du deplacement pour pouvoir verifier
	 * 		si le robot est en contacte avec une particule.
	 */
	int robot_translation(ROBOT *courant,double *tran);
	
	/**
	 * \brief Verifie si le deplacement souhaité du robot ne provoque 
	 * 		pas de collision avec d'autres robots. Si c'est le cas
	 * 		renvoie la distance de deplacement maximum autorisée.
	 * \param holo	le cercle représentant le robot à déplacer
	 * \param alpha	l'angle du robot à déplacer
	 * \param num	le numero du robot à déplacer pour na pas considérer
	 * 		le cas de collision contre lui-même
	 * \param v_tran vitesse de translation souhaité
	 * \param toucher	int pour verifier s'il y a eu collision
	 */
	double robot_collision(C2D holo, double alpha, int num, double v_tran, int *toucher);

#endif
