#include "util.h"


long sizeInByte(char* size)
{

    // Il faut faire de l'erreur handling /!\

    long res = 0;

    char coef = size[strlen(size) - 1];
    switch (coef)
    {
    case 'c':
        res = atoi(size); //conversion en long
        break;
    case 'k':
        res = atoi(size);
        res *= k;    // multiplication par le coeff
        break;
    case 'M':
        res = atoi(size);
        res *= M;
        break;
    case 'G':
        res = atoi(size);
        res *= G;
        break;
    default:
        res = atoi(size);
        break;
    }
    return res;
}

double timeInSecond(char* size)
{
    double res = 0;

    char coef = size[strlen(size) - 1];
    switch (coef)
    {
    case 'm':
        res = atoi(size) * m; //conversion en double
        break;
    case 'h':
        res = atoi(size);
        res *= h;
        res *= m;    // multiplication par le coeff
        break;
    case 'j':
        res = atoi(size);
        res *= h;
        res *= m;
        res *= j;
        break;
    default:
        res = atoi(size);
        break;
    }

    return res;
}
