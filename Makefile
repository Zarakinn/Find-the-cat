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
# Dossier Lib
L = lib/

ftc: main.o explorer.o checker.o util.o parser.o MegaMimes.o
	$(COMPIL) -o ftc main.o explorer.o checker.o util.o parser.o MegaMimes.o && $(MOV)

parser: parser.o util.o
	$(COMPIL) -o parser parser.o util.o && $(MOV)

main.o:
	$(COMPIL) -c $(S)main.c 

parser.o:
	$(COMPIL) -c $(S)parser.c

explorer.o: checker.o 
	$(COMPIL) -c $(S)explorer.c 

checker.o: 
	$(COMPIL) -c $(S)checker.c

util.o:
	$(COMPIL) -c $(S)util.c

MegaMimes.o:
	$(COMPIL) -c $(L)MegaMimes.c
	
# Nettoyage
clean:
	rm -f ./bin/*
	rm -rf ./*.o
	rm -rf ./obj/*.o
	rm ftc
	rm -f parser

