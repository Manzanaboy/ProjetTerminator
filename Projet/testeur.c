#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utilitaire.h"
#include "error.h"

enum Etat_lecture {NB_R,RO};
typedef struct robot ROBOT;
struct robot
{
	int numero;
	S2D corps;
	double angle;
	ROBOT* suivant;
};

void lecture_robots(ROBOT** tete_liste, char* nom_fichier);
ROBOT * liste_ajouter ( ROBOT ** p_tete );
void analyse_nbrbot (int nbbot_att,int nbbot_recu,unsigned int line);
void analyse_angle_bot (double alpha);
void liste_afficher ( ROBOT *tete );

int main (int argc, char* argv[])
{
	if(argc !=2)
	{
		printf("erreur de lecture \n");
		ROBOT *tete_liste=NULL;
		lecture_robots(&tete_liste, argv[1]);
		return 0;
	}
	
}
void lecture_robots(ROBOT** tete_liste, char* nom_fichier)
{
	int nbbot_att,nbbot_recu, etat=NB_R;
	int lg_fin = 9;
	float a,b,c;
	ROBOT* courant=NULL;
	char tab [80];
	FILE * fichier =fopen(nom_fichier,"r");
	if(fichier)
	{
		while(fgets(tab,80,fichier))
		{
			if((tab[0]=='#')||(tab[0]=='\n')||(tab[0]=='\r'))
			continue; 
			switch (etat)
			{
				case NB_R : 
					if (sscanf(tab,"%d",&nbbot_att)==1)
					{
						etat++;
					}
					else
					{
						printf("erreur il n'y a pas robot"); // fonction erreur à rajouter dans le module error !
						exit(0); 
					}
					break;
				case RO :
					if(strncmp("FIN_LISTE",tab,lg_fin)!=0)
					{
						while (sscanf(tab,"%f %f %f", &a,&b,&c)==3) 	//lire les données et les ranger dans le tas dans une liste chaînée
						{
							analyse_angle_bot (c);
							courant = liste_ajouter(tete_liste);
							courant->numero = nbbot_recu++;
							courant->corps.x = a;
							courant->corps.y = b;
							courant->angle = c;
						}
					}
					break;
			}
			analyse_nbrbot(nbbot_att, nbbot_recu, __LINE__ );	
		}
	}
	fclose(fichier);
}

ROBOT * liste_ajouter ( ROBOT ** p_tete ) //fonction copié-collé serie17
{
	 ROBOT *new_bot;
	 if (!(new_bot= (ROBOT*) malloc(sizeof(ROBOT))))
	 {
		 printf("problem d'allocation dasn %s\n",__func__);// fonction erreur à ajouter dans le module error
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
		error_fin_liste_robots(line);
		exit(0);
	}
	if(nbbot_att<nbbot_recu)
	{
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

}
