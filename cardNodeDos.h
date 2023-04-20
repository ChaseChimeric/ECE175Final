#ifndef _CardNode
#define _CardNode
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>

typedef struct _cardNode {
    // Data
    int value;
    char action;
    char color;


    // ptr to next
    struct _cardNode *nextCard;
} card;

void newCardNode(card *thisobj, card *next, int value, char action, char color);
void insertAfter(card* first, card* second);
int countHand(card* headNode);
card * getFromIndex(card* headNode, int toFind);
void initDeckUno(card *head, char filepath[]);
void listHandText(card* headNode);
void removeFrom(card *headNode, card *toRemove);
void shuffleHand(card* headNode, card*shuffleHead);
void pullFrom(card *from, card *destination, int amount);



void newCardNode(card *thisobj, card *next, int value, char action, char color){
    /*
    Initializes empty card node with given data.
    */
    thisobj->value = value;
    thisobj->action = action;
    thisobj->color = color;
    thisobj->nextCard = next;
}

void insertAfter(card* first, card* second){
    /*
    Inserts card directly after the given head node.
    */
    second->nextCard = first->nextCard;
    first->nextCard = second;
}

int countHand(card* headNode){
    /*
    Counts all cards in given hand.
    returns the number of cards.
    */
    card *currentNode = headNode->nextCard;
    int inHand = 0;

    while(currentNode != NULL){
        inHand+=1;
        currentNode = currentNode->nextCard;
    }
    return inHand;
}

card * getFromIndex(card* headNode, int toFind){
    /*
    returns a pointer to the card at the given index.
    no bounds checking.
    */
    card* currentNode = headNode->nextCard;

    for(int i = 0; i < toFind; i++){
        currentNode = currentNode->nextCard;
    }
    return currentNode;
}

void initDeck(card *head, char filepath[]){
    /*
    opens file at filepath, reads cards in dynamically
    */
    FILE* inFile = NULL;
    inFile = fopen(filepath, "r");
    char line[25], tmpDat3;
    char tmpDat1;
    int tmpDat2;

    fgets(line, 25, inFile);
    // Reading each card in
    while(!feof(inFile)){ 
        card *tmp = (card*)malloc(sizeof(card));
        fscanf(inFile, "%c%*c", &tmpDat1);
        tmp->action = tmpDat1;
        fscanf(inFile, "%c%*c", &tmpDat3);
        tmp->color = tmpDat3;
        fscanf(inFile, "%d%*c", &tmpDat2);
        tmp->value = tmpDat2;
        insertAfter(head, tmp);
    }
    // Extra copy of last card is added because of feof() behavior, this fixed that
    //card *tempdel = head->nextCard;
    //removeFrom(head, tempdel);
    //free(tempdel);
    //fclose(inFile);
}

void listHandText(card* headNode){
    /*
    Lists all cards in given linked list head node
    prints card values out in text, no symbols
    */

    card *currentCard = (headNode->nextCard);

    while(currentCard != NULL){
        switch (currentCard->color)
        {
        case 'R':
            printf("Red ");
            break;
        case 'G':
            printf("Green ");
            break;
        case 'B':
            printf("Blue ");
            break;
        case 'Y':
            printf("Yellow ");
            break;
        case 'W':
            printf("Wild ");
            break;
        default:
            printf("ColorError");
            break;
        }
        switch (currentCard->value)
        {
        case 0:
            printf("#");
            break;
        case 1:
            printf("1");
            break;
        case 2:
            printf("2");
            break;
        case 3:
            printf("3");
            break;
        case 4:
            printf("4");
            break;
        case 5:
            printf("5");
            break;
        case 6:
            printf("6");
            break;
        case 7:
            printf("7");
            break;
        case 8:
            printf("8");
            break;
        case 9:
            printf("9");
            break;
        case 10:
            printf("10");
            break;
        default:
            printf("ValueError");
            break;
        }
        printf("\n");
        currentCard = currentCard->nextCard;
    }
}

void removeFrom(card *headNode, card *toRemove){
    /*
    Removes specific item in linked list
    Does not free memory, only removes pointer references
    */

    card *oneBefore = headNode, *currentNode;

    currentNode = headNode->nextCard;
    while(currentNode != toRemove){
        oneBefore = currentNode;
        currentNode = currentNode->nextCard;
    }
    oneBefore->nextCard = toRemove->nextCard;
}

void shuffleHand(card* headNode, card*shuffleHead){
    /*
    Pulls all cards in random order from initial head
    node to the second 'shuffle' head node.
    should be used an even number of times to properly shuffle original list
    */

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
        newCardNode(removeCopy, NULL, shuffleTemp->value, shuffleTemp->action, shuffleTemp->color); //make new copy of data
        insertAfter(shuffleHead, removeCopy); // insert new data copy to other head
        removeFrom(headNode, shuffleTemp); // remove old memory from original head
        free(shuffleTemp); // free old memory
        inHand = countHand(headNode); // recount deck
    }
    removeCopy = (card*)malloc(sizeof(card)); // initialize new memory for card
    shuffleTemp = headNode->nextCard; //set shuffleTemp == to old memory
    newCardNode(removeCopy, NULL, shuffleTemp->value, shuffleTemp->action, shuffleTemp->color); //make new copy of data
    insertAfter(shuffleHead, removeCopy); // insert new data copy to other head
    removeFrom(headNode, shuffleTemp); // remove old memory from original head
    free(shuffleTemp);
}

void pullFrom(card *from, card *destination, int amount){
    /*
    Pulls specific amount of cards from first linked list and puts them 
    into the second one
    */

    for(int i = 0; i < amount; i++){
        card *toPull = from->nextCard, *tempCpy = NULL;
        tempCpy = (card*)malloc(sizeof(card));
        newCardNode(tempCpy, NULL, toPull->value, toPull->action, toPull->color);
        insertAfter(destination, tempCpy);
        removeFrom(from, toPull);
        free(toPull);
    }
}

#endif // _CardNode
