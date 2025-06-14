#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <climits>

using namespace std;

class ChangeCounter
{
private:
    int N;
    int M;
    vector<int> coins;
    vector<int> bestCombination;
    int minCoins;

public:
    ChangeCounter(int _N, int _M, vector<int> _coins) : N(_N), M(_M), coins(_coins), minCoins(INT_MAX) {}
    void findComb(int pos, int currentSum, int currentCoins, vector<int> &currentCombination);
    void solve();
    void printSolution(ofstream &output);
};

int main()
{
    ifstream input("teto.txt");
    ofstream output("oteto.txt");

    int N, M;
    input >> N >> M;

    vector<int> coins;
    for (int i = 0; i < M; ++i)
    {
        int coin;
        input >> coin;
        coins.push_back(coin);
    }

    ChangeCounter counter(N, M, coins);
    counter.solve();
    counter.printSolution(output);

    return 0;
}

void ChangeCounter::findComb(int pos, int currentSum, int currentCoins, vector<int> &currentCombination)
{
    if (currentSum == N)
    {
        if (currentCoins < minCoins)
        {
            minCoins = currentCoins;
            bestCombination = currentCombination;
        }
        return;
    }

    if (pos >= coins.size() || currentSum > N || currentCoins >= minCoins)
    {
        return;
    }

    for (int take = 0; take <= 2; ++take)
    {
        if (take > 0)
        {
            currentCombination.push_back(coins[pos]);
        }
        findComb(pos + 1, currentSum + take * coins[pos], currentCoins + take, currentCombination);
        if (take > 0)
        {
            currentCombination.pop_back();
        }
    }
}

void ChangeCounter::solve()
{
    vector<int> currentCombination;
    findComb(0, 0, 0, currentCombination);
}

void ChangeCounter::printSolution(ofstream &output)
{
    long long totalSum = 0;
    for (int coin : coins)
    {
        totalSum += 2 * coin;
    }

    if (totalSum < N)
    {
        output << -1;
        return;
    }

    if (minCoins == INT_MAX)
    {
        output << 0;
        return;
    }

    output << minCoins << "\n";
    for (int coin : bestCombination)
    {
        output << coin << " ";
    }
}