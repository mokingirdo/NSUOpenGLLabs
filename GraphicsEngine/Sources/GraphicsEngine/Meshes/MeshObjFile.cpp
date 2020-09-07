#include "MeshObjFile.h"
#include "GraphicsEngine/Application.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

MeshObjFile::MeshObjFile(const char * filepath)
{
	m_filepath = Application::Instance().GetDataDirectory() + "/" + filepath;
}

vector<string> getStrings(string line, char del) {
	vector<string> values;
	unsigned long first = 0;
	unsigned long last;
	do {
		last = line.find(del, first);
		string substr = line.substr(first, last - first);
		values.push_back(substr);
		first = last + 1;
	} while (last != string::npos);

	return values;
}

vector<double> parseStrings(string str) {
	vector<string> strings = getStrings(str, ' ');
	vector<double> values;

	for (string s : strings) {
		values.push_back(atof(s.c_str()));
	}
	return values;
}

void MeshObjFile::Init()
{
	Mesh::Init();

	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Vector3> uv0;

	vector<Vector4> color;

	vector<int> vertexInd;
	vector<int> textureInd;
	vector<int> normalInd;

	string line;
	unsigned long stringsSize;

	ifstream input;
	input.open(m_filepath);

	if (!input) {
		return;
	}

	while (getline(input, line)) {
		//cout << line << endl;
		switch (line[0])
		{
		case ('v') :{
			switch (line[1])
			{
			case (' ') :{
				line = line.substr(2);
				vector<double> vertCoords = parseStrings(line);
				vertices.push_back(Vector3(vertCoords[0], vertCoords[1], vertCoords[2]));
				break;
			}
			case ('n') :{
				line = line.substr(3);
				vector<double> normalCoords = parseStrings(line);
				normals.push_back(Vector3(normalCoords[0], normalCoords[1], normalCoords[2]));
				break;
			}
			case ('t') :{
				line = line.substr(3);
				vector<double> uvCoords = parseStrings(line);
				uv0.push_back(Vector3(uvCoords[0], uvCoords[1], 0));
				break;
			}

			default:
				break;
			}
			break;
		}
		case('f') :{
			line = line.substr(2);
			vector<string> strings = getStrings(line, ' ');
			stringsSize = strings.size();
			for (string s : strings) {
				vector<string> inds = getStrings(s, '/');
				vector<int> indsNumbers;
					for (string s : inds) {
						indsNumbers.push_back(atoi(s.c_str()));
					}	
					for (int i = 0; i < indsNumbers.size(); ++i) {
						indsNumbers[i] -= 1;
					}
				vertexInd.push_back(indsNumbers[0]);
				textureInd.push_back(indsNumbers[1]);
				normalInd.push_back(indsNumbers[2]);
			}
			break;
		}
		default:
			break;
		}
	}

	for (int i = 0; i < vertices.size(); i++) {
		color.push_back(Vector4(1.0, 1.0, 1.0, 1.0));
	}

	meshImpl->SetVertices(vertices);
	meshImpl->SetColors(color);
	meshImpl->SetNormals(normals);
	meshImpl->SetUV0(uv0);

	meshImpl->SetIndices(vertexInd, MESH_TOPOLOGY_TRIANGLE_LIST);

	meshImpl->Apply();
}

void MeshObjFile::Deinit()
{
	Mesh::Deinit();
}
