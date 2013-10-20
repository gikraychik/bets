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
    int N(int maxN, double &gain) const  //если вернули (maxN - 1) => иммем возможность сделать ставку номер maxN
    {
        gain = 0.0;
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
                if (copy_s >= s) { gain += (copy_s - s); copy_s = s; }
            }
            else
            {
                copy_s -= y;
            }
        }
        return N;
    }
    double will_survive(int n, double &average_gain)  //вероятность того, что сможем сделать шаг n; average_gain - средний заработок при условии, что дотянули
    {
        const int all = 100000;
        int counter = 0;
        double global_gain = 0.0;
        double gain = 0.0;
        for (int i = 1; i < all; i++)
        {
            gain = 0.0;
            int number = N(n, gain);
            if (number == n - 1) { global_gain += gain; counter++; }
        }
        average_gain = global_gain / counter;
        return (double)counter / (double)all;
    }
    void print_survival_table(int N = 100)
    {
        double average_gain;
        for (int i = 1; i <= N; i++)
        {
            //average_gain = 0.0;
            cout << "n = " << i << " -> " << will_survive(i, average_gain) << " Average Gain: " << (double)average_gain << endl;
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
    Model model (3.2, 0.329843, 100.0, 20);
    //model.mkmodel(30);
    model.print_survival_table(100);
    double gain = 0.0;

    //model.will_survive(10, gain);
    //cout << gain << endl;

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
