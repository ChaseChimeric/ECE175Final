#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cardNodeDos.h"
#include "Graphics.h"
#include "Game.h"



int main(){

    /*
    Main game loop logic is all here
    Calls other functions to execute game actions, but 
    main setup and flow is here
    */

    // Main setup for game, variable declarations, and card deck/head node setup here
    card *deckHead = NULL, *shuffleHead = NULL, *playDeck = NULL;
    card* players[6];
    int playerScore[6];
    int playerAmount = 0, targetCard, amountToPlay = -111, cardsToPlay[2];
    int cont = 0, gameloop = 1, hasPlayed = 0, currentPlayer = 0, playerWon = 0, scoreTmp;
    for(int i = 0; i < 6; i++)
        playerScore[i] = 0;
    char cardGfx[12][41], filepath[100] = "cardDeckDos.dat", tmpInput = 'r';
    loadGfx(cardGfx);
    fflush(stdout);
    deckHead = (card*)malloc(sizeof(card));
    printf("%s\n", cardGfx[1]);
        newCardNode(deckHead, NULL, -10, '!', '!'); 
    shuffleHead = (card*)malloc(sizeof(card));
        newCardNode(shuffleHead, NULL, -11, '!', '!'); 
    playDeck = (card*)malloc(sizeof(card));
        newCardNode(playDeck, NULL, -420, '!', '!');
    printf("Fullscreen is recommended\nThis game has a deck already set up, or you can load your own.\nDo you want to load a custom deck? (y/n): ");
    while(tmpInput != 'y' && tmpInput != 'Y' && tmpInput != 'n' && tmpInput != 'N'){
        scanf("%c", &tmpInput);
        if(tmpInput == 'y' || tmpInput == 'Y'){
            printf("Enter filepath: ");
            scanf("%s", filepath);
        }
        else if(tmpInput == 'n' || tmpInput == 'N'){
            strcpy(filepath, "cardDeckDos.dat");
        }
    }

    initDeck(deckHead, filepath);
    // end setup
    



    ClearScreen();
    G_intro(); // scrolling intro
    ClearScreen();


    for(int i = 0; i < 100;i++){ // shuffle deck
        shuffleHand(deckHead, shuffleHead);
        shuffleHand(shuffleHead, deckHead);
    }
    while(playerAmount < 2 || playerAmount > 6){ // this and switch below, setup player array
        printf("Welcom to DOS\nHow many players? (2-6): ");
        if(scanf("%d", &playerAmount)==0)
            scanf("%*c");
    }
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

    while(!playerWon){ // MAIN GAME LOOP   
        for(int i = 0; i < playerAmount; i++){
            pullFrom(deckHead, players[i], 7); // deal cards to players
        }
        pullFrom(deckHead, playDeck, 2); // deal to center row
        gameloop = 1;
        while(gameloop){ // ROUND LOOP

            if(currentPlayer > (playerAmount-1))
                currentPlayer = 0;
            ClearScreen();
            printf("Current Center Row\n");
            showHand(playDeck, cardGfx);
            printf("Your Hand, player %d\n", currentPlayer+1);
            showHand(players[currentPlayer], cardGfx);
            targetCard = -1;

            while((targetCard < 0 || targetCard > countHand(playDeck))){ // selecting target cneter row card
                printf("Select Center Row Card to play on (1-%d, 0 if not playing): ", countHand(playDeck));
                if(scanf("%d", &targetCard) == 0)
                    scanf("%*c");
            }
            if(targetCard == 0) // if not playing/cant play
                amountToPlay = 0;

            while((amountToPlay < 1 || amountToPlay > 2)&& amountToPlay != 0){ // selecting how many cards to play
                printf("How many cards do you want to play? (up to 2): ");
                if(scanf("%d", &amountToPlay)==0)
                    scanf("%*c");
            }
            while(!cont && (amountToPlay != 0)){ // selecting card 1
                while((cardsToPlay[0] < 1) || (cardsToPlay[0] > countHand(players[currentPlayer]))){
                    printf("Select Card 1 to play (1-%d): ", countHand(players[currentPlayer]));
                    if(scanf("%d", &cardsToPlay[0])==0)
                        scanf("%*c");
                    cont = 1;
                }

                if(amountToPlay == 2){ // selecting card 2
                    while((cardsToPlay[1] < 1) || cardsToPlay[1] > countHand(players[currentPlayer])){
                        printf("Select Card 2 to play (1-%d): ", countHand(players[currentPlayer]));
                        if(scanf("%d",&cardsToPlay[1])==0)
                            scanf("%*c");
                    }
                }
            }
            while((amountToPlay == 0) && (cardsToPlay[0] < 1 || cardsToPlay[0] > countHand(players[currentPlayer])) && (hasPlayed == 0)){
                // if not playing and has not already played a card
                printf("Your New Hand:\n");
                pullFrom(deckHead, players[currentPlayer], 1);
                showHand(players[currentPlayer], cardGfx);
                cardsToPlay[0] = -1;
                while(cardsToPlay[0] < 1 || cardsToPlay[0] > countHand(players[currentPlayer])){
                    printf("Select card to discard to center row (1-%d): ", countHand(players[currentPlayer]));
                    if(scanf("%d", &cardsToPlay[0])==0)
                        scanf("%*c");

                }
            }
            if((amountToPlay == 0)&&(hasPlayed==1)){ // if not playing and has already played
                amountToPlay = -9;
                cardsToPlay[0] = -1;
                cardsToPlay[1] = -1;
            }
            // executing play aciton
            int actionState = ExecuteAction(players[currentPlayer],playDeck, shuffleHead, targetCard, amountToPlay, cardsToPlay, cardGfx);
            if(actionState != 0)
                hasPlayed = 1;


            if(players[currentPlayer]->nextCard == NULL){ // when player has won round
                scoreTmp = calcPoints(players[currentPlayer], players, playerAmount);
                playerScore[currentPlayer] += scoreTmp;
                gameloop = 0;
            }
            switch(actionState){ // swwitch for turn state
                case 1:
                    printf("single match\n");
                    break;
                case 2:
                    printf("single color match\n");
                    showHand(players[currentPlayer], cardGfx);
                    if(countHand(players[currentPlayer]) != 0) {
                        cardsToPlay[0] = -1;
                        while(cardsToPlay[0] < 1 || cardsToPlay[0] > countHand(players[currentPlayer])){
                            printf("Select card to discard to center row (1-%d): ", countHand(players[currentPlayer]));
                            if(scanf("%d", &cardsToPlay[0])==0)
                                scanf("%*c");
                        }
                        amountToPlay = 0;
                        ExecuteAction(players[currentPlayer],playDeck, shuffleHead, targetCard, amountToPlay, cardsToPlay, cardGfx);
                    }
                    break;
                case 3:
                    printf("double match\n");
                    break;
                case 4:
                    printf("double color match\n");
                    showHand(players[currentPlayer], cardGfx);
                    if(countHand(players[currentPlayer]) != 0) {
                        cardsToPlay[0] = -1;
                        while(cardsToPlay[0] < 1 || cardsToPlay[0] > countHand(players[currentPlayer])){
                            printf("Select card to discard to center row (1-%d): ", countHand(players[currentPlayer]));
                            if(scanf("%d", &cardsToPlay[0])==0)
                                scanf("%*c");
                        }
                        amountToPlay = 0;
                        
                        ExecuteAction(players[currentPlayer],playDeck, shuffleHead, targetCard, amountToPlay, cardsToPlay, cardGfx);
                        othersDraw(players[currentPlayer], players, playerAmount, deckHead);
                    }
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
                    break;
                case -3:
                    printf("Cannot play on an already stacked card.\n");
                    break;
                case -4:
                    printf("Ending turn.\n");
                    hasPlayed = 0;
                    resetPlayDeck(playDeck, deckHead);
                    currentPlayer++;
                    break;
                default:
                    break;
            }
            // printing round win
            if(gameloop == 0){
                printf("Player %d has won this round and scored %d points\nStarting new round\n", currentPlayer+1, scoreTmp);
            }
            amountToPlay = -111;
            cont = 0;
            cardsToPlay[0] = -1;
            cardsToPlay[1] = -1;

                for(int i = 0; i < 1; i++)
                delay(2,0);
                shuffleHand(deckHead, shuffleHead);
                shuffleHand(shuffleHead, deckHead);

        }
        playerWon = checkWin(playerScore, playerAmount);
    for(int i = 0; i < playerAmount; i++)
        shuffleHand(players[i], shuffleHead);
    shuffleHand(playDeck, shuffleHead);
    shuffleHand(deckHead, shuffleHead);
    shuffleHand(shuffleHead, deckHead);

}
printf("Player %d has won\nThanks for playing.\n", playerWon+1);
    fflush(stdout);
    return 0;
}



