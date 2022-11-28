CC = clang
FLAGS = -Wall -Wextra -pedantic -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls
COMPIL = $(CC) $(FLAGS)

MOV = mv *.o obj/

# Source du code
S = src/
# .o générer à la compilation
O = obj/
# Dossier exécutable
B = bin/

ftc: main.o explorer.o
	$(COMPIL) -o ftc main.o explorer.o && $(MOV)
	
main.o:
	$(COMPIL) -c $(S)main.c

explorer.o:
	$(COMPIL) -c $(S)explorer.c
	
# Nettoyage
clean:
	rm -f ./bin/*
	rm -rf ./*.o
	rm -rf ./obj/*.o

