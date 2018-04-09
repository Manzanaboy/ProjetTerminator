/*
 *  Brief: ce module s'accupe de lire les données qui concernent les 
 * dans un fichier fourni. Et d'appeler les bonnes focntions en cas 
 * d'erreur. 
 */
#include "utilitaire.h"
#include "error.h"
#include "robot.h"
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
	int nbbot_att,nbbot_recu=0, etat=NB_R;
	int lg_fin = 9;
	int compteur=0;
	float pos_x,pos_y,ang;
	int i;
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
						courant->numero = nbbot_recu++;
						courant->corps.x = pos_x;
						courant->corps.y = pos_y;
						courant->angle = ang;
						strtod(deb, &fin); // fonction du cours fichiers
						deb = (fin+5); //on compte aussi les espaces 
					}
				break;
			}
		}	
		analyse_nbrbot(nbbot_att, nbbot_recu, compteur );		
	}
	fclose(fichier);
}


ROBOT * liste_ajouter ( ROBOT ** p_tete ) 
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
ROBOT* bot_creation (void)
{
	ROBOT* tete_liste;
	if (!(tete_liste= (ROBOT*) malloc(sizeof(ROBOT))))
	 {
		 printf("problem d0allocation dasn %s\n",__func__);
		 exit (EXIT_FAILURE);
	}
	if(!tete_liste)
	{
		test2();
	}
	return tete_liste;
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
