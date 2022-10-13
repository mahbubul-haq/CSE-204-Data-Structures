#include<iostream>
#include<queue>
using namespace std;

class Nodes{
public:
    char data;
    int freq;
    Nodes *left, *right;

    Nodes(char data, int freq){
        left=right=NULL;
        this->data=data;
        this->freq=freq;
    }
};

class compare{
public:
    bool operator()(Nodes *l,Nodes *r){
        return l->freq > r->freq;
    }
};

void printCodes(Nodes *root, string str){

    if(root==NULL) return;

    if(root->data!='0'){
        cout<<root->data<<": "<<str<<endl;
    }

    printCodes(root->left,str+"0");
    printCodes(root->right,str+"1");

}

void huffManCodes(char data[], int freq[], int size){

    Nodes *left, *right, *top;

    priority_queue< Nodes*, vector<Nodes*>, compare> huffManTree;

    for(int i=0;i<size;i++){
        huffManTree.push(new Nodes(data[i],freq[i]));
    }

    while(huffManTree.size()!=1){


        left=huffManTree.top();
        huffManTree.pop();
        right=huffManTree.top();
        huffManTree.pop();

        top=new Nodes('0',left->freq+right->freq);
        top->left=left;
        top->right=right;

        huffManTree.push(top);

    }

    printCodes(huffManTree.top(),"");

}


int main()
{
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };

    int size = sizeof(arr) / sizeof(arr[0]);

    huffManCodes(arr, freq, size);


    return 0;
}
