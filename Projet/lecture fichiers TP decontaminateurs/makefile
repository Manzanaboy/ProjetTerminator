# Makefile

build:
	gcc -Wall -Wextra -c utilitaire.c -o utilitaire.o
	gcc -Wall -Wextra -c error.c -o error.o
	gcc -Wall -Wextra -c particule.c -o particule.o
	gcc -Wall -Wextra -c robot.c -o robot.o
	gcc -Wall -Wextra -c simulation.c -o simulation.o
	gcc -Wall -Wextra -c main.c -o main.o
	gcc -Wall -Wextra main.o utilitaire.o robot.o particule.o simulation.o error.o -lm -lstdc++ -o main.x


# Definitions de macros

CC     = gcc
CFLAGS = -Wall
CFILES = utilitaire.c error.c robot.c particule.c main.c simulation.c
OFILES = $(CFILES:.c=.o)

# Definition de la premiere regle

#test.x: test.o 
#	gcc test.o -lm -o test.x	  

main.x: $(OFILES)
	$(CC) $(OFILES) -lm -o main.x

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
particule.o: particule.c utilitaire.h tolerance.h error.h particule.h \
 constantes.h
main.o: main.c utilitaire.h tolerance.h error.h constantes.h simulation.h \
 robot.h particule.h
simulation.o: simulation.c utilitaire.h tolerance.h error.h constantes.h \
 simulation.h robot.h particule.h
