//done
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
using namespace std;

//score node
typedef struct node{
    void* dataPtr;
    struct node* next;
}scoreNode;

//student node
typedef struct name{
    struct name *next_name;
    void* dataPtr;
    scoreNode* head;
    scoreNode* tail;
    int count;      //count there are how many score node
}nameNode;

typedef struct{
    int count;
    nameNode* head;
    nameNode* tail;
}List;

//=================================================
List* genNewList(){
    List *list = new List;
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void genNewStu(List* list,void *name){
    nameNode* new_name = new nameNode;
    new_name->dataPtr = name;
    new_name->next_name = NULL;
    if(list->count == 0){
        list->head = new_name;
        list->tail = new_name;
    }
    else{
        list->tail->next_name = new_name;
        list->tail = new_name;
    }
    new_name->head = NULL;
    new_name->tail = NULL;
    new_name->count = 0;
    list->count++;
}

void enScore(List* list,void *score){
    //find that person
    nameNode *p = new nameNode;
    p = list->head;
    for(int i=0;i<(list->count)-1;i++){
        p = p->next_name;
    }
    //create new score node
    scoreNode *new_score = new scoreNode;
    new_score->dataPtr = score;
    new_score->next = NULL;
    if(p->count==0){
        p->head = new_score;
        p->tail = new_score;
    }
    else{
        p->tail->next = new_score;
        p->tail = new_score;
    }
    p->count++;
}
//================================================
//print===========================================
void printList(List* list){
    int total=0,avg=0,num;
    nameNode *n = new nameNode;
    scoreNode *s = new scoreNode;
    n = list->head;
    while(n!=NULL){
        cout<<setw(10)<<*(string*)n->dataPtr<<":\t";
        s = n->head;
        num = n->count;
        while(s!=NULL){
            if(s->next == NULL){
                cout<<*(int*)s->dataPtr;
                total += *(int*)s->dataPtr;
            }
            else{
                cout<<*(int*)s->dataPtr<<"->";
                total += *(int*)s->dataPtr;
            }
            s = s->next;
        }
        avg = total/num;
        n = n->next_name;

        cout<<"\t"<<total<<"(total)\t"<<avg<<"(average)"<<endl;
        total = 0;
        avg = 0;
    }
}
//================================================
int main(){
    ifstream infile;
    infile.open("student.txt");
    if(!infile){
        cout<<"file open fail"<<endl;
    }
    List* list;
    list = genNewList();
    string input;
    size_t prev=0,pos=0;
    while(!infile.eof()){
        pos = prev = 0;
        getline(infile,input);
        //cout<<input<<endl;
        int count = 0;
        while((pos = input.find_first_of(" ",pos)) != string::npos){
            //cout<<pos<<endl;
            if(count == 0){
                string* name = new string;
                *name = input.substr(prev,pos-prev);
                genNewStu(list,name);
                count++;
            }
            else{
                int* score = new int;
                *score = stoi(input.substr(prev,pos-prev));
                enScore(list,score);
            }
            prev = pos+1;
            pos++;
        }
        if(pos==string::npos && prev==0){
            string* name = new string;
            *name = input.substr(prev,pos-prev);
            genNewStu(list,name);
        }
        else if(pos == string::npos && count!=0){
            int* score = new int;
            *score = stoi(input.substr(prev,pos-prev));
            enScore(list,score);
        }
    }
    printList(list);
}
