#include<iostream>
#include<queue>
#include<cstring>
#include<map>
#include<fstream>
using namespace std;

class Huffman{
    char* data_st;
    char* data_end;
    int data_size;
    char* Encode=new char[1000000];
    const int maxn=10000;
    // int* vis=new int[maxn]{};
    // string* dictionary_data_to_code=new string[maxn]{};
    // map<string,char>dictionary_code_to_data;
    map<char,int>vis;
    map<string,char>dictionary_code_to_data;
    map<char,string>dictionary_data_to_code;
    string code_res;

    struct node{
        node* lson;
        node* rson;
        char data;
        int freq;
        node(node* x,node* y,char z,int f){
            this->lson=x;
            this->rson=y;
            this->data=z;
            this->freq=f;
        };
        bool operator <(const node* x)const {
                return this->freq<x->freq;
        }
    };
    node* root;
    priority_queue<node*> q;

    public:
    Huffman(char* dt_st,char* dt_end);

    void init();

    void build_tree();

    void build_code(node* x,string code);

    string encode();

    pair<char*,int> decode(string code);

};
