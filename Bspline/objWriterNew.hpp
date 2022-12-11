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

	void addFaces(int size) {

		OBJFile.open("curve.obj", ios::app);

		int index = 0;
		int faces = 0;

		for (int i = 0; i < size -1; i++) {
			int j = i + 1;
			OBJFile << "f " << j << "/" << 1 << "/" << 1 << " " <<
				j + 1 << "/" << 2 << "/" << 1 << " " <<
				j + size << "/" << 4 << "/" << 1 <<
				std::endl;

			OBJFile <<
				"f " << j + size << "/" << 4 << "/" << 1 << " " <<
				j + 1 << "/" << 2 << "/" << 1 << " " <<
				j + 1 + size << "/" << 3 << "/" << 1 <<
				std::endl;
		}
		OBJFile.close();

	}

	void addNormalExternalCurve(int size) {
		OBJFile.open("curve.obj", ios::app);
		OBJFile << "vn 0 1 0" << endl;
		
		OBJFile.close();
	}

	void addPointsCurve(vector<glm::vec3*>* vec) {
		OBJFile.open("curve.obj", ios::app);

		for (int i = 0; i < vec->size(); i++) {
			OBJFile << "v " <<
				vec->at(i)->x << " " <<
				vec->at(i)->z << " " <<
				vec->at(i)->y << std::endl;
		}

		OBJFile.close();
	}

	void saveTextureValuesToOBJ() {
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