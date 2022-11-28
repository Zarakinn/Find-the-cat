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

ftc: main.o explorer.o checker.o
	$(COMPIL) -o ftc main.o explorer.o checker.o && $(MOV)

parser: parser.o
	$(COMPIL) -o parser parser.o && $(MOV)

main.o:
	$(COMPIL) -c $(S)main.c

parser.o:
	$(COMPIL) -c $(S)parser.c

explorer.o: checker.o
	$(COMPIL) -c $(S)explorer.c 

checker.o:
	$(COMPIL) -c $(S)checker.c
	
# Nettoyage
clean:
	rm -f ./bin/*
	rm -rf ./*.o
	rm -rf ./obj/*.o
	rm ftc
	rm parser

