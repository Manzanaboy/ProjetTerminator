#include "utilitaire.h"
#include "error.h"
#include "particule.h"
#include "constantes.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <string.h>

enum Etat_lecture {NB_PAR,PAR};
#define LG_FIN_LISTE 9

struct particule
{
	int numero;
	double energie;
	double rayon;
	S2D corps;
	PARTICULE* suivant;
};

void particule_test3 (void)
{
	printf("problem de pointeur dans le fichier %s", __FILE__);		
}
int particule_chercheur_ligne(char* nom_fichier)
{
	int line;
	char tab[80];
	FILE * fichier =fopen(nom_fichier,"r");
	if(fichier)
	{
		while((fgets(tab,80,fichier))&&
								(strncmp("FIN_LISTE",tab,
													LG_FIN_LISTE))!=0)
		{
			line++;
		}
		line++;
		fclose(fichier);
		return line;
	}
	else 
	{
		particule_test3();
		fclose(fichier);
		exit(EXIT_FAILURE);
	}
}
void particule_lecture_particules(PARTICULE** tete_liste, char* nom_fichier)
{
	int nbpart_att,nbpart_recu=0, etat=NB_PAR,ligne=0,i=0, ligne_depart; 
	float en,ray,pos_x,pos_y;
	PARTICULE* courant=NULL;
	char tab [80];
	char* deb = tab; 
	char*fin = NULL;
	ligne_depart = particule_chercheur_ligne(nom_fichier);
	FILE * fichier =fopen(nom_fichier,"r");
	if(fichier)
	{
		while(ligne!=ligne_depart)
		{
			fgets(tab,80,fichier);
			ligne++;
		}
		while((fgets(tab,80,fichier))&&(strncmp("FIN_LISTE",tab,
													LG_FIN_LISTE))!=0)
		{
			deb = tab;
			ligne++;
			while((tab[i]==' ' )||tab[i]=='\t')
			{
				i++;
			}
			if((tab[i]=='#')||(tab[i]=='\n')||(tab[i]=='\r')||
				(tab[i]==' ')||(tab[i]=='\t'))
			{
				continue;
			}
			switch (etat)
			{
				case NB_PAR : 
					if (sscanf(tab,"%d",&nbpart_att)==1)
					{
						etat++;
					}
					break;
				case PAR :
					while(sscanf(deb,"%f %f %f %f",&en,&ray,&pos_x,
															&pos_y)==4)
					{
						particule_analyse_validite_part(en, ray,pos_x,pos_y);
						courant = particule_liste_add(tete_liste); 		
						particule_passage_donnees(nbpart_recu,en,ray,pos_x,pos_y,
															courant);
						strtod(deb, &fin); // fonction du cours fichiers
						deb = (fin+8); //8 parce qu'on compte aussi 
						nbpart_recu++;
					}
				break;
			}	
		}	
		particule_analyse_nbrpart(nbpart_att, nbpart_recu, ligne);
	}
	fclose(fichier);
}
void particule_analyse_validite_part(double energie, double rayon,double pos_x, 
														double pos_y)
{
	if((fabs(pos_x))>DMAX || (fabs(pos_y))>DMAX || energie<0 ||
	energie > E_PARTICULE_MAX || rayon < R_PARTICULE_MIN ||
	rayon>R_PARTICULE_MAX)
	{
		error_invalid_particule_value(energie,rayon, pos_x, pos_y);
		exit(0);
	}
}
PARTICULE * particule_liste_add ( PARTICULE ** p_tete )
{
	 PARTICULE *new_part;
	 if (!(new_part= (PARTICULE*) malloc(sizeof(PARTICULE))))
	 {
		 printf("problem d'allocation dasn %s\n",__func__);// fonction erreur à ajouter dans le module error
		 exit (EXIT_FAILURE);
	}
	 new_part->suivant = *p_tete;
	 *p_tete = new_part;
	 return new_part;
}
void particule_analyse_nbrpart(int nbpart_att,int nbpart_recu,unsigned int ligne)
{
	if(nbpart_att>nbpart_recu)
	{
		ligne++;
		error_fin_liste_particules(ligne);
		exit(0);
	}
	else if(nbpart_att<nbpart_recu)
	{
		ligne++;
		error_missing_fin_liste_particules(ligne);
		exit(0);
	}
}
void particule_liste_show ( PARTICULE *tete )
{
	PARTICULE* voiture;
	
	if(tete)
	{
		voiture = tete;
		do
		{
			printf("particule %d \n", voiture->numero);
			printf("%f ", voiture->corps.x);
			printf("%f \n", voiture->corps.y);
			printf("%f \n", voiture->energie);
			printf("%f \n", voiture->rayon);
			voiture = voiture->suivant;
		}
		while((voiture)!=NULL);
	}
	else 
	{
		printf("erreur de tete liste, ja'rrive pas à lire %s",__func__);
	}

}
void particule_part_destruction ( PARTICULE ** p_tete, PARTICULE *el)
{
	PARTICULE *part = *p_tete;
	if(p_tete)
	{
		if (part == el)
		{
			*p_tete= part->suivant;
			free(part);
		}
		else
		{
			PARTICULE *test_part = *p_tete;
			while ((test_part->suivant !=NULL)&&(test_part->suivant!= el))
			{
				test_part = test_part->suivant;
			}
			if(test_part->suivant !=NULL)
			{
				PARTICULE * bad_part = test_part->suivant;
				test_part->suivant = test_part->suivant->suivant;
				free(bad_part);
			}
		}
	}
}
void particule_part_total_destruction(PARTICULE**p_liste)
{
	if(!p_liste)
	{
		test3();
	}
	PARTICULE *part = *p_liste;
	while(part->suivant != NULL)
	{
		particule_part_destruction(p_liste,part);
		part = *p_liste;
	}
	part_destruction(p_liste,part);
}
void particule_passage_donnees(int nbpart_recu, double en, double ray,
					double pos_x, double pos_y, PARTICULE*courant)
{
	courant->numero = nbpart_recu++;
	courant->energie= en;
	courant->rayon = ray;
	courant->corps.x = pos_x;
	courant->corps.y = pos_y;
}
