#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//----------------------------------- Define -----------------------------------//
enum Etat_Lect {VALEURS, RIEN};


//----------------------------------- Structures -----------------------------------//
typedef struct particule PARTICULE;

struct particule
{
	double rayon;
	double xc;
	double yc;
	PARTICULE* next;	
};

//----------------------------------- Fonctions -----------------------------------//
PARTICULE* init(int etat);
void init_valeurs(PARTICULE* part);
void decomposition(PARTICULE* part, PARTICULE* avant, PARTICULE* apres);
void change_part(PARTICULE* part_change, PARTICULE* part_decomp);

//----------------------------------- Code -----------------------------------//

int main()
{

	PARTICULE* first=NULL;
	PARTICULE* second=NULL;
	PARTICULE* third=NULL;

//	printf("--------,----------1\n");
	int test=VALEURS;
	first=init(test);
	second=init(VALEURS);
	third=init(VALEURS);
	
//	printf("-------------------2\n");
	first->next= second;
	second->next= third;
	third->next= NULL;
	
//	printf("-------------------3\n");

	// printf("rayon: %f \n", first->rayon);
	// printf("rayon: %f \n", second->rayon);
	// printf("second: %p\n",second );
	// printf("next: %p \n", first->next);

	printf("XC %f \n",second->xc );

	decomposition(second, first, third);
}

PARTICULE* init(int etat)
{
//	printf("Init particules \n");
	PARTICULE* part=NULL;
	part=malloc(sizeof(PARTICULE));
	if (part==NULL) exit(EXIT_FAILURE);
	if(!etat) init_valeurs(part);
	return part;

}

void init_valeurs(PARTICULE* part)
{
	printf("Entrez la valeur du rayon de la particule: \n");
	scanf("%lf", &part->rayon);
	printf("Entrez la valeur du x de la particule: \n");
	scanf("%lf", &part->xc);
	printf("Entrez la valeur du y de la particule: \n");
	scanf("%lf", &part->yc);

}

void decomposition(PARTICULE* part, PARTICULE* avant, PARTICULE* apres)
{
	printf("xc %lf\n", part->xc);

	PARTICULE *part1, *part2, *part3, *part4;
	part1=init(RIEN);
	part2=init(RIEN);
	part3=init(RIEN);
	part4=init(RIEN);

	printf("OK \n");

	avant->next=part1;
	part4->next=apres;

	change_part(part1, part);
	change_part(part2, part);
	change_part(part3, part);
	change_part(part4, part);

	// part2->xc= part->xc - part->rayon * cos(3.14159265/4);
	// part2->yc= part->yc + part->rayon * sin(3.14159265/4);
	// part2->rayon= part->rayon/4;

	// part3->xc= part->xc - part->rayon * cos(3.14159265/4);
	// part3->yc= part->yc - part->rayon * sin(3.14159265/4);
	// part3->rayon= part->rayon/4;

	// part4->xc= part->xc + part->rayon * cos(3.14159265/4);
	// part4->yc= part->yc - part->rayon * sin(3.14159265/4);
	// part4->rayon= part->rayon/4;

//	printf("xc Part1: %lf \n", part1->xc);
//	printf("xc : %lf, rayon %lf, cos %lf, xc1 %lf \n",part->xc , part->rayon ,cos(3.14159265/4) , part->xc + part->rayon* cos(3.14159265/4));

	free(part);

}

void change_part(PARTICULE* part_change, PARTICULE* part_decomp)
{
//	printf("Changement valeurs particules. \n");
	part_change->xc= part_decomp->xc + part_decomp->rayon * cos(3.14159265/4);
	part_change->yc= part_decomp->yc - part_decomp->rayon * sin(3.14159265/4);
	part_change->rayon= part_decomp->rayon/4; //Changer en ajoutant E_PARTICULE_FACTOR

}