// 45
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

struct テトBook
{
    std::string name;
    std::string number;
    std::string 番号;
};

bool operator==(const テトBook &lhs, const テトBook &rhs);

class テトshelf
{
private:
    std::vector<テトBook> shelf;

public:
    テトshelf(std::vector<テトBook> &r_shelf);
    テトshelf(テトshelf &other);
    テトshelf &operator=(テトshelf &other);
    テトshelf(テトshelf &&other);
    テトshelf &operator=(テトshelf &&other);
    ~テトshelf();

    int take_books(int N);
    void v_print();
    void remove(size_t pos);
    void add(テトBook& book);
    void add(size_t pos, テトBook& book);
};

テトshelf::テトshelf(std::vector<テトBook> &r_shelf) : shelf(r_shelf)
{
}

テトshelf::テトshelf(テトshelf &other) : shelf(other.shelf)
{
}

テトshelf &テトshelf::operator=(テトshelf &other)
{
    if (this != &other)
    {
        shelf = other.shelf;
    }
    return *this;
}

テトshelf::テトshelf(テトshelf &&other) : shelf(other.shelf)
{
    other.shelf.clear();
}

テトshelf &テトshelf::operator=(テトshelf &&other)
{
    if (this != &other)
    {
        shelf = other.shelf;
        other.shelf.clear();
    }
    return *this;
}

テトshelf::~テトshelf()
{
    shelf.clear();
}

int テトshelf::take_books(int N)
{
    std::vector<std::vector<int>> dp(N, std::vector<int>(N, INT_MAX));

    for (int i = 0; i < N; ++i)
    {
        dp[i][i] = 1;
    }

    for (int len = 2; len <= N; ++len)
    {
        for (int i = 0; i <= N - len; ++i)
        {
            int j = i + len - 1;
            dp[i][j] = dp[i + 1][j] + 1;
            for (int k = i + 1; k <= j; ++k)
            {
                if (shelf[i] == shelf[k])
                {
                    int mid = (i + 1 <= k - 1) ? dp[i + 1][k - 1] : 0;
                    dp[i][j] = std::min(dp[i][j], mid + dp[k][j]);
                }
            }
        }
    }

    return dp[0][N - 1];
}

void テトshelf::v_print()
{
    for (std::size_t i = 0; i < shelf.size(); i++)
    {
        std::cout << "Name " << shelf[i].name << ", 番号 " << shelf[i].番号 << ", number " << shelf[i].number << std::endl;
    }
}

void テトshelf::remove(size_t pos)
{
    if (pos >= shelf.size())
        return;
    auto it = shelf.begin() + pos;
    shelf.erase(it);
}

void テトshelf::add(テトBook& book)
{
    shelf.push_back(book);
}

void テトshelf::add(size_t pos, テトBook &book)
{
    if (pos <= shelf.size()) {
        shelf.insert(shelf.begin() + pos, book);
    } 
}

int main()
{
    std::ifstream input("teto.txt");
    std::ofstream output("oteto.txt");

    int N;
    input >> N;
    std::vector<テトBook> all_books;

    for (std::size_t i = 0; i < N; i++)
    {
        テトBook book;
        input >> book.name;
        all_books.push_back(book);
    }

    テトshelf shelf(all_books);
    int res = shelf.take_books(N);
    output << res;

    input.close();
    output.close();
    return 0;
}

bool operator==(const テトBook &lhs, const テトBook &rhs)
{
    return lhs.name == rhs.name;
}
