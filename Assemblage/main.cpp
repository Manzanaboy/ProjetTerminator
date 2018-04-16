extern "C"
{
	#include "utilitaire.h"
	#include "error.h"
	#include "constantes.h"
	#include "simulation.h"
	#include  "draw.h"
}

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include  <GL/glu.h>
#include  <GL/glut.h>
#include <string.h>

void display();
void reshape(int w,int h);
void dessine_tout();

#define LG_TEST 8

namespace
	{
	char entrees_command_test[LG_TEST];
	ROBOT *tete_liste_bot=NULL;
	PARTICULE* tete_liste_part=NULL;
	GLfloat aspect_ratio;
	}
	
int main(int argc, char* argv[])
{
	if(argc !=3)
	{
		printf("erreur de lecture, entrées des fichiers \n");
		printf("exectubale suivi du mode et enfin le fichier a lire\n");
		exit(0);
	}
	else
	{
		strncpy(entrees_command_test,(argv[2]),8);
	}

	if (argv[1][0]=='E')
	{

	simulation_mode_error(tete_liste_bot, argv[2], tete_liste_part);
	tete_liste_bot =NULL;
	tete_liste_part=NULL;
	return 0;

 	}

 	else if (argv[1][0]=='D')
 	{
 		
 		printf("DRAW \n");
 		
		glutInit(&argc,argv);
		glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
		glutInitWindowPosition( 50, 50 );
		glutInitWindowSize( 400, 400 );
		aspect_ratio = (GLfloat)400/(GLfloat)400;
	 
		glutCreateWindow("Fenetre");
	 
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
	 
		glutMainLoop();


 	}
 	else
 	{
		//AFFICHAGE initiale
 		printf("on doit faire  affichage initale !!! avec amour Jose\n");

 	}
}

void display()
{
	dessine_tout();
	printf("Display");

}

void reshape(int width,int height)
{
	glViewport( 0, 0, width, height);
	aspect_ratio=(GLfloat)width/(GLfloat)height;
	glutPostRedisplay();
}
void dessine_tout()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat g=-20,d=20,bas=-20,haut=20;
	if(entrees_command_test[0]=='D')
	{
		glLoadIdentity();
		if(aspect_ratio<=1)
		{
			glOrtho(g,d,bas/aspect_ratio,haut/aspect_ratio,-1.,+1.);
		}
		else
		{
			glOrtho(g*aspect_ratio,d*aspect_ratio,bas,haut,-1.,+1.);
		}
		
		//~ glClear(GL_COLOR_BUFFER_BIT); // efface le frame buffer
		glClearColor(1,1,1,1); // selectionne la couleur noire 
		simulation_mode_draw(tete_liste_bot,entrees_command_test,
												tete_liste_part);
		tete_liste_bot =NULL;
		tete_liste_part=NULL;
		/* Affiche l'image a l'ecran. */
		glutSwapBuffers();
	}
	else
	{
		printf("problem de lecture");
	}

}
