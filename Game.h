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
int ExecuteAction(card*, card*, card*, int, int, int[2], wchar_t[11][41]);
void resetPlayDeck(card *playDeck, card *deckHead);

void showHand(card* headNode, wchar_t gfx[11][41]){
    card* currentNode = headNode->nextCard;
    int iter = 1;
    while (currentNode != NULL)
    {       printf("\e[1;97m");
            printf("%d\n", iter);
        if(currentNode->stacked == 0){
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
        }
        else{
            printf("\e[0;35m");
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
        if(currentNode->value == 2 && currentNode->stacked != 1){
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
        else if(currentNode->value == 2 && currentNode->stacked == 1){
            printf("\e[0;35m");
            for(int i = 0; i < 40; i++){
                printf("%lc", gfx[2][i]);
            }
        }
        printf("\033[0m");
        fflush(stdout);
    currentNode = currentNode->nextCard;
    iter++;
    }
    
    

}


int ExecuteAction(card* player, card* centerRow, card* shuffleHead, int targetIndex, int amountToPlay, int cardsToPlay[2], wchar_t gfx[11][41]){
    
    int largerIndex = -1, smallerIndex = -1, swapTmp, input;
    if(amountToPlay == -9){
        return -4;
    }
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
        
        return -2;
    }
    else if(amountToPlay == 1){
        if((getFromIndex(player,cardsToPlay[0]-1)->value == getFromIndex(centerRow, targetIndex-1)->value || getFromIndex(player,cardsToPlay[0]-1)->value == 0 || getFromIndex(centerRow, targetIndex-1)->value == 0)&& getFromIndex(centerRow, targetIndex-1)->stacked != 1){
            if((getFromIndex(player,cardsToPlay[0]-1)->color == getFromIndex(centerRow, targetIndex-1)->color) || (getFromIndex(player,cardsToPlay[0]-1)->color == 'W') || (getFromIndex(centerRow, targetIndex-1)->color == 'W')){
                //single color match
                
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[0]-1, 1);
                //insertAfter()
                return 2;
                
            }
            else{
                
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[0]-1, 1);
                return 1;
            }
            //single match
            
        }
        else{
            // no match
                
                return 0;
        }
    
    
    }
    else if(amountToPlay == 2){
        int cardSum = getFromIndex(player,cardsToPlay[0]-1)->value + getFromIndex(player,cardsToPlay[1]-1)->value;
        // if one card is bigger than the target card, return -1
        cardSum = (getFromIndex(player,cardsToPlay[0]-1)->value == 0)? 0 : cardSum;
        cardSum = (getFromIndex(player,cardsToPlay[1]-1)->value == 0)? 0 : cardSum;
        

        
        if((cardSum == getFromIndex(centerRow, targetIndex-1)->value || cardSum == 0 )&& getFromIndex(centerRow, targetIndex-1)->stacked != 1){
            //print action
            //card *tmpHead = (card*)malloc(sizeof(card)), *move1 = (card*)malloc(sizeof(card)), *move2 = (card*)malloc(sizeof(card));

            
            if(cardsToPlay[0] < cardsToPlay[1]){
                smallerIndex = 0;
                largerIndex = 1;
            }
            else{
                smallerIndex = 1;
                largerIndex = 0;
            }
            if(((getFromIndex(player,cardsToPlay[0]-1)->color == getFromIndex(centerRow, targetIndex-1)->color) || (getFromIndex(player,cardsToPlay[0]-1)->color == 'W') || (getFromIndex(centerRow, targetIndex-1)->color == 'W')) && ((getFromIndex(player,cardsToPlay[1]-1)->color == getFromIndex(centerRow, targetIndex-1)->color) || (getFromIndex(player,cardsToPlay[1]-1)->color == 'W') || (getFromIndex(centerRow, targetIndex-1)->color == 'W'))){
                // double color match
                
                //stackVal2 = (stackVal1 == 1)? 2:1;
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, shuffleHead, cardsToPlay[largerIndex]-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[smallerIndex]-1, 1);

                
                return 4;
            }
            else{
                
                //stackVal2 = (stackVal1 == 1)? 2:1;
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, shuffleHead, cardsToPlay[largerIndex]-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[smallerIndex]-1, 1);
                
                
                 // error
                return 3;
                //double match

            }
        }
        else if(getFromIndex(centerRow, targetIndex-1)->stacked == 1){
            return -3;
        }
        else{
            
            return 0;
        }
        printf("");
        
    }
    
    return -1;
}

void resetPlayDeck(card *playDeck, card *deckHead){
    for(int i = 0; i < countHand(playDeck); i++){
        if(getFromIndex(playDeck, i)->stacked == 1){
            removeFrom(playDeck, getFromIndex(playDeck, i));
        }
    }
    while(countHand(playDeck) < 2){
        pullFrom(deckHead, playDeck, 1);
    }



}

#endif