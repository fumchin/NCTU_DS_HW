#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "0611069_7_22.h"
using namespace std;
typedef struct{
    string name;
    string phone_number;
}Personal_Info;

void menu(){
    cout<<"what you want to do?"<<endl
        <<"(1) search for specific name"<<endl
        <<"(2) insert a new name"<<endl
        <<"(3) deleting a existing name"<<endl
        <<"(4) print the entire phone list"<<endl
        <<"(5) Exit"<<endl
        <<"================================="<<endl
        <<"enter here->: ";
}

ifstream readfile(){
    ifstream infile;
    infile.open("HW7_22.txt");
    if(!infile){
        cout<<"fail to open file"<<endl;
    }
    else{
        return infile;
    }
}
int compare(void* a, void* b){
    //compare by the first character of name
    int length = ((((Personal_Info*)a)->name).length() < (((Personal_Info*)b)->name).length())? (((Personal_Info*)a)->name).length() :(((Personal_Info*)b)->name).length();
    for(int i=0;i<length;i++){
        char key1 = (((Personal_Info*)a)->name)[i];
        char key2 = (((Personal_Info*)b)->name)[i];
        if(key1>key2) return 1;
        else if(key1 < key2) return -1;
        else continue;
    }
    return 0;
}

void printBST(void *dataPtr){
    cout<<((Personal_Info*)dataPtr)->name<<"\t"<<((Personal_Info*)dataPtr)->phone_number<<endl;
}

void _search(NODE* root,void* target){
    if(root){
        if(compare(root->dataPtr,target)==0){
            cout<<"Result: Found"<<endl;
            cout<<"Name: "<<((Personal_Info*)root->dataPtr)->name<<endl
                <<"Phone number: "<<((Personal_Info*)root->dataPtr)->phone_number<<endl;
            return;
        }
        else if(compare(target,root->dataPtr) < 0){
            _search(root->left,target);
        }
        else{
            _search(root->right,target);
        }
    }
    else{
        cout<<"Result: Not found"<<endl;
    }
return;
}

void BST_Search(BST_TREE* tree){
    Personal_Info* target = new Personal_Info;
    cout<<"enter name: ";
    cin>>target->name;
    _search(tree->root,target);
    delete target;
}


void initialize(BST_TREE* tree,ifstream &infile){
    string input1,input2;
    while(!infile.eof()){
        Personal_Info *dataIn = new Personal_Info;
        infile>>(dataIn->name);
        infile>>(dataIn->phone_number);
        //cout<<dataIn->name<<endl<<dataIn->phone_number<<endl;
        if(!BST_Insert(tree,dataIn)){
            cout<<"fail insert"<<endl;
        }
    }

}

void delete_list(BST_TREE* tree){
    Personal_Info* target = new Personal_Info;
    cout<<"enter name: ";
    cin>>target->name;
    BST_Delete(tree,target);
    delete target;
}

void insert_list(BST_TREE* tree){
    Personal_Info* target = new Personal_Info;
    cout<<"enter name: ";
    cin>>target->name;
    cout<<"enter phone number: ";
    cin>>target->phone_number;
    BST_Insert(tree,target);
}

void operate(BST_TREE* tree,ifstream &infile){
    initialize(tree,infile);
    int command;
    while(1){
        menu();
        cin>>command;
        cout<<"================================="<<endl;
        if(command == 5) break;
        else{
            switch(command){
                case 1:
                    BST_Search(tree);
                    break;
                case 2:
                    insert_list(tree);
                    break;
                case 3:
                    delete_list(tree);
                    break;
                case 4:
                    BST_Traverse(tree,printBST);
                    break;
                default:
                    cout<<"wrong input, please input again"<<endl;
                    break;
            }
        }
    cout<<"================================="<<endl;
    }
    BST_Destroy(tree);
}

int main()
{
    ifstream infile;
    BST_TREE* tree;
    tree = BST_Create(compare);
    infile = readfile();
    operate(tree,infile);
    return 0;
}
