﻿//-------------------------------------------------------------------------------------------
// JordanGauss.h
// Description: Класс, реализующий алгоритм Жордана-Гаусса для решения СЛАУ
// Date: 31.01.2023
// Authors: Хьюго М.А. & Наумов Н.В.
// Ⓒ Sibsutis university
//-------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "../SimpleFraction/SimpleFraction.h"

typedef std::vector<std::vector<Fraction::SimpleFraction>> FractionMatrix;

namespace LinearEquations {
class JordanGauss {
public:
	JordanGauss();

	void Process(FractionMatrix& matrix);

	void FindBasicSolutions();

	FractionMatrix ReadMatrixFromFile(std::string fileName = "JordanGauss\\Matrix.txt");
	void PrintMatrix(FractionMatrix& matrix);
protected:
	int m_variablesCount = 0;
	FractionMatrix m_matrix;
	std::vector<Fraction::SimpleFraction> m_result;

	void LineAdditional(FractionMatrix& matrix, int firstLine, int secondLine, int column);
	void LineDivision(FractionMatrix& matrix, int lineNum, int dividerInd);
	bool DeleteZeroLines(FractionMatrix& matrix);
	bool CheckFalseEqualities(FractionMatrix& matrix);
	void Finishing(FractionMatrix& matrix);
	bool FindAndSwapMaxColumnElem(FractionMatrix& matrix, int lineNum, int columnNum);

	FractionMatrix ExtractMatrixWithIncludedVariables(std::vector<int>& columnInds);
	std::vector<std::vector<int>> CombinationsWithoutRepeats(int n, int k);
	void SolutionVerification(FractionMatrix& matrix, FractionMatrix& solutions);
};
}