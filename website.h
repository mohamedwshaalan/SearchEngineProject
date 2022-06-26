#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <list>
using namespace std;

class website {
private:
	string link;
	int numberofimpressions;
	int numberofclicks;
	double pagerank;
	double ctr;
	double score;
	int graphindex;
	vector<string> keywords;
public:

	//GETTERS
	string getLink();
	int getImpressions();
	int getClicks();
	double getPagerank();
	double getCTR();
	double getScore();
	int getIndex();
	vector<string> getKeywords();

	//SETTERS
	void setLink(string l);
	void setImpressions(int i);
	void setClicks(int c);
	void setPagerank(double p);
	void setCTR();
	void setScore();
	void setIndex(int i);
	void setKeywords(vector<string> k);
	void addClick();
	void addImpression();
};