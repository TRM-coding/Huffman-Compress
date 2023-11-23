#include "Huffman.h"
using namespace std;

//提供压缩文本的起始地址和结束地址以构建哈夫曼树
Huffman::Huffman(char*dt_st,char*dt_end)
{
    cout<<"start init........."<<endl;
    while(!q.empty())
        q.pop();
    data_st=dt_st;
    data_end=dt_end;
    data_size=data_end-data_st+1;
    root=NULL;
    // memset(dictionary_data_to_code,0,sizeof(dictionary_data_to_code));
    init();
    build_tree();
    build_code(NULL,"");
    cout<<"init finished!!!"<<endl;
}
void Huffman::init()
{
    
    cout.flush();
    vis.clear();
    dictionary_code_to_data.clear();
    dictionary_data_to_code.clear();
    code_res="";
    for(int i=0;data_st+i<=data_end;i++)
    {
        if(vis.find(data_st[i])!=vis.end())
            vis[data_st[i]]++;
        else
            vis[data_st[i]]=1;
    }
    cout<<endl;
    for(int i=-129;i<129;i++)
    {
        if(vis.find(i)!=vis.end())
        {
            node*tmp=new node(NULL,NULL,i,vis[i]);
            q.push(tmp);
        }
    }
}
void Huffman::build_tree()
{
    while(q.size()>1)
    {
        node*x1=q.top();
        q.pop();
        node*x2=q.top();
        q.pop();
        node*tmp=new node(x1,x2,x1->data,x1->freq+x2->freq);
        q.push(tmp);
    }
    root=new node(q.top(),NULL,q.top()->data,q.top()->freq);
}

void Huffman::build_code(node* x,string code)
{
    if(x==NULL)x=root;
    if(x->lson==NULL&&x->rson==NULL)
    {
        dictionary_data_to_code.insert(make_pair(x->data,code));
        dictionary_code_to_data.insert(make_pair(code,x->data));
        return;
    }
    if(x->lson !=NULL)
        build_code(x->lson,code+"0");
    if(x->rson !=NULL)
        build_code(x->rson,code+"1");
}
//返回压缩后的字符串
string Huffman::encode()
{
    cout<<"start encoding";
    for(int i=0;i+data_st<=data_end;i++){
        
        code_res=code_res+dictionary_data_to_code[data_st[i]];
        if(i%((data_end-data_st)/10)==0){
            cout<<".";
        }
    }
    cout<<endl;
    cout<<"encoding finished!!!"<<endl;
    return code_res;
}
//提供要解压的哈夫曼编码的字符串，返回解压后的字符串
pair<char*,int> Huffman::decode(string code)
{
    int ctt=0;
    cout<<"start decoding";
    int l=-1,r=0;
    string this_code="";
    string ans="";
    int lth=code.length();
    while(r<lth)
    {
        if(r%(lth/10)==0){
            cout<<".";
        }
        this_code.push_back(code[r]);
        if(dictionary_code_to_data.find(this_code)!=dictionary_code_to_data.end())
        {
            Encode[++ctt]=dictionary_code_to_data[this_code];
            this_code="";
            l=r-1;
            // if()
        }
        r++;
    }
    cout<<"decoding finished!!!"<<endl;
    return make_pair(Encode,ctt);
}
