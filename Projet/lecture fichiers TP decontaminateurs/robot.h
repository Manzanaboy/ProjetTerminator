#include "particule.h"

typedef struct robot ROBOT;
void lecture_robots(ROBOT** tete_liste, char* nom_fichier);
ROBOT* bot_creation (void);
void bot_destruction ( ROBOT ** p_tete, ROBOT *el);
void bot_total_destruction (ROBOT** p_liste);
ROBOT * liste_ajouter ( ROBOT ** p_tete );
void analyse_nbrbot (int nbbot_att,int nbbot_recu,unsigned int line);
void analyse_angle_bot (double alpha);
void robot_collision_bot_bot(ROBOT*tete_liste_bot);
void robot_collisions_bot_part (ROBOT*tete_liste_bot,
											PARTICULE* tete_liste_part);

void liste_afficher ( ROBOT *tete );
