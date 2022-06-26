#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Graph {
private:
	int** adjacencymatrix;
	int nodeNumber;
public:


	Graph(int numberofwebsites);
	void addEdge(int websitesource, int websitedestination);

	//GETTERS
	int** getadjacencyMatrix();
	vector<int> getIncomingwebsites(int website);
	int getOutgoingwebsitenumber(int website);
	//SETTERS

};