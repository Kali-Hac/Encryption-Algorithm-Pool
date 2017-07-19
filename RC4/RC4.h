#include "Header.h"
class RC4{
private:
    unsigned char S[256];//状态向量 
    unsigned char T[256];//临时向量
    unsigned char K[256];//密钥
    unsigned char K_stream[256];//密钥流
    int data_len;//明文数据长度
    char *encrypted_data;
 
public:
   RC4(){
    }
    
    RC4(char *key,char *data){
        data_len=strlen((char*)data);
        int length=strlen(key);
        for(int i=0;i<length&&i<256;i++){
            K[i]=key[i];
        }
        for(int i=0;i<256;i++){
            S[i]=i;
            T[i]=K[i%length];
        }
        create_k_stream();
        encrypted_data=enRC4(data);
//        cout<<"明文：";
//        for(int i=0;i<strlen(data);i++){
//            cout<<data[i];
//        }
//        cout<<endl;
//        cout<<"密钥：";
//        get_Key(true);
//        cout<<"密钥流：";
//        get_K_stream(true);
//        cout<<"密文：";
//        get_encrypted_data(true);
    }
    void create_k_stream();//由密钥产生密钥流
    void random_S();// 初始排列状态向量S，供keyStream方法调用 
   char* enRC4(char *data); //用制定密钥给明文加密并返回密钥流
   char* deRC4(char *data,char *k_stream);//通过密钥流解密
   char* get_K_stream(bool);//获取密钥流
   char* get_Key(bool);//获取密钥
   char* set_Key(char *);
   char* get_encrypted_data(bool);
};
void RC4::random_S(){
    int j=0;
    for(int i=0;i<256;i++){
        j=(j+S[i]+T[i])%256;
        swap(S[j],S[i]);
    }
}

void RC4::create_k_stream(){
    random_S();
    int j=0,i=0,t,len=data_len;
    int cnt=0;
    while(len--){
        i=(i+1)%256;
        j=(j+S[i])%256;
        swap(S[i],S[j]);
        t=(S[i]+S[j])%256;
        K_stream[cnt++]=S[t];
    }
}
char* RC4::get_K_stream(bool flag){
    if(strlen((char *)K_stream)==0){
        cout<<"请先设置密钥"<<endl;
        return NULL;
    }
    if(flag){
        for(int i=0;i<strlen((char*)K_stream);i++){
            cout<<K_stream[i];
        }
        cout<<endl;
    }
    return (char *)K_stream;
}
char* RC4::get_Key(bool flag){
         if(strlen((char*)K)==0){
            cout<<"请先设置密钥"<<endl;
            return NULL;
        }
    if(flag){
        for(int i=0;i<strlen((char *)K);i++){
            cout<<K[i];
        }
        cout<<endl;
    }
    return (char *)K;
}
char* RC4::enRC4(char *data){
    if(strlen((char *)K)==0){
        cout<<"请先输入密钥"<<endl;
        return NULL;
    }
    encrypted_data=new  char[data_len];
    for(int i=0;i<data_len;i++){
        encrypted_data[i]=(data[i]^K_stream[i]);
    }
    return encrypted_data;
}
char* RC4::deRC4(char *k_stream,char *data){
    ofstream out("../process.txt",ios::out|ios::binary);
    int length=strlen(data);
    char *decrypted_data=new char[length];
    for(int i=0;i<length;i++){
        decrypted_data[i]=(unsigned char)(data[i]^k_stream[i]);
        out<<data[i]<<" ^ "<<k_stream[i]<<" = "<<decrypted_data[i]<<endl;
    }
    cout<<"解密(异或)过程已成功保存至process.txt文件～"<<endl;
    return decrypted_data;
}
char* RC4::set_Key(char *key){
    int length=strlen(key);
        for(int i=0;i<length&&i<256;i++){
            K[i]=key[i];
        }
        for(int i=0;i<256;i++){
            S[i]=i;
            T[i]=K[i%length];
        }
            create_k_stream();
            return (char*)K;
}
char* RC4::get_encrypted_data(bool flag){
    if(flag){
        for(int i=0;i<strlen(encrypted_data);i++){
            cout<<encrypted_data[i];
        }
        cout<<endl;
    }
    return encrypted_data;
}