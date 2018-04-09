#include "utilitaire.h"
#include "error.h"
#include "constantes.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


enum Etat_lecture {NB_PAR,PAR};
#define LG_FIN_LISTE 9
typedef struct particule PARTICULE;
struct particule
{
	int numero;
	double energie;
	double rayon;
	S2D corps;
	PARTICULE* suivant;
};

void lecture_particules(PARTICULE** tete_liste, char* nom_fichier);
void analyse_validite_part(double energie, double rayon,double pos_x, 
														double pos_y);
int chercheur_ligne(char* nom_fichier);
PARTICULE * liste_add ( PARTICULE ** p_tete );
void analyse_nbrpart(int nbpart_att,int nbpart_recu,unsigned int ligne);
void liste_show ( PARTICULE *tete );
void part_destruction ( PARTICULE ** p_tete, PARTICULE *el);
void part_total_destruction(PARTICULE**tete_liste);
void test3 (void)
{
	printf("problem de pointeur dans la ligne %d \n", __LINE__);	
}

int main (int argc, char* argv[])
{
	if(argc !=3)
	{
		printf("erreur de lecture, entrées des fichiers \n");
		printf("exectubale suivi du mode et enfin le fichier a lire\n");
		exit(0);
	}
	PARTICULE* tete_liste;
	lecture_particules(&tete_liste, argv[2]);
	liste_show(tete_liste);
	part_total_destruction(&tete_liste);
	free(tete_liste);
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
void lecture_particules(PARTICULE** tete_liste, char* nom_fichier)
{
	int nbpart_att,nbpart_recu=0, etat=NB_PAR;
	int ligne=0;
	float en,ray,pos_x,pos_y;
	int i; 
	int ligne_depart; 
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
			printf("ligne %d \n", ligne);
			printf("nbr de particules recus %d \n",nbpart_recu);
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
					else
					{
						printf("erreur il n'y a pas particules"); 
						exit(0); 
					}

				printf("etat est  %d\n",etat);
					break;
				case PAR :
					printf("je lis les donnees \n" );
					while(sscanf(deb,"%f %f %f %f",&en,&ray,&pos_x,
															&pos_y)==4)	//lire les données et les ranger dans le tas dans une liste chaînée
					{
						printf("energie:%f rayon:%f pos.x.%f pos.y:%f\n"
												,en,ray,pos_x,pos_y);
						analyse_validite_part(en, ray,pos_x,pos_y); //fonctions a reprendre !!!
						courant = liste_add(tete_liste); 		//fonctions a reprendre !!!
						courant->numero = nbpart_recu++;
						courant->energie= en;
						courant->rayon = ray;
						courant->corps.x = pos_x;
						courant->corps.y = pos_y;
						strtod(deb, &fin); // fonction du cours fichiers
						deb = (fin+8); //8 parce qu'on compte aussi 
					}
				break;
			}
			
		}	
		analyse_nbrpart(nbpart_att, nbpart_recu, ligne);		//fonctions a reprendre !!!
	}
	fclose(fichier);
}
void analyse_validite_part(double energie, double rayon,double pos_x, 
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
void analyse_nbrpart(int nbpart_att,int nbpart_recu,unsigned int ligne)
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
