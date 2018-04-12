typedef struct particule PARTICULE;
void lecture_particules(PARTICULE** tete_liste, char* nom_fichier);
void analyse_validite_part(double energie, double rayon,double pos_x, 
														double pos_y);
int chercheur_ligne(char* nom_fichier);
PARTICULE * liste_add ( PARTICULE ** p_tete );
void analyse_nbrpart(int nbpart_att,int nbpart_recu,unsigned int ligne);
void liste_show ( PARTICULE *tete );
void part_destruction ( PARTICULE ** p_tete, PARTICULE *el);
void part_total_destruction(PARTICULE**tete_liste);
void test3 (void); 
void passage_donnees(double en, double ray,
					double pos_x, double pos_y, PARTICULE*courant);
void particule_collision_part_part(PARTICULE*tete_liste_part);
void particule_collision_bot_part(PARTICULE*courant,double*p_posx,
						double*p_posy, double*p_rayon, int*p_num);
