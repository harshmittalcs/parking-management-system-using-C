#include <stdio.h>
#include "auth.h"
#include <string.h>
int login()
{
    char u[20];
    char p[20];
    printf("-----Admin Login Called------\n");
    printf("Enter Username:");
    fgets(u,20, stdin);
    printf("Enter Password:");
    fgets(p,20, stdin);
    u[strcspn(u, "\n")] = 0;
    p[strcspn(p, "\n")] = 0;

    if((strcmp(u,"admin1")==0 && strcmp(p,"1234")==0) || (strcmp(u,"admin2")==0 && strcmp(p,"4321") ==0)){
        return 1;
    }
    
    else{
        return 0;
    }
}