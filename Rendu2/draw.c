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
#define PETIT_RAYON 0.1
#define SIDES 50

void draw_robot(double xc, double yc, double angle)
{

  double petit_rayon = PETIT_RAYON;
  float x=0,y=0,px=0,py=0, alpha=0;
  int i=0;

	glBegin(GL_LINE_LOOP);
	for (i=0; i < SIDES; i++)
    {
      alpha = i * 2. * M_PI / SIDES;
      x = R_ROBOT*cos(alpha);
      y = R_ROBOT*sin(alpha);
      glColor3f(0,0,0);
      glVertex2f(x+xc,y+yc);
    }
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2d(xc,yc);
	glVertex2d(xc+R_ROBOT*cos(angle),yc+R_ROBOT*sin(angle));
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	for (i=0; i < SIDES; i++)
    {
      alpha = i * 2. * M_PI / SIDES;
      px = petit_rayon*cos(alpha);
      py = petit_rayon*sin(alpha);
      glColor3f(1,0,0);
      glVertex2f(xc+px,yc+py);
    }
	glEnd();

}

void draw_part(double xc, double yc,double rayon)
{

  float x=0,y=0, alpha=0;
  int i=0;

	glBegin(GL_TRIANGLE_FAN);

	for (i=0; i < SIDES; i++)
    {
      alpha = i * 2. * M_PI / SIDES;
      x = rayon*cos(alpha);
      y = rayon*sin(alpha);

      glColor3f(0.5,0.5,0.5);
      glVertex2f(x+xc,y+yc);
      
    }
	glEnd();
}
