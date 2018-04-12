#ifndef ROBOT_H
#define ROBOT_H

typedef struct robot ROBOT;
void lecture_robots(ROBOT** tete_liste, char* nom_fichier);
ROBOT* bot_creation (void);
void bot_destruction ( ROBOT ** p_tete, ROBOT *el);
void bot_total_destruction (ROBOT** p_liste);
ROBOT * liste_ajouter ( ROBOT ** p_tete );
void analyse_nbrbot (int nbbot_att,int nbbot_recu,unsigned int line);
void analyse_angle_bot (double alpha);

void liste_afficher ( ROBOT *tete );

#endif