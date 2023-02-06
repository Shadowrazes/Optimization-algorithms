#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "../SimpleFraction/SimpleFraction.h"

namespace LinearEquations {
class JordanGauss {
public:
	JordanGauss();

	void Process();
	void LineAdditional(int firstLine, int secondLine, int column);
	void LineDivision(int lineNum, int dividerInd);
	void DeleteZeroLines();
	bool CheckFalseEqualities();
	void Finishing();
	bool FindAndSwapMaxColumnElem(int lineNum, int columnNum);

	void ReadMatrixFromFile(std::string fileName = "JordanGauss\\Matrix.txt");
	void PrintMatrix();
protected:
	int m_variablesCount = 0;
	std::vector<std::vector<Fraction::SimpleFraction>> m_matrix;
};
}