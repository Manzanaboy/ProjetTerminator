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

void display();
void reshape(int w,int h);

namespace{
	float tab[3][3];

	ROBOT *tete_liste_bot=NULL;
	PARTICULE* tete_liste_part=NULL;
}


int main(int argc, char* argv[])
{
	if(argc !=3)
	{
		printf("erreur de lecture, entrées des fichiers \n");
		printf("exectubale suivi du mode et enfin le fichier a lire\n");
		exit(0);
	}

	if (strncmp("ERROR", argv[1],5)==0)
	{

	simulation_mode_error(tete_liste_bot, argv[2], tete_liste_part);
	tete_liste_bot =NULL;
	tete_liste_part=NULL;
	return 0;

 	}

 	else if (strncmp("DRAW", argv[1],5)==0)
 	{
 		simulation_mode_error(tete_liste_bot, argv[2], tete_liste_part);
		tete_liste_bot =NULL;
		tete_liste_part=NULL;

 		printf("DRAW \n");
 		tab[0][0]=1;
		tab[0][1]=2;
		tab[0][2]=3;
		tab[1][0]=4;
		tab[1][1]=5;
		tab[1][2]=6;
		tab[2][0]=-4;
		tab[2][1]=-8;
		tab[2][2]=3;

		glutInit(&argc,argv);
		glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
		glutInitWindowPosition( 50, 50 );
		glutInitWindowSize( 400, 400 );
	 
		glutCreateWindow("Fenetre");
	 
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
	 
		glutMainLoop();


 	}
 	else
 	{
 		printf("Problemo\n");

 	}
}

void display()
{
	draw(tab);
	printf("Display");

}

void reshape(int w,int h)
{
	int width = w;
	int height = h;

  glViewport( 0, 0, width, height);
}
