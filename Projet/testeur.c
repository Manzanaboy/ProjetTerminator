#include <math.h>
#include <stdio.h>
//#include <stdbool.h>
#include "tolerance.h"
#include "constantes.h"


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
S2D		util_deplacement(S2D p, double alpha, double dist);
_Bool 	util_ecart_angle(S2D a, double alpha, S2D b, double *p_ecart_angle);
_Bool 	util_alignement(S2D a, double alpha, S2D b);

int main(void)
{

	double angle;
	S2D a = {3,6};
	S2D b = {3,-5};
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
		printf("\npoint dans cercle\n");
		}
	if(util_collision_cercle(c, d, p_dist)){
		printf("le cercle sont en collision \nen la distance entre les 2 centre est %f \n",distance);
		}
		
	S2D e = {3+2*EPSIL_ZERO,6};
	S2D f = {3,6};
	printf("\na est en x=%f y=%3f", a.x, a.y);
	double alpha=-M_PI/4;
	double longueur=5;
	a=util_deplacement(a, alpha, longueur);
	printf("\na est en x=%f y=%3f", a.x, a.y);
	if(util_ecart_angle(e,0,f, p_dist)){
		printf("\na et b > eplsilon zero");
		}
	util_alignement(a,util_angle(a,b)+0.00625,b);

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

S2D		util_deplacement(S2D p, double alpha, double dist)
{
	
	p.x = p.x + dist*cosf(alpha);
	p.y = p.y + dist*sinf(alpha);
	return p;
	}

_Bool 	util_ecart_angle(S2D a, double alpha, S2D b, double *p_ecart_angle)
{
	if((p_ecart_angle)){
		if(util_distance(a, b) > EPSIL_ZERO){
			*p_ecart_angle = util_angle(a,b) - alpha;
			util_range_angle(p_ecart_angle);
			return VRAIE;
			}
		}
	return FAUX;
	}
	
_Bool 	util_alignement(S2D a, double alpha, S2D b)
{
	double ecart_angle;
	double * p_ecart_angle = &ecart_angle;
	printf("\ndans alignement");
	printf("\n 1 ecart=%f alpha=%f",util_angle(a,b),alpha);
	if(util_ecart_angle(a,alpha,b,p_ecart_angle)){
		printf("\n 2 ecart=%f",ecart_angle);
		if(fabs(ecart_angle) < EPSIL_ALIGNEMENT){
				printf("\n cont align V");
			return VRAIE;
			}
		}
	printf("\n cont align F");
	return FAUX;
	}
bool 	util_inner_triangle(double la, double lb, double lc, double lb_new,
						    double * p_la_new);
{
	if((la>EPSILON_ZERO)&&(lc>EPSILON_ZERO)&&(lb>=0)&&((lb_new>=lb)
										||(lb_new<=lc)))
	{
		if(p_la_new)
		{
			double delta;
			double beta;
			beta = (pow(la,2)+pow(lc,2)-pow(lb,2))/(2*la*lc);
			delta = pow(2*lc*cos(beta),2)-4(pow(lc,2)-pow(lb_new,2));
			*p_la_new = (2*lc*cos(beta)-sqrt(delta))/2;
		}
		return true;
	}


}


