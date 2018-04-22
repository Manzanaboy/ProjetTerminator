/*!
 \file particule.c
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

#include "utilitaire.h"
#include "error.h"
#include "particule.h"
#include "constantes.h"
#include "draw.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <string.h>

enum Etat_lecture {NB_PAR,PAR};
#define LG_FIN_LISTE 9
#define ESP_PAR_PAR 8

/**
	 numero de la particule dans l'ordre d'appartion dans le fichier
	* commence à 1.
	* energie de la partcule, doit être inférieur à E_PARTICULE_MAX.
	* rayon de la particule, doit être compris en R_PARTICULE_MIN
	* et R_PARTICULE_MAX. 
	* Corps de la partciule est la position de son centre.Chaque 
	* coordonée doit être comprise en -DMAX ET + DMAX.
	* pointeur sur l'adresse de la prochaine particule dans la liste
 */ 
struct particule
{
	int numero;
	double energie;
	double rayon;
	S2D corps;
	PARTICULE* suivant;
};

void test3 (void)
{
	printf("problem de pointeur dans le fichier %s", __FILE__);		
}
int chercheur_ligne(char* nom_fichier)
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
		test3();
		fclose(fichier);
		exit(EXIT_FAILURE);
	}
}
void lecture_particules(PARTICULE** tete_liste, char* nom_fichier,
									char*mode_lecture, int*p_ok)
{
	int nbpart_att,nbpart_recu=0, etat=NB_PAR,ligne=0,i=0, ligne_depart; 
	float en,ray,pos_x,pos_y;
	PARTICULE* courant=NULL;
	char tab [80];
	char* deb = tab; 
	char*fin = NULL;
	ligne_depart = chercheur_ligne(nom_fichier);
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
						analyse_validite_part(en, ray,pos_x,pos_y,
												mode_lecture,p_ok);
						courant = liste_add(tete_liste); 		
						passage_donnees(en,ray,pos_x,pos_y,
															courant);
						strtod(deb, &fin); // fonction du cours fichiers
						deb = (fin+ESP_PAR_PAR);  
						nbpart_recu++;
					}
				break;
			}	
		}
		if(*p_ok)
		{
				analyse_nbrpart(nbpart_att, nbpart_recu,
											ligne,mode_lecture,p_ok);
		}	
	}
	fclose(fichier);
}
void analyse_validite_part(double energie, double rayon,double pos_x, 
						double pos_y,char*mode_lecture, int*p_ok)
{
	if((fabs(pos_x))>DMAX || (fabs(pos_y))>DMAX || energie<0 ||
	energie > E_PARTICULE_MAX || rayon < R_PARTICULE_MIN ||
	rayon>R_PARTICULE_MAX)
	{
		error_invalid_particule_value(energie,rayon, pos_x, pos_y);
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
PARTICULE * liste_add ( PARTICULE ** p_tete )
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
void analyse_nbrpart(int nbpart_att,int nbpart_recu,unsigned int ligne,
					char*mode_lecture, int*p_ok)
{
	if(nbpart_att>nbpart_recu)
	{
		error_fin_liste_particules(ligne);
		if(!(strncmp(mode_lecture,"Error",5)))
		{
			exit(0);
		}
		else
		{
			*p_ok=0;
		}
	}
	else if(nbpart_att<nbpart_recu)
	{
		error_missing_fin_liste_particules(ligne);
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
void liste_show ( PARTICULE *tete )
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
void part_destruction ( PARTICULE ** p_tete, PARTICULE *el)
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
void part_total_destruction(PARTICULE**p_liste)
{
	if(!p_liste)
	{
		test3();
	}
	PARTICULE *part = *p_liste;
	while(part->suivant != NULL)
	{
		part_destruction(p_liste,part);
		part = *p_liste;
	}
	part_destruction(p_liste,part);
}
void passage_donnees( double en, double ray,
					double pos_x, double pos_y, PARTICULE*courant)
{
	static int compteur_particule=1;
	courant->numero = compteur_particule++;
	courant->energie= en;
	courant->rayon = ray;
	courant->corps.x = pos_x;
	courant->corps.y = pos_y;
}
void particule_collision_part_part(PARTICULE*tete_liste_part,
								char*mode_lecture, int*p_ok)
{
	int collision=0;
	double dist =0;
	if(tete_liste_part && (tete_liste_part->suivant))
	{
		PARTICULE*courant1 = tete_liste_part;
		PARTICULE*courant2 = courant1->suivant;
		double* p_dist = NULL;
		p_dist = &dist;
		while ((collision==0)&&(courant2!=NULL))
		{
			C2D particule1 ={courant1->corps,courant1->rayon};
			C2D particule2 ={courant2->corps,courant2->rayon};
			if(util_collision_cercle(particule1,particule2,p_dist)) // rentrer les cercles et la distances
			{
				error_collision(PARTICULE_PARTICULE,courant1->numero,
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
void particule_acces_donnees (PARTICULE**courant,double*p_posx,
			double*p_posy, double*p_energie, double*p_rayon, int*p_num)
{
	if(courant)
	{
		*p_posx  = (*courant)->corps.x;
		*p_posy  = (*courant)->corps.y;
		*p_rayon  = (*courant)->rayon;
		*p_energie = (*courant)->energie;
		*p_num = (*courant)->numero;
		*courant=(*courant)->suivant;
	}	
}
void particule_dessin(PARTICULE*tete_liste)
{
	double part_x,part_y,part_en, part_ray;
	int part_num;
	double *p_part_x=&part_x;
	double *p_part_y=&part_y;
	double *p_part_en=&part_en;
	double *p_part_ray=&part_ray;
	int *p_part_num=&part_num;
	if(tete_liste)
	{
		PARTICULE*courant = tete_liste;
		while(courant)
		{
			particule_acces_donnees(&courant,p_part_x,
							p_part_y,p_part_en,p_part_ray,p_part_num);
			draw_part(*p_part_x,*p_part_y,*p_part_ray);
		}
	}
}
