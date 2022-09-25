#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    string s = "ABCD";
    int arr[4] = {};
    arr[2] = 1;
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        cout<<arr[i];
    }
    
    cout << s.size();
    return 0;
}
