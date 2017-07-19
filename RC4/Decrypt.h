#include "Header.h"
#include "RC4.h"
void Decrypt(){
    char * toDecrypt_filename=new char[100];
    char * key_filename=new char[100];
    int cnt=0;
    char ch;
    getchar();
    while ((ch=getchar()) != '\n'){
    toDecrypt_filename[cnt++]=ch;
    }
    if(cnt==0){
       toDecrypt_filename="../密文.txt";
    }
    cout<<"输入密钥流所在的文件名(请放在相同目录下，若不输入则默认为“key.txt”文件)"<<endl;
    cnt=0;
    while ((ch=getchar()) != '\n'){
    key_filename[cnt++]=ch;
    }
    if(cnt==0){
       key_filename="../key.txt";
    }
    const char * Decrypted_filename="../已解密.txt";
    char *Encrypted_data,*key_stream,*Decrypted_data;
    long long size;
//读取密文
     ifstream in (toDecrypt_filename, ios::in|ios::ate|ios::binary);  
        if (! in.is_open()) { 
            cout << "找不到要解密的txt文件，请将密文保存至C++可执行文件相同目录下的 密文.txt"<<endl; 
            exit (1); 
       }  
        size = in.tellg();  
        in.seekg (0, ios::beg);  
        Encrypted_data=new char[size];
        Decrypted_data=new char[size];
        in.read (Encrypted_data, size);  
        in.close();  
//读取密钥流文件
         ifstream key_in (key_filename, ios::in|ios::ate|ios::binary);  
        if (! key_in.is_open()) { 
            cout << "找不到密钥所在txt文件，请将密钥流字符保存至C++可执行文件相同目录下的 key.txt"<<endl; 
            exit (1); 
       }  
        size = key_in.tellg();  
        key_in.seekg (0, ios::beg);  
        key_stream=new char[size];
        key_in.read (key_stream, size);  
        key_in.close();  
        
        RC4 temp=RC4();
        Decrypted_data=temp.deRC4(key_stream,Encrypted_data);
    ofstream out(Decrypted_filename,ios::out|ios::binary);
    if(out.is_open()){
        out.seekp(0,ios::beg);
        out<<Decrypted_data;
         out.close();
         cout<<"解密后的文件成功保存至相同目录下的 已解密.txt文件～"<<endl;
    }
    delete []Encrypted_data;
    delete []Decrypted_data;
}