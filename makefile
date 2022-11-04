CC = clang
FLAGS = -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
COMPIL = $(CC) $(FLAGS)

MOV = mv *.o obj/

# Source du code
S = src/
# .o générer à la compilation
O = obj/
# Dossier exécutable
B = bin/

ftc: main.o
	$(COMPIL) -o $(B)ftc main.o && $(MOV)
	
main.o:
	$(COMPIL) -c $(S)main.c
	
# Nettoyage
clean:
	rm -f ./bin/*
	rm -rf ./*.o
	rm -rf ./obj/*.o

