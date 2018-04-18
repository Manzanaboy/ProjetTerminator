#include "particule.h"


typedef struct robot ROBOT;
void robot_lecture_robots(ROBOT** tete_liste, char* nom_fichier);
ROBOT* robot_bot_creation (void);
void robot_bot_destruction ( ROBOT ** p_tete, ROBOT *el);
void robot_bot_total_destruction (ROBOT** p_liste);
ROBOT * robot_liste_ajouter ( ROBOT ** p_tete );
void robot_analyse_nbrbot (int nbbot_att,int nbbot_recu,unsigned int line);
void robot_analyse_angle_bot (double alpha);
void robot_collision_bot_bot(ROBOT*tete_liste_bot);
void robot_collisions_bot_part (ROBOT*tete_liste_bot,
											PARTICULE* tete_liste_part);
void robot_dessin(ROBOT*tete_liste);
void robot_get_values(ROBOT*courant,double*p_pos_x,double*p_pos_y,
														double*p_angle);

void robot_liste_afficher ( ROBOT *tete );
