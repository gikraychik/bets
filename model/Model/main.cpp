#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Model
{
public:
    Model(double sum, double k, double p, double x) : s(sum), k(k), p(p), x(x) {}
    Model(void) : s(0), k(0), p(0), x(0) {}
    double bet(int n)
    {
        return x;
    }
    int N(int maxN)
    {
        double y;
        int N = maxN - 1;
        for (int i = 1; i < maxN ;i++)
        {
            y = bet(i);
            if (y > s) { N = i; break; }
            int result = random();
            if (result == 1)
            {
                s += y * (k - 1);
            }
            else
            {
                s -= y;
            }
        }
        return N;
    }
    void mkmodel(int maxN)
    {
        const int all = 100;
        const int size = maxN;
        vector <double> P(size, 0);
        for (int i = 0; i < all; i++)
        {
            int number = N(maxN);
            P[number] += 1;
        }
        for (int i = 0; i < size; i++)
        {
            P[i] /= all;
            cout << "N = " << i << " -> " << P[i] << endl;
        }
    }
    int random() const
    {
        int pw = 1;
        double cp = p;
        while (round(cp) != cp)
        {
            pw *= 10;
            cp *= 10;
        }
        int q = rand() % pw;
        return q < cp;
    }
    double k;  //коэффицент
    double p;  //вероятность выигрыша
    double s;  //имеющаяся сумма денег
    double x;

};

int main(int argc, char *argv[])
{
    srand(time(NULL));
    //Model model(1000, 3.2, 0.329843, 300);
    Model model (1000, 2, 0.75, 100);
    //model.mkmodel(1000);
    int z = 0;
    int o = 0;
    int const c = 10000000;
    for (int i = 0; i < c; i++)
    {
        if (model.random() == 0) { o++; }
        else { z++; }
    }
    cout << (double)o / (double) c<< " " << (double) z / (double) c << endl;
    //cout << model.N(1000) << endl;
    return 0;
}
