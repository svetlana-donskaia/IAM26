#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

double poisson(double mu, int k)
{
    return (pow(mu, k) * exp(-mu) / tgamma(k + 1));
}

double prob(const std::vector<int> &data, double mu)
{
    double likelihood = 1.0;
    for (int k : data)
    {
        likelihood *= poisson(mu, k);
    }
    return likelihood;
}

double nll(const std::vector<int> &data, double mu)
{

    double sum = 0;
    for (int k : data)
    {
        sum += log(poisson(mu, k));
    }
    return -2 * sum;
}

int main()
{
    ifstream fin("sums.txt");
    vector<int> data;
    double number;
    while (fin >> number)
    {
        data.push_back(number);
    }

    cout << prob(data, 3.11538) << endl;

    ofstream fout("likelihood.txt");

    for (int i = 0; i <= 60; i++)
    {
        double mu = 0.1 * i;
        double result = prob(data, mu);
        fout << mu << " " << prob(data, mu) << endl;
    }

    ofstream fout2("nll.txt");
    for (int i = 0; i <= 60; i++)
    {
        double mu = 0.1 * i;
        double result = nll(data, mu);
        fout2 << mu << " " << nll(data, mu) << endl;
    }

    ofstream fout3("deltanll.txt");
    for (int i = 0; i <= 60; i++)
    {
        double mu = 0.1 * i;
        double delta = nll(data, mu) - nll(data, 3.11538);
        fout3 << mu << " " << delta << endl;
    }

    return 0;
}
