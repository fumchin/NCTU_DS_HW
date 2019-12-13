#include <stdio.h>
#include <stdlib.h>

typedef struct student{
    int id;
    float score;
}student;

typedef struct node{
    void* dataPtr;
    struct node* link;
}Node;

Node* createNode(void *itemPtr){
    Node* nodePtr;
    nodePtr = (Node*)malloc(sizeof(Node));
    nodePtr->dataPtr = itemPtr;
    nodePtr->	link = NULL;
    return nodePtr;
}

int compare(void *ptr1,void *ptr2){
    if(*(int*)ptr1 > *(int*)ptr2){
        return 1;
    }
    else{
        return -1;
    }
}

void *larger(void *dataPtr1,void *dataPtr2,int (*ptrToFun)(void*,void*)){
    if((*ptrToFun)(dataPtr1,dataPtr2)>0){
        return dataPtr1;
    }
    else{
        return dataPtr2;
    }
}

int main(){
    //read file
    FILE* finput,*foutput;
    finput = fopen("input.txt","r");
    //foutput = fopen("output.txt","w+");
    if(finput == NULL){
        printf("no");
    }
    //new Data
    student* newData;
    newData = (student*)malloc(sizeof(student));

    //temp node
    Node *head,*scan,*prev = (Node*)malloc(sizeof (Node));
    head = NULL;
    Node *p = (Node*)malloc(sizeof (Node));
    
	//sort before insert
    while(fscanf(finput,"%d%f",&(newData->id),&(newData->score)) != EOF){
        //create new node with new data
        p = createNode(newData);
        
		//NULL
        prev = head;
        if(prev == NULL){
            p->link = head;
            head = p;
        }
        //not NULL
        else if(prev != NULL){
            scan = prev->link;
            //one node
            if(scan==NULL){
                if(*(int*)larger(&((student*)(p->dataPtr))->id,&((student*)(prev->dataPtr))->id,compare) == ((student*)(prev->dataPtr))->id){
                    p->link = head;
                    head = p;
                }
                else{
                    p->link = NULL;
                    head->link = p;
                }
            }
			//more than one node in linked list
            if(scan!=NULL){
            	//smaller than first node
                if(prev == head && *(int*)larger(&((student*)(p->dataPtr))->id,&((student*)(prev->dataPtr))->id,compare) == ((student*)(prev->dataPtr))->id){
                    p->link = head;
                    head = p;
                }
                //smaller
                else{
                    while(scan!=NULL && *(int*)larger(&((student*)(p->dataPtr))->id,&((student*)(scan->dataPtr))->id,compare) == ((student*)(p->dataPtr))->id){
                        prev = prev->link;
                        scan = prev->link;
                    }
                    p->link = scan;
                    prev->link = p;
                }
            }
        }
		//new data
        newData = (student*)malloc(sizeof(student));
    }
    p = head;
    printf("sorted by id\nid\tscore\n-------------------\n");
    while(p!=NULL){
        printf("%d\t%.2f\n",((student*)(p->dataPtr))->id,((student*)(p->dataPtr))->score);
        //output to output.txt
		//fprintf(foutput,"%d\t%.2f\n",((student*)(p->dataPtr))->id,((student*)(p->dataPtr))->score);
        p = p->link;
    }

    return 0;
}
