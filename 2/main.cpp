#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
// 28
// using namespace std;

std::map<char, char> tmap = {{'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'}};

class DNA
{
private:
    std::string sequence;
    // std::map<char, char> mpp;

public:
    DNA() = default;
    DNA(const std::string &seq);
    DNA &operator=(DNA &other);
    DNA(DNA &other);
    DNA(DNA &&other) noexcept;
    DNA &operator=(DNA &&other) noexcept;
    ~DNA();
    std::string getReverse() const;
    void print();
    bool isPoli() const;
};
int main()
{
    std::ifstream input("teto.txt");
    std::ofstream output("oteto.txt");
    std::size_t size = 0;

    std::string sec;
    input >> size >> sec;
    if (size != sec.size())
    {
        input.close();
        output.close();
        throw std::runtime_error("size is not equal to string size");
    }
    DNA dna(sec);
    dna.print();

    if (dna.isPoli())
        output << "Yes";
    else
        output << "No";

    input.close();
    output.close();
    return 0;
}

DNA::DNA(const std::string &seq) : sequence(seq)
{
    for (std::size_t i = 0; i < sequence.size(); i++)
    {
        if (sequence[i] != 'A' && sequence[i] != 'T' && sequence[i] != 'G' && sequence[i] != 'C')
            throw std::runtime_error("element present is not in given alphabet");
    }
}

DNA &DNA::operator=(DNA &other)
{
    if(this != &other)
    {
        sequence = other.sequence;
        // mpp = other.mpp;
    }
    return *this;
}

DNA::DNA(DNA &other)
{
    sequence = other.sequence;
    // mpp = other.mpp;
}

DNA::DNA(DNA &&other) noexcept : sequence(other.sequence)
{
    other.sequence = nullptr;
}

DNA &DNA::operator=(DNA &&other) noexcept
{
    if (this != &other)
    {
        sequence = other.sequence;
        other.sequence = nullptr;
    }
    return *this;
}

// DNA::DNA(const std::string &&seq) : sequence(std::move(seq)){

// }

DNA::~DNA()
{
    sequence.clear();
}

std::string DNA::getReverse() const
{
    std::string reverseStr;
    for (auto i = sequence.rbegin(); i != sequence.rend(); i++)
    {
        reverseStr += tmap.at(*i);
    }
    return reverseStr;
}

void DNA::print()
{
    std::cout << "Normal: " << sequence << " | After rev: " << getReverse() << std::endl;
}

bool DNA::isPoli() const
{
    return sequence == getReverse();
}
