#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

typedef struct node{
    struct node* next;
    struct node* prev;
    void* dataPtr;
}Node;

typedef struct{
    Node* head;
    Node* tail;
    int count;
}List;

typedef struct{
    string area;
    string population2000;
    string population1990;
}Data;

List* createList(){
    List* list = new List;
    list->count = 0;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void enNode(List* list,void* dataInPtr){
    Node* new_node = new Node;
    new_node->dataPtr = dataInPtr;
    if(list->count == 0){
        new_node->next = nullptr;
        new_node->prev = nullptr;
        list->head = new_node;
        list->tail = new_node;
    }
    else{
        new_node->next = nullptr;
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->count++;
}

void printList(List* list){
    Node* p = new Node;
    cout<<"up -> down: "<<endl;
    p = list->head;
    while(p!=nullptr){
        cout<<setw(15)<<((Data*)(p->dataPtr))->area
            <<setw(15)<<((Data*)(p->dataPtr))->population2000
            <<setw(15)<<((Data*)(p->dataPtr))->population1990<<endl;
        p = p->next;
    }
    cout<<endl;
    cout<<"down->up: "<<endl;
    p = list->tail;
    while(p!=nullptr){
        cout<<setw(15)<<((Data*)(p->dataPtr))->area
            <<setw(15)<<((Data*)(p->dataPtr))->population2000
            <<setw(15)<<((Data*)(p->dataPtr))->population1990<<endl;
        p = p->prev;
    }
    delete p;
}

int main(){
    ifstream infile;
    List* list = new List;
    list = createList();
    string area,population2000,population1990;
    infile.open("data.txt");
    while(!infile.eof()){
        Data *dataInPtr = new Data;
        infile>>area;
        infile>>population2000;
        infile>>population1990;
        dataInPtr->area = area;
        dataInPtr->population2000 = population2000;
        dataInPtr->population1990 = population1990;
        enNode(list,dataInPtr);
    }
    printList(list);
    delete list;
}
