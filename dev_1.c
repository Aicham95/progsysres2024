#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int puissance(int n){
    if(n == 0)
        return 1;
    return 2*puissance(n - 1);
}

int multplication(int m){
    return 2*m;
}

int f_rond_g(int x){
    return puissance(multplication(x));
}

int g_rond_f(int x){
    return multplication(puissance(x));
}

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Nombre d'argument sur la ligne de commande inuffisant\n");
        printf("Usage : %s <option> <value>\n",argv[0]);
        return 0;
    }

    int n = atoi(argv[2]);
    if((strcmp(argv[1],"-f") == 0) && (argc == 3)){
        printf("2^%d = %d \n",n,puissance(n));
    }
    else{
        if((strcmp(argv[1],"-g") == 0) && (argc == 3)){
            printf("2*%d = %d \n",n,multplication(n));
        }
        else{
            if((strcmp(argv[1],"-g") == 0) && (argc < 5) && (strcmp(argv[3],"-f") == 0)){
                printf("g(f(%d)) = %d \n",n,g_rond_f(n));
            }
            else{
                if((strcmp(argv[1],"-f") == 0) && (argc < 5) && (strcmp(argv[3],"-g") == 0)){
                    printf("f(g(%d)) = %d \n",n,f_rond_g(n));
                }
                else
                    printf("option invalide\n");
            }
        }
    }
    return 0;
}