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
	
	/**
	 * \brief trier un tableau avec les numéros des particules, selon 
	 * 			leur rayon dans l'ordre décroissant
	 * \param compteur_deja-lue	 numero de particule dans
	 * 							 le tableau une fois trié
	 * \param deja_lues 	tableau contenant tous les numéros des
	 * 						particules triéesselon leur rayon
	 */
	double particule_tri(int compteur_deja_lue,int deja_lues[]);
	
	/**
	 * \brief renvoie le nombre total de particules
	 */
	int particule_nombre_total();
	
	/**
	 * \brief décompose une particule en 4
	 * \param part	 adresse de la particule à decomposer
	 */
	void particule_decomposition(PARTICULE* part);
	
	PARTICULE* part_init(int etat);
	
	/**
	 * \brief Créer une nouvelle particule à partir de la 
	 * 			décomposition d'une particule
	 * \param part_change	adresse de l'ancienne particule
	 * \param part_decomp	adresse de la nouvelle particule
	 * \param nb_part 		indique de quelle nouvelle particule 
	 * 						on traite : 1ère, 2ème,..
	 * \param num			numéro de la nouvelle particule
	 */
	void part_change_part(PARTICULE* part_change,
						PARTICULE* part_decomp, int nb_part,int num);
	/**
	 * \brief Lancer boucle de décomposition, si la condition est 
	 * 		  remplie, décomposer la particule en question
	 */
	int part_decomposition_start();
	
	PARTICULE* init(int etat);
	/**
	 * \brief trouver la particule correspondante à un numéro donnée
	 * \param num_part	numéro de la paricule qu'on cherche
	 */
	PARTICULE* particule_correspondante (int num_part);
	
	/**
	 * \brief indique si la paricule existe encore
	 * \param coord		coordonnées du centre d'une particule
	 */
	int particule_existe(S2D coord);
	
	/**
	 * \brief indique si la paricule a atteint le nombre de robots 
	 * 		  maximum qui peuvent aller vers elle
	 * \param courant	adresse de la particule
	 */
	int particule_verify_nb_bot(PARTICULE*courant);
	
	void particule_ajout_robot(PARTICULE*courant);
	
	void particule_reach(PARTICULE*courant,double*p_posx,double*p_posy);
	/** \brief calcul et renvoie le taux de décontamination en 
	*		fonction des variables statics energie_decontamine
	*		et energie_initiale
	**/
	float particule_energie();
/**
	 * \brief sauver les informations des particules dans le fichier 
	 * 		donné en argument
	 * \param fichier_save	nom du fichier ou l'on sauve les 
	 * 		  informations
	 */
	void particule_sauver(char* fichier_save);
	/**
	 * \brief	verifie si le robot touche une particule dans son
	 * 		deplacement et renvoie le numero de cette particule.
	 * \param rob	cercle representant le robot
	 * \param p_dist	permet de renvoier la distance entre les centres
	 * 		du robot et de la particule touchée
	 * \param p_rayon	permet de renvoyer le rayon de la particule 
	 * 		touchée
	 * \param corps_part	permet de renvoyer le centre de la particule
	 * 		touchée
	 */
	int particule_collision(C2D rob,double *p_dist, double *p_rayon,
							S2D *corps_part);

	/**
	 * \brief	compare le numero de la particule et le corps de la 
	 * 		cible, s'il correspondent à la même particule elle est 
	 * 		éliminée, sinon le centre de la particule num est renvoyé
	 * \param num	numéro de la particule touchée
	 * \param cible	coordonnées de la cible du robot
	 */
	S2D particule_cible(int num, S2D cible);
	
	PARTICULE* particule_donner_acces(S2D coord);
	
	void particule_less_robot(PARTICULE*courant);
	
#endif
