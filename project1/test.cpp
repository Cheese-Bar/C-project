#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char const *argv[])
{
struct Person{

    bool male;

    int id;

    char label;

};

 std::cout << sizeof(struct Person);
}
