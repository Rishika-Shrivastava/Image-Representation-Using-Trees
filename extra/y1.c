#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXCHAR 1000
#define MAXNODE 4
#define INITSIZE 4

int row = 1, i=0, j=0;

typedef enum {FALSE, TRUE} Bool;          // to check whether the node is a leaf node or not

typedef struct bTreeNode {

    Bool isLeaf;
    int level;
    int size;                         // total 2m+1 levels
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

int imageMatrix[INITSIZE][INITSIZE];                             //INITSIZE*INITSIZE ARRAY


void insertIntoMatrix(char filename[]){            //FILE READING

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

//-------------------------------------------------------CREATE TREE--------------------------------------------------------

void createTree(int x, int y, int size, bTree *parentNode){
    //printf("row is %d \n", row);
    //row ++;

    parentNode ->childNode[0] = (bTree *)malloc(sizeof(bTree));
    parentNode ->childNode[1] = (bTree *)malloc(sizeof(bTree));
    parentNode ->childNode[2] = (bTree *)malloc(sizeof(bTree));
    parentNode ->childNode[3] = (bTree *)malloc(sizeof(bTree));

    if(size > 2)
    {
        parentNode ->childNode[0] ->isLeaf = FALSE;
        parentNode ->childNode[0] ->level = parentNode ->level + 1;
        parentNode ->childNode[0] ->size = size / 2;
        parentNode ->childNode[0] ->startX = x ;
        parentNode ->childNode[0] ->startY = y ;
        parentNode ->childNode[0] ->pixelVal = -1;

        parentNode ->childNode[1] ->isLeaf = FALSE;
        parentNode ->childNode[1] ->level = parentNode ->level + 1;
        parentNode ->childNode[1] ->size = size / 2;
        parentNode ->childNode[1] ->startX = x + (size)/2;
        parentNode ->childNode[1] ->startY = y ;
        parentNode ->childNode[1] ->pixelVal = -1;

        parentNode ->childNode[2] ->isLeaf = FALSE;
        parentNode ->childNode[2] ->level = parentNode ->level + 1;
        parentNode ->childNode[2] ->size = size / 2;
        parentNode ->childNode[2] ->startX = x + (size)/2;
        parentNode ->childNode[2] ->startY = y + (size)/2;
        parentNode ->childNode[2] ->pixelVal = -1;

        parentNode ->childNode[3] ->isLeaf = FALSE;
        parentNode ->childNode[3] ->level = parentNode ->level + 1;
        parentNode ->childNode[3] ->size = size / 2;
        parentNode ->childNode[3] ->startX = x ;
        parentNode ->childNode[3] ->startY = y + (size)/2;
        parentNode ->childNode[3] ->pixelVal = -1;


        createTree(x, y, size/2, parentNode ->childNode[0]);
        createTree(x+ size/2, y, size/2, parentNode ->childNode[3]);
        createTree(x+ size/2, y + size/2, size/2, parentNode ->childNode[2]);
        createTree(x , y + size/2, size/2, parentNode ->childNode[1]);

    }
    else
    {
        //printf("entered child ");

        parentNode ->childNode[0] ->isLeaf = TRUE;
        parentNode ->childNode[0] ->level = parentNode ->level + 1;
        parentNode ->childNode[0] ->size = size / 2;
        parentNode ->childNode[0] ->startX = x ;
        parentNode ->childNode[0] ->startY = y ;
        parentNode ->childNode[0] ->pixelVal = imageMatrix[x][y];
        //printf("\tvalue - %d ", parentNode ->childNode[0] ->pixelVal);

        parentNode ->childNode[1] ->isLeaf = TRUE;
        parentNode ->childNode[1] ->level = parentNode ->level + 1;
        parentNode ->childNode[1] ->size = size / 2;
        parentNode ->childNode[1] ->startX = x + (size)/2;
        parentNode ->childNode[1] ->startY = y ;
        parentNode ->childNode[1] ->pixelVal = imageMatrix[x][y+1];
        //printf("\tvalue - %d ", parentNode ->childNode[1] ->pixelVal);

        parentNode ->childNode[2] ->isLeaf = TRUE;
        parentNode ->childNode[2] ->level = parentNode ->level + 1;
        parentNode ->childNode[2] ->size = size / 2;
        parentNode ->childNode[2] ->startX = x + (size)/2;
        parentNode ->childNode[2] ->startY = y + (size)/2;
        parentNode ->childNode[2] ->pixelVal = imageMatrix[x+1][y+1];
        //printf("\tvalue - %d ", parentNode ->childNode[2] ->pixelVal);

        parentNode ->childNode[3] ->isLeaf = TRUE;
        parentNode ->childNode[3] ->level = parentNode ->level + 1;
        parentNode ->childNode[3] ->size = size / 2;
        parentNode ->childNode[3] ->startX = x;
        parentNode ->childNode[3] ->startY = y + (size)/2;
        parentNode ->childNode[3] ->pixelVal = imageMatrix[x+1][y];
        //printf("\tvalue - %d ", parentNode ->childNode[3] ->pixelVal);

    }
   // printf("\n");

}


//------------------------------------------------------------- QUESTION 2 ----------------------------------------------

int forePixels =0;

void countForeground(bTree *parentNode) {

    int i, j;

    for(i= 0; i < 4 ; i++) {

        if(parentNode ->childNode[i] ->isLeaf == FALSE ) {

            countForeground(parentNode->childNode[i]);

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

    printf("Number of foreground pixels: %d\n", forePixels);

}



//  ------------------------------  QUESTION 3 ---------------------------------------------------

int retVal = 0 ;

int searchTree(bTree *parentNode, int x, int y){                              // SEARCH PIXEL VALUE CORRESPONDING TO COORDINATES

    int flag1=0, i=0;


    for(int i = 0; (i < 4) ; i++){

        if(parentNode ->childNode[i] ->isLeaf == FALSE ) {

                searchTree(parentNode->childNode[i], x, y);

        }
        else {

            if(parentNode ->childNode[i] ->startX == x && parentNode ->childNode[i] ->startY == y) {

                retVal = parentNode ->childNode[i] ->pixelVal;
                //printf("%d ", retVal);

            }

        }

    }

   return retVal;

}



int searchMod (bTree *parentNode, int x, int y)     //MODIFIED SEARCH FUNCTION
{
   // printf("Entered function\n");
    int s = (parentNode->size) / 2, retValue;
    //printf("%d %d %d\n", x, y, s);
    if(parentNode ->isLeaf == FALSE)
    {
        //printf("NOT LEAF\n");
        if(x >= s)
        {
            if(y < s)
            {
                //printf("D\n");
                retValue = searchMod(parentNode ->childNode[3], x - s, y);
            }
            else
            {
                //printf("C\n");
                retValue = searchMod(parentNode ->childNode[2], x - s, y - s);
            }
        }
        else
        {
            if(y < s)
            {
                //printf("A\n");
                retValue = searchMod(parentNode ->childNode[0], x, y);
            }
            else
            {
                //printf("B\n");
                retValue = searchMod(parentNode ->childNode[1], x , y - s);
            }
        }
    }
    else
    {
        //printf("Entering LEAF\n");
        //printf("\n");
        printf("%d ", parentNode->pixelVal);
        retValue = parentNode->pixelVal;

    }
    return retValue;

}



int main()
{
    initRootNode();
    insertIntoMatrix("test2.txt");

    int i, j, val;
   /* for (i = 0 ; i < INITSIZE; i++)
    {
        for(j = 0 ; j < INITSIZE; j++)
        {
            scanf("%d",&imageMatrix[i][j]);
        }
    } */


    for (i = 0 ; i < INITSIZE; i++)
    {
	    for(j = 0 ; j < INITSIZE; j++)
               printf("%d ", imageMatrix[i][j]);
        printf("\n");
    }

    printf("\n\n");


    createTree(0, 0, INITSIZE, bTreeRoot);


    /*for (int i =0 ; i< 16; i++){

        int val = searchMod(bTreeRoot, i, 1);
        printf(" value: %d\n", val);

    } */


    //val = searchMod(bTreeRoot, 0, 1);

    for (i = 0 ; i < INITSIZE; i++)
    {
        for(j = 0; j < INITSIZE; j++)
            val = searchMod(bTreeRoot, i, j);
        printf("\n");
    }

    //printf("%d ", val);
    // printf("\n");


   // countForeground(bTreeRoot);

    return 0;
}
