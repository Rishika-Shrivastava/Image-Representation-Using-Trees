#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXCHAR 1000
#define MAXNODE 4
#define INITSIZE 4
#define LEVELS 3

int row = 1, i=0, j=0;

typedef enum {FALSE, TRUE} Bool;          // to check whether the node is a leaf node or not

typedef struct bTreeNode {

    Bool isLeaf;
    int level;
    int size;                         // total 2m+1 levels
    int isOne;
    int startX;
    int startY;
    struct bTreeNode *childNode[MAXNODE];
    int pixelVal;

}bTree;


bTree *bTreeRoot;                                  //ROOT NODE

void initRootNode() {

    bTreeRoot = (bTree *)malloc(sizeof(bTree));
    bTreeRoot ->level =1;
    bTreeRoot ->isLeaf = FALSE;
    bTreeRoot ->startX = 0;
    bTreeRoot ->startY =0;
    bTreeRoot ->size = INITSIZE;

}

int imageMatrix[INITSIZE][INITSIZE];                             //16*16 ARRAY


void insertIntoMatrix(char filename[]){            //file reading

    FILE *fp;
    char lineStr[MAXCHAR];
    char *charPtr;

    fp = fopen(filename, "r");

    int i=0, j=0;

    if(fp == NULL) {
        printf("Error opening file\n");
    }
    else {

            for(i = 0; i< INITSIZE ; i++){

                    //printf("row %d -   ", i);

                    for(j= 0 ; j < INITSIZE && (fgets(lineStr, MAXCHAR, fp) != NULL); j++){
                        charPtr = strtok(lineStr, " ");
                        if ( charPtr != NULL){

                            //printf("%d ", atoi(charPtr));
                            imageMatrix[i][j] = (atoi(charPtr));
                            //printf("%d    ", imageMatrix[i][j]);

                        }
                    }

                 //   printf("\n");
            }
    }

    fclose(fp);
}

int createTree(int x, int y, int size, bTree *parentNode){
    //printf("row is %d \n", row);
    //row ++;

    int onePresent = 0;

    parentNode ->childNode[0] = (bTree *)malloc(sizeof(bTree));
    parentNode ->childNode[1] = (bTree *)malloc(sizeof(bTree));
    parentNode ->childNode[2] = (bTree *)malloc(sizeof(bTree));
    parentNode ->childNode[3] = (bTree *)malloc(sizeof(bTree));

    if(size > 2){
        parentNode ->childNode[0] ->isLeaf = FALSE;
        parentNode ->childNode[0] ->level = parentNode ->level + 1;
        parentNode ->childNode[0] ->size = size/2;
        parentNode ->childNode[0] ->startX = x ;
        parentNode ->childNode[0] ->startY = y ;
        parentNode ->childNode[0] ->pixelVal = -1;

        parentNode ->childNode[1] ->isLeaf = FALSE;
        parentNode ->childNode[1] ->level = parentNode ->level + 1;
        parentNode ->childNode[1] ->size = size/2;
        parentNode ->childNode[1] ->startX = x + (size)/2;
        parentNode ->childNode[1] ->startY = y ;
        parentNode ->childNode[1] ->pixelVal = -1;

        parentNode ->childNode[2] ->isLeaf = FALSE;
        parentNode ->childNode[2] ->level = parentNode ->level + 1;
        parentNode ->childNode[2] ->size = size/2;
        parentNode ->childNode[2] ->startX = x + (size)/2;
        parentNode ->childNode[2] ->startY = y + (size)/2;
        parentNode ->childNode[2] ->pixelVal = -1;

        parentNode ->childNode[3] ->isLeaf = FALSE;
        parentNode ->childNode[3] ->level = parentNode ->level + 1;
        parentNode ->childNode[3] ->size = size/2;
        parentNode ->childNode[3] ->startX = x ;
        parentNode ->childNode[3] ->startY = y + (size)/2;
        parentNode ->childNode[3] ->pixelVal = -1;


        parentNode ->childNode[0] ->isOne = createTree(x, y, size/2, parentNode ->childNode[0]);
        parentNode ->childNode[3] ->isOne = createTree(x+ size/2, y, size/2, parentNode ->childNode[3]);
        parentNode ->childNode[2] ->isOne = createTree(x+ size/2, y + size/2, size/2, parentNode ->childNode[2]);
        parentNode ->childNode[1] ->isOne = createTree(x , y + size/2, size/2, parentNode ->childNode[1]);

         if ( parentNode ->childNode[0] ->isOne ==1
              || parentNode ->childNode[1] ->isOne == 1
              || parentNode ->childNode[2] ->isOne == 1
              || parentNode ->childNode[3] ->isOne == 1){
            onePresent = 1;
        }


        //onePresent = createTree(x, y, size/2, parentNode ->childNode[0]);                        //recursive calls for every node
        //onePresent = createTree(x+ size/2, y, size/2, parentNode ->childNode[3]);
        //onePresent = createTree(x+ size/2, y + size/2, size/2, parentNode ->childNode[2]);
        //onePresent = createTree(x , y + size/2, size/2, parentNode ->childNode[1]);

    }
    else {
        //printf("entered child ");

        parentNode ->childNode[0] ->isLeaf = TRUE;
        parentNode ->childNode[0] ->level = parentNode ->level + 1;
        parentNode ->childNode[0] ->size = size/2;
        parentNode ->childNode[0] ->startX = x ;
        parentNode ->childNode[0] ->startY = y ;
        parentNode ->childNode[0] ->pixelVal = imageMatrix[x][y];
        //printf("\tvalue - %d ", parentNode ->childNode[0] ->pixelVal);
        if( parentNode ->childNode[0] ->pixelVal == 1) {

            onePresent = 1;
            parentNode ->childNode[0] ->isOne = 1;

        }
        else {

            parentNode ->childNode[0] ->isOne = 0;

        }


        parentNode ->childNode[1] ->isLeaf = TRUE;
        parentNode ->childNode[1] ->level = parentNode ->level + 1;
        parentNode ->childNode[1] ->size = size/2;
        parentNode ->childNode[1] ->startX = x + (size)/2;
        parentNode ->childNode[1] ->startY = y ;
        parentNode ->childNode[1] ->pixelVal = imageMatrix[x][y+1];
        //printf("\tvalue - %d ", parentNode ->childNode[1] ->pixelVal);
        if( parentNode ->childNode[1] ->pixelVal == 1) {

            onePresent = 1;
            parentNode ->childNode[1] ->isOne = 1;

        }
        else {

            parentNode ->childNode[1] ->isOne = 0;

        }


        parentNode ->childNode[2] ->isLeaf = TRUE;
        parentNode ->childNode[2] ->level = parentNode ->level + 1;
        parentNode ->childNode[2] ->size = size/2;
        parentNode ->childNode[2] ->startX = x + (size)/2;
        parentNode ->childNode[2] ->startY = y + (size)/2;
        parentNode ->childNode[2] ->pixelVal = imageMatrix[x+1][y+1];
        //printf("\tvalue - %d ", parentNode ->childNode[2] ->pixelVal);
        if( parentNode ->childNode[2] ->pixelVal == 1) {

            onePresent = 1;
            parentNode ->childNode[2] ->isOne = 1;

        }
        else {

            parentNode ->childNode[2] ->isOne = 0;

        }


        parentNode ->childNode[3] ->isLeaf = TRUE;
        parentNode ->childNode[3] ->level = parentNode ->level + 1;
        parentNode ->childNode[3] ->size = size/2;
        parentNode ->childNode[3] ->startX = x;
        parentNode ->childNode[3] ->startY = y + (size)/2;
        parentNode ->childNode[3] ->pixelVal = imageMatrix[x+1][y];
        //printf("\tvalue - %d ", parentNode ->childNode[3] ->pixelVal);
        if( parentNode ->childNode[3] ->pixelVal == 1) {

            onePresent = 1;
            parentNode ->childNode[3] ->isOne = 1;

        }
        else {

            parentNode ->childNode[3] ->isOne = 0;

        }

        if(onePresent == 1){
            parentNode ->isOne = 1;
        }

    }


    return onePresent;
   // printf("\n");

}


void printTree(bTree *parentNode){
    char seg = NULL;

    int i,j;

    for (i=0; i < 4; i++){

        if ( i==0){

            seg = 'A';

        }
        else if ( i ==1 ){

            seg = 'B';

        }
        else if ( i== 2){

            seg ='C';

        }
        else{

            seg = 'D';

        }

        for ( j=0; j < parentNode->childNode[i]->level; j++){

            printf("   ");

        }

        if ( parentNode->childNode[i]->isLeaf ==  FALSE){

            printf("%c(%d) - size %d , X=%d   Y=%d   " , seg, parentNode->childNode[i]->level, parentNode ->childNode[i] ->size, parentNode ->childNode[i]->startX, parentNode ->childNode[i]->startY);
            printf("isOne - %d\n", parentNode ->childNode[i] ->isOne);
            printTree(parentNode->childNode[i]);

        }
        else{

            printf("%c(%d) - size %d  , X=%d   Y=%d   " , seg , parentNode->childNode[i]->level, parentNode ->childNode[i] ->size, parentNode ->childNode[i]->startX, parentNode ->childNode[i]->startY);
            printf("isOne - %d\n", parentNode ->childNode[i] ->isOne);


        }

    }

}

//----------------------------------------------------- QUESTION 2 ------------------------------------------------

int forePixels ;

int countForeground(bTree *parentNode) {                               //count total number of 1 in all nodes

    int i;


    for(i= 0; i < 4 ; i++) {

        if(parentNode ->childNode[i] ->isLeaf == FALSE ) {

            forePixels = countForeground(parentNode->childNode[i]);

        }
        else {

            if(parentNode ->childNode[i] ->pixelVal == 1 ) {

                //printf("%d ", parentNode ->childNode[i] ->pixelVal );

                forePixels ++;

            }
           /* else {
               printf("%d ", parentNode ->childNode[i] ->pixelVal );
            } */

        }

    }

    return forePixels;

}


//------------------------------------------------- GENERIC SEARCH FUNCTION ------------------------------------------------


int searchTreeMod (bTree *parentNode, int x, int y) {                         //search tree function based upon coordinates

   // printf("Entered function\n");

    int currSize = (parentNode->size) / 2, retValue;

    if(parentNode ->isLeaf == FALSE) {

        //printf("NOT LEAF\n");

        if(x >= currSize ) {

            if(y < currSize ) {

                //printf("D ");

                retValue = searchTreeMod(parentNode ->childNode[3], x - currSize , y);

            }
            else {

                //printf("C ");

                retValue = searchTreeMod(parentNode ->childNode[2], x - currSize, y - currSize);

            }

        }
        else {

            if(y < currSize ) {

                //printf("A ");

                retValue = searchTreeMod(parentNode ->childNode[0], x, y );

            }
            else {

                //printf("B ");

                retValue = searchTreeMod(parentNode ->childNode[1], x , y - currSize);

            }
        }

    }
    else {
        //printf("Entering LEAF\n");

       // printf("%d ", parentNode->pixelVal);
        retValue = parentNode->isOne;

       // printf("\n");

    }

    return retValue;

}

int searchLevel(bTree *parentNode, int inputLevel) {

    int tX =-1, tY =-1;
    int i, totalDisjoint = 0, disjointNumber = 0;

    for(i = 0; i < 4 ; i++) {

        if ( parentNode->childNode[i] ->level < inputLevel){

            disjointNumber = searchLevel(parentNode->childNode[i], inputLevel);
            totalDisjoint = totalDisjoint + disjointNumber;
        }
        else{
            if(parentNode ->childNode[i] ->isOne == 1) {

                tX = ((parentNode->childNode[i]->startX)/(parentNode->childNode[i]->size));
                tY = ((parentNode->childNode[i]->startY)/(parentNode->childNode[i]->size));
                printf("Level, size and value is %d %d %d  ", parentNode ->childNode[i] ->level, parentNode ->childNode[i] ->size, parentNode ->childNode[i] ->isOne);
                printf("Starting Coordinates : startX=%d startY=%d\n", (parentNode->childNode[i]->startX), (parentNode->childNode[i]->startY));
                printf("Starting Coordinates : tX=%d tY=%d\n", tX, tY);


                for( int p = tX -1; p <= tX +1; p++){
                    for( int q =  tY-1; q <= tY +1; q++){
                        if ( !( p == tX && q == tY && p>=0 && q>=0 && p < INITSIZE && q < INITSIZE)){
                            printf("\n");
                            printf("searchLevel : checking node tX=%d  tY=%d \n", p, q);
                            disjointNumber = getDisJointLevels(bTreeRoot, p, q,
                                        inputLevel, parentNode->childNode[i]->size
                                        );
                            totalDisjoint = totalDisjoint + disjointNumber;
                        }
                    }
                }
             }
        }
    }
    return totalDisjoint;
}


int getDisJointLevels(bTree *parentNode, int tX, int tY, int inputLevel, int transformFactor) {

    int totalDisjoint = 0;
    int disjointNum = 0;
    int tX1 = -1, tX2 = -1, tY1 = -1, tY2 = -1;


    if ( parentNode->level < inputLevel-1){
        printf("getDisJointLevels : level = %d \n", parentNode->level);
        for(int i=0; i < 4; i++){

            tX1 = (parentNode->childNode[i]->startX)/transformFactor;
            tY1 = (parentNode->childNode[i]->startY)/transformFactor;
            tX2 = ((parentNode->childNode[i]->startX)+(parentNode->childNode[i]->size))/transformFactor;
            tY2 = ((parentNode->childNode[i]->startY)+(parentNode->childNode[i]->size))/transformFactor;

            printf( "getDisJointLevels tX=%d tY=%d tX1=%d tY1=%d tX2=%d tY2=%d \n",tX, tY, tX1, tY1, tX2, tY2);

            if ( tX >= tX1 && tY >= tY1 && tX < tX2 &&  tY < tY2 ){
                printf("getDisJointLevels : Recurse node %d  %d  %d \n", (parentNode->childNode[i]->level), parentNode->childNode[i]->startX, parentNode->childNode[i]->startY );
                disjointNum = getDisJointLevels(parentNode->childNode[i], tX, tY, inputLevel, transformFactor);
                totalDisjoint = totalDisjoint + disjointNum;
                printf( "getDisJointLevels : totalDisjoint=%d disjointNum=%d \n",totalDisjoint, disjointNum);
            }
        }
    }
    else{
        printf("getDisJointLevels : in leaf node \n");
        for(int j=0; j < 4; j++){

            tX1 = (parentNode->childNode[j]->startX)/transformFactor;
            tY1 = (parentNode->childNode[j]->startY)/transformFactor;

            printf("getDisJointLevels : tX1=%d  tY1=%d isOne=%d\n", tX1, tY1, parentNode->childNode[j]->isOne);

            if ( tX == tX1 && tY== tY1 && parentNode->childNode[j]->isOne == 0 ){
                printf("getDisJointLevels : Zero Match found \n");
                totalDisjoint = 1;
            }
        }
    }
    return totalDisjoint;
}




//  -----------------------------------------  QUESTION 3 ---------------------------------------------------

int calculateDisjoint(int x, int y, bTree *parentNode, int level) {

    //printf("Entering calculate disjoint \n");

    int i, j, disjointPairs = 0, currentValue = 0;

    if(level > LEVELS) {

        printf("Enter correct level\n");

    }
    else {

        for(i= x-1 ; i< x+2; i++) {

            for(j = y-1; j < y+2; j++) {

                if(i >= 0 && j >= 0 && i < INITSIZE && j < INITSIZE ) {

                    //printf("Coordinates are (%d, %d)  ", i,j );

                    currentValue = searchTreeMod(parentNode, i, j);
                    //printf("Value retrieved is %d\n", currentValue);

                    if(currentValue == 0) {

                        disjointPairs ++;

                       // printf("calculate disjoint pair sum %d \n", disjointPairs);

                    }

                }

            }

        }

    }

    printf("Returning value %d\n", disjointPairs);

    return disjointPairs;

}



void totalDisjointPairs(bTree *parentNode) {

    int i, j, totalDisjointVal= 0, currentVal = 0, disjointVal= 0;

    for(i = 0; i < INITSIZE ; i++) {

        for (j = 0; j < INITSIZE ; j++) {

            currentVal = searchTreeMod(parentNode, i, j);

            if(currentVal == 1) {

                disjointVal = calculateDisjoint(i, j, parentNode, 3);
                totalDisjointVal = totalDisjointVal + disjointVal;
                printf("\n");

                printf("current total disjoint values %d\n", totalDisjointVal);

            }


        }


    }

    printf("Total disjoint pairs are : % d\n", totalDisjointVal);

}




//--------------------------------------------  QUESTION 4 --------------------------------------------------


void rowTraversal(bTree *parentNode) {                  // a) Row Traversal
    int i=0, j=0, pixVal;

    for(i = 0 ; i < INITSIZE; i++){

        for (j = 0; j <INITSIZE ; j++){

            pixVal = searchTreeMod(parentNode, i, j);
            printf("%d  ", pixVal);

        }

        printf("\n");
    }

}


void columnTraversal(bTree *parentNode) {               // b) Column Traversal
    int i=0, j=0, pixVal;

    for(i = 0 ; i < INITSIZE; i++){

        for (j = 0; j <INITSIZE ; j++){

            pixVal = searchTreeMod(parentNode, j, i);
            printf("%d  ", pixVal);

        }

        printf("\n");
    }

}


void spiralTraversal (bTree *parentNode, int x, int y, int maxX, int maxY) {                // c) Spiral Traversal

    int i;

    if(x >= maxX || y>= maxY) {
        printf(" end ");
    }

    else {

            for(i = x ; i < maxY; i++) {

                printf("%d  ", searchTreeMod(bTreeRoot, x, i));

            }
            printf("\n");

            for(i = x+1 ; i< maxX ; i++) {

                printf("%d  ", searchTreeMod(bTreeRoot, i, maxX - 1));

            }
            printf("\n");

            if((maxX - 1) != x) {

                for(i = maxY - 2 ; i>= y ; i--) {

                    printf("%d  ", searchTreeMod(bTreeRoot, maxX - 1, i));

                }

            }
            printf("\n");

            if((maxY - 1) != y) {

                for(i = maxX - 2; i > x ; i--) {

                    printf("%d  ", searchTreeMod(bTreeRoot, i, y));

                }

            }

            printf("\n");


            spiralTraversal(bTreeRoot, x + 1, y + 1, maxX - 1, maxY - 1);

    }

}


int main()
{
    initRootNode();
    insertIntoMatrix("test2.txt");
    int val;



    for ( int i = 0 ; i < INITSIZE; i++){

            for(int j = 0 ; j < INITSIZE; j++){

               printf("%d  ", imageMatrix[i][j]);

            }
        printf("\n");
    }

    printf("\n\n");


    int rootVal = createTree(0, 0, INITSIZE, bTreeRoot);
    bTreeRoot ->isOne = rootVal;

    //printf("Root is one value %d\n\n", bTreeRoot ->isOne);
   printf("ROOTNODE L1\n");
   printTree(bTreeRoot);

   int totalDisjoint = searchLevel(bTreeRoot, 3);
   printf("Total disjoint = %d \n", totalDisjoint);


    //spiralTraversal(bTreeRoot, 0, 0, 16, 16);


    //totalDisjointPairs(bTreeRoot);

    //int disjoint = calculateDisjoint(0,0, bTreeRoot, 3);
    //printf("Disjoint for 0,0 %d \n", disjoint);

    //rowTraversal(bTreeRoot);
   // printf("\n\n");
    //columnTraversal(bTreeRoot);


    //int totalOne = countForeground(bTreeRoot);
    //printf("Foreground count: %d\n", totalOne);



    return 0;
}
