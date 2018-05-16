#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/glui.h>

namespace {
	char texti[20] = "valeur initiale";
	int etatsim=0;
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
}

/* GLUI control callback*/
#define NO_RETURN_ID 100
#define EDITTEXTF_ID 101
#define EDITTEXTO_ID 102
#define SIMSTART_ID 103
#define SIMSTEP_ID 104
#define CHECKREC_ID 105
#define RADIOBUTTONCONT_ID 106

void control_cb( int control )
{
  /********************************************************************
    imprimer la valeur du paramètre pour indiquer qui a produit l'appel.
    utiliser les fonctions de type get_int_val() ou get_float_val()
    plutôt que de créer des live variables.
    ********************************************************************/
    //printf( "callback: %d\n", control );
switch (control){ 
	case (NO_RETURN_ID):
		break;
	case (EDITTEXTF_ID):
		printf("save: %s\n", FileText->get_text() );
		break;
	case (EDITTEXTO_ID):
		printf("open: %s\n", OpenText->get_text() );
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

int main(int argc, char* argv[])
{
	//initialisation de la fenetre
	glutInit(&argc, argv);
	GLUI *glui = GLUI_Master.create_glui( "Terminator kontrol");
	
	//open 
	GLUI_Panel *open_panel = glui->add_panel((char*) "Open");
	OpenText = glui->add_edittext_to_panel(open_panel, (char*)"ex4", GLUI_EDITTEXT_TEXT, texti,NO_RETURN_ID, control_cb);
	glui->add_button_to_panel(open_panel,(char*)"open", EDITTEXTO_ID,control_cb );
	
	//file
	GLUI_Panel *file_panel = glui->add_panel((char*) "Saving");
	FileText = glui->add_edittext_to_panel(file_panel, (char*)"ex5", GLUI_EDITTEXT_TEXT, texti,NO_RETURN_ID, control_cb);
	glui->add_button_to_panel(file_panel,(char*)"save", EDITTEXTF_ID,control_cb );
	
	glui->add_column(true);
	//glui->add_separator();
	
	//simulation
	GLUI_Panel *simul_panel = glui->add_panel((char*) "Simulation");
	buttonstart = glui->add_button_to_panel(simul_panel,(char*)"start", SIMSTART_ID,control_cb );
	buttonstep = glui->add_button_to_panel(simul_panel,(char*)"step", SIMSTEP_ID,control_cb );
	
	
	//recording
	GLUI_Panel *record_panel = glui->add_panel((char*) "Recording");
	reccheck = glui->add_checkbox_to_panel(record_panel,(char*)"record",NULL,CHECKREC_ID, control_cb);
	RecRate = glui->add_statictext_to_panel(record_panel,"rate off");
	RecTurn = glui->add_statictext_to_panel(record_panel,"turn off");
	
	glui->add_column(true);
	
	//control mode
	GLUI_Panel *control_panel = glui->add_panel((char*) "Control mode");
	contradio = glui->add_radiogroup_to_panel(control_panel, NULL, RADIOBUTTONCONT_ID,control_cb);
	glui->add_radiobutton_to_group( contradio,(char*)   "Automatic" );  
	glui->add_radiobutton_to_group( contradio,(char*)   "Manual" );
	
	//robot control 
	GLUI_Panel *r_control_panel = glui->add_panel((char*) "Robot control");
	robrot = glui->add_statictext_to_panel(r_control_panel,"rotaion : 0.00");
	robtran = glui->add_statictext_to_panel(r_control_panel,"translation : 0.00");
	
	//bouton quitter
	glui->add_button((char*)"Quit", 0,(GLUI_Update_CB)exit );
	glutMainLoop();
	return 0;
}
