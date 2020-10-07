/* This program computes compound interest
 * g++ program-02.cpp -o compoundinterest
 * ./compoundinterest 0.08 10000 5
 */

#include <iostream>
#include <cmath>

class CompoundInterest
{
public:
    CompoundInterest(double rate);
    CompoundInterest(const CompoundInterest &c);
    CompoundInterest &operator =(const CompoundInterest &c);
    ~CompoundInterest();

    double multiplePeriod(double value, int numPeriods);
    double continuousCompounding(double value, int numPeriods);
private:
    double mRate;
};

CompoundInterest::CompoundInterest(double rate) : mRate(rate)
{
}

CompoundInterest::CompoundInterest(const CompoundInterest &c) : mRate(c.mRate)
{
}

CompoundInterest &CompoundInterest::operator =(const CompoundInterest &c)
{
    if (&c != this)
        this->mRate = c.mRate;
    return *this;
}

CompoundInterest::~CompoundInterest()
{
}

double CompoundInterest::multiplePeriod(double value, int numPeriods)
{
    return value * pow(1 + mRate, numPeriods);
}

double CompoundInterest::continuousCompounding(double value, int numPeriods)
{
    return value * exp(mRate * numPeriods);
}

int main(int argc, char *argv[])
{
    if (argc < 4) {
        std::cerr << "Usage : " << argv[0] << " <interest rate> <principal> <num periods>" << std::endl;
        return -1;
    }

    double rate = atof(argv[1]);
    double value = atof(argv[2]);
    double numPeriods = atoi(argv[3]);

    CompoundInterest c(rate);
    double result = c.multiplePeriod(value, numPeriods);
    double contResult = c.continuousCompounding(value, numPeriods);

    std::cout << "Future value of discrete compounding = " << result << std::endl;
    std::cout << "Future value of continuous compounding = " << contResult << std::endl;

    return 0;
}
