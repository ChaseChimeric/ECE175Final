#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "cardNode.h"
#define DECK_FILE_PATH "./cardDeck.dat"



int main(){
    card *deckHead = NULL,*shuffleHead = NULL;
    deckHead = (card*)malloc(sizeof(card));
    newCardNode(deckHead, NULL, -1, '#', '#'); 
        initDeck(deckHead, DECK_FILE_PATH);
    shuffleHead = (card*)malloc(sizeof(card));
    //playerHand = (card*)malloc(sizeof(card));
    //player2Hand = (card*)malloc(sizeof(card));
    //newCardNode(deckHead, NULL, -1, '#', '#'); 
    //newCardNode(playerHand, NULL, -2, '#', '#');
    //newCardNode(player2Hand, NULL, -3, '#', '#');
    int playerAmount;
    printf("How many players? (2-10): ");
    scanf("%d", &playerAmount);
    switch(playerAmount){
        case 2:
        card *player1Hand,*player2Hand;
        player1Hand = (card*)malloc(sizeof(card));
        player2Hand = (card*)malloc(sizeof(card));
        newCardNode(player1Hand, NULL, -2, '#', '#');
newCardNode(player2Hand, NULL, -3, '#', '#');
        break;
        case 3:
        card *player1Hand, *player2Hand, *player3Hand;
        player1Hand = (card*)malloc(sizeof(card));
        player2Hand = (card*)malloc(sizeof(card));
        player3Hand = (card*)malloc(sizeof(card));
        newCardNode(player1Hand, NULL, -2, '#', '#');
newCardNode(player2Hand, NULL, -3, '#', '#');
newCardNode(player3Hand, NULL, -4, '#', '#');
        break;
        case 4:
        card *player1Hand, *player2Hand, *player3Hand, *player4Hand;
        player1Hand = (card*)malloc(sizeof(card));
        player2Hand = (card*)malloc(sizeof(card));
        player3Hand = (card*)malloc(sizeof(card));
        player4Hand = (card*)malloc(sizeof(card));
        newCardNode(player1Hand, NULL, -2, '#', '#');
newCardNode(player2Hand, NULL, -3, '#', '#');
newCardNode(player3Hand, NULL, -4, '#', '#');
newCardNode(player4Hand, NULL, -5, '#', '#');
        break;
        case 5:
        card *player2Hand, *player2Hand, *player3Hand, *player4Hand, *player5Hand;
        player1Hand = (card*)malloc(sizeof(card));
        player2Hand = (card*)malloc(sizeof(card));
        player3Hand = (card*)malloc(sizeof(card));
        player4Hand = (card*)malloc(sizeof(card));
        player5Hand = (card*)malloc(sizeof(card));
        newCardNode(player1Hand, NULL, -2, '#', '#');
newCardNode(player2Hand, NULL, -3, '#', '#');
newCardNode(player3Hand, NULL, -4, '#', '#');
newCardNode(player4Hand, NULL, -5, '#', '#');
newCardNode(player5Hand, NULL, -6, '#', '#');
        break;
        case 6:
        card *player1Hand, *player2Hand, *player3Hand, *player4Hand, *player5Hand, *player6Hand;
        player1Hand = (card*)malloc(sizeof(card));
        player2Hand = (card*)malloc(sizeof(card));
        player3Hand = (card*)malloc(sizeof(card));
        player4Hand = (card*)malloc(sizeof(card));
        player5Hand = (card*)malloc(sizeof(card));
        player6Hand = (card*)malloc(sizeof(card));
        newCardNode(player1Hand, NULL, -2, '#', '#');
newCardNode(player2Hand, NULL, -3, '#', '#');
newCardNode(player3Hand, NULL, -4, '#', '#');
newCardNode(player4Hand, NULL, -5, '#', '#');
newCardNode(player5Hand, NULL, -6, '#', '#');
newCardNode(player6Hand, NULL, -7, '#', '#');
        break;
        case 7:
        card *player1Hand, *player2Hand, *player3Hand, *player4Hand, *player5Hand, *player6Hand, *player7Hand;
        player1Hand = (card*)malloc(sizeof(card));
        player2Hand = (card*)malloc(sizeof(card));
        player3Hand = (card*)malloc(sizeof(card));
        player4Hand = (card*)malloc(sizeof(card));
        player5Hand = (card*)malloc(sizeof(card));
        player6Hand = (card*)malloc(sizeof(card));
        player7Hand = (card*)malloc(sizeof(card));
        newCardNode(player1Hand, NULL, -2, '#', '#');
newCardNode(player2Hand, NULL, -3, '#', '#');
newCardNode(player3Hand, NULL, -4, '#', '#');
newCardNode(player4Hand, NULL, -5, '#', '#');
newCardNode(player5Hand, NULL, -6, '#', '#');
newCardNode(player6Hand, NULL, -7, '#', '#');
newCardNode(player7Hand, NULL, -8, '#', '#');
        break;
        case 8:
        card *player1Hand, *player2Hand, *player3Hand, *player4Hand, *player5Hand, *player6Hand, *player7Hand, *player8Hand;
        player1Hand = (card*)malloc(sizeof(card));
        player2Hand = (card*)malloc(sizeof(card));
        player3Hand = (card*)malloc(sizeof(card));
        player4Hand = (card*)malloc(sizeof(card));
        player5Hand = (card*)malloc(sizeof(card));
        player6Hand = (card*)malloc(sizeof(card));
        player7Hand = (card*)malloc(sizeof(card));
        player8Hand = (card*)malloc(sizeof(card));
        newCardNode(player1Hand, NULL, -2, '#', '#');
newCardNode(player2Hand, NULL, -3, '#', '#');
newCardNode(player3Hand, NULL, -4, '#', '#');
newCardNode(player4Hand, NULL, -5, '#', '#');
newCardNode(player5Hand, NULL, -6, '#', '#');
newCardNode(player6Hand, NULL, -7, '#', '#');
newCardNode(player7Hand, NULL, -8, '#', '#');
newCardNode(player8Hand, NULL, -9, '#', '#');
        break;
        case 9:
        card *player1Hand, *player2Hand, *player3Hand, *player4Hand, *player5Hand, *player6Hand, *player7Hand, *player8Hand, *player9Hand;
        player1Hand = (card*)malloc(sizeof(card));
        player2Hand = (card*)malloc(sizeof(card));
        player3Hand = (card*)malloc(sizeof(card));
        player4Hand = (card*)malloc(sizeof(card));
        player5Hand = (card*)malloc(sizeof(card));
        player6Hand = (card*)malloc(sizeof(card));
        player7Hand = (card*)malloc(sizeof(card));
        player8Hand = (card*)malloc(sizeof(card));
        player9Hand = (card*)malloc(sizeof(card));
        newCardNode(player1Hand, NULL, -2, '#', '#');
newCardNode(player2Hand, NULL, -3, '#', '#');
newCardNode(player3Hand, NULL, -4, '#', '#');
newCardNode(player4Hand, NULL, -5, '#', '#');
newCardNode(player5Hand, NULL, -6, '#', '#');
newCardNode(player6Hand, NULL, -7, '#', '#');
newCardNode(player7Hand, NULL, -8, '#', '#');
newCardNode(player8Hand, NULL, -9, '#', '#');
newCardNode(player9Hand, NULL, -10, '#', '#');
        break;
        case 10:
        card *player1Hand, *player2Hand, *player3Hand, *player4Hand, *player5Hand, *player6Hand, *player7Hand, *player8Hand, *player9Hand, *player10Hand;
        player1Hand = (card*)malloc(sizeof(card));
        player2Hand = (card*)malloc(sizeof(card));
        player3Hand = (card*)malloc(sizeof(card));
        player4Hand = (card*)malloc(sizeof(card));
        player5Hand = (card*)malloc(sizeof(card));
        player6Hand = (card*)malloc(sizeof(card));
        player7Hand = (card*)malloc(sizeof(card));
        player8Hand = (card*)malloc(sizeof(card));
        player9Hand = (card*)malloc(sizeof(card));
        player10Hand = (card*)malloc(sizeof(card));
newCardNode(player1Hand, NULL, -2, '#', '#');
newCardNode(player2Hand, NULL, -3, '#', '#');
newCardNode(player3Hand, NULL, -4, '#', '#');
newCardNode(player4Hand, NULL, -5, '#', '#');
newCardNode(player5Hand, NULL, -6, '#', '#');
newCardNode(player6Hand, NULL, -7, '#', '#');
newCardNode(player7Hand, NULL, -8, '#', '#');
newCardNode(player8Hand, NULL, -9, '#', '#');
newCardNode(player9Hand, NULL, -10, '#', '#');
newCardNode(player10Hand, NULL, -11, '#', '#');
        break;




    }

    for(int i = 0; i < 50; i++){
        shuffleHand(deckHead, shuffleHead);
        shuffleHand(shuffleHead, deckHead);

    }

return 0;
}