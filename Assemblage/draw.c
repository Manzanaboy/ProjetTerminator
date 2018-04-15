#include <stdio.h>
#include  <GL/glu.h>
#include  <GL/glut.h>
#include  <math.h>
#include  "draw.h"

//~ void draw(float tableau[3][3])
//~ {



	//~ for(int i=0; i<3; i++)
	//~ {
		//~ draw_robot(tableau[i][0],tableau[i][1],tableau[i][2]);
	//~ }
	
	//~ //glFlush(); // affichage de la scène
	//~ glutSwapBuffers();

//~ }

void draw_robot(double xc, double yc, double angle)
{
	const int SIDES = 50;
	float r=0.5;

	printf("drawing robot\n");

	glBegin(GL_LINE_LOOP);

	for (int i=0; i < SIDES; i++)
    {
      float alpha = i * 2. * 3.14159265 / SIDES;
      float x = r*cos(alpha);
      float y = r*sin(alpha);

      glColor3f(0,0,0);
      glVertex2f(x+xc,y+yc);
      
    }
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2d(xc,yc);
	glVertex2d(xc+r*cos(angle),yc+r*sin(angle));
	glEnd();

	glBegin(GL_POINTS);
	glVertex2f(xc,yc);
	glColor3f(1,0,0);
	glEnd();

}

void draw_part(double xc, double yc)
{
	const int SIDES = 50;
	int r=3;

	glBegin(GL_TRIANGLE_FAN);

	for (int i=0; i < SIDES; i++)
    {
      float alpha = i * 2. * 3.14159265 / SIDES;
      float x = r*cos(alpha);
      float y = r*sin(alpha);

      glColor3f(0.5,0.5,0.5);
      glVertex2f(x+xc,y+yc);
      
    }
	glEnd();
}
