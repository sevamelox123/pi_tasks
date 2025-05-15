// 18
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

using namespace std;
class Ground
{
private:
    size_t _M,_N;

    unique_ptr<char*[]> teto_array;
public:
    Ground(int M, int N,unique_ptr<char*[]>& teto_char);

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
