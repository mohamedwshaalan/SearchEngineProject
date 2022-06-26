#pragma once
#include <iostream>
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <list>
#include "graph.h"
#include "website.h"

//using namespace std;

void welcomePage();
void viewPage(website viewingwebsite, vector<website> websitevector);
int enterUserChoice();
string searchQuery();
vector<website> sortByscore(vector<website> websitevector);
vector<website> getSortedWebsiteVector(vector<website> websitevector, Graph websitegraph);
string getSearchType(string searchquery);
vector<string> getSearchedWords(string searchquery);
vector<website> getRelevantwebsites(vector<string> searchedwordsvector, vector<website> websitevector, string searchType);
vector<website> searchEngine(vector<website> websitevector, Graph websitegraph,string searchquery);
