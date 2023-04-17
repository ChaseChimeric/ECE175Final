#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "cardNode.h"
#define DECK_FILE_PATH "./cardDeck.dat"

int main(){
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
    
    listHand(deckHead);
    printf("\n");
    card *currentNode = (deckHead->nextCard);
    card* testFind = getFromIndex(deckHead, 51);
    shuffleHand(deckHead, shuffleHead);
    shuffleHand(shuffleHead, deckHead);
    shuffleHand(deckHead, shuffleHead);
    shuffleHand(shuffleHead, deckHead);
    shuffleHand(deckHead, shuffleHead);
    shuffleHand(shuffleHead, deckHead);
    shuffleHand(deckHead, shuffleHead);
    shuffleHand(shuffleHead, deckHead);

    listHand(deckHead);
    int temp = countHand(deckHead);


    // test print deck

    return 0;
}