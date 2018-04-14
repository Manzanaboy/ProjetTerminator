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

namespace{
	float tab[3][3];
	char entrees_command_test[8];
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
	else
	{
		strncpy(entrees_command_test,(argv[2]),8);
	}

	if (strncmp("ERROR", argv[1],5)==0)
	{

	simulation_mode_error(tete_liste_bot, argv[2], tete_liste_part);
	tete_liste_bot =NULL;
	tete_liste_part=NULL;
	return 0;

 	}

 	else if (strncmp("DRAW", argv[1],4)==0)
 	{
 		
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
	//~ draw(tab);
	dessine_tout();
	printf("Display");

}

void reshape(int w,int h)
{
	int width = w;
	int height = h;

  glViewport( 0, 0, width, height);
}
void dessine_tout()
{
	
	if(entrees_command_test[0]=='D')
	{
		simulation_mode_draw(tete_liste_bot,entrees_command_test,
												tete_liste_part);
		tete_liste_bot =NULL;
		tete_liste_part=NULL;
	}
	else
	{
		printf("problem de lecture");
	}

}
