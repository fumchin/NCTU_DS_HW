#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct node{
    int data;
    struct node* next;
}Node;

typedef struct{
    int count;
    string file_name;
    Node* head;
}List;
//insert
void insert(List *list,int i,int data){
    Node* new_node = new Node;
    new_node->data = data;
    if(list[i].count == 0){
        list[i].head = new_node;
        new_node->next = nullptr;
    }
    else{
        new_node->next = list[i].head;
        list[i].head = new_node;
    }
    list[i].count++;
}

int main(){
    int file_num;
    string file_name = "";
    cin>>file_num;
    List* listary = new List[file_num];

    for(int i=0;i<file_num;i++){
        listary[i].count = 0;
        listary[i].head = NULL;
        listary[i].file_name = "";
        cout<<"input file name(a,b,c,d): ";
        cin>>listary[i].file_name;
    }
    int data;
    for(int i=0;i<file_num;i++){
        ifstream* infile = new ifstream;
        infile->open(listary[i].file_name+".txt");
        if(!infile){
            cout<<"fail to open"<<endl;
        }
        while(*infile>>data){
            insert(listary,i,data);
        }
    }
    string result = "";
    Node* p = new Node;
    for(int i=0;i<file_num;i++){
        p = listary[i].head;
        while(p!=nullptr){
            result = to_string(p->data) + " " + result;
            p = p->next;
        }
        cout<<listary[i].file_name<<": "<<result<<endl;
        result.clear();
    }

}
