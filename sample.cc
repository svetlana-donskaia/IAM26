#include <iostream>
#include <fstream>
#include <cmath>

int main()
{
    std::ifstream fin("sums.txt");

    int n = 0;
    double a, mean, sum = 0;

    while (fin >> a)
    {
        sum += a;
        ++n;
    }

    mean = sum / n;

    std::cout << "The mean value is: " << mean << std::endl;

    fin.close();

    std::ifstream flin("sums.txt");

    double var, sumsquare = 0;

    while (flin >> a)
    {
        sumsquare += ((a - mean) * (a - mean));
    }

    var = sumsquare / n;

    std::cout << "The variance value is: " << var << std::endl;

    fin.close();

    double dev;
    dev = sqrt(var);
    std::cout << "The deviation value is: " << dev << std::endl;

    return 0;
}