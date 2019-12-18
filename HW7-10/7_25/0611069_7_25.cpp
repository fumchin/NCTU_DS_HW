//1. fist construct binary tree layer by layer and input at L.162
//2. construct preorder threaded binary tree
//3. traverse by threaded

#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef struct node{
    char c;
    struct node* right;
    struct node* left;
    bool rightThread;
}NODE;

typedef struct{
    int count;
    NODE* root;
}BT;

BT* createBT(){
    BT *tree = new BT;
    tree->count = 0;
    tree->root = nullptr;
    return tree;
}

NODE* createNode(char input){
    NODE* new_node = new NODE;
    new_node->c = input;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->rightThread=false;
}

void LevelOrderConstruct(BT* tree,string &str){
    char c;
    int i=0;
    queue<NODE*> q;
    NODE* current;
    NODE* new_node;
    c = str[i];
    new_node = createNode(c);
    tree->root = new_node;
    i++;
    tree->count++;
    current = tree->root;
    while(i<str.length()){
        if(str[i]!='x'){
            NODE* new_node;
            c = str[i];
            new_node = createNode(c);
            //cout<<new_node->c<<"\t";
            current->left = new_node;
            tree->count++;
            q.push(new_node);
        }

        i++;
        if(i>=str.length()) break;

        if(str[i]!='x'){
            NODE* new_node;
            c = str[i];
            new_node = createNode(c);
            current->right = new_node;
            q.push(new_node);
            tree->count++;
        }
        current = q.front();
        q.pop();
        i++;
    }
}
void toThread(NODE* root){
    if(root->left!=nullptr && root->right!=nullptr){
        NODE* temp1 = root->left;
        NODE* temp2 = root->right;
        while(temp1->right!=nullptr){
            temp1 = temp1->right;
        }
        if(temp1->left!=nullptr){
            temp1 = temp1->left;
        }
        if(temp1->rightThread==false){
            temp1->right = temp2;
            temp1->rightThread = true;
        }
    }
    return;
}


void ThreadTraverse(NODE* root){
    //construct preorder threaded
    if(root){
        toThread(root);
        ThreadTraverse(root->left);
        if(root->rightThread==false){
            ThreadTraverse(root->right);
        }
    }
    return;
}

void Preorder(NODE* root){
    if(root){
        cout<<root->c;;
        Preorder(root->left);
        Preorder(root->right);
    }
    return;
}
void ThreadPreorder(NODE* root){
    if(root){
        cout<<root->c;;
        ThreadPreorder(root->left);
        if(root->rightThread == true){
            ThreadPreorder(root->right);
        }
    }
    return;
}

void initialize(BT* tree){
    string str="ACEBD";
    LevelOrderConstruct(tree,str);
    //cout<<tree->root->left->c<<endl;
}



int main(){
    //create tree;
    BT* tree;
    tree  = createBT();
    initialize(tree);
    cout<<"normal preorder: ";
    Preorder(tree->root);
    cout<<endl;
    ThreadTraverse(tree->root);
    cout<<"================="<<endl;
    cout<<"threaded: ";
    ThreadPreorder(tree->root);
    cout<<endl;
}
