#include "JordanGauss.h"

namespace LinearEquations {
//-----------------------------------------------------------------------------------
JordanGauss::JordanGauss() {

}
//-----------------------------------------------------------------------------------
void JordanGauss::Process() {
	ReadMatrixFromFile();
	PrintMatrix();

	for (int i = 0, j = 0; i < m_matrix.size() && j < m_variablesCount; i++, j++) {
		if (CheckFalseEqualities()) {
			std::cout << "The system have no solution\n";
			return;
		}

		if (FindAndSwapMaxColumnElem(i, j)) {
			PrintMatrix();
		}

		if (m_matrix[i][j].IsZero()) {
			i--;
			continue;
		}

		LineDivision(i, j);
		PrintMatrix();

		for (int k = 0; k < m_matrix.size(); k++) {
			if (k != i) {
				LineAdditional(i, k, j);
			}
		}
		PrintMatrix();
	}

	DeleteZeroLines();
	PrintMatrix();
	Finishing();
}
//-----------------------------------------------------------------------------------
void JordanGauss::LineAdditional(int firstLine, int secondLine, int column) {
	Fraction::SimpleFraction coef = m_matrix[secondLine][column] * Fraction::SimpleFraction(-1, 1);

	for (int i = 0; i < m_variablesCount + 1; i++) {
		m_matrix[secondLine][i] += m_matrix[firstLine][i] * coef;
	}

}
//-----------------------------------------------------------------------------------
void JordanGauss::LineDivision(int lineNum, int dividerInd) {
	Fraction::SimpleFraction divider = m_matrix[lineNum][dividerInd];
	for (auto& elem : m_matrix[lineNum]) {
		elem /= divider;
	}
}
//-----------------------------------------------------------------------------------
void JordanGauss::DeleteZeroLines() {
	std::vector<int> deleteInds;
	for (int i = 0; i < m_matrix.size(); i++) {
		int zeroesCount = std::count_if(m_matrix[i].begin(), m_matrix[i].end(),
			[](Fraction::SimpleFraction elem) {return elem.IsZero(); });

		if (zeroesCount == m_variablesCount + 1) {
			deleteInds.push_back(i);
		}
	}

	if (deleteInds.empty())
		return;

	std::reverse(deleteInds.begin(), deleteInds.end());

	for (const auto& ind : deleteInds) {
		m_matrix.erase(m_matrix.begin() + ind);
	}
}
//-----------------------------------------------------------------------------------
bool JordanGauss::CheckFalseEqualities() {
	int zeroesCount = 0;
	for (const auto& line : m_matrix) {
		for (int i = 0; i < line.size(); i++) {
			line[i].IsZero() ? zeroesCount++ : zeroesCount;
		}
		
		if (zeroesCount == m_variablesCount && !line.back().IsZero()) {
			return true;
		}
		zeroesCount = 0;
	}
	return false;
}
//-----------------------------------------------------------------------------------
void JordanGauss::Finishing() {
	for (int i = 0; i < m_matrix.size(); i++) {
		int zeroesCount = std::count_if(m_matrix[i].begin(), m_matrix[i].end(),
			[](Fraction::SimpleFraction elem) {return elem.IsZero(); });

		if (zeroesCount == m_variablesCount - 1 && !m_matrix[i].back().IsZero() || 
			zeroesCount == m_variablesCount && m_matrix[i].back().IsZero()) {
			int variableNum = std::distance(m_matrix[i].begin(), std::find_if(m_matrix[i].begin(), m_matrix[i].end(),
																	[](Fraction::SimpleFraction elem) {return elem.IsOne(); }));
			std::cout << "x" << variableNum << " = " << m_matrix[i].back();
		}
		else {
			std::vector<std::pair<int, Fraction::SimpleFraction>> elems;
			for (int j = 0; j < m_variablesCount + 1; j++) {
				if (!m_matrix[i][j].IsZero()) {
					elems.push_back(std::make_pair(j, m_matrix[i][j]));
				}
			}

			if (!m_matrix[i].back().IsZero()) {
				std::cout << "x" << elems.front().first << " = " << elems.back().second;
			}
			else {
				std::cout << "x" << elems.front().first << " = " << elems.back().second * Fraction::SimpleFraction(-1, 1) << "x" << elems.back().first;
			}

			for (int j = 1; j < elems.size() - 1; j++) {
				std::cout << " + " << elems[j].second * Fraction::SimpleFraction(-1, 1) << "x" << elems[j].first;
			}
		}
		std::cout << std::endl;
	}
}
//-----------------------------------------------------------------------------------
bool JordanGauss::FindAndSwapMaxColumnElem(int lineNum, int columnNum) {
	int swapLineInd = -1;
	Fraction::SimpleFraction max = m_matrix[lineNum][columnNum].ToAbs();

	for (int i = lineNum + 1; i < m_matrix.size(); i++) {
		if (max < m_matrix[i][columnNum].ToAbs()) {
			max = m_matrix[i][columnNum].ToAbs();
			swapLineInd = i;
		}
	}

	if (swapLineInd != -1) {
		std::swap(m_matrix[lineNum], m_matrix[swapLineInd]);
		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------
void JordanGauss::ReadMatrixFromFile(std::string fileName) {
	std::fstream file(fileName);

	if (!file.is_open()) {
		std::cout << "Error opening the file" << std::endl;
	}

	std::string line = "";

	while (getline(file, line)) {
		m_matrix.push_back(std::vector<Fraction::SimpleFraction>());
		while (line.size() != 0) {
			int spaceInd = line.find(" ");

			m_matrix.back().push_back(Fraction::SimpleFraction(std::stoi(line.substr(0, spaceInd)), 1));

			line.erase(0, spaceInd + 1);
			if (spaceInd == -1)
				break;
		}
	}

	m_variablesCount = m_matrix[0].size() - 1;
}
//-----------------------------------------------------------------------------------
void JordanGauss::PrintMatrix() {
	for (const auto& line : m_matrix) {
		for (const auto& column : line) {
			std::cout << column << "\t";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}
//-----------------------------------------------------------------------------------
}