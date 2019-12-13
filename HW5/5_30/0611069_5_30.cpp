#include <iostream>
using namespace std;

//node
typedef struct node{
    void* dataPtr;
    struct node* next;
}Node;
//head
typedef struct{
    Node* head;
    Node* tail;
    int count;
}List;

typedef struct{
    int digit;
    bool carry;
}Digit;

//create list=============
List* createList(){
    List* list = new List;
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}
//=========================

void enDigit(List* list,void* dataInPtr){
    Node* new_node = new Node;
    new_node->next = NULL;
    new_node->dataPtr = dataInPtr;
    //input like queue
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

//print
void printList(List* list){
    string result = "";
    string carry = "";
    Node* p = new Node;
    p = list->head;
    while(p!=NULL){
        result = to_string(((Digit*)(p->dataPtr))->digit) + result;
        p = p->next;
    }
    cout<<result<<"\t(result)"<<endl;
    p = list->head->next;
    while(p!=NULL){
        carry = to_string(((Digit*)(p->dataPtr))->carry) + carry;
        p = p->next;
    }
    cout<<carry<<"\t(carry)"<<endl;
    delete p;
}
//add
List* add_by_digit(List* list1,List* list2){
    List* result = new List;
    result = createList();
    Node* p = new Node;
    Node* q = new Node;

    p = list1->head;
    q = list2->head;

    bool carry = 0;
    while(p!=NULL){
        while(q!=NULL){
            Digit* new_digit = new Digit;
            new_digit->carry = carry;
            new_digit->digit = (((Digit*)(p->dataPtr))->digit + ((Digit*)(q->dataPtr))->digit)%10 + carry;
            carry = (((Digit*)(p->dataPtr))->digit + ((Digit*)(q->dataPtr))->digit)/10;
            enDigit(result,new_digit);
            p = p->next;
            q = q->next;
            if(p==NULL || q==NULL){
               break;
            }
        }
        if(p==NULL || q==NULL){
            break;
        }
    }
    while(q!=NULL && p==NULL){
        Digit* new_digit = new Digit;
        new_digit->digit = ((Digit*)(q->dataPtr))->digit;
        new_digit->carry = carry;
        enDigit(result,new_digit);
        q = q->next;
    }
    while(q==NULL && p!=NULL){
        Digit* new_digit = new Digit;
        new_digit->digit = ((Digit*)(p->dataPtr))->digit;
        new_digit->carry = carry;
        enDigit(result,new_digit);
        p = p->next;
    }
    //delete p,q;
    //carry

    return result;
}

int main(){
    cout<<"input two numbers: ";
    int num1,num2;
    cin>>num1>>num2;

    //create List
    List* list1 = new List;
    List* list2 = new List;
    List* result = new List;
    list1 = createList();
    list2 = createList();
    result = createList();

    //enDigit
    while(num1>0){
        Digit* dataInPtr = new Digit;
        dataInPtr->carry = 0;
        dataInPtr->digit = num1%10;
        enDigit(list1,dataInPtr);
        num1/=10;
    }
    while(num2>0){
        Digit* dataInPtr = new Digit;
        dataInPtr->carry = 0;
        dataInPtr->digit = num2%10;
        enDigit(list2,dataInPtr);
        num2/=10;
    }

    result = add_by_digit(list1,list2);

    //print
    printList(result);
}
