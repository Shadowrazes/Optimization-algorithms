#include <iostream>

#include "SimpleFraction/SimpleFraction.h"
#include "JordanGauss/JordanGauss.h"

int main()
{
    LinearEquations::JordanGauss jordanGauss;

    FractionMatrix matrix = jordanGauss.ReadMatrixFromFile();
    jordanGauss.FindBasicSolutions();
}
