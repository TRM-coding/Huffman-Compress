#include "Decompress.h"
using namespace std;
void Decompressor::decode()
{
    int ctt=0;
    cout<<"start decoding";
    int r=0;
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
        }
        r++;
    }
    cout<<endl;
    const char* tmp=new char[file_name.size()+1+11];
    strcpy((char*)tmp,(file_name+"_decompress").c_str());
    if(!opendir(tmp))mkdir(tmp);

    ofstream off(file_name+"_decompress/"+file_name,ios::binary);

    // ofstream off(file_name+".dcp");
    for(int i=1;i<=ctt;i++)off<<Encode[i];
    off.close();
    cout<<"decoding finished!!!"<<endl;

    
    return;
}

Decompressor::Decompressor(string file_name)
{
    this->file_name=file_name;
    dictionary_code_to_data.clear();
    dictionary_data_to_code.clear();
}

void Decompressor:: read_dic(){
    ifstream iff(file_name+"_compress/"+file_name+".dct");
    cout<<"start loading dictionary";
    if(!iff.is_open())
    {
        cout<<"file not found!"<<endl;
        return;
    }
    string* x1=new string;
    int x2;
    iff.seekg(0,ios::beg);
    int inputsize=0;
    iff>>inputsize;
    int tpcnt=inputsize;
    while(inputsize--){
        if(inputsize%(tpcnt/5)==0)cout<<".";
        iff>>*x1>>x2;
        dictionary_code_to_data.insert(make_pair(*x1,(unsigned char)x2));
        dictionary_data_to_code.insert(make_pair((unsigned char)x2,*x1));
        // cout<<*x1<<" "<<x2<<endl;
        // system("pause");
    }
    iff.close();

    iff.open(file_name+"_compress/"+file_name+".huf",ios::binary);
    if(!iff.is_open())
    {
        cout<<"file not found!"<<endl;
        return;
    }
    int end00=0;
    iff.seekg(0,ios::end); int sizeofecd=iff.tellg(); iff.seekg(0,ios::beg);
    iff>>end00;
    for(int i=0;i<sizeofecd;i++){
        char tmp;
        if(i%(sizeofecd/5)==0)cout<<".";
        iff.read(&tmp,1);
        for(int j=0;j<8;j++){
            if((tmp&(1<<(7-j)))!=0)code.push_back('1');
            else code.push_back('0');
        }
    }
    cout<<endl;
    code=code.substr(0,code.length()-end00);
    // cout<<code<<endl;
    iff.close();
    cout<<"dictionary load finished!!!"<<endl;
    return;
}