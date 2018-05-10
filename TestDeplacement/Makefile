# Compilateur a utiliser :
##########################

CC     = gcc

# Options de compilation : (-g = pour deverminer)
#################################################

CFLAGS = -g

# Repertoire include :
#########################

#INCLUDE_DIR   = /usr/local/include/

# Librairies a utiliser :
#########################

LIBS   = -lstdc++ -lglut -lGL -lGLU -lm -Llib -lglui -L/usr/X11R6/lib -lX11 -lXext -lXmu -lXi

# Liste de fichiers source (.c) a compiler :
############################################

CFILES = deplacement.c utilitaire.c 
#lancer.cpp

# Liste de modules objets (generee a partir de CFILES) :
########################################################

OFILES = $(CFILES:.c=.o)

# Nom du fichier executable :
#############################

CIBLE  = deplacement.x 

# edition de liens (rassembler tous les objets -> executable)
#############################################################

$(CIBLE): $(OFILES)
	$(CC) $(OFILES) ${LIBS} -o $(CIBLE)


# compilation separee (production du module objet seulement)

#test.o: test.c
#	$(CC) -c test.c $(CFLAGS)



# Definitions de cibles particulieres :
#
# "make depend" : genere la liste des dependances
# "make clean"  : efface les fichiers .o et .x
#################################################

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o cine.x

#
# -- Regles de dependances generees par "make depend"
#####################################################
# DO NOT DELETE THIS LINE
deplacement.o: deplacement.c utilitaire.h tolerance.h constantes.h
utilitaire.o: utilitaire.c utilitaire.h tolerance.h
