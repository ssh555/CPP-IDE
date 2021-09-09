#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
    int n = system(argv[1]);
    cout << "_____________________________________" << endl;
    cout << "Process exited with return value : " + n << endl;
    system("pause");
    return 0;
}
