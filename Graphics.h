#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>

void G_intro();
void delay(int);
void ClearScreen();

void G_intro(){
    FILE *logoFile = fopen("DosLogo.dat", "r");
    char tmp;
    int count = 0;
    printf("\033[31m");
    while(!feof(logoFile)){
        fscanf(logoFile, "%c", &tmp);
        printf("%c", tmp);
        if(tmp == '\n'){
            delay(60);
            fflush(stdout);
            count = 0;
        }
        count++;
    }
    rewind(logoFile);

    printf("\033[32m");
    while(!feof(logoFile)){
        fscanf(logoFile, "%c", &tmp);
        printf("%c", tmp);
        if(tmp == '\n'){
            delay(60);
            fflush(stdout);
            count = 0;
        }
        count++;
    }
    rewind(logoFile);
    
    printf("\033[33m");
    while(!feof(logoFile)){
        fscanf(logoFile, "%c", &tmp);
        printf("%c", tmp);
        if(tmp == '\n'){
            delay(60);
            fflush(stdout);
            count = 0;
        }
        count++;
    }
    rewind(logoFile);
    
    printf("\033[34m");
    while(!feof(logoFile)){
        fscanf(logoFile, "%c", &tmp);
        printf("%c", tmp);
        if(tmp == '\n'){
            delay(60);
            fflush(stdout);
            count = 0;
        }
        count++;
    }
    rewind(logoFile);
    
    printf("\n\033[0mBy Ryan Fong & Lilly Gentry");
    fflush(stdout);
    delay(2000);
}
void delay(int ms){
    struct timespec remaining, request = { 0, ms*1000000 };
    nanosleep(&request, &remaining);
}

void ClearScreen(){
    for(int i = 0; i < 50; i++){
        printf("\n");
    }
        fflush(stdout);

}