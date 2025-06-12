#include <iostream>
#include <string>

int main()
{
    std::string* teto = new std::string;
    *teto = "teto";
    std::cout << *teto << std::endl;
    return 0;
}