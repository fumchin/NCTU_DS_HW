//store expression into the queue
//scan and find the operator that followed by two operand
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node{
    void* dataPtr;
    struct node* next;
}NODE;

typedef struct{ //queue head
    int count;
    NODE* head;
    NODE* tail;
}QUEUE;

//create queue head==============================================
QUEUE* createQueue(){
    QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
    if(q){
        q->count = 0;
        q->head = NULL;
        q->tail = NULL;
    }
    return q;
}
//===========================================================

//operator or not===================================
bool isOperator(int token){
    if(token=='+'-'0'||token=='-'-'0'||token=='*'-'0'||token=='/'-'0'){
        return true;
    }
    else{
        return false;
    }
}

//enqueue==============================================
void enqueue(QUEUE* queue,void* dataInPtr){
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->dataPtr = dataInPtr;
    newNode->next = NULL;
    if(queue->count == 0){
        queue->head = newNode;
        queue->tail = newNode;
    }
    else{
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    queue->count++;
}

//========================================================

//print queue===========================
void printQueue(QUEUE* queue){
    NODE *p = (NODE*)malloc(sizeof(NODE));
    p = queue->head;
    while(p!=NULL){
        if(*(int*)p->dataPtr == '+'-'0') printf("+");
        else if(*(int*)p->dataPtr == '-'-'0') printf("-");
        else if(*(int*)p->dataPtr == '*'-'0') printf("*");
        else if(*(int*)p->dataPtr == '/'-'0') printf("/");
        else printf("%d",*(int*)p->dataPtr);

        if(p->next != NULL) printf(" -> ");
        p = p->next;
    }
    printf("\n");
    free(p);
}
//======================================

//calPrefix
int calPrefix(QUEUE* queue){
    //find operator follow by two operand
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    NODE* del_1 = (NODE*)malloc(sizeof(NODE));
    NODE* del_2 = (NODE*)malloc(sizeof(NODE));
    temp = queue->head;
    int value=0;

    int operand1,operand2;
    while(queue->count>=3){
        if(isOperator(*(int*)temp->dataPtr)){

            //check if next two character are operand or not
            if(!isOperator(*(char*)temp->next->dataPtr) && !isOperator(*(char*)temp->next->next->dataPtr)){
               operand1 = (*(int*)temp->next->dataPtr);
               operand2 = (*(int*)temp->next->next->dataPtr);
               //printf("%d\t%d\n",operand1,operand2);
               if(*(int*)temp->dataPtr == '+'-'0') value = (operand1+operand2);
               else if(*(int*)temp->dataPtr == '-'-'0') value = (operand1-operand2);
               else if(*(int*)temp->dataPtr == '*'-'0') value = (operand1*operand2);
               else if(*(int*)temp->dataPtr == '/'-'0') value = (operand1/operand2);
               //dequeue replace operator with value
               *(int*)temp->dataPtr = value;
               del_1 = temp->next;
               del_2 = del_1->next;
               temp->next = temp->next->next->next;
               temp = queue->head;

               //delete node
               free(del_1);
               free(del_2);
               queue->count -= 2;
               printQueue(queue);
            }
            else{
                temp = temp->next;
            }
        }
        else{
            temp = temp->next;
        }
    }
    return value;
}

int main(){
    QUEUE* queue;
    queue = createQueue();
    //input
    char token;
    int* operandPtr;
    char* operatorPtr;
    int* dataInPtr;
    printf("input expression: ");
    //store in queue
    while((token = getchar()) != '\n'){
        //operator or not
        if(token!=' '){
            dataInPtr = (NODE*)malloc(sizeof(NODE));
            *dataInPtr = token-'0';
            enqueue(queue,dataInPtr);
        }
    }

    int result;
    result = calPrefix(queue);
    printf("answer: %d\n",result);

    //print queue
    return 0;
}
