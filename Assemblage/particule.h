#ifndef PARTICULES_H
#define PARTICULES_H\

typedef struct particule PARTICULE;
void particule_lecture_particules(PARTICULE** tete_liste, char* nom_fichier);
void particule_analyse_validite_part(double energie, double rayon,double pos_x, 
														double pos_y);
int particule_chercheur_ligne(char* nom_fichier);
PARTICULE * particule_liste_add ( PARTICULE ** p_tete );
void particule_analyse_nbrpart(int nbpart_att,int nbpart_recu,unsigned int ligne);
void particule_liste_show ( PARTICULE *tete );
void particule_part_destruction ( PARTICULE ** p_tete, PARTICULE *el);
void particule_part_total_destruction(PARTICULE**tete_liste);
void particule_test3 (void); 
void particule_passage_donnees(int nbpart_recu, double en, double ray,
					double pos_x, double pos_y, PARTICULE*courant);


#endif
