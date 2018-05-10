#include "utilitaire.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include <unistd.h>


typedef struct robot ROBOT;
struct robot
{
	int numero;
	S2D corps;
	double angle;
	ROBOT* suivant;
};

typedef struct particule PARTICULE;
struct particule
{
	int numero;
	double energie;
	double rayon;
	S2D corps;
	PARTICULE* suivant;
};

void deplacement(PARTICULE* part, ROBOT* rob)
{
	double alpha=0, dist=0, v_rotation=0, v_translation=0;
	double dist_contact=R_ROBOT + part->rayon;
	dist=util_distance(rob->corps, part->corps);

	if( ! (util_alignement(rob->corps, rob->angle, part->corps)) ) //ROTATION
	{
		//ca tourne si pas aligné

		if( util_ecart_angle(rob->corps, rob->angle, part->corps, &alpha) ) //inutile car tjrs vrai
		{
			if(fabs(alpha/DELTA_T)<VROT_MAX) 
				v_rotation=alpha/DELTA_T;
			else
				v_rotation=VROT_MAX; 

			//printf("vRot = %lf\n", v_rotation);

			if(alpha > 0) rob->angle+= v_rotation*DELTA_T;
			else rob->angle-= v_rotation*DELTA_T; 
		}

		//printf("Not aligned\n");
		//printf("rob part angle = %lf\n", util_angle(rob->corps, part->corps));
		//printf("Robot angle %lf\n", rob->angle);
	}
	
/*	else 
	{
		//printf("no rotation, aligned\n");
		//printf("Rob anbgle: %lf, part rob angle: %lf\n", rob->angle, util_angle(rob->corps, part->corps));
	}
*/		
	printf("dist: %lf, dist_contact %lf, diff: %lf \n \n", dist, dist_contact,dist-dist_contact);
	
	if(fabs(dist) > dist_contact+EPSIL_ZERO) // avance // ??? Tolérance?? 
	{	
		if(fabs(dist-dist_contact)/DELTA_T < VTRAN_MAX)
		{
			v_translation=(dist-dist_contact)/DELTA_T;
		}

		else
			v_translation=VTRAN_MAX;

		printf("v_translation= %lf \n ", v_translation);
		rob->corps=util_deplacement(rob->corps, rob->angle, v_translation*DELTA_T);
		
	}
	else
	{
//		printf("dist2: %lf, dist_contact2 %lf, diff2: %lf \n \n", dist, dist_contact, dist-dist_contact);
		printf("STOPPED\n");
		exit(EXIT_FAILURE);
	}
}


int main()
{
	double a = 0;
	int b, i=0;
	ROBOT* r = malloc(sizeof(ROBOT));
	PARTICULE* p = malloc(sizeof(PARTICULE));

	if(r==NULL) exit(EXIT_FAILURE);
	if(p==NULL) exit(EXIT_FAILURE);

	r->corps.x = 0;
	r->corps.y = 0;
	r->angle = 0;

	p->corps.x = 5;
	p->corps.y = 5;
	p->rayon = 0;

//	if((util_alignement(r->corps, M_PI/6, p->corps)))
//		printf("aligned\n");

	while(1)
	{
		printf("\n i= %d \n", i++);
		if(!util_ecart_angle(p->corps, r->angle, r->corps, &a))
			break;

		deplacement(p, r);
		printf("dx: %lf, dy: %lf\n", r->corps.x,r->corps.y);
		//printf("dx: %lf, dy: %lf\n", fabs(r->corps.x - p->corps.x), fabs(r->corps.y - p->corps.y));
		//printf("px: %lf, py: %lf\n", p->corps.x, p->corps.y);
		//sleep(1);
	}
}
