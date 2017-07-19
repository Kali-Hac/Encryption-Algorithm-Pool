#include "Header.h"
#include "Decrypt.h"
#include "Encrypt.h"
int main(int argc, char **argv)
{   int choose;
    char file[100];
    while(true){
        cout<<"[CR4加密算法]"<<endl<<"加密请输入1,解密请输入2"<<endl;
        cin>>choose;
        switch(choose){
         case 1:
            cout<<"输入要加密的文件名(请放在相同目录下，若不输入则默认为“明文.txt”文件)"<<endl;
            Encrypt();
            break;
        case 2:
            cout<<"输入要解密的文件名(请放在相同目录下，若不输入则默认为“密文.txt”文件)"<<endl;
            Decrypt();
            break;
        }
        cout<<"-------------------------------------------------------------"<<endl;
    }
    return 0;
}
