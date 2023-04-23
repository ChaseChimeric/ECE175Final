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
int ExecuteAction(card*, card*, card*, int, int, int[2]);

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


int ExecuteAction(card* player, card* centerRow, card* shuffleHead, int targetIndex, int amountToPlay, int cardsToPlay[2]){
    // make case for if target is # or wild 2
    int stackVal1 = -1, stackVal2 = -1, swapTmp;
    if(amountToPlay == 2){
        if(cardsToPlay[0] > cardsToPlay[1]){
            swapTmp = cardsToPlay[0];
            cardsToPlay[0] = cardsToPlay[1];
            cardsToPlay[1] = swapTmp;
        }
    }
    if((getFromIndex(player, cardsToPlay[0]-1)->color == 'W') || (amountToPlay == 2 && getFromIndex(player, cardsToPlay[1]-1)->color == 'W')){
        printf("wildcard played\n");
    }
    if(amountToPlay == 0){
        moveIndTo(player, centerRow, cardsToPlay[0]-1, 0);
        printf("Card Discarded\n");
    }
    else if(amountToPlay == 1){
        if(getFromIndex(player,cardsToPlay[0]-1)->value == getFromIndex(centerRow, targetIndex-1)->value || getFromIndex(player,cardsToPlay[0]-1)->value == 0 || getFromIndex(centerRow, targetIndex-1)->value == 0){
            if(getFromIndex(player,cardsToPlay[0]-1)->color == getFromIndex(centerRow, targetIndex-1)->color || getFromIndex(player,cardsToPlay[0]-1)->color == 'W' || getFromIndex(centerRow, targetIndex-1)->color == 'W'){
                //single color match
                printf("single color match\n");
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[0]-1, 1);
                //insertAfter()
                
                
            }
            else{
                printf("single match\n");
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[0]-1, 1);
                
            }
            //single match
            
        }
        else{
            // no match
                printf("Not a valid match\n");
                return 0;
        }
    
    
    }
    else if(amountToPlay == 2){
        int cardSum = getFromIndex(player,cardsToPlay[0]-1)->value + getFromIndex(player,cardsToPlay[1]-1)->value;
        // if one card is bigger than the target card, return -1
        cardSum = (getFromIndex(player,cardsToPlay[0]-1)->value == 0)? 0 : cardSum;
        cardSum = (getFromIndex(player,cardsToPlay[1]-1)->value == 0)? 0 : cardSum;
        

        
        if(cardSum == getFromIndex(centerRow, targetIndex-1)->value || cardSum == 0){
            if((getFromIndex(player,cardsToPlay[0]-1)->color == getFromIndex(centerRow, targetIndex-1)->color || getFromIndex(player,cardsToPlay[0]-1)->color == 'W' || getFromIndex(centerRow, targetIndex-1)->color == 'W') && (getFromIndex(player,cardsToPlay[1]-1)->color == getFromIndex(centerRow, targetIndex-1)->color || getFromIndex(player,cardsToPlay[1]-1)->color == 'W' || getFromIndex(centerRow, targetIndex-1)->color == 'W')){
                // double color match
                while(stackVal1 != 1 && stackVal1 != 2){
                    printf("Which card should be on top? (1-2): ");
                    scanf("%d", &stackVal1);
                }
                stackVal2 = (stackVal1 == 1)? 2:1;
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, shuffleHead, cardsToPlay[stackVal2-1]-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[stackVal1-1]-1, 1);
                printf("double color match\n");
                
            }
            else{
                while(stackVal1 != 1 && stackVal1 != 2){
                    printf("Which card should be on top? (1-2): ");
                    scanf("%d", &stackVal1);
                }
                stackVal2 = (stackVal1 == 1)? 2:1;
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, shuffleHead, cardsToPlay[stackVal2-1]-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[stackVal1-1]-1, 1);
                
                
                printf("double match\n");
                
                //double match

            }
        }
        else{
            printf("Not a valid match\n");
            return 0;
        }
        printf("");
        
    }
    
    return -1;
}


#endif