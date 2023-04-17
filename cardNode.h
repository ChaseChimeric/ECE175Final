#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef struct _cardNode {
    // Data
    int marker;
    char suit;
    char color;

    // ptr to next
    struct _cardNode *nextCard;
} card;

void newCardNode(card *thisobj, card *next, int marker, char suit, char color){
    thisobj->marker = marker;
    thisobj->suit = suit;
    thisobj->color = color;
}

void insertAfter(card* first, card* second){
    second->nextCard = first->nextCard;
    first->nextCard = second;
}

int countHand(card* headNode){
    card *currentNode = headNode->nextCard;
    int inHand = 0;
    while(currentNode != NULL){
        inHand+=1;
        currentNode = currentNode->nextCard;
    }
    return inHand;
}

card * getFromIndex(card* headNode, int toFind){
    card* currentNode = headNode->nextCard;
    for(int i = 0; i < toFind; i++){
        currentNode = currentNode->nextCard;
    }
    return currentNode;
}

void initDeck(card *head, char filepath[]){
    FILE* inFile = NULL;
    inFile = fopen(filepath, "r");
    char line[25];
    char tmpDat1;
    int tmpDat2;
    fgets(line, 25, inFile);
    while(!feof(inFile)){ 
        card *tmp = (card*)malloc(sizeof(card));
        fscanf(inFile, "%c%*c", &tmpDat1);
        tmp->suit = tmpDat1;
        fscanf(inFile, "%c%*c", &tmpDat1);
        tmp->color = tmpDat1;
        fscanf(inFile, "%d%*c", &tmpDat2);
        tmp->marker = tmpDat2;
        insertAfter(head, tmp);
    }
    //fclose(inFile);
}

void listHand(card* headNode){
    card *currentCard = (headNode->nextCard);

    while(currentCard != NULL){
        if(currentCard->marker <= 10 && currentCard->marker > 1){
            printf("%d of ", currentCard->marker);
        }
        else if((currentCard->marker) == 1){
            printf("Ace of ");
        }   
        else{
            switch (currentCard->marker)
            {
            case 11:
                printf("Jack of ");
                break;
            case 12:
                printf("Queen of ");
                break;
            case 13:
                printf("King of ");
                break;
            default:
                break;
            }
        }
        switch( currentCard->suit ){
            case 'C':
                printf("Clubs\n");
                break;
            case 'H':
                printf("Hearts\n");
                break;
            case 'D':
                printf("Diamonds\n");
                break;
            case 'S':
                printf("Spades\n");
                break;
            default:
                break;
        }
        currentCard = currentCard->nextCard;
    }
}
void removeFrom(card *headNode, card *toRemove){
    card *oneBefore = headNode, *currentNode;

    currentNode = headNode->nextCard;
    while(currentNode != toRemove){
        oneBefore = currentNode;
        currentNode = currentNode->nextCard;
    }
    oneBefore->nextCard = toRemove->nextCard;
}
void shuffleHand(card* headNode, card*shuffleHead){
    time_t t;
    srand((unsigned) time(&t));
    card *currentNode, *shuffleTemp, *removeCopy;
    int inHand = countHand(headNode), randSelect;

    newCardNode(shuffleHead, NULL, -69, '#', '#');
    currentNode = headNode->nextCard;
    while(inHand != 1){
        randSelect = (rand()%(inHand-1))+1; // get random index
        removeCopy = (card*)malloc(sizeof(card)); // initialize new memory for card
        shuffleTemp = (card*)(getFromIndex(headNode, randSelect)); //set shuffleTemp == to old memory
        newCardNode(removeCopy, NULL, shuffleTemp->marker, shuffleTemp->suit, shuffleTemp->color); //make new copy of data
        insertAfter(shuffleHead, removeCopy); // insert new data copy to other head
        removeFrom(headNode, shuffleTemp); // remove old memory from original head
        free(shuffleTemp); // free old memory
        inHand = countHand(headNode); // recount deck
        //printf("still shuffling\n"); for debug ****
    }
        removeCopy = (card*)malloc(sizeof(card)); // initialize new memory for card
        shuffleTemp = headNode->nextCard; //set shuffleTemp == to old memory
        newCardNode(removeCopy, NULL, shuffleTemp->marker, shuffleTemp->suit, shuffleTemp->color); //make new copy of data
        insertAfter(shuffleHead, removeCopy); // insert new data copy to other head
        removeFrom(headNode, shuffleTemp); // remove old memory from original head
        free(shuffleTemp);
}

