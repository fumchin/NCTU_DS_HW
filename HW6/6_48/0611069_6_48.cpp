#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct node{
    char c;
    int weight;
    string code;
    struct node* leftNode;
    struct node* rightNode;
}Node;

Node* createNode(char c_input,int weight_input){
    Node* new_node = new Node;
    new_node->c = c_input;
    new_node->weight = weight_input;
    new_node->code = "";
    new_node->leftNode = nullptr;
    new_node->rightNode = nullptr;
    return new_node;
}

Node* copyNode(Node* in){
    Node* p = new Node;
    p = in;
    p->weight = in->weight;
    p->code = in->code;
    p->leftNode = in->leftNode;
    p->rightNode = in->rightNode;
    return p;
}

void initial(vector<Node*> &list){
    list.push_back(createNode('A',7));
    list.push_back(createNode('B',2));
    list.push_back(createNode('C',2));
    list.push_back(createNode('D',3));
    list.push_back(createNode('E',11));
    list.push_back(createNode('F',2));
    list.push_back(createNode('G',2));
    list.push_back(createNode('H',6));
    list.push_back(createNode('I',6));
    list.push_back(createNode('J',1));
    list.push_back(createNode('K',1));
    list.push_back(createNode('L',4));
    list.push_back(createNode('M',3));
    list.push_back(createNode('N',7));
    list.push_back(createNode('O',9));
    list.push_back(createNode('P',2));
    list.push_back(createNode('Q',1));
    list.push_back(createNode('R',6));
    list.push_back(createNode('S',6));
    list.push_back(createNode('T',8));
    list.push_back(createNode('U',4));
    list.push_back(createNode('V',1));
    list.push_back(createNode('W',2));
    list.push_back(createNode('X',1));
    list.push_back(createNode('Y',2));
    list.push_back(createNode('Z',1));
}


//create new root
void hufTree(vector<Node*> &list,int index1,int index2){
    Node* new_node = new Node;
    Node* p = new Node;
    Node* q = new Node;
    p = copyNode(list[index1]);
    q = copyNode(list[index2]);
    new_node->weight = p->weight + q->weight;
    new_node->leftNode = q;
    new_node->rightNode = p;
    new_node->c = '*';
    list.push_back(new_node);
    if(index1 > index2){
        list.erase(list.begin()+index1);
        list.erase(list.begin()+index2);
    }
    else{
        list.erase(list.begin()+index2);
        list.erase(list.begin()+index1);
    }

}

void build_tree(vector<Node*> &list){
    //find two min numbers
    int index1,index2;
    int min;
    while(list.size() > 1){
        min = list[0]->weight;
        index1 = 0;
        index2 = 1;
        for(int i=1;i<list.size();i++){
            if(list[i]->weight <= min){
                index2 = index1;
                index1 = i;
                min = list[i]->weight;
            }
            else if(list[i]->weight <= list[index2]->weight){
                index2 = i;
            }
        }
        hufTree(list,index1,index2);
    }
}
void huf_encode(Node* p){
    if(p->leftNode != nullptr){
        p->leftNode->code = p->code + "0";
        huf_encode(p->leftNode);
    }
    if(p->leftNode==nullptr && p->rightNode==nullptr){
        cout<<p->c<<"\t"<<p->weight<<"\t"<<p->code<<endl;
    }
    if(p->rightNode != nullptr){
        p->rightNode->code = p->code + "1";
        huf_encode(p->rightNode);
    }
}

void find_code(Node* p,char target,string &result_code){
    //left
    if(p->leftNode==nullptr && p->rightNode==nullptr){
        if(p->c == target){
            result_code = result_code + p->code;
        }
    }
    else if(p!=nullptr){
        find_code(p->leftNode,target,result_code);
        //cout<<p->c<<"\t"<<p->weight<<"\t"<<p->code<<endl;
        find_code(p->rightNode,target,result_code);
    }
}

//put 0 on left node, 1 on right node
string encode(Node* p,string &input){
    string result_code = "";
    int i=0;
    while(input[i] != '\0'){
        find_code(p,input[i],result_code);
        i++;
    }
    return result_code;
}

//traverse and find character
string decode(Node* p,string &result_code){
    string result_decode = "";
    int i=0;
    Node* temp = new Node;
    temp = p;
    while(result_code[i]!='\0'){
        if(result_code[i] == '0'){
            temp = temp->leftNode;
        }
        else if(result_code[i] == '1'){
            temp = temp->rightNode;
        }
        if(temp->leftNode==nullptr && temp->rightNode==nullptr){
            result_decode+=temp->c;
            temp = p;
        }
        i++;
    }
    result_decode+='\0';
    delete temp;
    return result_decode;
}

int main(){
    vector <Node*> list;
    initial(list);
    build_tree(list);
    Node* p = new Node;
    p = list[0];
    huf_encode(p);
    string input;
    string result_code="";
    string result_decode="";
    p = list[0];
    //encode
    cout<<"======================================"<<endl;
    cout<<"input text: "<<endl;
    cin>>input;
    cout<<"user's input: "<<input<<endl;
    result_code = encode(p,input);
    cout<<"Huffman_Encoding: "<<result_code<<endl;
    p = list[0];
    //decode
    result_decode = decode(p,result_code);
    cout<<"Huffman_Decoding: "<<result_decode<<endl;
    delete p;
    return 0;
}
