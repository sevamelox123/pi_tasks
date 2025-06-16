// 92
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class depacker
{
private:
    std::string *teto;

public:
    depacker(std::string str);
    depacker(depacker &other);
    depacker &operator=(depacker &other);
    depacker(depacker &&other);
    depacker &operator=(depacker &&other);
    ~depacker();
    string depack() const;
    void s_print();
};

int main()
{
    std::ifstream input("teto.txt");
    std::ofstream output("oteto.txt");
    string in;
    input >> in;
    depacker teto(in);
    int counter = 0;
    for (char ch : teto.depack())
    {
        output << ch;
        if (++counter % 40 == 0)
        {
            output << '\n';
        }
    }

    input.close();
    output.close();
    return 0;
}

depacker::depacker(std::string str){
    teto = new string;
    *teto = str;
}

depacker::depacker(depacker &other) : teto(other.teto)
{
}

depacker &depacker::operator=(depacker &other)
{
    if (this != &other)
    {
        teto = other.teto;
    }
    return *this;
}

depacker::depacker(depacker &&other) : teto(other.teto)
{
    delete other.teto;
}

depacker &depacker::operator=(depacker &&other)
{
    if (this != &other)
    {
        teto = other.teto;
        delete other.teto;
    }
    return *this;
}

depacker::~depacker()
{
    delete teto;
}

string depacker::depack() const
{
    string new_str;
    for (std::size_t i = 0; i < teto->size(); i++)
    {
        int num;
        if (isdigit((*teto)[i]) && (isupper((*teto)[i+1]) && i + 2 < teto->size()))
        {
            num = (*teto)[i] - '0' - 1;
            for (size_t j = 0; j < num; j++)
            new_str += (*teto)[i+1];
        }
        else if (isdigit((*teto)[i]) && (isdigit((*teto)[i+1]) &&  isupper((*teto)[i+2]) &&  i + 3 < teto->size()))
        {
            num = ((*teto)[i] - '0') * 10 + ((*teto)[i+1] - '0') - 1;
            for (size_t j = 0; j < num; j++)
            new_str += (*teto)[i+2];
            i++;
        }
        else if(isupper((*teto)[i]))
        {
            new_str += (*teto)[i];

        } else{
            new_str += '0';
            break;
        }
    }
    return new_str;
}

void depacker::s_print()
{
    cout << *teto << endl;
}
