# Makefile

build:
	gcc -Wall -Wextra -c utilitaire.c -o utilitaire.o
	gcc -Wall -Wextra -c error.c -o error.o
	gcc -Wall -Wextra -c testeur_particules.c -o testeur_particules.o
	gcc -Wall -Wextra -c robot.c -o robot.o
	gcc -Wall -Wextra -c testeur_robots.c -o testeur_robots.o
	gcc -Wall -Wextra testeur_robots.o utilitaire.o robot.o error.o -lm -lstdc++ -o testeur_robots.x


# Definitions de macros

CC     = gcc
CFLAGS = -Wall
CFILES = utilitaire.c error.c robot.c testeur_robots.c testeur_particules.c
OFILES = $(CFILES:.c=.o)

# Definition de la premiere regle

#test.x: test.o 
#	gcc test.o -lm -o test.x	  

testeur_robots.x: $(OFILES)
	$(CC) $(OFILES) -lm -o testeur_robots.x

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
	  egrep -v "/usr/include" \
	 ) >makefile.new
	@mv makefile.new makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f utilitaire.o test.x 

#
# -- Regles de dependances generees automatiquement
#

utilitaire.o: utilitaire.c utilitaire.h tolerance.h
error.o: error.c error.h constantes.h tolerance.h
robot.o: robot.c utilitaire.h tolerance.h error.h robot.h
testeur_particules.o: constantes.h utilitaire.h tolerance.h error.h testeur_particules.c
testeur_robots.o: constantes.h utilitaire.h robot.h tolerance.h error.h testeur_robots.c
