/*
 *  Brief: ce module s'accupe de lire les données qui concernent les 
 * dans un fichier fourni. Et d'appeler les bonnes focntions en cas 
 * d'erreur. 
 */
#include "utilitaire.h"
#include "error.h"
#include "robot.h"


enum Etat_lecture {NB_R,RO};
typedef struct robot ROBOT;
struct robot
{
	int numero;
	S2D corps;
	double angle;
	ROBOT* suivant;
};

void lecture_robots(ROBOT** tete_liste, char* nom_fichier)
{
	int nbbot_att,nbbot_recu=0, etat=NB_R;
	int lg_fin = 9;
	int compteur=0;
	float a,b,c;
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
					while (sscanf(deb,"%f %f %f", &a,&b,&c) ==3)
					{
						analyse_angle_bot (c);
						courant = liste_ajouter(tete_liste);
						courant->numero = nbbot_recu++;
						courant->corps.x = a;
						courant->corps.y = b;
						courant->angle = c;
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
	 ROBOT *new_bot;
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
	return tete_liste;
}

void bot_total_destruction (**ROBOT p_liste)
{
	ROBOT *bot = *p_liste;
	while(bot->suivant != NULL)
	{
		liste_retirer (p_liste,bot);
		bot = *p_liste;
	}
	liste_retirer (p_liste,bot);
}

void bot_destruction ( ELEMENT ** p_tete, ELEMENT *el )
{
	ELEMENT *bot = *p_tete;
	if(p_tete)
	{
		if (vbot == el)
		{
			*p_tete= bot->suivant;
			free(bot);
		}
		else
		{
			ELEMENT *test_bot = *p_tete;
			while ((test_bot->suivant !=NULL)&&(test_bot->suivant!= el))
			{
				test_bot = test_bot->suivant;
			}
			if(test_bot->suivant !=NULL)
			{
				ELEMENT * bad_bot = test_bot->suivant;
				test_bot->suivant = ancienne_bot->suivant->suivant;
				free(bad_bot);
			}
		}
	}
}
