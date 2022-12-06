#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <glm/ext/vector_float3.hpp>
using namespace std;
class OBJWriter {

public:
	ofstream OBJFile;

	static void createMtlFile() {
		static ofstream mtlFile;
		mtlFile.open("curve.mtl");
		mtlFile << "newmtl " << "curve\n" << endl;
		mtlFile << "Kd " << 1.0 << " " << 0.5 << " " << 0 << endl;
		mtlFile << "Ka " << 1.0 << " " << 1.0 << " " << 1.0 << endl;
		mtlFile << "Tf " << 1.0 << " " << 1.0 << " " << 1.0 << endl;
		mtlFile << "map_Kd " << "curve.png" << endl;
		mtlFile << "Ni " << 1.0 << endl;
		mtlFile << "Ns " << 100.0 << endl;
		mtlFile << "Ks " << 1.0 << " " << 1.0 << " " << 1.0 << endl;
		mtlFile.close();
	}

	void createOBJFile() {
		OBJFile.open("curve.obj");
		OBJFile << "mtllib " << "curve.mtl" << "\n" << endl;
		OBJFile << "g " << "curve" << "\n" << endl;
		OBJFile << "usemtl curve\n" << endl;
		OBJFile.close();
	}

	void addFaces(int index, int externalCurveSize, int faces, int n) {
		OBJFile.open("curve.obj", ios::app);
		if (n == 1) {
			OBJFile << "f " << index + externalCurveSize << "/" << 1 << "/" << faces << " " <<
				index + 1 + externalCurveSize << "/" << 2 << "/" << faces << " " <<
				index << "/" << 3 << "/" << faces << endl;
		}
		if (n == 2) {
			OBJFile << "f " << index + 1 + externalCurveSize << "/" << 2 << "/" << faces << " " <<
				index + 1 << "/" << 4 << "/" << faces << " " <<
				index << "/" << 3 << "/" << faces << endl;
		}
		if (n == 3) {
			OBJFile << "f " << index + externalCurveSize << "/" << 1 << "/" << faces << " " <<
				externalCurveSize + 1 << "/" << 2 << "/" << faces << " " <<
				index << "/" << 3 << "/" << faces << endl;
		}
		if (n == 4) {
			OBJFile << "f " << 1 + externalCurveSize << "/" << 2 << "/" << faces << " " <<
				1 << "/" << 4 << "/" << faces << " " <<
				index << "/" << 3 << "/" << faces << endl;
		}
		OBJFile.close();
	}

	void addNormalExternalCurve(glm::vec3 normal_vec_abac, glm::vec3 normal_vec_dbdc) {
		OBJFile.open("curve.obj", ios::app);
		OBJFile << "vn " << normal_vec_abac[0] << " " << normal_vec_abac[1] << " " << normal_vec_abac[2] << endl;
		OBJFile << "vn " << normal_vec_dbdc[0] << " " << normal_vec_dbdc[1] << " " << normal_vec_dbdc[2] << endl;
		OBJFile.close();
	}

	void addPointsFinalCurve(float x, float y, float z) {
		OBJFile.open("curve.obj", ios::app);
		OBJFile << "v " << x << " " << z << " " << y << endl;
		OBJFile.close();
	}

	void saveTextureValuesToOBJ() {
		//save texture points on obj
		OBJFile.open("curve.obj", ios::app);
		OBJFile << endl;
		OBJFile << "vt " << 1.0 << " " << 1.0 << endl;  
		OBJFile << "vt " << 1.0 << " " << 0.0 << endl;
		OBJFile << "vt " << 0.0 << " " << 1.0 << endl;
		OBJFile << "vt " << 0.0 << " " << 0.0 << endl;
		OBJFile << endl;
		OBJFile.close();
	}

};