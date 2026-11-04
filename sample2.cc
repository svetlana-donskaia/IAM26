#include <iostream>
#include <fstream>
#include <cmath>

int main()
{
    std::ifstream fin1("sums.txt");
    std::ifstream fin2("sums.txt");

    std::ofstream fout1("means.txt");
    std::ofstream fout2("variances.txt");

    double a1, a2;
    int interval = 1;

    double sum_means = 0;
    double sum_sq_means = 0;

    while (true)
    {
        double sum = 0;
        int count = 0;

        while (count < 9 && fin1 >> a1)
        {
            sum += a1;
            count++;
        }

        if (count == 0)
        {
            break;
        }

        double mean = sum / count;
        fout1 << mean << std::endl;

        double sumsquare = 0;
        for (int i = 0; i < count; ++i)
        {
            fin2 >> a2;
            sumsquare += (a2 - mean) * (a2 - mean);
        }

        double var = sumsquare / count;
        double var_bessel = sumsquare / (count - 1);
        double dev = sqrt(var);

        fout2 << var << std::endl;

        sum_means += mean;
        sum_sq_means += (mean * mean);

        std::cout << interval << " interval" << std::endl;
        std::cout << "Mean is " << mean << std::endl;
        std::cout << "Variance is " << var << std::endl;
        std::cout << "Variance with Bessels correction is " << var_bessel << std::endl;
        std::cout << "Deviation is " << dev << std::endl;
        std::cout << "\n"
                  << std::endl;

        interval++;
    }

    int total_intervals = interval - 1;

    if (total_intervals > 0)
    {
        double mean_of_means = sum_means / total_intervals;

        double var_of_means = (sum_sq_means / total_intervals) - (mean_of_means * mean_of_means);
        double dev_of_means = sqrt(var_of_means);

        std::cout << "26 intervals" << std::endl;
        std::cout << "Mean of the " << total_intervals << " means: " << mean_of_means << std::endl;
        std::cout << "Variance of the " << total_intervals << " means: " << var_of_means << std::endl;
        std::cout << "Deviation of the " << total_intervals << " means: " << dev_of_means << std::endl;
    }

    fin1.close();
    fin2.close();
    fout1.close();
    fout2.close();

    return 0;
}