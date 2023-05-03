#ifndef _Game
#define _Game
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cardNodeDos.h"

void showHand(card*, char[11][41]);
int ExecuteAction(card*, card*, card*, int, int, int[2], char[11][41]);
void resetPlayDeck(card *playDeck, card *deckHead);
int calcPoints(card *winner, card *players[6], int playerAmount);
int checkWin(int playerScores[6], int playerAmount);
void othersDraw(card *currentPlayer, card *players[6], int playerAmount, card*);

void showHand(card* headNode, char gfx[11][41]){
    /*
    Prints out hand graphically
    */
    card* currentNode = headNode->nextCard;
    int iter = 1;
    while (currentNode != NULL)
    {       printf("\033[1;97m");
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
            printf("\033[0;35m");
        }
        switch(currentNode->value){
            case 1:
                for(int i = 0; i < 40; i++){
                    printf("%c", gfx[1][i]);
                }
                break;
            case 3:
                for(int i = 0; i < 40; i++){
                    printf("%c", gfx[3][i]);
                }
                break;
            case 4:
                for(int i = 0; i < 40; i++){
                    printf("%c", gfx[4][i]);
                }
                break;
            case 5:
                for(int i = 0; i < 40; i++){
                    printf("%c", gfx[5][i]);
                }
                break;
            case 6:
                for(int i = 0; i < 40; i++){
                    printf("%c", gfx[6][i]);
                }
                break;
            case 7:
                for(int i = 0; i < 40; i++){
                    printf("%c", gfx[7][i]);
                }
                break;
            case 8:
                for(int i = 0; i < 40; i++){
                    printf("%c", gfx[8][i]);
                }
                break;
            case 9:
                for(int i = 0; i < 40; i++){
                    printf("%c", gfx[9][i]);
                }
                break;
            case 10:
                for(int i = 0; i < 40; i++){
                    printf("%c", gfx[10][i]);
                }
                break;
        }
        if(currentNode->action == '#'){
            for(int i = 0; i < 40; i++){
                printf("%c", gfx[0][i]);
            }
        }
        if(currentNode->value == 2 && currentNode->stacked != 1){
            for(int i = 0; i < 40; i++){
                /*
                if(i < 3){
                    printf("\033[31m");}
                else if((i > 3 && i < 8)){
                    printf("\033[32m");}
                else if((i > 31 && i < 35)){
                    printf("\033[33m");}
                else if((i > 35)){
                    printf("\033[34m");}
                else{
                    printf("\033[0m");}*/
                printf("%c", gfx[2][i]);

            }
        }
        else if(currentNode->value == 2 && currentNode->stacked == 1){
            printf("\033[0;35m");
            for(int i = 0; i < 40; i++){
                printf("%c", gfx[2][i]);
            }
        }
        printf("\033[0m");
        fflush(stdout);
    currentNode = currentNode->nextCard;
    iter++;
    }
}


int ExecuteAction(card* player, card* centerRow, card* shuffleHead, int targetIndex, int amountToPlay, int cardsToPlay[2], char gfx[11][41]){
    /*
    Executes action based on inputs, returns a number to operate on
    */
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
        printf("wild Dos card played\n");
    }
    if(amountToPlay == 0){
        moveIndTo(player, centerRow, cardsToPlay[0]-1, 0);
        
        return -2;
    }
    else if(amountToPlay == 1){
        if((getFromIndex(player,cardsToPlay[0]-1)->value == getFromIndex(centerRow, targetIndex-1)->value || getFromIndex(player,cardsToPlay[0]-1)->value == 0 || getFromIndex(centerRow, targetIndex-1)->value == 0)&& getFromIndex(centerRow, targetIndex-1)->stacked != 1){
            if((getFromIndex(player,cardsToPlay[0]-1)->color == getFromIndex(centerRow, targetIndex-1)->color) || (getFromIndex(player,cardsToPlay[0]-1)->color == 'W') || (getFromIndex(centerRow, targetIndex-1)->color == 'W')){
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[0]-1, 1);
                return 2;
            }
            else{
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[0]-1, 1);
                return 1;
            }
        }
        else{
                return 0;
        }
    }
    else if(amountToPlay == 2){ 
        int cardSum = getFromIndex(player,cardsToPlay[0]-1)->value + getFromIndex(player,cardsToPlay[1]-1)->value;
        // if one card is bigger than the target card, return -1
        cardSum = (getFromIndex(player,cardsToPlay[0]-1)->value == 0)? 0 : cardSum;
        cardSum = (getFromIndex(player,cardsToPlay[1]-1)->value == 0)? 0 : cardSum;
        if(getFromIndex(centerRow, targetIndex-1)->value == 0){
            cardSum = 0;   
        }  
        if((cardSum == getFromIndex(centerRow, targetIndex-1)->value || cardSum == 0 )&& getFromIndex(centerRow, targetIndex-1)->stacked != 1){
            if(cardsToPlay[0] < cardsToPlay[1]){
                smallerIndex = 0;
                largerIndex = 1;
            }
            else{
                smallerIndex = 1;
                largerIndex = 0;
            }
            if(((getFromIndex(player,cardsToPlay[0]-1)->color == getFromIndex(centerRow, targetIndex-1)->color) || (getFromIndex(player,cardsToPlay[0]-1)->color == 'W') || (getFromIndex(centerRow, targetIndex-1)->color == 'W')) && ((getFromIndex(player,cardsToPlay[1]-1)->color == getFromIndex(centerRow, targetIndex-1)->color) || (getFromIndex(player,cardsToPlay[1]-1)->color == 'W') || (getFromIndex(centerRow, targetIndex-1)->color == 'W'))){
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, shuffleHead, cardsToPlay[largerIndex]-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[smallerIndex]-1, 1);
                return 4;
            }
            else{
                moveIndTo(centerRow, shuffleHead, targetIndex-1, 1);
                moveIndTo(player, shuffleHead, cardsToPlay[largerIndex]-1, 1);
                moveIndTo(player, centerRow, cardsToPlay[smallerIndex]-1, 1);
                return 3;
            }
        }
        else if(getFromIndex(centerRow, targetIndex-1)->stacked == 1){
            return -3;
        }
        else{
            
            return 0;
        }       
    } 
    return -1;
}

void resetPlayDeck(card *playDeck, card *deckHead){
    /*
    Clears all stacked cards on center row
    */
    for(int i = 0; i < countHand(playDeck); i++){
        if(getFromIndex(playDeck, i)->stacked == 1){
            removeFrom(playDeck, getFromIndex(playDeck, i));
            resetPlayDeck(playDeck, deckHead);
        }
    }
    while(countHand(playDeck) < 2){
        pullFrom(deckHead, playDeck, 1);
    }
}

int calcPoints(card *winner, card *players[6], int playerAmount){
    /*
    calculates the points won in the round and adds them to the players score
    */
    card *currentCard;
    int sum = 0;
    for(int i = 0; i < playerAmount; i++){
        if(players[i] == winner){
                continue;
            }
        currentCard = players[i]->nextCard;
        while(currentCard != NULL) {
            {
                if((currentCard->value == 1) || (currentCard->value > 2)){
                    sum += currentCard->value;
                }
                else if(currentCard->value == 2){
                    sum += 20;
                }
                else if(currentCard->value == 0){
                    sum += 40;
                }
            }   
            currentCard = currentCard->nextCard;
        }        
    }
    return sum;
}

int checkWin(int playerScores[6], int playerAmount){
    // Checks for final win state
    for(int i = 0; i < playerAmount; i++){
        if(playerScores[i] >= 200){
            return i+1;
        }
    }
    return 0;
}


void othersDraw(card *currentPlayer, card *players[6], int playerAmount, card *deck){
    // deals 1 card to everyone other than the specified player
    card *currentCard;
    for(int i = 0; i < playerAmount; i++){
        if(players[i] == currentPlayer){
                continue;
            }
        pullFrom(deck, players[i], 1);
    } 
}
#endif