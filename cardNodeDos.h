#ifndef _CardNode
#define _CardNode
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
    All (or most) of the functions dealing mainly with linked lists
    and the card structs
*/

typedef struct _cardNode {
    // Data
    int value;
    int stacked;
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
void moveIndTo(card*, card*, int, int);





void newCardNode(card *thisobj, card *next, int value, char action, char color){
    /*
    Initializes empty card node with given data.
    */
    thisobj->value = value;
    thisobj->action = action;
    thisobj->color = color;
    thisobj->nextCard = next;
    thisobj->stacked = 0;
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
   int def = 0;
    if(strcmp("cardDeckDos.dat", filepath) == 0){
        def = 1;
    }
        
    FILE* inFile = NULL;
    inFile = fopen(filepath, "r");
    if(inFile == NULL){
        printf("Error reading filepath, defaulting to cardDeckDos.dat\n");
        inFile = fopen("cardDeckDos.dat", "r");
        def = 1;
    }
    if(def == 0){
        char tmpDat3[40];
        char tmpDat1[40];
        int tmpDat2;
        while(!feof(inFile)){ 
            card *tmp = (card*)malloc(sizeof(card));
            fscanf(inFile, "%s%*c", &tmpDat1);
            if(strcmp("red", tmpDat1) == 0){
                tmp->color = 'R';
            }
            else if(strcmp("blue", tmpDat1) == 0){
                tmp->color = 'B';
            }
            else if(strcmp("yellow", tmpDat1) == 0){
                tmp->color = 'Y';
            }
            else if(strcmp("green", tmpDat1) == 0){
                tmp->color = 'G';
            }
            fscanf(inFile, "%d%*c", &tmpDat2);
            tmp->value = tmpDat2;
            fscanf(inFile, "%s%*c", &tmpDat3);
            if(strcmp("none", tmpDat3) == 0){
                tmp->action = 'X';
            }
            else if(strcmp("AnyNumber", tmpDat3) == 0){
                tmp->action = '#';
            }
            if(tmp->value == 2){
                tmp->action = '2';
            }
            insertAfter(head, tmp);
            tmp->stacked = 0;
        }

    }


    else if(def == 1){
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
            tmp->stacked = 0;
        }
    }
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
    if(headNode->nextCard != NULL){
    time_t t;
    srand((unsigned) time(&t));
    card *currentNode, *shuffleTemp, *removeCopy;
    int inHand = countHand(headNode), randSelect;

    newCardNode(shuffleHead, NULL, -69, '#', '#');
    currentNode = headNode->nextCard;
    while(inHand > 1){
        randSelect = (rand()%(inHand-1))+1; // get random index
        removeCopy = (card*)malloc(sizeof(card)); // initialize new memory for card
        shuffleTemp = (card*)(getFromIndex(headNode, randSelect)); //set shuffleTemp == to old memory
        newCardNode(removeCopy, NULL, shuffleTemp->value, shuffleTemp->action, shuffleTemp->color); //make new copy of data
        insertAfter(shuffleHead, removeCopy); // insert new data copy to other head
        removeCopy->stacked = 0;
        removeFrom(headNode, shuffleTemp); // remove old memory from original head
        free(shuffleTemp); // free old memory
        inHand = countHand(headNode); // recount deck
    }
    
    removeCopy = (card*)malloc(sizeof(card)); // initialize new memory for card
    shuffleTemp = headNode->nextCard; //set shuffleTemp == to old memory
    newCardNode(removeCopy, NULL, shuffleTemp->value, shuffleTemp->action, shuffleTemp->color); //make new copy of data
    insertAfter(shuffleHead, removeCopy); // insert new data copy to other head
    removeCopy->stacked = 0;
    removeFrom(headNode, shuffleTemp); // remove old memory from original head
    free(shuffleTemp);
    }
    
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

void moveIndTo(card* fromHead, card* toHead, int index, int stack){
    //make all references -1
    card *toPull = getFromIndex(fromHead, index), *tempCpy = NULL;
        tempCpy = (card*)malloc(sizeof(card));
        newCardNode(tempCpy, NULL, toPull->value, toPull->action, toPull->color);
        insertAfter(toHead, tempCpy);
        removeFrom(fromHead, toPull);
        tempCpy->stacked = stack;
        free(toPull);



}


#endif // _CardNode
