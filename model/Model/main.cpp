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
    Model(double k, double p, double x, int proportion) : s(x * proportion), k(k), p(p), x(x) {}
    Model(void) : s(0), k(0), p(0), x(0) {}
    double bet(int n) const
    {
        return x;
    }
    int N(int maxN) const  //если вернули (maxN - 1) => иммем возможность сделать ставку номер maxN
    {
        double copy_s = s;
        double y;
        int N = maxN - 1;
        for (int i = 1; i < maxN ;i++)
        {
            y = bet(i);
            if (y > copy_s) { N = i; break; }
            int result = this->random();
            if (result == 1)
            {
                copy_s += y * (k - 1);
            }
            else
            {
                copy_s -= y;
            }
        }
        return N;
    }
    double will_survive(int maxN)  //вероятность того, что сможем сделать шаг maxN
    {
        const int all = 100000;
        const int size = maxN;
        vector <double> P(size, 0);
        for (int i = 1; i < all; i++)
        {
            int number = N(maxN);
            P[number] += 1;
        }
        /*for (int i = 0; i < size; i++)
        {
            //P[i] /= (double)all;
            //cout << "N = " << i << " -> " << (double)P[i] / (double)all << endl;
        }*/
        return P[maxN - 1] / all;
    }
    void print_survival_table(int N = 100)
    {
        for (int i = 1; i < N; i++)
        {
            cout << "n = " << i << " -> " << will_survive(i) << endl;
        }
    }

    int random() const
    {
        const int precision = 5;
        int pw = 1;
        double cp = p;
        int counter = 0;
        while (round(cp) != cp)
        {
            if (counter >= precision) { break; }
            counter++;
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
    Model model (1000, 3.2, 0.329843, 100);
    //model.mkmodel(30);
    model.print_survival_table(100);
    /*const int c = 100000;
    double zer = 0.0;
    double ones = 0.0;
    for (int i = 0; i < c; i++)
    {
        int result = model.random();
        if (result == 1) { ones += 1.0; }
        else { zer += 1.0; }
    }*/
    //cout << "P = " << ones / c << endl;
    //cout << model.N(1000) << endl;
    return 0;
}
