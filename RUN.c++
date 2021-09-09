#include <iostream>
#include <windows.h>
using namespace std;


//UTF-8到GB2312的转换
char* U2G(const char* utf8)
{
int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
wchar_t* wstr = new wchar_t[len+1];
memset(wstr, 0, len+1);
MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
char* str = new char[len+1];
memset(str, 0, len+1);
WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
if(wstr) delete[] wstr;
return str;
}

int main(int argc,char *argv[]) 
{
    string str = U2G(argv[1]);
    str = "\"" + str + "\"";
    int n = system(str.data());
    cout << "_____________________________________" << endl;
    cout << "Process exited with return value : ";
	cout << n << endl;
    system("pause");
    return 0;
}
