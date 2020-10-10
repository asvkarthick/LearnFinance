/* Program to compute volatility of equity
 * g++ volatilitycalculator.cpp -std=c++11 -o volatilitycalculator
 */

#include <iostream>
#include <vector>
#include <cmath>

class VolatilityCalculator
{
public:
    VolatilityCalculator();
    ~VolatilityCalculator();
    VolatilityCalculator(const VolatilityCalculator&);
    VolatilityCalculator &operator =(const VolatilityCalculator&);

    void addPrice(double price);
    double rangeVolatility();
    double stdDev();
    double mean();

private:
    std::vector<double> mPrices;
};

VolatilityCalculator::VolatilityCalculator()
{
}

VolatilityCalculator::~VolatilityCalculator()
{
}

VolatilityCalculator::VolatilityCalculator(const VolatilityCalculator &v) : mPrices(v.mPrices)
{
}

VolatilityCalculator &VolatilityCalculator::operator=(const VolatilityCalculator &v)
{
    if (this != &v) mPrices = v.mPrices;
    return *this;
}

void VolatilityCalculator::addPrice(double price)
{
    mPrices.push_back(price);
}

double VolatilityCalculator::rangeVolatility()
{
    if (mPrices.size() < 1) return 0.0;

    double min = mPrices[0];
    double max = min;

    for (int i = 1; i < mPrices.size(); i++) {
        if (mPrices[i] < min) min = mPrices[i];
        if (mPrices[i] > max) max = mPrices[i];
    }

    return max - min;
}

double VolatilityCalculator::mean()
{
    double sum = 0;

    for (int i = 0; i < mPrices.size(); i++) sum += mPrices[i];
    return sum / mPrices.size();
}

double VolatilityCalculator::stdDev()
{
    double m = mean();
    double sum = 0;
    for (int i = 0; i < mPrices.size(); i++) {
        double val = mPrices[i] - m;
        sum += val * val;
    }

    return sqrt(sum / (mPrices.size() - 1));
}

int main(int argc, char *argv[])
{
    double price;
    VolatilityCalculator vc;

    while (true) {
        std::cin >> price;
        if (price == -1) break;
        vc.addPrice(price);
    }

    std::cout << "Range volatility = " << vc.rangeVolatility() << std::endl;
    std::cout << "Standard Deviation = " << vc.stdDev() << std::endl;

    return 0;
}
