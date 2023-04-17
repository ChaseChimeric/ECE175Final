#ifndef _CardNode
#define _CardNode
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>

typedef struct _cardNode {
    // Data
    int marker;
    wchar_t suit;
    char color;

    // ptr to next
    struct _cardNode *nextCard;
} card;

void newCardNode(card *thisobj, card *next, int marker, wchar_t suit, char color){
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
    wchar_t tmpDat1;
    int tmpDat2;
    char tmpDat3;
    fgets(line, 25, inFile);
    while(!feof(inFile)){ 
        card *tmp = (card*)malloc(sizeof(card));
        fscanf(inFile, "%lc%*c", &tmpDat1);
        tmp->suit = tmpDat1;
        fscanf(inFile, "%c%*c", &tmpDat3);
        tmp->color = tmpDat3;
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
        int tempchar = (int)currentCard->suit;
            if(currentCard->suit >= 0x1F0D1 && currentCard->suit <= 0x1F0DE)
                printf("Clubs\n");
            if(currentCard->suit >= 0x1F0B1 && currentCard->suit <= 0x1F0BE)
                printf("Hearts\n");
            if(currentCard->suit >= 0x1F0C1 && currentCard->suit <= 0x1F0CE)
                printf("Diamonds\n");
            if(currentCard->suit >= 0x1F0A1 && currentCard->suit <= 0x1F0AE)
                printf("Spades\n");
        
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

void pullFrom(card *from, card *destination){
    card *toPull = from->nextCard, *tempCpy = NULL;
    tempCpy = (card*)malloc(sizeof(card));
    newCardNode(tempCpy, NULL, toPull->marker, toPull->suit, toPull->color);
    insertAfter(destination, tempCpy);
    removeFrom(from, toPull);
    free(toPull);


}

#endif // _CardNode