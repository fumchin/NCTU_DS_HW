#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    void* dataPtr;
    struct node* link;
}stack_node;

typedef struct{
    int count;
    stack_node *top;
}stack_head;

stack_head* createHead(){
    stack_head* head;
    head = (stack_head*)malloc(sizeof(stack_head));
    head->count = 0;
    head->top = NULL;
    return head;
}

bool createNode(stack_head *head,void *dataInPtr){
    stack_node *p;
    p = (stack_node*)malloc(sizeof(stack_node));
    if(!p){
        return false;
    }
    //printf("%d",*(int*)dataInPtr);
    p->dataPtr = dataInPtr;
    p->link = head->top;
    head->top = p;

    (head->count)++;
    return true;
}

void printStack(stack_head *head){
    stack_node *p;
    p = head;
    while(p != NULL){
        printf("%d->",*(int*)p->dataPtr);
        p = p->link;
    }
}

int main(){
    int num;
    //create head
    stack_head *head;
    stack_node *p;
    void *dataInPtr;
    head = createHead();
    //start input
    while(scanf("%d",&num)!=EOF){
        dataInPtr = &num;
        //create node
        if(!createNode(head,dataInPtr)){
            printf("boom\n");
        }
        //print
        printStack(head);
    }
}
