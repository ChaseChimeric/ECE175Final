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


    setlocale(LC_ALL, "");
    card *deckHead = NULL, *shuffleHead = NULL, *playDeck = NULL;
    card* players[6];
    wchar_t cardGfx[11][41];
    loadGfx(cardGfx);
    deckHead = (card*)malloc(sizeof(card));
        newCardNode(deckHead, NULL, -10, '!', '!'); 
    shuffleHead = (card*)malloc(sizeof(card));
        newCardNode(shuffleHead, NULL, -11, '!', '!'); 
    playDeck = (card*)malloc(sizeof(card));
        newCardNode(playDeck, NULL, -420, '!', '!');
    initDeck(deckHead, DECK_FILE_PATH);

    
    int playerAmount = 0, targetCard, amountToPlay = -111, cardsToPlay[2], cont = 0, gameloop = 1;
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
    
    pullFrom(deckHead, players[0], 7);
    pullFrom(deckHead, playDeck, 2);
    while(gameloop){
        ClearScreen();
        printf("Current Center Row\n");
        showHand(playDeck, cardGfx);
        printf("Your Hand\n");
        showHand(players[0], cardGfx);
        targetCard = -1;

        while(targetCard < 0 || targetCard > countHand(playDeck)){
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
            while((cardsToPlay[0] < 1) || (cardsToPlay[0] > countHand(players[0]))){
                printf("Select Card 1 to play (1-%d): ", countHand(players[0]));
                scanf("%d", &cardsToPlay[0]);
                cont = 1;
            }

            if(amountToPlay == 2){
            while((cardsToPlay[1] < 1) || cardsToPlay[1] > countHand(players[0])){
                printf("Select Card 2 to play (1-%d): ", countHand(players[0]));
                scanf("%d",&cardsToPlay[1]);
            }
            }
        }
        while(amountToPlay == 0 && cardsToPlay[0] < 1 || cardsToPlay[0] > countHand(players[0])){
            printf("Your New Hand:\n");
            pullFrom(deckHead, players[0], 1);
            showHand(players[0], cardGfx);
            printf("Select card to discard to center row (1-%d): ", countHand(players[0]));
            scanf("%d", &cardsToPlay[0]);
        }
        ExecuteAction(players[0],playDeck, shuffleHead, targetCard, amountToPlay, cardsToPlay);
        for(int i = 0; i < 1; i++)
            delay(5,0);
        playerAmount = 0;
        amountToPlay = -111;
        cont = 0;
        cardsToPlay[0] = -1;
        cardsToPlay[1] = -1;
    }

    showHand(playDeck, cardGfx);
    printf("\n\n");
    showHand(players[0], cardGfx);
    //reset all vars
    //end turn
    fflush(stdout);
    return 0;
}



