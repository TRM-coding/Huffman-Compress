#include"Compress.h"
using namespace std;
Compressor::Compressor(char*dt_st,char*dt_end,string file_name)
{
    this->file_name=file_name;
    cout<<"start init";
    while(!q.empty())
        q.pop();
    data_st=dt_st;
    data_end=dt_end;
    data_size=data_end-data_st+1;
    root=NULL;
    init();
    build_tree();
    build_code(NULL,"");
    cout<<"init finished!!!"<<endl;
}

void Compressor::init()
{
    
    cout.flush();
    vis.clear();
    dictionary_code_to_data.clear();
    dictionary_data_to_code.clear();

    for(int i=0;data_st+i<=data_end;i++)
    {
        if(i%(data_size/10)==0)
            cout<<".";
        if(vis.find(data_st[i])!=vis.end())
            vis[data_st[i]]++;
        else
            vis[data_st[i]]=1;
    }

    for(int i=0;i<256;i++)
    {
        if(vis.find(i)!=vis.end())
        {
            node*tmp=new node(NULL,NULL,i,vis[i]);
            q.push(tmp);
            
        }
    }
}

void Compressor::build_tree()
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
    root=q.top();
}


void Compressor::build_code(node* x,string code)
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

void Compressor::encode()//need change.
{
    cout<<"Start encoding";
    int ctt=0;
    for(int i=0;i+data_st<=data_end;i++){
        if(ctt>800000000){
            cout<<"Error:code too long!!!compress failed......"<<endl;
            return;
        }
        memccpy(code_res+ctt,dictionary_data_to_code[data_st[i]].c_str(),0,strlen(dictionary_data_to_code[data_st[i]].c_str())); 
        ctt+=strlen(dictionary_data_to_code[data_st[i]].c_str());
        if(i%((data_end-data_st)/10)==0){
            cout<<".";
        }
    }
    cout<<endl;
    cout<<"Encoding finished!!!"<<endl;
    return;
}

void Compressor::write_dictionary()
{
    cout<<"Start writing dictionary file";
    int psp=0;
    for(int i=0;i<=file_name.size();i++)
        if(file_name[i]=='/'||file_name[i]=='\\'){psp=i;}
    if(psp!=0)file_name=file_name.substr(psp+1,file_name.size()-psp-1);
    if(!opendir((file_name+"_compress").c_str()))mkdir((file_name+"_compress").c_str());


    ofstream dtcof(file_name+"_compress/"+file_name+".dct");
    dtcof<<dictionary_code_to_data.size()<<"\n";
    for(auto x:dictionary_code_to_data)
    {

        // if((x-dictionary_code_to_data.begin())%((dictionary_code_to_data.end()-dictionary_code_to_data.begin())/20)==0)
        //     cout<<".";
        dtcof<<x.first<<" "<<(int)x.second<<"\n";
    }
    int dic_size;
    dtcof.seekp(0,ios::end); dic_size=dtcof.tellp(); dtcof.seekp(0,ios::beg); 
    dtcof.close();

    ofstream out(file_name+"_compress/"+file_name+".huf");
    out<<strlen(code_res)%8;
    out.close();
    out.open(file_name+"_compress/"+file_name+".huf",ios::app|ios::binary);
    int ctt=0;
    char tmp=0;
    int lne=strlen(code_res);
    for(int i=0;i<lne;i++){
        if(i%((lne)/10)==0){
            cout<<".";
        }
        tmp=tmp<<1;
        if(code_res[i]=='1')tmp=tmp|1;
        ctt++;
        if(ctt==8){
            out<<tmp;
            ctt=0;
            tmp=0;
        }
    }
    if(ctt!=0){
        tmp=tmp<<(8-ctt);
        out<<tmp;
    }
    int code_size;
    out.seekp(0,ios::end); code_size=out.tellp(); out.seekp(0,ios::beg);
    out.close();
    cout.flush();
    cout<<"writing dictionary finished!!!"<<endl;
    cout<<endl;
    cout<<"Compressed Code Size:"<<code_size<<" KB"<<endl;
    cout<<"compress rate:"<<1.0*(code_size+dic_size)/data_size*100<<"%"<<endl;
    return ;
}

void Compressor::compute_compress_rate(){
    ifstream ctdif(file_name+".huf");
    ctdif.seekg(0,ios::end); Encode_size=ctdif.tellg(); ctdif.seekg(0,ios::beg);
    ctdif.close();

    ctdif.open(file_name+".ctd");
    ctdif.seekg(0,ios::end); ctd_size=ctdif.tellg(); ctdif.seekg(0,ios::beg);
    ctdif.close();


    cout<<"compress rate:"<<1.0*(ctd_size+dtc_size+Encode_size)/data_size*100<<"%"<<endl;
}
