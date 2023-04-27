#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include "cardNodeDos.h"
#include "Graphics.h"
#include "Game.h"
#define DECK_FILE_PATH "cardDeckDos.dat"



int main(){


    //setlocale(LC_ALL, "");
    card *deckHead = NULL, *shuffleHead = NULL, *playDeck = NULL;
    card* players[6];
    int playerScore[6];
    for(int i = 0; i < 6; i++)
        playerScore[i] = 0;
    char cardGfx[12][81];
    loadGfx(cardGfx);
    fflush(stdout);
    deckHead = (card*)malloc(sizeof(card));
    printf("%s\n", cardGfx[1]);
        newCardNode(deckHead, NULL, -10, '!', '!'); 
    shuffleHead = (card*)malloc(sizeof(card));
        newCardNode(shuffleHead, NULL, -11, '!', '!'); 
    playDeck = (card*)malloc(sizeof(card));
        newCardNode(playDeck, NULL, -420, '!', '!');
    initDeck(deckHead, DECK_FILE_PATH);

    
    int playerAmount = 0, targetCard, amountToPlay = -111, cardsToPlay[2], cont = 0, gameloop = 1, hasPlayed = 0, currentPlayer = 0, playerWon = 0;
    char playCards[200], tmpStr[50];

    // Shuffle deck
    ClearScreen();
    //G_intro();
    ClearScreen();


    for(int i = 0; i < 100;i++){
        shuffleHand(deckHead, shuffleHead);
        shuffleHand(shuffleHead, deckHead);
    }
    printf("Welcom to DOS\nHow many players? (1-6): ");
    scanf("%d", &playerAmount);

    switch(playerAmount){
        case 6:
            players[5] = (card*)malloc(sizeof(card));
            newCardNode(players[5], NULL, -6, '!', '!');
        case 5:
            players[4] = (card*)malloc(sizeof(card));
            newCardNode(players[4], NULL, -5, '!', '!');
        case 4:
            players[3] = (card*)malloc(sizeof(card));
            newCardNode(players[3], NULL, -4, '!', '!');
        case 3:
            players[2] = (card*)malloc(sizeof(card));
            newCardNode(players[2], NULL, -3, '!', '!');
        case 2:
            players[1] = (card*)malloc(sizeof(card));
            newCardNode(players[1], NULL, -2, '!', '!');
        case 1:
            players[0] = (card*)malloc(sizeof(card));
            newCardNode(players[0], NULL, -1, '!', '!');
        default:
            break;
    }

    while(!playerWon)
    {   
        for(int i = 0; i < playerAmount; i++){
            pullFrom(deckHead, players[i], 2);
        }
        pullFrom(deckHead, playDeck, 2);
        gameloop = 0;
        while(gameloop){
            if(currentPlayer > (playerAmount-1))
                currentPlayer = 0;
            
            ClearScreen();
            printf("Current Center Row\n");
            showHand(playDeck, cardGfx);
            printf("Your Hand, player %d\n", currentPlayer);
            showHand(players[currentPlayer], cardGfx);
            targetCard = -1;

            while((targetCard < 0 || targetCard > countHand(playDeck))){
                printf("Select Center Row Card to play on (1-%d, 0 if not playing): ", countHand(playDeck));
                scanf("%d", &targetCard);
            }
            if(targetCard == 0)
                amountToPlay = 0;

            while((amountToPlay < 1 || amountToPlay > 2)&& amountToPlay != 0){
                printf("How many cards do you want to play? (up to 2): ");
                scanf("%d", &amountToPlay);
            }
            while(!cont && (amountToPlay != 0)){
                while((cardsToPlay[0] < 1) || (cardsToPlay[0] > countHand(players[currentPlayer]))){
                    printf("Select Card 1 to play (1-%d): ", countHand(players[currentPlayer]));
                    scanf("%d", &cardsToPlay[0]);
                    cont = 1;
                }

                if(amountToPlay == 2){
                    while((cardsToPlay[1] < 1) || cardsToPlay[1] > countHand(players[currentPlayer])){
                        printf("Select Card 2 to play (1-%d): ", countHand(players[currentPlayer]));
                        scanf("%d",&cardsToPlay[1]);
                    }
                }
            }
            while((amountToPlay == 0) && (cardsToPlay[0] < 1 || cardsToPlay[0] > countHand(players[currentPlayer])) && (hasPlayed == 0)){
                printf("Your New Hand:\n");
                pullFrom(deckHead, players[currentPlayer], 1);
                showHand(players[currentPlayer], cardGfx);
                printf("Select card to discard to center row (1-%d): ", countHand(players[currentPlayer]));
                scanf("%d", &cardsToPlay[0]);
            }
            if((amountToPlay == 0)&&(hasPlayed==1)){
                amountToPlay = -9;
                cardsToPlay[0] = -1;
                cardsToPlay[1] = -1;
            }
            int actionState = ExecuteAction(players[currentPlayer],playDeck, shuffleHead, targetCard, amountToPlay, cardsToPlay, cardGfx);
            if(actionState != 0)
                hasPlayed = 1;


            //playerAmount = 0;

            switch(actionState){
                case 1:
                    printf("single match\n");
                    break;
                case 2:
                    printf("single color match\n");
                    break;
                case 3:
                    printf("double match\n");
                    break;
                case 4:
                    printf("double color match\n");
                    break;
                case 0:
                    if(getFromIndex(playDeck, targetCard-1)->stacked == 1){
                        printf("Cannot play on an already stacked card.\n");
                    }
                    else{
                        printf("Not a valid match\n");
                    }
                    break;
                case -1:
                    printf("shouldn't have gotten to this point, errorororrrrrrrrrr\n");
                    break;
                case -2:
                    printf("Card Discarded\nEnding Turn\n");
                    hasPlayed = 0;
                    resetPlayDeck(playDeck, deckHead);
                    currentPlayer++;
                    //increment player
                    
                    break;
                case -3:
                    printf("Cannot play on an already stacked card.\n");
                    
                    break;
                case -4:
                    //increment player
                    printf("Ending turn.\n");
                    hasPlayed = 0;
                    resetPlayDeck(playDeck, deckHead);
                    currentPlayer++;
                    break;
                default:
                    break;
            }
            //check win round state

            
            amountToPlay = -111;
            cont = 0;
            cardsToPlay[0] = -1;
            cardsToPlay[1] = -1;
            if(players[currentPlayer]->nextCard == NULL){
                int scoreTmp;
                scoreTmp = calcPoints(players[currentPlayer], players, playerAmount);
                playerScore[currentPlayer] += scoreTmp;
                gameloop = 0;
                printf("Player %d has won this round and scored %d points\nStarting new round\n", currentPlayer, scoreTmp);
            }
                for(int i = 0; i < 1; i++)
                delay(2,0);

        }
        playerWon = checkWin(playerScore, playerAmount);
    for(int i = 0; i < playerAmount; i++)
        shuffleHand(players[i], shuffleHead);
    shuffleHand(playDeck, shuffleHead);
    shuffleHand(deckHead, shuffleHead);
    shuffleHand(shuffleHead, deckHead);

}
printf("Player %d has won\n", playerWon);
    //showHand(playDeck, cardGfx);
    //printf("\n\n");
    //showHand(players[currentPlayer], cardGfx);
    //reset all vars
    //end turn
    fflush(stdout);
    return 0;
}



