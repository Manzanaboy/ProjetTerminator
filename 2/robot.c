

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
 
#include "utilitaire.h"
#include "error.h"
#include "robot.h"
#include "constantes.h"
#include "particule.h"
#include "draw.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


enum Etat_lecture {NB_R,RO};
enum State{OFF,ON};
#define ESP_BOT_BOT 5
#define TRES_GRAND 100000
static int NB_TOT_BOT = 0;
static float vit_rot=0;
static float vit_tran=0;

static ROBOT* tete_liste_bot=NULL;

/**
	 numero du robot dans l'ordre d'appartion dans le fichier
	* commence à 1.
	* Corps de la partciule est la position de son centre.Chaque 
	* coordonée doit être comprise en -DMAX ET + DMAX.
	* angle que fait l'axe du robot avec l'horizontale
	* pointeur sur l'adresse du prochain robot dans la liste
 */ 

struct robot
{
	int numero;
	S2D corps;
	double angle;
	ROBOT* suivant;
	S2D cible;
	int select;
};

void lecture_robots(char* nom_fichier,
						char*mode_lecture, int* p_ok)
{
	int nbbot_att,nbbot_recu=0,etat=NB_R, compteur_bot=1;
	int lg_fin = 9;
	int compteur=0;
	float pos_x,pos_y,ang;
	int i=0;
	ROBOT* courant=NULL;
	char tab [80];
	char* deb = tab;
	char*fin = NULL;
	FILE * fichier =fopen(nom_fichier,"r");
	if(fichier)
	{
		while((fgets(tab,80,fichier))&&
				(strncmp("FIN_LISTE",tab,lg_fin))!=0)
		{
			deb = tab;
			compteur++;
			while((tab[i]==' ' )||tab[i]=='\t')
				i++;
			if((tab[i]=='#')||(tab[i]=='\n')||(tab[i]=='\r')
						||(tab[i]==' ')||(tab[i]=='\t'))
			{
				continue;
			}

			switch (etat)
			{
				case NB_R : 
					if (sscanf(tab,"%d",&nbbot_att)==1)
						etat++;
					break;
				case RO :
					while (sscanf(deb,"%f %f %f",&pos_x,&pos_y,&ang)==3)
					{
						analyse_angle_bot (ang,mode_lecture,p_ok);
						courant = liste_ajouter();
						courant->numero = compteur_bot++;
						courant->corps.x = pos_x;
						courant->corps.y = pos_y;
						courant->cible.x = pos_x;
						courant->cible.y = pos_y;
						courant->angle = ang;
						courant->select=0;
						strtod(deb, &fin); // fonction du cours fichiers
						deb = (fin+ESP_BOT_BOT);
						nbbot_recu++;
					}
					break;
			}
		}
		if(*p_ok)
		{
			analyse_nbrbot(nbbot_att, nbbot_recu,
								compteur,mode_lecture,p_ok);
			NB_TOT_BOT=nbbot_att;
		}	
	}
	fclose(fichier);
}


ROBOT * liste_ajouter() 
{
	ROBOT *new_bot=NULL;
	if (!(new_bot= (ROBOT*) malloc(sizeof(ROBOT))))
	{
		printf("problem d'allocation dasn %s\n",__func__);
		exit (EXIT_FAILURE);
	}
	new_bot->suivant = tete_liste_bot;
	tete_liste_bot = new_bot;
	return new_bot;
}

void analyse_nbrbot (int nbbot_att,int nbbot_recu,unsigned int line, 
							char*mode_lecture, int*p_ok)
{
	if(nbbot_att>nbbot_recu)
	{
		line++;
		error_fin_liste_robots(line);
		if(!(strncmp(mode_lecture,"Error",5)))
		{
			exit(0);
		}
		else
		{
			*p_ok=0;
		}
	}
	else if(nbbot_att<nbbot_recu)
	{
		error_missing_fin_liste_robots(line);
		if(!(strncmp(mode_lecture,"Error",5)))
		{
			exit(0);
		}
		else
		{
			*p_ok=0;
		}
	}
}

void analyse_angle_bot (double alpha,char*mode_lecture, int*p_ok)
{
	if(util_alpha_dehors(alpha))
	{
		error_invalid_robot_angle(alpha);
		if(!(strncmp(mode_lecture,"Error",5)))
		{
			exit(0);
		}
		else
		{
			*p_ok=0;
		}
	}
}

void bot_total_destruction ()
{
	if(!(tete_liste_bot))
	{
		printf("problème pointeur l.%d in file %s",__LINE__,__FILE__);
	}
	ROBOT *bot = tete_liste_bot;
	while(bot->suivant != NULL)
	{
		bot_destruction(bot);
		bot = tete_liste_bot;
	}
	bot_destruction(bot);
	tete_liste_bot= NULL;
}

void bot_destruction (ROBOT *el )
{
	ROBOT *bot = tete_liste_bot;
	if(tete_liste_bot)
	{
		if (bot == el)
		{
			tete_liste_bot= bot->suivant;
			free(bot);
		}
		else
		{
			ROBOT *test_bot = tete_liste_bot;
			while ((test_bot->suivant !=NULL)&&(test_bot->suivant!= el))
			{
				test_bot = test_bot->suivant;
			}
			if(test_bot->suivant !=NULL)
			{
				ROBOT * bad_bot = test_bot->suivant;
				test_bot->suivant = test_bot->suivant->suivant;
				free(bad_bot);
			}
		}
	}
}

void liste_afficher ()
{
	ROBOT* voiture;
	
	if(tete_liste_bot)
	{
		voiture = tete_liste_bot;
		do
		{
			printf("robot %d \n", voiture->numero);
			printf("%f ", voiture->corps.x);
			printf("%f \n", voiture->corps.y);
			printf("%f \n", voiture->angle);
			voiture = voiture->suivant;
		}
		while((voiture)!=NULL);
	}
	else 
	{
		printf("erreur de tete liste, ja'rrive pas à lire %s", __func__);
	}

}
void robot_collision_bot_bot(char*mode_lecture, int*p_ok)
{
	int collision=0;
	double dist =0;
	if(tete_liste_bot && (tete_liste_bot->suivant))
	{
		ROBOT*courant1 = tete_liste_bot;
		ROBOT*courant2 = courant1->suivant;
		double* p_dist = NULL;
		p_dist = &dist;
		while ((collision==0)&&(courant2!=NULL))
		{
			C2D robot1 ={courant1->corps,R_ROBOT};
			C2D robot2 ={courant2->corps,R_ROBOT};
			if(util_collision_cercle(robot1,robot2,p_dist)) 
			{
				error_collision(ROBOT_ROBOT,courant1->numero,
									courant2->numero);
				if(!(strncmp(mode_lecture,"Error",5)))
				{
					exit(0);
				}
				else
				{
					*p_ok=0;
				}
			}
			courant1 = courant2;
			courant2 = courant1->suivant;
		}
	}
}
void robot_collisions_bot_part (char*mode_lecture, int*p_ok)
{
	double dist =0;
	double part_x,part_y,part_ray,part_en;
	int part_num;
	double *p_part_x=&part_x;
	double *p_part_y=&part_y;
	double *p_part_ray=&part_ray;
	double *p_part_en=&part_en;
	int *p_part_num=&part_num;
	PARTICULE *tete_liste_part=particule_acces_tete();
	if(tete_liste_bot && tete_liste_part) 
	{
		ROBOT*courant_bot = tete_liste_bot;
		PARTICULE*courant_part = tete_liste_part;
		double* p_dist = NULL;
		p_dist = &dist;
		while(courant_bot)
		{
			C2D robot1 ={courant_bot->corps,R_ROBOT};
			while(courant_part)
			{
				particule_acces_donnees(&courant_part,p_part_x,
							p_part_y,p_part_en,p_part_ray,p_part_num);
				S2D part_center ={*p_part_x,*p_part_y};
				C2D particule1 ={part_center,*p_part_ray};
				if(util_collision_cercle(robot1,particule1,p_dist))
				{
					error_collision(ROBOT_PARTICULE,courant_bot->numero,
										*p_part_num);
					if(!(strncmp(mode_lecture,"Error",5)))
					{
						exit(0);
					}
					else
					{
						*p_ok=0;
					}
				}
			}
			courant_bot = courant_bot->suivant;
		}
	}
}

void robot_dessin()
{
	double bot_x,bot_y,bot_angle;
	double *p_bot_x=&bot_x;
	double *p_bot_y=&bot_y;
	double *p_bot_angle=&bot_angle;
	if(tete_liste_bot)
	{
		ROBOT*courant = tete_liste_bot;
		while(courant)
		{
			robot_get_values(courant,p_bot_x,p_bot_y,p_bot_angle);
			/**moi**/
			if (!(courant->select))
			{
				draw_robot(*p_bot_x,*p_bot_y,*p_bot_angle);
			}
			else
			{
				draw_red(*p_bot_x,*p_bot_y,*p_bot_angle);
			}
			courant=courant->suivant;
		}
	}
}
void robot_get_values(ROBOT*courant,double*p_pos_x,double*p_pos_y,
						double*p_angle)
{
	if(courant)
	{
		*p_pos_x = courant->corps.x;
		*p_pos_y = courant->corps.y;
		*p_angle = courant->angle;
	}
}

int robot_sauver(char* fichier_save)
{
	ROBOT *courant_robot=NULL;
	int ok=1;
	FILE * p_fichier;
	if(!(tete_liste_bot))
	{
		printf("pas de robots a sauver\n");
		ok = 0;
		
	}
	if(ok)
	{
		if((p_fichier = fopen(fichier_save, "w")))
		{
			courant_robot = tete_liste_bot;
			fprintf(p_fichier, "#liste robots\n%d\n",NB_TOT_BOT);
			while(courant_robot)
			{
				fprintf(p_fichier, "\n%f %f %f",courant_robot->corps.x,
						courant_robot->corps.y,courant_robot->angle);
				courant_robot = courant_robot->suivant;
			}
			fprintf(p_fichier, "\nFIN_LISTE\n");
		}
		else
		{
			printf("\nerreur du fichier save");
			ok =0;
		}
		fclose(p_fichier);
	}
	return ok;
}

void robot_assoc_robot_part()
{
	int nb_particules = 0;
	nb_particules= particule_nombre_total();
	int compteur=0;
	double rayon = 0;
	int tab_part[nb_particules];
	for(compteur=0;compteur<nb_particules;compteur++)
	{
		rayon=particule_tri(compteur,tab_part);
//		printf("rayon est %f",rayon);
//		printf("numero de la prticule %d\n",tab_part[compteur]);
	}
	robot_nearest(tab_part,nb_particules);
}

void robot_nearest(int tab_part[], int nb_part)
{
	int compteur=0,num_bot_associe;
	double part_x=0,part_y=0;
	double *p_part_x=&part_x;
	double *p_part_y=&part_y;
	PARTICULE*courant=NULL;
	int max_robot_part =0;
	for(compteur=0;compteur<nb_part;compteur++)
	{
		courant = particule_correspondante(tab_part[compteur]);
		max_robot_part= particule_verify_nb_bot(courant);
		if(max_robot_part)
		{
			continue;
		}
		particule_reach(courant,p_part_x,p_part_y);
		num_bot_associe=robot_calcul_temps(part_x,part_y);
		if(num_bot_associe)
		{
			robot_ciblage(num_bot_associe,part_x,part_y,courant);
//			printf("les nouvelles assos sont \n");
//			printf("le robot numero %d a comme cible la particule triee %d, au coordonnes %f %f\n",num_bot_associe,compteur,part_x,part_y);
		}
		if((compteur>=NB_TOT_BOT)||(!num_bot_associe))
		{
			break;
		}
	}
}
int robot_calcul_temps(double part_x, double part_y)
{
	// mettre dasn un tableau les numeros deja sortis pour ne pas les ressortir par la suite
	ROBOT*courant = NULL;
	int bot_proche= 0, compteur=0;
	int arret=OFF, suite=ON, particule_elimine=OFF;
	int*p_particule_elimine=&particule_elimine;
	int*p_arret=&arret;
	int*p_suite=&suite;
	double temps_min=TRES_GRAND;
	double temps_trans,temps_rot,temps_tot;
	double dist_trans,dist_rot=0;
	S2D part_center = {part_x,part_y};
	if(tete_liste_bot)
	{
		courant=tete_liste_bot;
		particule_elimine=
					robot_part_elimine(courant->corps,courant->cible);
		for(compteur=0;compteur<NB_TOT_BOT;compteur++)
		{
			robot_next_part(&courant,p_particule_elimine,
								p_arret,p_suite);
			if(!suite)
			{
				suite=ON;
				continue;
			}
			if(arret)
			{
				break;
			}
			dist_trans = util_distance(courant->corps,part_center);
			dist_rot=robot_calcul_delta_angle(courant->corps,
												part_center);
			dist_rot = fabs(dist_rot-courant->angle);
			temps_trans = dist_trans / VTRAN_MAX ;
			temps_rot = dist_rot/VROT_MAX;
			temps_tot= temps_trans+temps_rot;
			if(temps_min>temps_tot)
			{
				temps_min=temps_tot;
				bot_proche = courant->numero;
			}
			//~ printf("la vvaraible bot proche est %d\n",bot_proche);
			//~ printf("la vvaraible temp tot est %f du robot %d\n",temps_tot,courant->numero);
			if(courant->suivant)
			{
				courant=courant->suivant;
				particule_elimine=robot_part_elimine(courant->corps,courant->cible);
			}
		}
	}
	
	return bot_proche;
}
	
void robot_ciblage(int num_bot,double part_x,double part_y,
					PARTICULE*courant)
{
	ROBOT* cherchee=NULL;
	if(tete_liste_bot)
	{
		cherchee = tete_liste_bot;
		while((cherchee->numero)!= num_bot)
		{
			cherchee=cherchee->suivant;
		}
		cherchee->cible.x=part_x;
		cherchee->cible.y=part_y;
		particule_ajout_robot(courant);
	}
	else 
	{
		printf("erreur de tete liste, ja'rrive pas à lire %s",__func__);
	}

}

int robot_part_elimine(S2D corps,S2D cible)
{
	if((corps.x!=cible.x)&&(corps.y!=cible.y))
	{
		if(particule_existe(cible))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

double robot_calcul_delta_angle(S2D corps,S2D cible)
{
	double angle_alignement=0;
	double *p_angle_alignement = &angle_alignement;
	if(cible.x<corps.x)
	{
		if(corps.y>cible.y)
		{
			angle_alignement=M_PI-util_angle(cible,corps);
		}
		else
		{
			angle_alignement=M_PI+util_angle(cible,corps);
		}
	}
	else if(cible.x>corps.x)
	{
		if(corps.y>cible.y)
		{
			angle_alignement=-util_angle(corps,cible);
		}
		else
		{
			angle_alignement=util_angle(corps,cible);
		}
	}
	else
	{
		if(corps.y>cible.y)
		{
			angle_alignement=-(M_PI/2);
		}
		else
		{
			angle_alignement=(M_PI/2);
		}
	}
	util_range_angle(p_angle_alignement);
	return angle_alignement;
}

void robot_next_part(ROBOT**courant,int*p_particule_elimine,
						int*p_arret,int*p_suite)
{
	while((((*courant)->cible.x)!=((*courant)->corps.x))&&
			((*courant)->cible.y)!=((*courant)->corps.y)
			&&(!*p_arret)&&(!(*p_particule_elimine)))
	{
		if(((*courant)->numero)>=2)
		{
//			printf("la cible du robot %d est %f %f\n",
//			(*courant)->numero,(*courant)->cible.x,(*courant)->cible.y);
			*courant = (*courant)->suivant;
			*p_particule_elimine=robot_part_elimine((*courant)->corps,
													(*courant)->cible);
			*p_suite=OFF;
		}
		else
		{
			*p_suite=ON;
			*p_arret=ON;
		}
	}
}


int robot_selection(float x, float y)
{
	ROBOT * courant =NULL;
	int ok=1;
	C2D rob;
	rob.rayon = R_ROBOT;
	S2D point = {x,y};
	robot_deselection();
	if(!(tete_liste_bot)) ok = 0;
	if(ok)
	{
		courant = tete_liste_bot;
		while (courant)
		{
			rob.centre = courant->corps;
			if (util_point_dans_cercle(point, rob)) 
			{
				courant->select =1;
				return courant->numero;
			}
			courant = courant->suivant;
		}
	}
	return 0;
}

void robot_deselection()
{
	int ok=1;
	ROBOT * courant=NULL;
	if(!(tete_liste_bot)) ok = 0;
	if(ok)
	{
		courant = tete_liste_bot;
		while(courant)
		{
			courant->select=0;
			courant = courant->suivant;
		}
	}
}

int robot_deplacer()
{
	ROBOT *courant = NULL;
	S2D part;
	int ok=1, num_part, reponse=0;
	double deplacement, *p_dep = &deplacement;
	bool decalage;
	if(!(tete_liste_bot))
	{
		printf("pas de robots a sauver\n");
		ok = 0;
	}
	courant = tete_liste_bot;
	if(ok)
	{
		while(courant)
		{
				double alpha=0;
				alpha = robot_rotaion(courant);
				if(alpha > -M_PI/4 && alpha < M_PI /4) //tourne avant de bouger
				{
					num_part = robot_translation(courant, p_dep);
					if(num_part && alpha ==0 && deplacement <= EPSIL_ZERO)
					{
						part = particule_cible(num_part,courant->cible);
						if (part.x == courant->cible.x && part.y == courant->cible.y)
							reponse = 1;
						else
							courant->cible = part;
					}
				}
			courant = courant->suivant;
		}
	}
	return reponse;
}

void robot_vitesse(float rot, float tran)
{
	vit_rot=rot;
	vit_tran=tran;
}

double robot_rotaion(ROBOT *courant)
{
	double alpha = 0, v_rotation;
	if (courant->select)
		{
			v_rotation = vit_rot;
			courant->angle+= v_rotation*DELTA_T;
			alpha=1;
			return alpha;
		}
	if( ! (util_alignement(courant->corps, courant->angle, courant->cible)) ) //ROTATION
	{
		//ca tourne si pas aligné
		util_ecart_angle(courant->corps, courant->angle, courant->cible, &alpha); //inutile car tjrs vrai
		if(fabs(alpha/DELTA_T)<VROT_MAX) 
			v_rotation=alpha/DELTA_T;			//tourne juste de la distance qui reste
		else
			v_rotation=VROT_MAX; 				//tourne dist max
		if(alpha > 0) 
			courant->angle+= v_rotation*DELTA_T;
		else 
			courant->angle-= v_rotation*DELTA_T; 
	}
	return alpha;

}

int robot_translation(ROBOT *courant, double *tran)
{
	C2D holo;
	S2D c_part, *p_c_part=&c_part;
	int part, collision=0, test=0, *p_test = &test;
	double alpha=0, v_translation=0;
	double rayon, ecart, la, lb, lc ,la_new, lb_new;
	double *p_ecart = &ecart, *p_rayon=&rayon, *p_la_new =&la_new;
	if (courant->select)
	{
		v_translation=vit_tran;
	}
	else 
	{
		v_translation=VTRAN_MAX;
	}
	holo.rayon = R_ROBOT;
	holo.centre = courant->corps;
	v_translation = robot_collision(holo, courant->angle, courant->numero, v_translation, p_test);
	if (test)
	{
		v_translation = robot_collision(holo, courant->angle, courant->numero, v_translation, p_test);
	}

	holo.centre = util_deplacement(courant->corps, courant->angle, v_translation);
	part = particule_collision(holo, p_ecart, p_rayon, p_c_part);
	while (part > 0 )
	{
		collision = part;
		la = v_translation;
		lb = ecart;
		lc = util_distance(courant->corps, c_part);
		lb_new = rayon + R_ROBOT;
		if (util_inner_triangle(la, lb, lc, lb_new, p_la_new))
			v_translation = la_new;
		else
			v_translation = 0;
		holo.centre = util_deplacement(courant->corps, courant->angle, v_translation);
		part = particule_collision(holo, p_ecart, p_rayon, p_c_part);
	}
	courant->corps = courant->corps=util_deplacement(courant->corps, courant->angle, v_translation*DELTA_T);
	*tran = v_translation*DELTA_T;
	return collision;
}

double robot_collision(C2D holo, double alpha, int num, double v_tran, int *toucher)
{
	ROBOT *courant;
	C2D rob, ref;
	rob.rayon = R_ROBOT;
	ref.rayon = R_ROBOT;
	ref.centre = holo.centre;
	double rayon, ecart, la, lb, lc ,la_new, lb_new, v_translation = v_tran;
	double *p_ecart = &ecart, *p_la_new =&la_new;
	if(!(tete_liste_bot))
		return 0;
	courant = tete_liste_bot;
	while (courant)
	{
		if(num != courant->numero)
		{
			ref.centre = util_deplacement(holo.centre, alpha, v_translation);
			rob.centre = courant->corps;
			if(util_collision_cercle(ref,rob, p_ecart))
			{
				*toucher = 1;
				la = v_translation;
				lb = ecart;
				lc = util_distance(courant->corps, rob.centre);
				lb_new = 2*R_ROBOT;
				if (util_inner_triangle(la, lb, lc, lb_new, p_la_new))
					v_translation = la_new;
				else
					v_translation = 0;
				ref.centre = util_deplacement(holo.centre, alpha, v_translation);
			}
			
		}
		courant = courant->suivant;
	}
	return v_translation;
}
