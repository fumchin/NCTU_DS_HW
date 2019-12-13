#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

typedef struct{
    int coefficient;
    int exp;
}Poly;

typedef struct poly{
    void* dataPtr;
    struct poly* next;
}Node;

typedef struct{
    Node* head;
    Node* tail;
    int count;
}List;

//generate list=========================================
List* createList(){
    List* list = new List;
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}
//enList
void enList(List* list,void* dataInPtr){
    Node* new_node = new Node;
    new_node->next = NULL;
    new_node->dataPtr = dataInPtr;

    if(list->count == 0){
        list->head = new_node;
        list->tail = new_node;
    }
    else{
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->count++;
}
//print list
void printList(List* list){
    Node *p = new Node;
    p = list->head;
    while(p!=NULL){
        if(p->next==NULL){
            if(((Poly*)(p->dataPtr))->exp == 0){
                cout<<((Poly*)(p->dataPtr))->coefficient;
            }
            else{
                cout<<setw(2)<<((Poly*)(p->dataPtr))->coefficient<<"x^"<<((Poly*)(p->dataPtr))->exp;
            }

        }
        else{
            if(((Poly*)(p->dataPtr))->exp == 0){
                cout<<((Poly*)(p->dataPtr))->coefficient<<" +";
            }
            else{
                cout<<setw(2)<<((Poly*)(p->dataPtr))->coefficient<<"x^"<<((Poly*)(p->dataPtr))->exp<<" +";
            }
        }

        p = p->next;
    }
    cout<<endl;
    delete p;
}

List* add(List* list1,List* list2){
    List* result = new List;
    result = createList();
    Node* p = new Node;
    Node* q = new Node;
    p = list1->head;
    q = list2->head;
    while(p!=NULL){
        while(q!=NULL){
            if(((Poly*)(p->dataPtr))->exp == ((Poly*)(q->dataPtr))->exp){
                Poly* dataInPtr = new Poly;
                dataInPtr->coefficient = ((Poly*)(p->dataPtr))->coefficient + ((Poly*)(q->dataPtr))->coefficient;
                dataInPtr->exp = ((Poly*)(p->dataPtr))->exp;
                if(dataInPtr->coefficient != 0){
                    enList(result,dataInPtr);
                }
                p = p->next;
                q = q->next;
            }
            else if(((Poly*)(p->dataPtr))->exp > ((Poly*)(q->dataPtr))->exp){
                Poly* dataInPtr = new Poly;
                dataInPtr->coefficient = ((Poly*)(p->dataPtr))->coefficient;
                dataInPtr->exp = ((Poly*)(p->dataPtr))->exp;
                enList(result,dataInPtr);
                p = p->next;
            }
            else if(((Poly*)(p->dataPtr))->exp < ((Poly*)(q->dataPtr))->exp){
                Poly* dataInPtr = new Poly;
                dataInPtr->coefficient = ((Poly*)(q->dataPtr))->coefficient;
                dataInPtr->exp = ((Poly*)(q->dataPtr))->exp;
                enList(result,dataInPtr);
                q = q->next;
            }
            if(p==NULL || q==NULL){
                break;
            }
        }
        if(p==NULL || q==NULL){
                break;
        }
    }
    while(p==NULL && q!=NULL){
        Poly* dataInPtr = new Poly;
        dataInPtr->coefficient = ((Poly*)(q->dataPtr))->coefficient;
        dataInPtr->exp = ((Poly*)(q->dataPtr))->exp;
        enList(result,dataInPtr);
        q = q->next;
    }
    while(p!=NULL && q==NULL){
        Poly* dataInPtr = new Poly;
        dataInPtr->coefficient = ((Poly*)(p->dataPtr))->coefficient;
        dataInPtr->exp = ((Poly*)(p->dataPtr))->exp;
        enList(result,dataInPtr);
        p = p->next;
    }
    delete p,q;
    return result;
}

//main program===========================================
int main(){
    ifstream infile1,infile2;
    infile1.open("1.txt");
    infile2.open("2.txt");
    if(!infile1 || !infile2){
        cout<<"file open fail"<<endl;
    }
    //create List
    List* list1 = new List;
    List* list2 = new List;
    List* result = new List;
    list1 = createList();
    list2 = createList();
    result = createList();

    //list1
    while(!infile1.eof()){
        Poly* dataInPtr = new Poly;
        infile1>>(dataInPtr->coefficient);
        infile1>>(dataInPtr->exp);
        //cout<<(dataInPtr->coefficient)<<"\t"<<(dataInPtr->exp)<<endl;
        enList(list1,dataInPtr);
    }

    //list2
    while(!infile2.eof()){
        Poly* dataInPtr = new Poly;
        infile2>>(dataInPtr->coefficient);
        infile2>>(dataInPtr->exp);
        //cout<<(dataInPtr->coefficient)<<"\t"<<(dataInPtr->exp)<<endl;
        enList(list2,dataInPtr);
    }
    //print
    cout<<"1: ";
    printList(list1);
    cout<<"2: ";
    printList(list2);

    result = add(list1,list2);
    cout<<"result: ";
    printList(result);


}
