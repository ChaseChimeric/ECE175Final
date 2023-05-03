#ifndef _Graphics
#define _Graphics
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int loadGfx(char[12][41]);
void G_intro();
void delay(int, int);
void ClearScreen();


int loadGfx(char deck[12][41]){
    /*
    Loads graphics into array
    */
    FILE* inFile = NULL;
    inFile = fopen("DosGraphics.dat", "r");

    char tmp;
    if(inFile == NULL)
        return -1;
    rewind(inFile);
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 40; j++){
            fscanf(inFile, "%c", &tmp);
            if (tmp == '\r') {
                j--;
                continue;
            }
            deck[i][j] = tmp;
            
        }

    }
    return 0;
}

void G_intro(){
    /*
    Prints scrolling intro screen
    */
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
    //Custom delay for < 1s delays
    struct timespec remaining, request = { seconds, ms*1000000};
    nanosleep(&request, &remaining);
}

void ClearScreen(){
    //Clears screen with newlines
    for(int i = 0; i < 75; i++){
        printf("\n");
    }
        fflush(stdout);

}
#endif