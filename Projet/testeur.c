#include <math.h>
#include <stdio.h>

typedef struct S2d S2D;
struct S2d
{
	double x;
	double y;
};
void 	util_range_angle(double * p_angle);
double 	util_angle(S2D a, S2D b);

int main(void)
{
	double *p_angle;
	double angle;
	S2D a = {3,6};
	S2D b = {5,4};
	int carre = 2;
	double dist, distx, disty;
	distx = fabs(b.x - a.x);
	disty = fabs(b.y -a.y);
	dist = sqrt(pow(distx,carre)+pow(disty,carre));
	printf ("la distance est %f", dist); 
	angle = util_angle(a,b);
	printf("\nl'angle est %f",angle);
	p_angle= &angle;
	util_range_angle(p_angle);
	printf("\nl'angle est %f",angle);
}
double 	util_distance(S2D a, S2D b)
{
	int carre = 2;
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
	alpha = util_range_angle(p_alpha);
	return alpha;
}
void 	util_range_angle(double * p_angle)
{
	double epsilon = 0.001;
	if (*p_angle > M_PI)
	{
		*p_angle = *p_angle + M_PI;
	}
	else
	{
		if(*p_angle<(-M_PI))
		{
			*p_angle = *p_angle + M_PI;
		}
		if(*p_angle==(-M_PI))
		{
			*p_angle = *p_angle + epsilon;
		}
	}
}

/*bool   util_point_dehors(S2D a, double max)
{
	if((a.x < (-max)) ||(a.x > max) || (a.y<(-max)) || (a.y >max))
	{
		return true;
	}
}

bool 	util_alpha_dehors(double alpha)
{
	if((alpha < -M_PI) || (alpha > M_PI))
	{
		return true;
	}
}

bool 	util_point_dans_cercle(S2D a, C2D c)
{
	double dist;
	dist = util_distance(a,c.centre);
	if(dist < (c.rayon - EPSIL_ZERO))
	{
		return true;
	}
}
*/
