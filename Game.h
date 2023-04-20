#ifndef _Game
#define _Game
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include "cardNodeDos.h"

void showHand(card*, wchar_t[11][41]);
int loadGfx(wchar_t[11][41]);

void showHand(card* headNode, wchar_t gfx[11][41]){
    card* currentNode = headNode->nextCard;
    while (currentNode != NULL)
    {
        switch (currentNode->color)
        {
        case 'R':
            printf("\033[31m");
            break;
        case 'B':
            printf("\033[32m");
            break;
        case 'Y':
            printf("\033[33m");
            break;
        case 'G':
            printf("\033[34m");
            break;        
        default:
            break;
        }
        switch(currentNode->value){
            case 1:
                for(int i = 0; i < 40; i++){
                    printf("%lc", gfx[1][i]);
                }
                break;
            case 3:
                for(int i = 0; i < 40; i++){
                    printf("%lc", gfx[3][i]);
                }
                break;
            case 4:
                for(int i = 0; i < 40; i++){
                    printf("%lc", gfx[4][i]);
                }
                break;
            case 5:
                for(int i = 0; i < 40; i++){
                    printf("%lc", gfx[5][i]);
                }
                break;
            case 6:
                for(int i = 0; i < 40; i++){
                    printf("%lc", gfx[6][i]);
                }
                break;
            case 7:
                for(int i = 0; i < 40; i++){
                    printf("%lc", gfx[7][i]);
                }
                break;
            case 8:
                for(int i = 0; i < 40; i++){
                    printf("%lc", gfx[8][i]);
                }
                break;
            case 9:
                for(int i = 0; i < 40; i++){
                    printf("%lc", gfx[9][i]);
                }
                break;
            case 10:
                for(int i = 0; i < 40; i++){
                    printf("%lc", gfx[10][i]);
                }
                break;
        }
        if(currentNode->action == '#'){
            for(int i = 0; i < 40; i++){
                printf("%lc", gfx[0][i]);
            }
        }
        if(currentNode->value == 2){
            for(int i = 0; i < 40; i++){
                if(i < 3){
                    printf("\033[31m");}
                else if((i > 3 && i < 8)){
                    printf("\033[32m");}
                else if((i > 31 && i < 35)){
                    printf("\033[33m");}
                else if((i > 35)){
                    printf("\033[34m");}
                else{
                    printf("\033[0m");}
                printf("%lc", gfx[2][i]);

            }
        }
        printf("\033[0m");
        fflush(stdout);
    currentNode = currentNode->nextCard;
    }
    
    

}

int loadGfx(wchar_t deck[11][41]){
    FILE* inFile = NULL;
    inFile = fopen("DosGraphics.dat", "r");
    if((inFile == NULL))
        return -1;
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 40; j++){
            fscanf(inFile, "%lc", &deck[i][j]);
        }
        //fscanf(inFile, "%*c");
    }
}


#endif