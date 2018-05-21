
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
void clavier(int key,int x,int y);
void manuel(int bouton, int etat, int x, int y);
void record_fichier();
void record();


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
enum Acitvite{INACTIF,ACTIF};

namespace
	{
		int main_window;
		char entrees_command_test[LG_TEST];
		char open[LG_TEST];
		char save[LG_TEST];
		char turn_text[10], controt[LG_TEST], conttran[LG_TEST];
		GLfloat aspect_ratio;
		char textiun[20] = "D04.txt";
		char textide[20] = "data.txt";
		int etatsim=0;
		int base=PG_DESSINS;
		int etat_lecture=NON_LU;
		int rec_turn, cont_mode;
		float vittran=0, vitrot=0;
		float largeur, haut, Xm, Ym;
		double taux_decontamination=0;
		double energie_initiale=0;
		char taux_text[LG_TEST];
	
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
		
		FILE *open_file=NULL, *save_file=NULL, *record_file=NULL;
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

void open_fonction(int control)
{
	remove("out.dat");
	taux_decontamination=0;
	if (fopen(OpenText->get_text(),"r") == NULL)
	{
		error_file_missing(OpenText->get_text());
	
	}
	else
	{
		base = PG_DESSINS;
		strncpy(open,(OpenText->get_text()),LG_TEST);
		strncpy(entrees_command_test,(open),LG_TEST);
		
		if(etat_lecture==LU)
		{
			simulation_detruire();
			etat_lecture=NON_LU;
		}
		rec_turn = 0;
		RecTurn->set_text("turn 0");
		glutPostRedisplay();
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
		case (SIMSTART_ID):
			if(!(etat_lecture==LU) || !(simulation_particules()))
				break;
			if (etatsim==0&&(simulation_particules))
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
			if((!(etatsim))&&(simulation_particules()))
			{
				record();
				simulation_decomposition();
				if (robot_deplacer())
					simulation_mja();
			}
			break;
		case (RADIOBUTTONCONT_ID):
			if(contradio->get_int_val())
			{
				robtran->enable();
				robrot->enable();
				cont_mode = 1;
				
			}
			else
			{
				robtran->disable();
				robrot->disable();
				cont_mode = 0;
				robot_deselection();
			}
			break;
		}
}

void clavier(int key,int x,int y)
{
	if (cont_mode)
	{
		switch (key)
		{
			case (GLUT_KEY_LEFT):
				if (vitrot < VROT_MAX)
				{
					vitrot+=DELTA_VROT;
				}
				sprintf(controt,"rotation : %.3f",vitrot);
				robrot->set_text(controt);
				break;
			case (GLUT_KEY_RIGHT):
				if (vitrot > -VROT_MAX)
				{
					vitrot-=DELTA_VROT;
				}
				sprintf(controt,"rotation : %.3f",vitrot);
				robrot->set_text(controt);
				break;
			case (GLUT_KEY_UP):
				if (vittran < VTRAN_MAX)
				{
					vittran+=DELTA_VTRAN;
				}
				sprintf(conttran,"translation : %.3f",vittran);
				robtran->set_text(conttran);
				break;
			case (GLUT_KEY_DOWN):
				if (vittran > -VTRAN_MAX)
				{
					vittran-=DELTA_VTRAN;
				}
				sprintf(conttran,"translation : %.3f",vittran);
				robtran->set_text(conttran);
				break;
		}
		robot_vitesse(vitrot, vittran);
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
	largeur = width;
	haut = height;
	glViewport( 0, 0, width, height);
	aspect_ratio=(GLfloat)width/(GLfloat)height;
	glutPostRedisplay();
}

void dessine_tout()
{
	int* p_base=&base;
	char mode_lecture[4] = {'D','R','A','W'};
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
			simulation_dessiner();
		}
		/* Affiche l'image a l'ecran. */
		glutSwapBuffers();
		fclose(fichier);
	}
}

void update(void)
{
	if(etatsim&&(simulation_particules()))
	{
		simulation_decomposition();
		if (robot_deplacer())
			simulation_mja();
		record();
	}
	if (glutGetWindow() != main_window)
	glutSetWindow(main_window);
	glutPostRedisplay();
}

void manuel(int bouton, int etat, int x, int y)
{
	if (cont_mode)
	{
		
		Xm = (20+20)*(x/largeur) -20;
		Ym = 20 - (20+20)*(y/haut);
		if (!(etat) && bouton ==  GLUT_LEFT_BUTTON) 
		{
			if(aspect_ratio<=1)
				Ym /= aspect_ratio;
			else
				Xm *=aspect_ratio;
			robot_selection(Xm, Ym);
		}
	}
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
	GLUI_Master.set_glutSpecialFunc(clavier);
	GLUI_Master.set_glutMouseFunc(manuel);
	
	//open 
	GLUI_Panel *open_panel = glui->add_panel((char*) "Opening");
	OpenText = glui->add_edittext_to_panel(open_panel, (char*)"File name:", 
					GLUI_EDITTEXT_TEXT, textiun,NO_RETURN_ID, control_cb);
	glui->add_button_to_panel(open_panel,(char*)"open",
								EDITTEXTO_ID,open_fonction );
	
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
	RecRate = glui->add_statictext_to_panel(record_panel,"rate 0");
	RecTurn = glui->add_statictext_to_panel(record_panel,"turn 0");
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
	robtran->disable();
	robrot->disable();
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

void record_fichier()
{
	taux_decontamination=particule_energie();
	if(reccheck->get_int_val())
	{
		if((record_file=fopen("out.dat", "a"))==NULL) //Si record_file==NULL fichier n'exisite pas, il faut le créer
		{
			record_file=fopen("out.dat", "a");
		}
		fprintf(record_file, "%d %lf \n", rec_turn, taux_decontamination );

		fclose(record_file);
	}

}

void record()
{
	if (etat_lecture == LU)
	{
		rec_turn++;
		sprintf(turn_text,"turn %d",rec_turn);
		RecTurn->set_text(turn_text);
		sprintf(taux_text, "Rate %.3lf", taux_decontamination);
		RecRate->set_text(taux_text);
		record_fichier();
	}
}
