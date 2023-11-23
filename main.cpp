#include"Compress.h"
#include"Decompress.h"
#include<chrono>
#include<thread>
using namespace std;

void show_start()
{
    int slept=350;
    cout<<"========================================================="<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|                                                       |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|                                                       |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|                                                       |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|      welcome! this is Huffman Compress System         |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|                                                       |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|                                                       |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|                                       author: @Tarime |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"========================================================="<<endl;
}

void show_list()
{
    int slept=50;
    cout<<"========================================================="<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|command list:                                          |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|dircp: show file Supported for compressed files        |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|dirdcp: show file Supported for decompressed files     |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|compress <filename.***>  :Compress a file              |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|decompress <filename.***>  :Decompress a file          |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|list  : show this list again                           |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"|exit  : exit the system                                |"<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(slept));
    cout<<"========================================================="<<endl;
}


void Cp(string filename)
{
    cout<<filename<<endl;
    char* org_data=new char[100000000];//最多100M
    ifstream iff(filename,ios::binary);
    if(!iff)
    {
        cout<<"file not found!"<<endl;
        return;
    }
    iff.seekg(0,ios::end); int size=iff.tellg(); iff.seekg(0,ios::beg);
    iff.read(org_data,size);
    cout<<"Accepted file size:"<<size<<" KB"<<endl;
    Compressor cp=Compressor(org_data,org_data+size-1,filename);
    
    cp.encode();
    cp.write_dictionary();

    cout<<"compress file is in folder:"<<filename+"_compress"<<endl;
    // cp.~Compressor();
}

void Dcp(string filename){
    Decompressor dcp=Decompressor(filename);
    dcp.read_dic();
    dcp.decode();

    // dcp.~Decompressor();
    cout<<"decompress file is in folder:"<<filename+"_decompress"<<endl;
}

int main(){
    show_start();
    show_list();
    string ip;
    cout<<">>";
    while(1){
        cin>>ip;
        if(ip=="compress"){
            string filename;
            cin>>filename;
            Cp(filename);
        }
        else if(ip=="dircp"){
            cout<<"============================================"<<endl;
            system("dir /s");
            cout<<"============================================"<<endl;
        }
        else if(ip=="dirdcp")
        {
            cout<<"============================================"<<endl;
            cout<<"Please remain not to input \".huf\" or \".dct\" in your commands "<<endl<<endl;
            system("dir /s *.huf");
            system("dir /s *.dct");
            cout<<"============================================"<<endl;
        }
        else if(ip=="decompress"){
            string filename;
            cin>>filename;
            Dcp(filename);
        }
        else if(ip=="list"){
            show_list();
        }
        else if(ip=="exit"){
            cout<<"bye bye!"<<endl;
            break;
        }
        else{
            cout<<"wrong command!"<<endl;
        }
        cout<<endl<<">>";
    }
    
    system("pause");
}