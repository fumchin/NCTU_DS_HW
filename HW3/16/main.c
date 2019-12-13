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

void* popFiveNode(stack_head *head){
    stack_node *temp;
    void *dataOutPtr;

    if(head->count == 0){
        dataOutPtr = NULL;
    }
    else{
        printf("pop:\n");
        for(int i=0;i<5;i++){
            temp = head->top;
            dataOutPtr = head->top->dataPtr;
            head->top = head->top->link;
            free(temp);
            printf("(%d)%d\n",i+1,*(int*)dataOutPtr);
        }
    }
}

void printStack(stack_head *head){
    stack_node *p;
    p = head->top;
    while(p != NULL){
        printf("%d",*(int*)p->dataPtr);
        if(p->link != NULL){
            printf("->");
        }
        p = p->link;
    }
    printf("\n");
}

int main(){
    //create head
    stack_head *head;
    void *dataInPtr;
    head = createHead();
    //start input
    dataInPtr = (int*)malloc(sizeof (int));
    while(scanf("%d",&(*(int*)dataInPtr))!=EOF){
        if(*(int*)dataInPtr>=0){
            if(!createNode(head,dataInPtr)){
                printf("push unsucessful\n");
            }
        }
        else if(*(int*)dataInPtr<0){
            if(head->count>=5){
                popFiveNode(head);
            }
            else{
                printf("error!!!\n");
                return  0;
            }

        }
        //print
        //printStack(head);
        dataInPtr = (int*)malloc(sizeof (int));
    }
    printStack(head);
    return  0;
}
