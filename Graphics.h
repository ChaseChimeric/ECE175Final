#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>

int loadGfx(wchar_t[11][41]);
void G_intro();
void delay(int, int);
void ClearScreen();


int loadGfx(wchar_t deck[11][41]){
    FILE* inFile = NULL;
    inFile = fopen("DosGraphics.dat", "r");
    if(inFile == NULL)
        return -1;
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 40; j++){
            fscanf(inFile, "%lc", &deck[i][j]);
        }
    }
}

void G_intro(){
    FILE *logoFile = fopen("DosLogo.dat", "r");
    char tmp;
    int count = 0;
    printf("\033[31m");
    while(!feof(logoFile)){
        fscanf(logoFile, "%c", &tmp);
        printf("%c", tmp);
        if(tmp == '\n'){
            delay(0,60);
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
            delay(0,60);
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
            delay(0,60);
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
            delay(0,60);
            fflush(stdout);
            count = 0;
        }
        count++;
    }
    rewind(logoFile);
    
    printf("\n\033[0mBy Ryan Fong & Lilly Gentry");
    fflush(stdout);
    delay(2, 0);

    
}
void delay(int seconds, int ms){
    struct timespec remaining, request = { seconds, ms*1000000 };
    nanosleep(&request, &remaining);
}

void ClearScreen(){
    for(int i = 0; i < 50; i++){
        printf("\n");
    }
        fflush(stdout);

}