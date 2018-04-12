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

LIBS   = -lglut -lGL -lGLU -lm -Llib -L/usr/X11R6/lib -lX11 -lXext -lXmu -lXi -lstdc++

# Liste de fichiers source (.c) a compiler :
############################################

CFILES = error.c simulation.c robot.c particule.c main.cpp utilitaire.c draw.c 
#lancer.cpp

# Liste de modules objets (generee a partir de CFILES) :
########################################################

OFILES = $(CFILES:.c=.o)

# Nom du fichier executable :
#############################

CIBLE  = test.x 

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
error.o: error.c error.h constantes.h tolerance.h
simulation.o: simulation.c utilitaire.h tolerance.h error.h constantes.h \
 simulation.h robot.h particule.h
robot.o: robot.c utilitaire.h tolerance.h error.h robot.h
particule.o: particule.c utilitaire.h tolerance.h error.h particule.h \
 constantes.h
main.o: main.cpp utilitaire.h tolerance.h error.h constantes.h \
 simulation.h robot.h particule.h
utilitaire.o: utilitaire.c tolerance.h
