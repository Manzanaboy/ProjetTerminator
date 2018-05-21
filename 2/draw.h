#ifndef DRAW_H
#define DRAW_H

/**
*\brief dessine une particule
*\param xc : coordonnée x du centre de la particule
*       yc : coordonnée y du centre de la particule
 *     rayon: rayon de la particule
**/
void draw_part(double xc, double yc,double rayon);


/**
*\brief dessine un robot
*\param xc : coordonnée x du centre du robot
*       yc : coordonnée y du centre du robot
 *      angle: angle du robot avec l'axe X
**/
void draw_robot(double xc, double yc, double angle);

/**
*\brief dessine un robot en rouge
*\param xc : coordonnée x du centre du robot
*       yc : coordonnée y du centre du robot
 *      angle: angle du robot avec l'axe X
**/
void draw_red(double xc, double yc, double angle);

/**
*\brief dessine le cadre autour du monde
**/
void draw_cadre ();

#endif
