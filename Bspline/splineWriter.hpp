#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <GLM/glm.hpp>

class SplineWriter {
private:
	const std::string FILENAME = "spline.txt";
	std::ofstream splineFile;
	std::vector<float> splineCurvePoints;

	void CreateSplineFile();
	void WriteSplineCurve();

	int GetSplinePointsCount();

public:
	SplineWriter(std::vector<float> splineCurvePoints);

	void WriteSpline();
};


SplineWriter::SplineWriter(std::vector<float> splineCurvePoints) {
	this->splineCurvePoints = splineCurvePoints;
}

void SplineWriter::WriteSpline() {
	CreateSplineFile();
	WriteSplineCurve();
}

int SplineWriter::GetSplinePointsCount() {
	return this->splineCurvePoints.size();
}

void SplineWriter::CreateSplineFile() {
	this->splineFile.open(FILENAME, std::ofstream::out | std::ofstream::trunc);

	this->splineFile.close();
}

void SplineWriter::WriteSplineCurve() {
	this->splineFile.open(FILENAME, std::ios_base::app);

	for (int i = 0; i < this->GetSplinePointsCount(); i += 3) {
		this->splineFile << "v " <<
			this->splineCurvePoints.at(i) << " " <<
			this->splineCurvePoints.at(i + 2) * 100 << " " <<
			this->splineCurvePoints.at(i + 1) << std::endl;
	}

	this->splineFile.close();
	std::cout << "foi" << std::endl;
}