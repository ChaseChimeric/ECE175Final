#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include "cardNodeDos.h"
#include "Graphics.h"
#include "Game.h"
#define DECK_FILE_PATH "cardDeckDos.dat"

void delay(int ms);
void GameStart();
void ClearScreen();

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

    
    int playerAmount = 0, targetCard;
    char playCards[200], tmpStr[50];

    // Shuffle deck
    ClearScreen();
    G_intro();
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
    ClearScreen();
    pullFrom(deckHead, players[0], 7);
    pullFrom(deckHead, playDeck, 2);\
    printf("Current Center Row\n");
    showHand(playDeck, cardGfx);
    printf("Your Hand\n");
    showHand(players[0], cardGfx);
    targetCard = -1;
    while(targetCard < 1 || targetCard > countHand(playDeck)){
        printf("Select Center Row Card to play on (1-%d): ", countHand(playDeck));
        scanf("%d", &targetCard);
    }
    targetCard = 0;
    while(targetCard < 1 || targetCard > countHand(playDeck)){
        printf("Select cards to play separated by comma (1-%d): ", countHand(players[0]));
        fgets(playCards, 200, stdin);
        

    }
    
    //printf("%s", cardGfx[0]);
    fflush(stdout);
    return 0;
}



