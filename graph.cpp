#include <iostream>
#include "graph.h"

Graph::Graph(int numberofwebsites) {

	nodeNumber = numberofwebsites;
	adjacencymatrix = new int* [nodeNumber];
	for (int i = 0; i < numberofwebsites; i++) {
		adjacencymatrix[i] = new int[numberofwebsites];
	}
	for (int i = 0; i < numberofwebsites; i++) {
		for (int j = 0; j < numberofwebsites; j++) {
			adjacencymatrix[i][j] = 0;
		}
	}
}

void Graph::addEdge(int websitesource, int websitedestination) {

	adjacencymatrix[websitesource][websitedestination] = 1;
}

int** Graph::getadjacencyMatrix() {
	return adjacencymatrix;
}

vector<int> Graph::getIncomingwebsites(int website) {
	vector<int> incomingwebsites;
	for (int i = 0; i < nodeNumber; i++) {
		if (adjacencymatrix[i][website] == 1) { //INCOMING WEBSITE FOUND
			incomingwebsites.push_back(i);
		}
	}
	return incomingwebsites;
}

int Graph::getOutgoingwebsitenumber(int website) {
	int n=0;
	for (int i = 0; i < nodeNumber; i++) {
		if (adjacencymatrix[website][i] == 1) //OUTGOING WEBSITE FOUND
			n++;
	}

	return n;
}
