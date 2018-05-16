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
ROBOT* bot_creation (void);
void bot_destruction ( ROBOT ** p_tete, ROBOT *el);
void bot_total_destruction (ROBOT** p_liste);
void test2 (void)
{
	printf("problem de pointeur dans la fonction %d \n", __LINE__);	
}

int main (int argc, char* argv[])
{
	if(argc !=2)
	{
		printf("erreur de lecture \n");
		exit(0);
	}

	ROBOT *tete_liste=NULL;
	//~ tete_liste = bot_creation();
	lecture_robots(&tete_liste, argv[1]);
	liste_afficher(tete_liste);
	bot_total_destruction(&tete_liste);
	liste_afficher(tete_liste);
	return 0;
	
}
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
		while((fgets(tab,80,fichier))&&(strncmp("FIN_LISTE",tab,lg_fin))!=0)
		{
			deb = tab;
			compteur++;
			test2();
			printf("ligne %d \n", compteur);
			printf("nbr de robots recus %d \n",nbbot_recu);
			printf("problem de pointeur dans la fonction %s", __func__);	
			test2();
			while((tab[i]==' ' )||tab[i]=='\t')
			{
				i++;
			}
			if((tab[i]=='#')||(tab[i]=='\n')||(tab[i]=='\r')||(tab[i]==' ')||(tab[i]=='\t'))
			{
				continue;
			}

			switch (etat)
			{
				case NB_R : 
				printf("compteur switch %d\n",compteur );
					if (sscanf(tab,"%d",&nbbot_att)==1)
					{
						etat++;
					}
					else
					{
						printf("erreur il n'y a pas robot"); // fonction erreur à rajouter dans le module error !
						exit(0); 
					}

				printf("etat est  %d\n",etat);
					break;


				case RO :
					printf("je lis les donnees \n" );
					while (sscanf(deb,"%f %f %f", &a,&b,&c) ==3)	//lire les données et les ranger dans le tas dans une liste chaînée
					{
						printf("a%f b%f c%f\n",a,b,c);
						analyse_angle_bot (c);
						courant = liste_ajouter(tete_liste);
						courant->numero = nbbot_recu++;
						courant->corps.x = a;
						courant->corps.y = b;
						courant->angle = c;
						strtod(deb, &fin); // fonction du cours fichiers
						deb = (fin+5); //5 parce qu'on compte aussi les espace
					}
				break;
			}
			
		}	
		analyse_nbrbot(nbbot_att, nbbot_recu, compteur );	
		
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
