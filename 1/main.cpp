// 18
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <cstring>
#include <stdexcept>

using namespace std;
class Ground
{
private:
    size_t _M = 0,_N = 0;

    unique_ptr<char*[]> teto_array = nullptr;
public:
    Ground() = default;
    Ground(int M, int N,unique_ptr<char*[]>& teto_char);
    Ground(const vector<vector<char>>& vec);
    void add_element(size_t row, size_t col, char value);

    void cement_eater();
    void print();

    operator string();

};

int main()
{
    ifstream is("teto.txt");
    ofstream os("oteto.txt");
    string teto_string;
    getline(is,teto_string);
     cout << teto_string << endl;

    stringstream ss(teto_string);
    size_t M, N, P;
    ss >> M >> N >> P;

    unique_ptr<char*[]> fmatrix(new char*[N]);
    for (size_t i = 0;i < N;i++) {
        fmatrix[i] = new char[M];
        getline(is, teto_string);
        copy(teto_string.begin(), teto_string.begin() + M, fmatrix[i]);
    }

    Ground tetos(M, N, fmatrix);
    for(size_t i = 0; i < P; i++)
    {
        tetos.cement_eater();
    }
    tetos.print();
    
    os << static_cast<string>(tetos);
    return 0;
}

Ground::Ground(int M, int N ,unique_ptr<char*[]>& teto_char) : _M(M), _N(N), teto_array(move(teto_char))
{
}

Ground::Ground(const vector<vector<char>> &vec) : _M(vec[0].size()), _N(vec.size()) {
    teto_array = make_unique<char*[]>(_N);
    
    for (size_t i = 0; i < _N; i++) {
        teto_array[i] = new char[_M + 1];
        copy(vec[i].begin(), vec[i].end(), teto_array[i]);
        teto_array[i][_M] = '\0';
    }
}

void Ground::add_element(size_t row, size_t col, char value) {
    if (row >= _N || col >= _M) {
        throw out_of_range("Invalid row or column index");
    }
    teto_array[row][col] = value;
}

void Ground::cement_eater()
{
    unique_ptr<char*[]> copy_of_teto_array(new char*[_N]);
    for (size_t i = 0;i < _N;i++) {
        copy_of_teto_array[i] = new char[_M];
        for (size_t j = 0;j < _M;j++) {
            copy_of_teto_array[i][j] = teto_array[i][j];
        }
    }
    for(size_t i = 0; i< _N; i++)
    {
        for(size_t j = 0; j<_M; j++)
        {
            if (teto_array[i][j] == '*') continue;
            int cnt = 0;
            for (int m = -1;m <= 1;m++) {
                for (int n = -1;n <= 1;n++) {
                    if (m == 0 && n == 0) continue;
                    if (j + m < _M && i + n < _N) {
                        if (teto_array[i + n][j + m] == '*') cnt++;
                    }
                }
            }
            if (cnt == 3) {
                copy_of_teto_array[i][j] = '*';
            }
        }
    }
    for(size_t i = 0; i< _N; i++)
    {
        for(size_t j = 0; j<_M; j++)
        {
            if (teto_array[i][j] == '.') continue;
            int cnt = 0;
            for (int m = -1;m <= 1;m++) {
                for (int n = -1;n <= 1;n++) {
                    if (m == 0 && n == 0) continue;
                    if (j + m < _M && i + n < _N) {
                        if (teto_array[i + n][j + m] == '*') cnt++;
                    }
                }
            }
            if (cnt != 2 && cnt != 3) {
                copy_of_teto_array[i][j] = '.';
            }
        }
    }
    for (size_t i = 0;i < _N;i++) {
        for (size_t j = 0;j < _M;j++) {
            teto_array[i][j] = copy_of_teto_array[i][j];
        }
    }
}

void Ground::print()
{
    for (size_t i = 0;i < _N;i++) {
        cout << teto_array[i] << endl;
    }

}

Ground::operator string()
{
    string tetos;
    for (size_t i = 0;i < _N;i++) {
        tetos += teto_array[i];
        tetos += "\n";
    }
    return tetos;
}
