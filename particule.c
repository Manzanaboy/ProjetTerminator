

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
#include <assert.h>

enum Etat_lecture {NB_PAR,PAR};
enum Etat_Lect {RIEN, VALEURS};
#define LG_FIN_LISTE 9
#define ESP_PAR_PAR 8
#define MAX_ROBOT_PART 1


static PARTICULE* tete_liste_part=NULL;
static int NB_TOT_PART =0;
static float energie_initiale=0;

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
	int nb_bot_part;
};


int chercheur_ligne(char* nom_fichier)
{
	int line=0;
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
		printf("problème pointeur l.%d in file %s",__LINE__,__FILE__);
		fclose(fichier);
		exit(EXIT_FAILURE);
	}
}
void lecture_particules(char* nom_fichier,char*mode_lecture,int*p_ok)
{
	int nbpart_att,nbpart_recu=0, etat=NB_PAR;
	int ligne=0,i=0,ligne_depart=0;
	int compteur_particule=1; 
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
				i++;
			if((tab[i]=='#')||(tab[i]=='\n')||(tab[i]=='\r')||
				(tab[i]==' ')||(tab[i]=='\t'))
				continue;
			switch (etat)
			{
				case NB_PAR : 
					if (sscanf(tab,"%d",&nbpart_att)==1)
						etat++;
					break;
				case PAR :
					while(sscanf(deb,"%f %f %f %f",&en,&ray,&pos_x,
									&pos_y)==4)
					{
						analyse_validite_part(en, ray,pos_x,pos_y,
												mode_lecture,p_ok);
						courant = liste_add(); 
						courant->numero = compteur_particule++;		
						passage_donnees(en,ray,pos_x,pos_y,courant);
						strtod(deb, &fin); 
						deb = (fin+ESP_PAR_PAR);  
						nbpart_recu++;
					}
					break;
			}	
		}
		if(*p_ok)
			analyse_nbrpart(nbpart_att, nbpart_recu,
									ligne,mode_lecture,p_ok);
	}
	fclose(fichier);
	NB_TOT_PART= nbpart_att;
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

PARTICULE * liste_add ()
{
	PARTICULE *new_part=NULL;
	if (!(new_part= (PARTICULE*) malloc(sizeof(PARTICULE))))
	 {
		printf("problem d'allocation dasn %s\n",__func__);
		exit (EXIT_FAILURE);
	}
	new_part->suivant = tete_liste_part;
	tete_liste_part = new_part;
	return new_part;
}

void analyse_nbrpart(int nbpart_att,int nbpart_recu,unsigned int ligne,
					char*mode_lecture, int*p_ok)
{
	if(nbpart_att>nbpart_recu)
	{
		ligne++;
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
void liste_show ()
{
	PARTICULE* voiture;
	
	if(tete_liste_part)
	{
		voiture = tete_liste_part;
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
void part_destruction (PARTICULE *el)
{
	PARTICULE *part = tete_liste_part;
	if(tete_liste_part)
	{
		if (part == el)
		{
			tete_liste_part= part->suivant;
			free(part);
		}
		else
		{
			PARTICULE *test_part = tete_liste_part;
			while ((test_part->suivant!=NULL)&&(test_part->suivant!= el))
			{
				test_part = test_part->suivant;
			}
			if(test_part->suivant !=NULL)
			{
				PARTICULE * bad_part = test_part->suivant;
				test_part->suivant = test_part->suivant->suivant;
				free(bad_part);
				NB_TOT_PART--;
			}
		}
	}
}
void part_total_destruction()
{
	if(!tete_liste_part)
	{
		printf("problème pointeur l.%d in file %s\n",__LINE__,__FILE__);
	}
	PARTICULE *part = tete_liste_part;
	while(part->suivant != NULL)
	{
		part_destruction(part);
		part =tete_liste_part;
	}
	part_destruction(part);
	tete_liste_part=NULL;
}
void passage_donnees( double en, double ray,
					double pos_x, double pos_y, PARTICULE*courant)
{
	courant->energie= en;
	courant->rayon = ray;
	courant->corps.x = pos_x;
	courant->corps.y = pos_y;
	courant->nb_bot_part =0;
}
void particule_collision_part_part(char*mode_lecture, int*p_ok)
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
			if(util_collision_cercle(particule1,particule2,p_dist)) 
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
	else
	{
		printf("problème de pointeur %s l.%d",__func__,__LINE__);
	}
}
void particule_dessin()
{
	double part_x,part_y,part_en, part_ray;
	int part_num;
	double *p_part_x=&part_x;
	double *p_part_y=&part_y;
	double *p_part_en=&part_en;
	double *p_part_ray=&part_ray;
	int *p_part_num=&part_num;
	if(tete_liste_part)
	{
		PARTICULE*courant = tete_liste_part;
		while(courant)
		{
			particule_acces_donnees(&courant,p_part_x,
							p_part_y,p_part_en,p_part_ray,p_part_num);
			draw_part(*p_part_x,*p_part_y,*p_part_ray);
		}
	}
}

PARTICULE* particule_acces_tete()
{
	if(tete_liste_part)
	{
		return tete_liste_part;
	}
	else
	{
		printf("problème accès a la tete des part l.%d \n", __LINE__);
		return NULL;
	}
}

double particule_tri(int compteur_deja_lue,int deja_lues[])
{
	double rayon_max=0;
	int compteur=0;
	int arret=0;
	int suite=1;
	int i=0;
	PARTICULE*courant = NULL;
	int max = 0;
	if(tete_liste_part)
	{
		courant = tete_liste_part;
		for(compteur=0;compteur<NB_TOT_PART;compteur++)
		{
			for(i=0;i<(compteur_deja_lue);i++)
			{
				if((courant->numero)==(deja_lues[i]))
				{
					if(courant->suivant)
					{
						courant=courant->suivant;
						suite=0;
					}
					else
					{
						arret=1;
					}
				}
			}
			if(arret)
			{
				break;
			}
			if(!suite)
			{
				suite=1;
				continue;
			}
			if(rayon_max<(courant->rayon))
			{
				rayon_max=courant->rayon;
				max = courant->numero;
			}
			if(courant->suivant)
			{
				courant =courant->suivant;
			}
			if(max==100)
			{
				continue;
			}
		}
		
		deja_lues[compteur_deja_lue]=max;
	}
	return rayon_max;
}

int particule_nombre_total()
{
	return NB_TOT_PART;
}


void particule_decomposition(PARTICULE* part)
{
	int nb=NB_TOT_PART+1;
	PARTICULE *part1, *part2, *part3, *part4;
	part1=liste_add();
	part2=liste_add();
	part3=liste_add();
	part4=liste_add();

	int cadran=1;
	part_change_part(part1, part,cadran,nb);
	cadran+=2;
	nb++;
	part_change_part(part2, part,cadran,nb);
	cadran+=2;
	nb++;
	part_change_part(part3, part,cadran,nb);
	cadran+=2;
	nb++;
	part_change_part(part4, part,cadran,nb);
	
	part_destruction(part);
	

}

void part_change_part(PARTICULE* part_change, PARTICULE* part_decomp,
					  int nb_part,int num)
{
	
	part_change->corps.x= part_decomp->corps.x + 
				sqrt(2)*(R_PARTICULE_FACTOR*part_decomp->rayon)*
				cos(nb_part*M_PI/4);
	part_change->corps.y= part_decomp->corps.y -
				sqrt(2)*(R_PARTICULE_FACTOR*part_decomp->rayon)*
				sin(nb_part*M_PI/4);
	part_change->rayon= part_decomp->rayon*R_PARTICULE_FACTOR;
	part_change->numero=num;
	part_change->energie= part_decomp->energie*E_PARTICULE_FACTOR;
	
	
}

int part_decomposition_start()
{
	PARTICULE*courant=NULL;
	int nb_decomp=0;
	float proba=0;
	int compteur=0;
	int sucess=0;
	if(tete_liste_part)
	{
		courant=tete_liste_part;
		while(compteur<NB_TOT_PART)
		{
			proba=(float)rand()/(float)RAND_MAX;
			printf("proba est de %f l.%d\n ",proba,__LINE__);
			if((proba<=DECOMPOSITION_RATE)&&
								(courant->rayon>R_PARTICULE_MIN))
			{
				particule_decomposition(courant);
				nb_decomp++;
				sucess=1;
		
			}
			if(courant->suivant)
			{
				courant=courant->suivant;
				compteur++;
			}
			else
			{
				courant=NULL;
				compteur=NB_TOT_PART;
			}
		}
	}
	NB_TOT_PART = NB_TOT_PART + nb_decomp*4;
	liste_show();
	return sucess;
}

void particule_sauver(char* fichier_save)
{	
	PARTICULE* courant_part=NULL;
	FILE * p_fichier;
	if((p_fichier = fopen(fichier_save, "a")))
	{
		courant_part = tete_liste_part;
		fprintf(p_fichier, "#liste particules\n%d",NB_TOT_PART);
		while(courant_part)
		{
			fprintf(p_fichier, "\n%f %f %f %f",courant_part->energie,
					courant_part->rayon,courant_part->corps.x,
					courant_part->corps.y);
			courant_part = courant_part->suivant;
		}
		fprintf(p_fichier, "\nFIN_LISTE\n");
		fclose(p_fichier);
	}
	else
	{
		printf("\nerreur du fichier save");
	}
}

PARTICULE* particule_correspondante (int num_part)
{
	PARTICULE* cherchee=NULL;
	if(tete_liste_part)
	{
		cherchee = tete_liste_part;
		while((cherchee->numero)!= num_part)
		{
			cherchee=cherchee->suivant;
		}
		return cherchee;
	}
	else 
	{
		printf("erreur de tete liste, ja'rrive pas à lire %s",__func__);
		return NULL;
	}
}

int particule_existe(S2D coord)
{
	PARTICULE*courant=NULL;
	if(tete_liste_part)
	{
		courant=tete_liste_part;
		while(courant)
		{
			if((courant->corps.x==coord.x)&&(courant->corps.y==coord.y))
			{
				return 1;
			}
			if(courant->suivant)
			{
				courant=courant->suivant;
			}
			else
			{
				break;
			}
		}
		return 0;
	}
	else
	{
		printf("problème d'association %s l.%d\n",__func__,__LINE__);
	}
}

void particule_ajout_robot(PARTICULE*courant)
{
	if(courant)
	{
		if((courant->nb_bot_part)<MAX_ROBOT_PART)
		{
			courant->nb_bot_part++;
		}
		else
		{
			printf("max de robto par part atteint\n");
		}
	}
	else
	{
		printf("problème d'association %s l.%d",__func__,__LINE__);
	}
}

int particule_verify_nb_bot(PARTICULE*courant)
{
	if(courant)
	{
		if((courant->nb_bot_part)>=MAX_ROBOT_PART)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		printf("problème d'association %s l.%d",__func__,__LINE__);

	}
	
}

void particule_reach (PARTICULE*courant,double*p_posx,double*p_posy)
{
	if(courant)
	{
		*p_posx  = courant->corps.x;
		*p_posy  = courant->corps.y;		
	}
		else
	{
		printf("problème d'association %s l.%d",__func__,__LINE__);
		exit(0);
	}
}

float particule_energie()
{
	float energie_particule=0;	
	PARTICULE* courant_part=NULL;
	courant_part = tete_liste_part;
	
	while(courant_part)
	{
			energie_particule += tete_liste_part->energie;
			printf("----------- Energie part: %f -----------\n", tete_liste_part->energie);
			courant_part = courant_part->suivant;
	}

	printf("------------------ ENERGIE TOTALE INITIALE %f ------------------\n ------------------ ENERGIE ACTUEL %f ------------------\n", energie_initiale, (energie_initiale-energie_particule)/energie_initiale *100 );

	return (energie_initiale-energie_particule)/energie_initiale *100;
}

int particule_collision(C2D rob,double *p_dist, double *p_rayon)
 {
	PARTICULE* courant=NULL;
	C2D part;
	if((tete_liste_part)) return -1;
	courant = tete_liste_part;
	while(courant)
	{
		part.centre = courant->corps;
		part.rayon = courant->rayon;
		if (util_collision_cercle(rob, part, p_dist))
		{
			*p_rayon = courant->rayon;
			return courant->numero;
		}
		courant = courant->suivant;
	}
	return 0;
}
void test_colision()
{
	int ok=1;
	double *p_dist, *p_rayon;
	if(!(tete_liste_bot)) ok = 0;
	if(ok)
	{
		C2D bobot= {tete_liste_bot->corps, R_ROBOT};
		if(particule_collision(bobot, p_dist,p_rayon))
		{
			printf("particule touchee");
		}
	}
}
