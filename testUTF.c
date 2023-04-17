#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include "cardNodeUTF.h"
#define DECK_FILE_PATH "./cardDeckUTF.dat"


int main(){
    setlocale(LC_ALL, "");
    wchar_t heart = 0x1F0A9;
    card *deckHead = NULL, *playerHand = NULL, *player2Hand = NULL, *shuffleHead = NULL;
    deckHead = (card*)malloc(sizeof(card));
    newCardNode(deckHead, NULL, -1, 'C', 'R'); 
    initDeck(deckHead, DECK_FILE_PATH);
    shuffleHead = (card*)malloc(sizeof(card));
    playerHand = (card*)malloc(sizeof(card));
    player2Hand = (card*)malloc(sizeof(card));
    newCardNode(deckHead, NULL, -1, '#', '#'); 
    newCardNode(playerHand, NULL, -2, '#', '#');
    newCardNode(player2Hand, NULL, -3, '#', '#');

    // Shuffle deck
    for(int i = 0; i < 100; i++){
        shuffleHand(deckHead, shuffleHead);
        shuffleHand(shuffleHead, deckHead);

    }
    for(int i = 0; i < 7; i++)
        pullFrom(deckHead, playerHand);
    //listHand(deckHead);



    return 0;
}