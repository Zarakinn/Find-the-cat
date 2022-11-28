#include <stdio.h>
  
long int findSize(char file_name[])
{
    
    FILE* fp = fopen(file_name, "r");
  
    
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
  
    fseek(fp, 0L, SEEK_END);
  
    // calcul de la taille du fichier ( positionement sur le bit de fin)
    long int res = ftell(fp);
  
    // fermeture
    fclose(fp);
  
    return res;
}
  
int main()
{
    char file_name[] = { "../src" };
    long int res = findSize(file_name);
    if (res != -1)
        printf("Size of the file is %ld bytes \n", res);
    return 0;
}