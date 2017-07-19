#include "Header.h"
void Encrypt(){
    char *toEncrpt_filename=new char [100];
    int cnt=0;
    char ch;
    getchar();
    while ((ch=getchar()) != '\n'){
    toEncrpt_filename[cnt++]=ch;
    }
    if(cnt==0){
        toEncrpt_filename="../明文.txt";
    }
    const char * Encrpted_filename="../密文.txt";
    const char * key_filename="../key.txt";
    char * key="568302203";
char *buffer,*Encrypted_data,*key_stream;
    long long size;
     ifstream in (toEncrpt_filename, ios::in|ios::ate|ios::binary);  
        if (! in.is_open()) { 
            cout << "找不到要加密的txt文件，请将想要加密的文字保存至C++可执行文件相同目录下的 明文.txt"<<endl; 
            exit (1); 
       }  
        size = in.tellg();  
        in.seekg (0, ios::beg);  
        buffer = new char [size];
        Encrypted_data=new char[size];
        key_stream=new char[size];
        in.read (buffer, size);  
        in.close();  
        RC4 rc4=RC4(key,buffer);
        Encrypted_data=rc4.get_encrypted_data(false);
        key_stream=rc4.get_K_stream(false);
    ofstream out(Encrpted_filename,ios::out|ios::binary);
    if(out.is_open()){
        out.seekp(0,ios::beg);
        out<<Encrypted_data;
         out.close();
          cout<<"加密后的文件成功保存至相同目录下的 密文.txt文件～"<<endl;
    }
     ofstream key_out(key_filename,ios::out|ios::binary);
    if(key_out.is_open()){
        key_out.seekp(0,ios::beg);
        key_out<<key_stream;
         key_out.close();
         cout<<"用于解密的密钥流成功保存至相同目录下的 key.txt文件～"<<endl;
    }
    delete []buffer;
    delete []Encrypted_data;
}