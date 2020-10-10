/* Program to find Moving Average
 * gcc movingaverage.cpp -std=c++11 -o movingaverage
 */

#include <vector>
#include <iostream>

class MovingAverage
{
public:
    MovingAverage(int period);
    MovingAverage(const MovingAverage&);
    MovingAverage &operator = (const MovingAverage&);
    ~MovingAverage();

    void addPriceQuote(double close);
    std::vector<double> calculateMA();
    std::vector<double> calculateEMA();

private:
    int mNumPeriods;
    std::vector<double> mPrices;
};

MovingAverage::MovingAverage(int periods) : mNumPeriods(periods)
{
}

MovingAverage::~MovingAverage()
{
}

MovingAverage::MovingAverage(const MovingAverage &ma) : mNumPeriods(ma.mNumPeriods)
{
}

MovingAverage& MovingAverage::operator =(const MovingAverage &ma)
{
    if (this != &ma) {
        mNumPeriods = ma.mNumPeriods;
        mPrices = ma.mPrices;
    }

    return *this;
}

std::vector<double> MovingAverage::calculateMA()
{
    std::vector<double> ma;
    double sum = 0;

    for (int i = 0; i < mPrices.size(); i++) {
        sum += mPrices[i];
        if (i >= mNumPeriods) {
          ma.push_back(sum / mNumPeriods);
          sum = sum - mPrices[i - mNumPeriods];
        }
    }
    return ma;
}

std::vector<double> MovingAverage::calculateEMA()
{
    std::vector<double> ema;
    double sum = 0;
    double multiplier = 2.0 / (mNumPeriods + 1);
    for (int i = 0; i < mPrices.size(); i++) {
        sum += mPrices[i];
        if (i == mNumPeriods) {
            ema.push_back(sum / mNumPeriods);
            sum -= mPrices[i - mNumPeriods];
        } else if (i > mNumPeriods) {
            double val = (1 - multiplier) * ema.back() + multiplier * mPrices[i];
            ema.push_back(val);
        }
    }
    return ema;
}

void MovingAverage::addPriceQuote(double close)
{
    mPrices.push_back(close);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <numPeriods>" << std::endl;
        return -1;
    }

    int numPeriods = atoi(argv[1]);
    double price;
    MovingAverage calculator(numPeriods);

    while (true) {
        std::cin >> price;
        if (price == -1) break;
        calculator.addPriceQuote(price);
    }

    std::vector<double> ma = calculator.calculateMA();
    for (int i = 0; i < ma.size(); i++)
        std::cout << "Average value " << i << " = " << ma[i] << std::endl;

    std::vector<double> ema = calculator.calculateEMA();
    for (int i = 0; i < ema.size(); i++)
        std::cout << "Exponential avg value " << i << " = " << ema[i] << std::endl;

    return 0;
}
