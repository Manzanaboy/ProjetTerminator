/*!
 \file particule.h
 \brief Module qui gère l'automate de lecture pour lire les particule
		Il les sauvegarde dasn le tas sous forme de liste chaînée
		* et les détruit quand on a en a plus besoin.
		* Pendant la lecture il s'occupe de vérifier chaque type
		* erreur quand peut avoir.
		* Il permet aussi de dessiner les particules en décomposant
		* la strcuture. 
 \author Jose Antonio Simon Greminger
		 Damian Perez Grether
		 Selina Bothner
 \version 3.01
 \date 21 avril 2018
 */
#ifndef PARTICULE_H
	typedef struct particule PARTICULE;
	#define NB_MAX_PART 200
	/**
	 * \brief automate de lecture des fichiers. De plus on va indquer
	 * si la simulation s'est bien déroulé ou non. 
	 * \param tete_liste	 L'adresse d'un pointeur de 
	 * 						type PARTICULE qui pointe sur un pointeur 
	 * 						tete de liste.
	 * \param nom_fichier 	 le nom du fichier qu'on veut lire
	 * \param mode_lecture  mode de lecture error ou draw
	 * \param p_ok  		pointeur sur la variable qui indique si la
	 * 						simulation est ok ou ko.
	 */ 
	void lecture_particules(char* nom_fichier,
							char*mode_lecture, int*p_ok);
	
	/**
	 * \brief fonction qui analyse si les différentes charactérisque de
	 * 		la particule sans compris dans leurs domaines de défintion
	 * 		Si ça ne joue pas et qu'on est en mode error, il faut 
	 * 		    arrêter le programme.Si c'est en mode Draw, il faut 
	 * 			juste signaler que la simulation n'est pas ok.
	 * \param energie		energie de la particule
	 * \param rayon 		rayon de la particule
	 * \param pos_x			coordonnée horizontale du centre de la 
	 * 						particule
	 * \param pos_y			coordonnée verticale du centre de la 
	 * 						particule
	 * \param mode_lecture  mode de lecture error ou draw
	 * \param p_ok  		pointeur sur la variable qui indique si la
	 * 						simulation est ok ou ko.
	 */
	void analyse_validite_part(double energie, double rayon,
								double pos_x, double pos_y,
									char*mode_lecture, int*p_ok);
	/**
	 * \brief chercher la ligne du premier "FIN_LISTE" du fichier afin 
	 * 		  commencer à lire après celui-ci
	 * \param nom_fichier 	nom du fihcier qu'on veut lire
	 */
	int chercheur_ligne(char* nom_fichier);
	
	/**
	 * \brief ajouter une particule dans la liste chaînée
	 * \param p_tete 	adresse du pointeur qui pointeur sur 
	 * 					le début de la liste
	 */
	PARTICULE * liste_add ();
	
	/**
	 * \brief comparer le nombre de particules qui sont décrites dans
	 * 		 le fichier au nombre de particules qu'on est censé avoir.
	 * 		Si ça ne joue pas et qu'on est en mode error, il faut 
	 * 		    arrêter le programme.Si c'est en mode Draw, il faut 
	 * 			juste signaler que la simulation n'est pas ok.
	 * \param nbpart_att	nombre de particules qu'on est censé avoir.
	 * \param nbpart_recu	nombre de particules décrites.
	 * \param ligne			numeor de la ligne du "FIN_LISTE".
	 * \param mode_lecture  mode de lecture error ou draw
	 * \param p_ok  		pointeur sur la variable qui indique si la
	 * 						simulation est ok ou ko.
	 */
	void analyse_nbrpart(int nbpart_att,int nbpart_recu,
						unsigned int ligne,char*mode_lecture, int*p_ok);
	
	/**
	 * \brief afficher dans le terminal les données des particules.
	 * \param p_tete 	adresse du pointeur qui pointe sur 
	 * 					le début de la liste
	 */
	void liste_show ();
	
	/**
	 * \brief eliminer une particule de la liste. 
	 * \param p_tete 	adresse du pointeur qui pointeur sur 
	 * 					le début de la liste
	 * \param el 		adresse de la particule que l'on 
	 * 					cherche à eliminer.
	 */
	void part_destruction (PARTICULE *el);
	
	/**
	 * \brief eliminer la liste de particules. 
	 * \param tete_liste 	adresse du pointeur qui pointe sur 
	 * 					le début de la liste
	 */
	void part_total_destruction();
	
	/**
	 * \brief transcrire les données lues dans 
	 * 			les champs d'une particule.
	 * \param en			energie de la particule
	 * \param rayon 		rayon de la particule
	 * \param pos_x			coordonnée horizontale du centre de la 
	 * 						particule
	 * \param pos_y			coordonnée verticale du centre de la 
	 * 						particule
	 * \param courant 		adresse la particule en question
	 */
	void passage_donnees(double en, double ray,
					double pos_x, double pos_y, PARTICULE*courant);
	/**
	 * \brief analyse s'il y a eu collision entre les particules
	 * 			Si ça ne joue pas et qu'on est en mode error, il faut 
	 * 		    arrêter le programme.Si c'est en mode Draw, il faut 
	 * 			juste signaler que la simulation n'est pas ok.
	 * \param tete_liste_part 	adresse du pointeur qui pointeur sur 
	 * 							le début de la liste
	 * \param mode_lecture  mode de lecture error ou draw
	 * \param p_ok  		pointeur sur la variable qui indique si la
	 * 						simulation est ok ou ko.
	 */
	void particule_collision_part_part(char*mode_lecture, int*p_ok);
	
	/**
	 * \brief retranscrire les données des champs d'une particule dans 
	 * 			des variables locales et passer à la particule suivante.
	 * \param courant		pointeur sur un pointeur de particule.
	 * \param p_posx		pointeur sur une coordonnée horizontale 
	 * 						du centre de la particule. 
	 *\param p_posy			pointeur sur une coordonnée verticale
	 * 						du centre de la particule.
	 * \param energie		pointeur sur une variable de l'energie.
	 * \param rayon 		pointeur sur une variable du rayon.
	 * \param p_num 		pointeur sur une variable du numero.
	 * 
	 */
	void particule_acces_donnees (PARTICULE**courant,double*p_posx,
			double*p_posy, double*p_energie, double*p_rayon, int*p_num);
	/**
	 * \brief dessiner toutes les particules
	 * \param tete_liste	adresse du pointeur qui pointer sur 
	 * 						le début de la liste des particules
	 */
	void particule_dessin();
	
	/**
	 * \brief passer la tete de liste des particule au module robot 
	 * 		  pour les collisions ROBOT-PART
	 */
	PARTICULE* particule_acces_tete();
	
	double particule_tri(int compteur_deja_lue,int deja_lues[]);
	
	int particule_nombre_total();
	
	
	void particule_decomposition(PARTICULE* part);
	
	PARTICULE* part_init(int etat);
	
	void part_change_part(PARTICULE* part_change,
						PARTICULE* part_decomp, int nb_part,int num);
	
	int part_decomposition_start();
	
	PARTICULE* init(int etat);
	
	void particule_sauver(char* fichier_save);
	
	PARTICULE* particule_correspondante (int num_part);
	
	int particule_existe(S2D coord);
	
	int particule_verify_nb_bot(PARTICULE*courant);
	
	void particule_ajout_robot(PARTICULE*courant);
	
	void particule_reach(PARTICULE*courant,double*p_posx,double*p_posy);
	
	float particule_energie();

	int particule_collision(C2D rob,double *p_dist, double *p_rayon);

	
#endif
