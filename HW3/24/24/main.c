//two stack
//one for path
//one for decision

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ROW 10
#define COL 12

void printMap(int arr[][COL]){
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            if(arr[i][j]==1){
                printf("* ");
            }
            else if(arr[i][j]==0){
                printf("  ");
            }
            else{
                printf("2");
            }
        }
        printf("\n");
    }
}

//node definition
typedef struct node{
    void *dataPtr;
    struct node *link;
}stack_node;

typedef struct{
    int count;
    stack_node *top;
}stack_head;

typedef struct pos{
    int row;
    int col;
} POS;

stack_head* createHead(){
    stack_head *p;
    p = (stack_head*)malloc(sizeof (stack_head));
    p->top = NULL;
    p->count = 0;
    return p;
}

void createNode(stack_head* head,void* dataInPtr){
    stack_node *p;
    p = (stack_node*)malloc(sizeof(stack_node));
    p->dataPtr = dataInPtr;
    p->link = head->top;
    head->top = p;
}

void* backNode(stack_head *head){
    stack_node *temp,*dataOutPtr;
    temp = head->top;
    dataOutPtr = head->top->dataPtr;
    head->top = head->top->link;
    free(temp);
    //printf("(%d,%d)->",(*(POS*)dataOutPtr).row,(*(POS*)dataOutPtr).col);
    return dataOutPtr;
}

void printNode(stack_head *head){
    stack_node *p;
    p = (stack_node*)malloc(sizeof (stack_node));
    p = head->top;
    while(p!=NULL){
        printf("(%d,%d)->",(*(POS*)p->dataPtr).row,(*(POS*)p->dataPtr).col);
        p = p->link;
    }
}

int main()
{
 //   bool goalFount = false;
    int arr[10][12] = {{1,1,1,1,1,1,1,1,1,1,1,1},
                       {1,0,0,0,1,1,0,1,0,1,0,1},
                       {1,1,1,0,1,0,0,0,0,0,0,1},
                       {1,1,0,0,0,0,1,1,1,1,0,1},
                       {1,1,0,1,1,1,1,1,1,1,0,0},
                       {1,1,0,1,0,1,1,1,1,1,1,1},
                       {1,1,0,0,0,1,1,1,1,1,1,1},
                       {1,1,1,1,0,1,1,1,0,1,0,1},
                       {1,1,0,0,0,0,0,1,0,0,0,1},
                       {1,1,1,1,1,1,1,1,1,1,1,1},
    };
    //printf("%d",arr[8][2]);
    //print map
    printMap(arr);
    //pos
    POS entrance_pos,current_pos;
    //dataInPtr
    void *dataInPtr;
    void *dataOutPtr;
    dataInPtr = (POS*)malloc(sizeof (POS));
    dataOutPtr = (POS*)malloc(sizeof (POS));
    //user choose entrance
    POS exit = {exit.row = 4,exit.col = 11};
    //POS current;
    do{
        printf("choose entrance(row,col): ");
        scanf("%d%d",&entrance_pos.row,&entrance_pos.col);
    }while(arr[entrance_pos.row][entrance_pos.col]!=0 || entrance_pos.row>ROW || entrance_pos.col>COL);

    entrance_pos.row-=1;
    entrance_pos.col-=1;
    //create stack;
    stack_head *path,*selection;
    path = createHead();
    selection = createHead();

    //push entrance
    current_pos = entrance_pos;
    *(POS*)dataInPtr = entrance_pos;
    createNode(path,dataInPtr);
    //printNode(path);
    //start
    printf("(%d,%d)->",current_pos.row+1,current_pos.col+1);
    //find
    while(current_pos.row!=exit.row && current_pos.col != exit.col){
        arr[current_pos.row][current_pos.col] = 2;
        dataInPtr = (POS*)malloc(sizeof (POS));
        //up
        if(arr[current_pos.row+1][current_pos.col]==0){
            current_pos.row+=1;
            *(POS*)dataInPtr = current_pos;
            createNode(path,dataInPtr);
        }
        //right
        else if(arr[current_pos.row][current_pos.col+1]==0){
            current_pos.col+=1;
            *(POS*)dataInPtr = current_pos;
            createNode(path,dataInPtr);
        }
        //down
        else if(arr[current_pos.row-1][current_pos.col]==0){
            current_pos.row-=1;
            *(POS*)dataInPtr = current_pos;
            createNode(path,dataInPtr);
        }
        //left
        else if(arr[current_pos.row][current_pos.col-1]==0){
            current_pos.col-=1;
            *(POS*)dataInPtr = current_pos;
            createNode(path,dataInPtr);
        }
        //dead ene
        else if(current_pos.row == entrance_pos.row && current_pos.col==entrance_pos.col){
            printf("no Exit here QQ\n");
            return 0;
        }
        else{
            current_pos = *(POS*)backNode(path);
            //printf("(%d,%d)->",current_pos.row,current_pos.col);
        }
        printf("(%d,%d)->",current_pos.row+1,current_pos.col+1);
    }
    printf("(5,12)->EXIT!!\n");



    return 0;
}
