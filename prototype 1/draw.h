/*!
 \file draw.h
 \brief module qui dessine les robots et les particules
 \author Selina Bothner
		 Jose Antonio Simon Greminger
		 Damian Perez Grether
 \version 3.01
 \date 21 avril 2018
 */
#ifndef DRAW_H
#define DRAW_H

/**
 * \brief dessiner une particule
 * \param xc 	coordonée horizontale du centre de la particule
 * \param yc 	coordonée verticale du centre de la particule
 * \param rayon rayon de la particule
 */
void draw_part(double xc, double yc,double rayon);

/**
 * \brief dessiner un robot
 * \param xc 	coordonée horizontale du centre du robot
 * \param yc 	coordonée verticale du centre du robot
 * \param angle angle du robbot
 */
void draw_robot(double xc, double yc, double angle);

#endif
