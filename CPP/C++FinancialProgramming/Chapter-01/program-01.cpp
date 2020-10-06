/* This program computes simple interest
 * g++ program-01.cpp -o simpleinterest
 * ./simpleinterest 0.08 10000
 */

#include <iostream>

class SimpleInterest
{
public:
    SimpleInterest(double rate);
    SimpleInterest(const SimpleInterest &s);
    SimpleInterest &operator =(const SimpleInterest &s);
    ~SimpleInterest();

    double singlePeriod(double value);
private:
    double mRate;
};

SimpleInterest::SimpleInterest(double rate) : mRate(rate)
{
}

SimpleInterest::~SimpleInterest()
{
}

SimpleInterest::SimpleInterest(const SimpleInterest &s) : mRate(s.mRate)
{
}

SimpleInterest &SimpleInterest::operator =(const SimpleInterest &s)
{
    if (&s != this)
        this->mRate = s.mRate;
    return *this;
}

double SimpleInterest::singlePeriod(double value)
{
    return value * (1 + mRate);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <interest rate> <principal>" << std::endl;
        return -1;
    }

    double rate = atof(argv[1]);
    double value = atof(argv[2]);

    SimpleInterest s(rate);
    double result = s.singlePeriod(value);
    std::cout << "Result = " << result << std::endl;

    return 0;
}
