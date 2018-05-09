
/*!
 \file main.cpp
 \brief Gère tout le traitement des fichiers, le dessin de l'interface 
		graphique et la boîte de dialogue. 
 \author Damian Perez Grether
		 Jose Antonio Simon Greminger 
		 Selina Bothner
 \version 3.01
 \date 21 avril 2018
 */
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
#include <GL/glut.h>
#include <GL/glui.h>
#include <string.h>

void display();
void reshape(int w,int h);
void dessine_tout();
void creer_fenetre(int *p_argc, char *argv[]);
void control_cb( int control);
void creer_boite_dialog();
void dessine_page_blanche();
void sauver(char* fichier_open, char* fichier_save);

#define LG_TEST 100
#define NO_RETURN_ID 100
#define EDITTEXTF_ID 101
#define EDITTEXTO_ID 102
#define SIMSTART_ID 103
#define SIMSTEP_ID 104
#define CHECKREC_ID 105
#define RADIOBUTTONCONT_ID 106

enum Type_dessin{PG_BLANCHE,PG_DESSINS};
enum Type_fichier{LU,NON_LU};
enum Acitvite{INACTIF=-1,ACTIF};

namespace
	{
		int main_window;
		char entrees_command_test[LG_TEST];
		char open[LG_TEST];
		char save[LG_TEST];
		GLfloat aspect_ratio;
		char textiun[20] = ".txt";
		char textide[20] = "data.txt";
		int etatsim=0;
		int base=PG_DESSINS;
		int etat_lecture=NON_LU;
	
		GLUI_EditText *FileText;
		GLUI_EditText *OpenText;
		GLUI_Checkbox *reccheck;
		GLUI_StaticText *RecRate;
		GLUI_StaticText *RecTurn;
		GLUI_RadioGroup *contradio;
		GLUI_Button *buttonstart;
		GLUI_Button *buttonstep;
		GLUI_StaticText *robrot;
		GLUI_StaticText *robtran;
		
		FILE *open_file=NULL, *save_file=NULL;
	}
	

	
int main(int argc, char* argv[])
{
	if(argc !=3 && argc !=1)
	{
		printf("erreur de lecture, entrées des fichiers \n");
		printf("exectubale suivi du mode et enfin le fichier a lire\n");
		exit(0);
	}
	if (argc ==3)
	{
		strncpy(entrees_command_test,(argv[2]),LG_TEST);
		if (!(strncmp("Error",argv[1],5)))
		{
			int* p_base=&base;
			simulation_first_lecture(argv[2],p_base,argv[1]);
			etat_lecture=LU;
			return 0;
	 	}
	
	 	else if (!(strncmp("Draw",argv[1],4)))
	 	{
			base=PG_DESSINS;
	 		creer_fenetre(&argc,argv);	
	 	}
	}
 	else
 	{
		base=PG_BLANCHE;
		creer_fenetre(&argc,argv);
 	}
}

void control_cb( int control )
{
   	switch (control)
	{ 
		case (NO_RETURN_ID):
			break;
		case (EDITTEXTF_ID):
			strncpy(save,(FileText->get_text()),LG_TEST);
			strncpy(open,(OpenText->get_text()),LG_TEST);
			if(robot_sauver(save))
			{
				particule_sauver(save);
			}
			break;	
		case (EDITTEXTO_ID):
			if (fopen(OpenText->get_text(),"r") == NULL)
			{
				error_file_missing(OpenText->get_text());
				break;
			}
			base = PG_DESSINS;
			strncpy(open,(OpenText->get_text()),LG_TEST);
			strncpy(entrees_command_test,(open),LG_TEST);
			
			if(etat_lecture==LU)
			{
				simulation_detruire();
				etat_lecture=NON_LU;
			}
			glutPostRedisplay();
			break;	
		case (SIMSTART_ID):
			if (etatsim==0)
			{
				buttonstart->set_name("Stop");
				etatsim = 1;
			}
			else
			{
				buttonstart->set_name("Start");
				etatsim = 0;
			}
			break;
		case (SIMSTEP_ID):
			robot_deplacer();
			break;
		case (CHECKREC_ID):
			printf("rec: %d\n", reccheck->get_int_val() );
			if(reccheck->get_int_val())
			{
				RecRate->set_text("rate on");
				RecTurn->set_text("turn on");
			}
			else
			{
				RecRate->set_text("rate off");
				RecTurn->set_text("turn off");
			}
			break;
		case (RADIOBUTTONCONT_ID):
			printf("mode: %d\n", contradio->get_int_val() );
			break;
		default: 
			printf("\n Unknown command\n");   
			break;
		}
}

void display()
{
	
	if(base)
	{
		dessine_tout();
	}
	else
	{
		base = PG_BLANCHE;
		dessine_page_blanche();
	}
	
}

void reshape(int width,int height)
{
	glViewport( 0, 0, width, height);
	aspect_ratio=(GLfloat)width/(GLfloat)height;
	glutPostRedisplay();
}

void dessine_tout()
{
	int* p_base=&base;
	char* mode_lecture = "Draw";
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat g=-20,d=20,bas=-20,haut=20;
	FILE *fichier = fopen(entrees_command_test,"r");
	
	if(fichier)
	{
		glLoadIdentity();
		if(aspect_ratio<=1)
			glOrtho(g,d,bas/aspect_ratio,haut/aspect_ratio,-1.,+1.);
		else
			glOrtho(g*aspect_ratio,d*aspect_ratio,bas,haut,-1.,+1.);
		if(etat_lecture==NON_LU)
		{
			simulation_first_lecture(entrees_command_test,
												p_base,mode_lecture);
			etat_lecture=LU;
		}
		else
		{
			simulation_developpement(ACTIF);
		}
		/* Affiche l'image a l'ecran. */
		glutSwapBuffers();
		fclose(fichier);
	}
}

void update(void)
{
	if(etatsim)robot_deplacer();
	if (glutGetWindow() != main_window)
	glutSetWindow(main_window);
	glutPostRedisplay();
}

void creer_fenetre(int *p_argc, char *argv[])
{
		glutInit(p_argc,argv);
		glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
		glutInitWindowPosition( 50, 50 );
		glutInitWindowSize( 400, 400 );
		aspect_ratio = (GLfloat)400/(GLfloat)400;
	 
		main_window = glutCreateWindow("decontaminators - display");
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		creer_boite_dialog();
		glutSwapBuffers();
	 
		glutMainLoop();
}

void creer_boite_dialog()
{
	//initialisation de la fenetre
	GLUI *glui = GLUI_Master.create_glui( "decontaminators - control");
	GLUI_Master.set_glutIdleFunc(update);
	
	//open 
	GLUI_Panel *open_panel = glui->add_panel((char*) "Opening");
	OpenText = glui->add_edittext_to_panel(open_panel, (char*)"File name:", 
					GLUI_EDITTEXT_TEXT, textiun,NO_RETURN_ID, control_cb);
	glui->add_button_to_panel(open_panel,(char*)"open",
								EDITTEXTO_ID,control_cb );
	
	//file
	GLUI_Panel *file_panel = glui->add_panel((char*) "Saving");
	FileText = glui->add_edittext_to_panel(file_panel, (char*)"File name:",
				GLUI_EDITTEXT_TEXT, textide,NO_RETURN_ID, control_cb);
	glui->add_button_to_panel(file_panel,(char*)"save", 
								EDITTEXTF_ID,control_cb );
	
	glui->add_column(true);
	//simulation
	GLUI_Panel *simul_panel = glui->add_panel((char*) "Simulation");
	buttonstart = glui->add_button_to_panel(simul_panel,(char*)"start",
											SIMSTART_ID,control_cb );
	buttonstep = glui->add_button_to_panel(simul_panel,(char*)"step", 
											SIMSTEP_ID,control_cb );
	//recording
	GLUI_Panel *record_panel = glui->add_panel((char*) "Recording");
	reccheck = glui->add_checkbox_to_panel(record_panel,(char*)"record",
											NULL,CHECKREC_ID, control_cb);
	RecRate = glui->add_statictext_to_panel(record_panel,"rate off");
	RecTurn = glui->add_statictext_to_panel(record_panel,"turn off");
	glui->add_column(true);
	//control mode
	GLUI_Panel *control_panel = glui->add_panel((char*) "Control mode");
	contradio = glui->add_radiogroup_to_panel(control_panel, NULL,
										RADIOBUTTONCONT_ID,control_cb);
	glui->add_radiobutton_to_group( contradio,(char*)   "Automatic" );  
	glui->add_radiobutton_to_group( contradio,(char*)   "Manual" );
	//robot control 
	GLUI_Panel *r_control_panel =
								glui->add_panel((char*)"Robot control");
	robrot = glui->add_statictext_to_panel(r_control_panel,
												"rotaion : 0.00");
	robtran = glui->add_statictext_to_panel(r_control_panel,
												"translation : 0.00");
	
	//bouton quitter
	glui->add_button((char*)"Exit", 0,(GLUI_Update_CB)exit );
}

void dessine_page_blanche()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat g=-20,d=20,bas=-20,haut=20;

	glLoadIdentity();
	
	if(aspect_ratio<=1)
		glOrtho(g,d,bas/aspect_ratio,haut/aspect_ratio,-1.,+1.);
	
	else
		glOrtho(g*aspect_ratio,d*aspect_ratio,bas,haut,-1.,+1.);
	
	glutSwapBuffers();
}
