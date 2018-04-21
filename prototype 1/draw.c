/*!
 \file draw.c
 \brief module qui dessine les robots et les particules
 \author Selina Bothner
		 Jose Antonio Simon Greminger
		 Damian Perez Grether
 \version 3.01
 \date 21 avril 2018
 */

#include <stdio.h>
#include  <GL/glu.h>
#include  <GL/glut.h>
#include  <math.h>
#include  "draw.h"
#include "constantes.h"

void draw_robot(double xc, double yc, double angle)
{
	const int SIDES = 50;
	//~ printf("drawing robot\n");

	glBegin(GL_LINE_LOOP);

	for (int i=0; i < SIDES; i++)
    {
      float alpha = i * 2. * 3.14159265 / SIDES;
      float x = R_ROBOT*cos(alpha);
      float y = R_ROBOT*sin(alpha);

      glColor3f(0,0,0);
      glVertex2f(x+xc,y+yc);
      
    }
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2d(xc,yc);
	glVertex2d(xc+R_ROBOT*cos(angle),yc+R_ROBOT*sin(angle));
	glEnd();

	double petit_rayon = 0.1;
	glBegin(GL_TRIANGLE_FAN);
	for (int i=0; i < SIDES; i++)
    {
      float alpha = i * 2. * 3.14159265 / SIDES;
      float px = petit_rayon*cos(alpha);
      float py = petit_rayon*sin(alpha);
      glColor3f(1,0,0);
      glVertex2f(xc+px,yc+py);
    }
	glEnd();

}

void draw_part(double xc, double yc,double rayon)
{
	const int SIDES = 50;

	glBegin(GL_TRIANGLE_FAN);

	for (int i=0; i < SIDES; i++)
    {
      float alpha = i * 2. * 3.14159265 / SIDES;
      float x = rayon*cos(alpha);
      float y = rayon*sin(alpha);

      glColor3f(0.5,0.5,0.5);
      glVertex2f(x+xc,y+yc);
      
    }
	glEnd();
}
