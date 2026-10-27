#include <iostream>
#include <fstream>

int main()
{
    std::ifstream fin("data.txt");

    std::ofstream fout("sums.txt");

    int num1, num2;

    for (int i = 0; i < 234; ++i)
    {
        fin >> num1 >> num2;
        fout << (num1 + num2) << std::endl;
    }

    fin.close();
    fout.close();

    std::cout << "Done." << std::endl;

    return 0;
}