
#include <stdio.h>
#include  <GL/glu.h>
#include  <GL/glut.h>
#include  <math.h>
#include  "draw.h"
#include "constantes.h"

#define SIDES 50
#define PETIT_R 0.1
#define LARGEUR_CADRE	5

void draw_robot(double xc, double yc, double angle)
{
  int i=0;
  float x=0,y=0,px=0,py=0, alpha=0;
  double petit_rayon = PETIT_R;

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
	for (int i=0; i < SIDES; i++)
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
  int i=0;
  float x=0,y=0, alpha=0;

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

void draw_cadre ()

{ 
    glBegin (GL_LINE_LOOP);

    glVertex2f (-DMAX,-DMAX);
    glVertex2f (-DMAX,DMAX);
    glVertex2f (DMAX,DMAX);
    glVertex2f (DMAX,-DMAX);
    
    glColor3f(0., 0., 0.);
    glLineWidth(LARGEUR_CADRE);

    glEnd ();
}
