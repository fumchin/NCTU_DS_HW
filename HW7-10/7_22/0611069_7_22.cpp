#include <iostream>
#include <string>
#include <fstream>
#include "P7-BST-ADT.h"
using namespace std;

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
    infile.open("7_22.txt");
    if(!infile){
        cout<<"fail to open file"<<endl;
    }
    else{
        return infile;
    }
}

void operate(){
    int command;
    while(1){
        menu();
        cin>>command;
        if(command == 5) break;
        else{
            switch(command){
                case 1:
                    search_list();
                    break;
                case 2:
                    insert_list();
                    break;
                case 3:
                    delete_list();
                    break;
                case 4:
                    print_list();
                    break
                default:
                    cout<<"wrong input, please input again"<<endl;
                    break;
            }
        }
    }
}

int main(){
    ifstream infile;
    BST
    infile = readfile();
    create_tree(infile);
    operate();
}
