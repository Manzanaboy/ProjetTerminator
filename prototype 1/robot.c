/*
 *  Brief: ce module s'accupe de lire les données qui concernent les 
 * dans un fichier fourni. Et d'appeler les bonnes focntions en cas 
 * d'erreur. 
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
struct robot
{
	int numero;
	S2D corps;
	double angle;
	ROBOT* suivant;
};
void test2 (void)
{
	printf("problem de pointeur dans le fichier %s", __FILE__);	
}
void lecture_robots(ROBOT** tete_liste, char* nom_fichier)
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
			{
				i++;
			}
			if((tab[i]=='#')||(tab[i]=='\n')||(tab[i]=='\r')
										||(tab[i]==' ')||(tab[i]=='\t'))
			{
				continue;
			}

			switch (etat)
			{
				case NB_R : 
					if (sscanf(tab,"%d",&nbbot_att)==1)
					{
						etat++;
					}
					break;
				case RO :
					while (sscanf(deb,"%f %f %f",&pos_x,&pos_y,&ang) ==3)
					{
						analyse_angle_bot (ang);
						courant = liste_ajouter(tete_liste);
						courant->numero = compteur_bot++;
						courant->corps.x = pos_x;
						courant->corps.y = pos_y;
						courant->angle = ang;
						strtod(deb, &fin); // fonction du cours fichiers
						deb = (fin+5); //on compte aussi les espaces 
						nbbot_recu++;
					}
				break;
			}
		}	
		analyse_nbrbot(nbbot_att, nbbot_recu, compteur );		
	}
	fclose(fichier);
}


ROBOT * liste_ajouter( ROBOT ** p_tete ) 
{
	 ROBOT *new_bot=NULL;
	 if (!(new_bot= (ROBOT*) malloc(sizeof(ROBOT))))
	 {
		 printf("problem d'allocation dasn %s\n",__func__);
		 exit (EXIT_FAILURE);
	}
	 new_bot->suivant = *p_tete;
	 *p_tete = new_bot;
	 return new_bot;
}

void analyse_nbrbot (int nbbot_att,int nbbot_recu,unsigned int line)
{
	if(nbbot_att>nbbot_recu)
	{
		line++;
		error_fin_liste_robots(line);
		exit(0);
	}
	else if(nbbot_att<nbbot_recu)
	{
		line++;
		error_missing_fin_liste_robots(line);
		exit(0);
	}
}

void analyse_angle_bot (double alpha)
{
	if(util_alpha_dehors(alpha))
	{
		error_invalid_robot_angle(alpha);
		exit(0);
	}
}

void bot_total_destruction (ROBOT** p_liste)
{
	if(!p_liste)
	{
		test2();
	}
	ROBOT *bot = *p_liste;
	while(bot->suivant != NULL)
	{
		bot_destruction(p_liste,bot);
		bot = *p_liste;
	}
	bot_destruction(p_liste,bot);
}

void bot_destruction ( ROBOT ** p_tete, ROBOT *el )
{
	ROBOT *bot = *p_tete;
	if(p_tete)
	{
		if (bot == el)
		{
			*p_tete= bot->suivant;
			free(bot);
		}
		else
		{
			ROBOT *test_bot = *p_tete;
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

void liste_afficher ( ROBOT *tete )
{
	ROBOT* voiture;
	
	if(tete)
	{
		voiture = tete;
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
void robot_collision_bot_bot(ROBOT*tete_liste_bot)
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
			if(util_collision_cercle(robot1,robot2,p_dist)) // rentrer les cercles et la distances
			{
				error_collision(ROBOT_ROBOT,courant1->numero,
													courant2->numero);
			}
			courant1 = courant2;
			courant2 = courant1->suivant;
		}
	}
}
void robot_collisions_bot_part (ROBOT*tete_liste_bot,
											PARTICULE* tete_liste_part)
{
	double dist =0;
	double part_x,part_y,part_ray,part_en;
	int part_num;
	double *p_part_x=&part_x;
	double *p_part_y=&part_y;
	double *p_part_ray=&part_ray;
	double *p_part_en=&part_en;
	int *p_part_num=&part_num;
	if(tete_liste_bot && tete_liste_part ) 
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
				}
			}
			courant_bot = courant_bot->suivant;
		}
	}
}

void robot_dessin(ROBOT*tete_liste)
{
	double bot_x,bot_y,bot_angle;
	double *p_bot_x=&bot_x;
	double *p_bot_y=&bot_y;
	double *p_bot_angle=&bot_angle;
	if(tete_liste)
	{
		ROBOT*courant = tete_liste;
		while(courant)
		{
			robot_get_values(courant,p_bot_x,p_bot_y,p_bot_angle);
			draw_robot(*p_bot_x,*p_bot_y,*p_bot_angle);
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
