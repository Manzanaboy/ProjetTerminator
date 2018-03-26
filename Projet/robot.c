#include "utilitaire.h"


enum Etat_lecture {NB_R,RO};
typedef struct robot ROBOT;
struct robot
{
	S2D corps;
	double angle;
};

void lecture_robots(char* nom_fichier)
{
	int nb_r_att,nbr_r_recu, etat=NB_R;
	int lg_fin = 9;
	char tab [80];
	FILE * fichier =NULL;
	if(fichier =(fopen(nom_fichier,"r"))!=0)
	{
		while(fgets(tab,80,fichier))
		{
			if((tab[0]=='#')||(tab[0]=='\n')||(tab[0]=='\r'))
			continue; 
			switch (etat)
			{
				case NB_R : 
					if (sscanf(tab,"%d",&nb_r)==1)
					{
						etat++
					}
					else
					{
						printf("erreur il n'y a pas robot"); // fonction erreur à rajouter dans le module error !
						exit(0); 
					}
					break;
				case RO :
					while(strncmp("FIN_LISTE",tab,lg_fin)!=0)
					{
						//lire les données et les ranger dans le tas dans une liste chaînée
					}
					break
			}
	
		}
	}
	
	
}
