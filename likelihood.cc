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

double nll(const std::vector<int> &data, double mu) // negative log likelyhood
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

    // true average of the sample is unknown -> test it from [0;6] in small steps
    // then for each of these values of average find likelyhood
    // plot likelyhood vs mu to find best estimate of mu
    for (int i = 0; i <= 600; i++)
    {
        double mu = 0.01 * i;
        double result = prob(data, mu);
        fout << mu << " " << prob(data, mu) << endl;
    }

    ofstream fout2("nll.txt");
    for (int i = 0; i <= 600; i++)
    {
        double mu = 0.01 * i;
        double result = nll(data, mu);
        fout2 << mu << " " << nll(data, mu) << endl;
    }

    ofstream fout3("deltanll.txt");
    for (int i = 0; i <= 600; i++)
    {
        double mu = 0.01 * i;
        double delta = nll(data, mu) - nll(data, 3.11538);
        fout3 << mu << " " << delta << endl;
    }

    // we need fine scan around n_bar = 3.11538
    double n_bar = 3.11538;
    double nll_nbar = nll(data, n_bar);

    double min_delta = 10000000;
    double mu_hat = 0.0;
    double mu_low = 0.0;
    double mu_high = 0.0;
    bool found_low = false;

    // scan from 2.5 to 3.8 with a tiny step size (0.0001)
    for (int i = 0; i <= 13000; i++)
    {
        double mu = 2.5 + 0.0001 * i;
        double delta = nll(data, mu) - nll_nbar;

        if (delta < min_delta)
        {
            min_delta = delta;
            mu_hat = mu;
        }

        // Find the left and right edges where delta < 1
        // delta (mu) is a distance on y-axis == 1   <=>   1-sigma confidence interval
        if (delta < 1.0)
        {
            if (!found_low)
            {
                mu_low = mu;
                found_low = true;
            }
            mu_high = mu;
        }
    }

    double uncertainty = (mu_high - mu_low) / 2.0;
    double N = data.size();
    double sigma = 1.65365;

    cout << " " << endl;
    cout << "MLE mu: " << mu_hat << "; mu theoretical: " << n_bar << endl;
    cout << "[mu_low, mu_high] = [" << mu_low << ", " << mu_high << "]" << endl;
    cout << "Uncertainty of MLE mu: " << uncertainty << endl;
    cout << "Uncertainty (sigma / sqrt(N)): " << sigma / sqrt(N) << endl;
    cout << "Uncertainty (sqrt(mu_hat / N)): " << sqrt(mu_hat / N) << endl;

// Part e
double nll_fit = nll(data, mu_hat);
double nll_sat = 0.0;

for (int k : data)
{
    if (k == 0)
    {
        continue;
    }
    nll_sat += -2 * log(poisson(k, k));
}

double test = nll_fit - nll_sat;
double ndof = N - 1;
double z = (test - ndof) / sqrt(2 * ndof);

cout << "\nPart e)" << endl;
cout << "-2 ln Lambda = " << test << endl;
cout << "Degrees of freedom = " << ndof << endl;
cout << "z = " << z << endl;

    return 0;
}
