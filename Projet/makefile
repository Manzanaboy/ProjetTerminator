# Makefile

build:
	gcc -Wall -Wextra -c utilitaire.c -o utilitaire.o
	gcc test.o utilitaire.o -lm -lstdc++ -o test.x


# Definitions de macros

CC     = gcc
CFLAGS = -Wall
CFILES = utilitaire.c
OFILES = $(CFILES:.c=.o)

# Definition de la premiere regle

test.x: test.o 
	gcc test.o -lm -o test.x
	  

#testeur.x: $(OFILES)
#	$(CC) $(OFILES) -lm -o testeur.x

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

utilitaire.o: utilitaire.c tolerance.h
