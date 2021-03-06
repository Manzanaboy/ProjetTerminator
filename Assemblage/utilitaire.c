#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "tolerance.h"


#define carre 2


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

double 	util_distance(S2D a, S2D b);
void 	util_range_angle(double * p_angle);
double 	util_angle(S2D a, S2D b);
bool    util_point_dehors(S2D a, double max);
bool 	util_alpha_dehors(double alpha);
bool 	util_point_dans_cercle(S2D b, C2D c);
bool 	util_collision_cercle(C2D a, C2D b, double * p_dist);
S2D		util_deplacement(S2D p, double alpha, double dist);
bool 	util_ecart_angle(S2D a, double alpha, S2D b, double *p_ecart_angle);
bool 	util_alignement(S2D a, double alpha, S2D b);
bool 	util_inner_triangle(double la, double lb, double lc, double lb_new,
							double * p_la_new);


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
	if(p_angle)
	{
		if (util_alpha_dehors(*p_angle))
		{
			while (*p_angle <= -M_PI)
				*p_angle = *p_angle +2* M_PI;
		
			while (*p_angle > M_PI)
				*p_angle = *p_angle -2* M_PI;
		}
		
		else if(*p_angle==-M_PI)
			*p_angle = M_PI;
		
	}
}

bool   util_point_dehors(S2D a, double max) 	
{
	if(fabs(a.x) > max || fabs(a.y) > max) 
		return true;

	return false;
}

bool 	util_alpha_dehors(double alpha)
{
	if((alpha < -M_PI) || (alpha > M_PI))
		return true;

	return false;
}

bool 	util_point_dans_cercle(S2D a, C2D c)
{
	double dist;
	dist = util_distance(a,c.centre);
	if(dist < (c.rayon - EPSIL_ZERO))
		return true;

	return false;
}
bool 	util_collision_cercle(C2D a, C2D b, double * p_dist)
{
	*p_dist = util_distance(a.centre,b.centre);
	if(*p_dist < ((a.rayon + b.rayon)- EPSIL_ZERO))
		return true;

	return false;
}

S2D		util_deplacement(S2D p, double alpha, double dist)
{
	
	p.x = p.x + dist*cosf(alpha);
	p.y = p.y + dist*sinf(alpha);
	return p;
}

bool 	util_ecart_angle(S2D a, double alpha, S2D b, double *p_ecart_angle) 
{
	if(util_distance(a,b)>EPSIL_ZERO)
	{
		if(p_ecart_angle != NULL)
		{
			*p_ecart_angle = util_angle(a,b) - alpha;
			util_range_angle(p_ecart_angle);	
		}
		return true;
	}
	
	return false;
}
	
bool 	util_alignement(S2D a, double alpha, S2D b)
{
	double ecart_angle;
	double * p_ecart_angle = &ecart_angle;
	if(util_ecart_angle(a,alpha,b,p_ecart_angle))
	{
		if(fabs(ecart_angle) < EPSIL_ALIGNEMENT)
			return true;	
	}
	return false;
}

bool	util_inner_triangle(double la, double lb, double lc, double lb_new,
						    double * p_la_new)
{
	if((la>EPSIL_ZERO)&&(lc>EPSIL_ZERO)&&(lb>=0)&&((lb_new>=lb)
										||(lb_new<=lc)))
	{
		if(p_la_new)
		{
			double delta;
			double cosbeta;
			cosbeta = (pow(la,2)+pow(lc,2)-pow(lb,2))/(2*la*lc);
			delta = pow(2*lc*cosbeta,2)-4*(pow(lc,2)-pow(lb_new,2));
			if(delta>=0)
				*p_la_new = (2*lc*cosbeta-sqrt(delta))/2;
		}
		return true;
	}
	return false;
}
