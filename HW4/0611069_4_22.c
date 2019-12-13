#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define constant 5
int service_provided_time,max_service_time,phone_count = 0;
typedef struct node{
    void* dataPtr;
    struct node* next;
}NODE;

typedef struct{
    NODE* head;
    NODE* tail;
    int count;
}QUEUE;

typedef struct call_info{
    int clock_time;
    int arrival_time;
    int wait_time;
    int start_time;
    int service_time;
    int call_number;
}CALL;

QUEUE* createQueue(){
    QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
    queue->head = NULL;
    queue->tail = NULL;
    queue->count = 0;
    return queue;
}

void enqueue(QUEUE* queue,NODE* newNode){
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

bool emptyQueue(QUEUE* queue){
    if(queue->count == 0){
        return true;
    }
    else{
        return false;
    }
}

void dequeue(QUEUE* queue){
    queue->count--;
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
           ((CALL*)(queue->head->dataPtr))->clock_time,
           ((CALL*)(queue->head->dataPtr))->call_number,
           ((CALL*)(queue->head->dataPtr))->arrival_time,
           ((CALL*)(queue->head->dataPtr))->wait_time,
           ((CALL*)(queue->head->dataPtr))->start_time,
           ((CALL*)(queue->head->dataPtr))->service_time,
           queue->count);
    queue->head = queue->head->next;

}

bool processActive(int i,QUEUE *queue){
    if(((CALL*)(queue->head->dataPtr))->start_time == -1){
        ((CALL*)(queue->head->dataPtr))->start_time = i;
        return true;
    }
    else if(((CALL*)(queue->head->dataPtr))->start_time + ((CALL*)(queue->head->dataPtr))->service_time != i){
        return true;
    }
    else{
        ((CALL*)(queue->head->dataPtr))->wait_time = ((CALL*)(queue->head->dataPtr))->start_time - ((CALL*)(queue->head->dataPtr))->arrival_time;
        ((CALL*)(queue->head->dataPtr))->clock_time = i;
        return false;
    }
}

bool call_simulator(){
    int num;
    num = rand()%10+1;
    //printf("%d\n",num);
    if(num>constant){
        return true;    //phone activate
    }
    else{
        return false;
    }
}

NODE* createNode(int arrive){
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    CALL* newCall = (CALL*)malloc(sizeof(CALL));
    newNode->dataPtr = newCall;
    phone_count++;
    ((CALL*)(newNode->dataPtr))->arrival_time = arrive;
    ((CALL*)(newNode->dataPtr))->service_time = rand() % max_service_time + 1;
    ((CALL*)(newNode->dataPtr))->start_time = -1;
    ((CALL*)(newNode->dataPtr))->call_number = phone_count;
    return newNode;
}

int main(){
    int total_calls=0,total_idle_time=0,
    total_wait_time=0,total_service_time=0,
    max_queue_size=0,avg_wait_time=0,
    avg_service_time=0;

    srand((unsigned)time(NULL));
    QUEUE* queue;
    queue = createQueue();
    //input

    printf("the length of time in hours that the service is provided: ");
    scanf("%d",&service_provided_time);
    printf("the maximum time it takes for the operator to take an order: ");
    scanf("%d",&max_service_time);
    //timing loop
    printf("Clock\tNumber\tArrival\tWait\tStart\tService\tQueue\n");
    for(int i=0;i<service_provided_time*60;i++){
        if(call_simulator()){
            NODE* newNode;
            newNode = createNode(i);
            enqueue(queue,newNode);
        }
        //answer call
        if(!emptyQueue(queue) && !processActive(i,queue)){
            total_calls = ((CALL*)queue->head->dataPtr)->call_number;
            total_wait_time += ((CALL*)queue->head->dataPtr)->wait_time;
            total_service_time += ((CALL*)queue->head->dataPtr)->service_time;
            avg_service_time = total_service_time/total_calls;
            avg_wait_time = total_wait_time/total_calls;
            dequeue(queue);
            if(queue->count > max_queue_size) max_queue_size = queue->count;
            if(queue->count==0){
                total_idle_time++;
            }
        }
        //print

    }
    printf("total_calls\ttotal_idle\ttotal_wait\ttotal_serve\tmax_queue\tavg_wait\tavg_service\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\n",
               total_calls,total_idle_time,total_wait_time,
               total_service_time,max_queue_size,avg_wait_time,avg_service_time);
    return 0;
}
