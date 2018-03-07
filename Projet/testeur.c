#include <math.h>
#include <stdio.h>
#include "tolerance.h"


#define carre 2
enum bool{FAUX,VRAIE};


typedef struct S2d S2D;
struct S2d
{
	double x;
	double y;
};
typedef struct C2d C2D;
struct C2d
{
	S2D centre;
	double rayon;
};

void 	util_range_angle(double * p_angle);
double 	util_angle(S2D a, S2D b);
_Bool   util_point_dehors(S2D a, double max);
_Bool 	util_alpha_dehors(double alpha);
_Bool util_point_dans_cercle(S2D b, C2D c);
_Bool 	util_collision_cercle(C2D a, C2D b, double * p_dist);

int main(void)
{

	double angle;
	S2D a = {3,6};
	S2D b = {3,5};
	C2D c ={a,2};
	C2D d = {b,2};
	double distance;
	double *p_dist;
	p_dist = &distance;
	angle = util_angle(a,b);
	printf("\nl'angle est %f",angle);
	if(util_point_dehors(a, 5)){
		printf("\nvraie");
		}
	if(util_alpha_dehors(M_PI/3)){
		printf("\nangle plus grand");
		}
	if(util_point_dans_cercle(b,c)){
		printf("\npoint dans cercle");
		}
	if(util_collision_cercle(c, d, p_dist)){
		printf("le cercle sont en collision en la distance entre les 2 centre est %f \n",distance);
		}

}
double 	util_distance(S2D a, S2D b)
{
	double dist, distx, disty;
	distx = fabs(b.x - a.x);
	disty = fabs(b.y - a.y);
	dist = sqrt(pow(distx,carre)+pow(disty,carre));
	return dist;
}
double 	util_angle(S2D a, S2D b)
{
	double alpha, distx, disty;
	double * p_alpha;
	p_alpha= &alpha;
	disty = (b.y - a.y);
	distx = (b.x - a.x);
	alpha = atan2(disty,distx);
	util_range_angle(p_alpha);
	return alpha;
}
void 	util_range_angle(double * p_angle)
{
	if (util_alpha_dehors(*p_angle))
	{
		*p_angle = *p_angle + M_PI;
	}
	else
	{
		
		if(*p_angle==(-M_PI))
		{
			*p_angle = *p_angle + 2* M_PI;
		}
	}
}

_Bool   util_point_dehors(S2D a, double max)
{
	if(fabs(a.x) > max || fabs(a.y) > max)
	{
		return VRAIE;
	}
	return FAUX;
}

_Bool 	util_alpha_dehors(double alpha)
{
	if((alpha < -M_PI) || (alpha > M_PI))
	{
		return VRAIE;
	}
	return FAUX;
}

_Bool 	util_point_dans_cercle(S2D a, C2D c)
{
	double dist;
	dist = util_distance(a,c.centre);
	if(dist < (c.rayon - EPSIL_ZERO))
	{
		return VRAIE;
	}
	return FAUX;
}
_Bool 	util_collision_cercle(C2D a, C2D b, double * p_dist)
{
	*p_dist = util_distance(a.centre,b.centre);
	if(*p_dist < ((a.rayon + b.rayon)- EPSIL_ZERO))
	{
		return VRAIE;
	}
	return FAUX;
}
