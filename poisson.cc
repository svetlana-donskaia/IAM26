#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

double poisson(double mu, int k)
{
    return (pow(mu, k) * exp(-mu) / tgamma(k + 1));
}

int main()
{
    std::vector<int> counts(11);

    std::ifstream fin("sums.txt");
    std::ofstream fout("hist.txt");
    std::ofstream fout2("histpoi.txt");

    int n;
    int N = 0;
    double sum = 0;

    while (fin >> n)
    {
        sum += n;
        counts.at(n) += 1;
        ++N;
    }

    for (unsigned int k = 0; k < counts.size(); ++k)
    {
        std::cout << k << " " << counts[k] << std::endl;
        fout << k << " " << counts[k] << std::endl;
    }

    fin.close();

    double mean = sum / N;
    std::cout << "Mean is " << mean << std::endl;

    for (unsigned int k = 0; k < counts.size(); ++k)
    {
        double histpoi = N * poisson(mean, k);
        fout2 << k << " " << counts[k] << " " << histpoi << std::endl;
    }

    fout.close();
    fout2.close();

    return 0;
}