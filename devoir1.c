#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int f(int n){
    if(n == 1)
        return 2;
    return 2*f(n - 1);
}

int g(int n){
    return 2*n;
}

int fog(int x){
    return f(g(x));
}

int gof(int x){
    return g(f(x));
}

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Nombre d'argument sur la ligne de commande inuffisant\n");
        printf("Usage : %s <option> <value>\n",argv[0]);
        return 0;
    }

    int n = atoi(argv[2]);
    if((strcmp(argv[1],"-f") == 0) && (argc == 3)){
        printf("2^%d = %d \n",n,f(n));
    }
    else{
        if((strcmp(argv[1],"-g") == 0) && (argc == 3)){
            printf("2*%d = %d \n",n,g(n));
        }
        else{
            if((strcmp(argv[1],"-g") == 0) && (argc == 4) && (strcmp(argv[3],"-f") == 0)){
                printf("gof(%d) = %d \n",n,gof(n));
            }
            else{
                if((strcmp(argv[1],"-f") == 0) && (argc == 4) && (strcmp(argv[3],"-g") == 0)){
                    printf("fog(%d) = %d \n",n,fog(n));
                }
                else
                    printf("option invalide\n");
            }
        }
    }
    return 0;
}