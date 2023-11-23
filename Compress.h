#include<iostream>
#include<queue>
#include<cstring>
#include<map>
#include<fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
using namespace std;

class Compressor{
    char* data_st;
    char* data_end;
    int data_size;
    // string code_res;
    char* code_res=new char[500000000];
    char* Encode=new char[1000000];
    int Encode_size;
    int ctd_size;
    int dtc_size;


    map<char,int>vis;
    map<string,char>dictionary_code_to_data;
    map<char,string>dictionary_data_to_code;

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
        // bool operator < (const node& x) const{
        //     return freq>x.freq;
        // }
    };

    struct compnode{
        bool operator()(node* x,node* y){
            return x->freq>y->freq;
        }
    };

    string file_name;

    node* root;
    priority_queue<node*,vector<node*>,compnode> q;

    public:

    Compressor(char* dt_st,char* dt_end,string file_name);

    void init();

    void build_tree();

    void build_code(node* x,string code);

    void encode();

    void write_dictionary();

    void compute_compress_rate();

};