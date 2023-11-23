#include<iostream>
#include<queue>
#include<cstring>
#include<map>
#include<fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include<unordered_map>
using namespace std;

class Decompressor{
    string file_name;

    unordered_map<string,char>dictionary_code_to_data;
    unordered_map<char,string>dictionary_data_to_code;
    string code;

    char* Encode=new char[100000000];
    public:
    Decompressor(string file_name);
    void decode();
    void read_dic();
    
};