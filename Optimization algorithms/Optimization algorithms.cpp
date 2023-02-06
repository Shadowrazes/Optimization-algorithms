#include <iostream>

#include "SimpleFraction/SimpleFraction.h"
#include "JordanGauss/JordanGauss.h"

int main()
{
    LinearEquations::JordanGauss jordanGauss;

    jordanGauss.Process();

    //Fraction::SimpleFraction first(1, 2);
    //Fraction::SimpleFraction second(1, 2);
    //first -= second;
    //std::cout << first << second;
}
