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
	
	/**
	 * \brief automate de lecture des fichiers
	 * \param tete_liste	 L'adresse d'un pointeur de 
	 * 						type PARTICULE qui pointe sur un pointeur 
	 * 						tete de liste.
	 * \param nom_fichier 	 le nom du fichier qu'on veut lire
	 */ 
	void lecture_particules(PARTICULE** tete_liste, char* nom_fichier);
	
	/**
	 * \brief fonction qui analyse si les différentes charactérisque de
	 * 		la particule sans compris dans leurs domaines de défintion
	 * \param energie		energie de la particule
	 * \param rayon 		rayon de la particule
	 * \param pos_x			coordonnée horizontale du centre de la 
	 * 						particule
	 * \param pos_y			coordonnée verticale du centre de la 
	 * 						particule
	 */
	void analyse_validite_part(double energie, double rayon,
										double pos_x, double pos_y);
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
	PARTICULE * liste_add ( PARTICULE ** p_tete );
	
	/**
	 * \brief comparer le nombre de particules qui sont décrites dans
	 * 		 le fichier au nombre de particules qu'on est censé avoir.
	 * \param nbpart_att	nombre de particules qu'on est censé avoir.
	 * \param nbpart_recu	nombre de particules décrites.
	 * \param ligne			numeor de la ligne du "FIN_LISTE".
	 */
	void analyse_nbrpart(int nbpart_att,int nbpart_recu,
												unsigned int ligne);
	
	/**
	 * \brief afficher dans le terminal les données des particules.
	 * \param p_tete 	adresse du pointeur qui pointe sur 
	 * 					le début de la liste
	 */
	void liste_show ( PARTICULE *tete );
	
	/**
	 * \brief eliminer une particule de la liste. 
	 * \param p_tete 	adresse du pointeur qui pointeur sur 
	 * 					le début de la liste
	 * \param el 		adresse de la particule que l'on 
	 * 					cherche à eliminer.
	 */
	void part_destruction ( PARTICULE ** p_tete, PARTICULE *el);
	
	/**
	 * \brief eliminer la liste de particules. 
	 * \param tete_liste 	adresse du pointeur qui pointe sur 
	 * 					le début de la liste
	 */
	void part_total_destruction(PARTICULE**tete_liste);
	
	/**
	 * \brief fonction qui affihce qu'on un problème de pointeur.
	 */
	void test3 (void); 
	
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
	 * \param tete_liste_part 	adresse du pointeur qui pointeur sur 
	 * 							le début de la liste
	 */
	void particule_collision_part_part(PARTICULE*tete_liste_part);
	
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
	 */
	void particule_acces_donnees (PARTICULE**courant,double*p_posx,
			double*p_posy, double*p_energie, double*p_rayon, int*p_num);
	/**
	 * \brief dessiner toutes les particules
	 * \param tete_liste	adresse du pointeur qui pointer sur 
	 * 						le début de la liste des particules
	 */
	void particule_dessin(PARTICULE*tete_liste);
#endif
