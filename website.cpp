#include "website.h"


//GETTERS
string website::getLink() {
	return link;
}
int website::getImpressions() {
	return numberofimpressions;
}
int website::getClicks() {
	return  numberofclicks;
}
double website::getCTR() {
	return ctr;
}
double website::getPagerank() {
	return pagerank;
}
double website::getScore() {
	return score;
}
int website::getIndex() {
	return graphindex;
}
vector<string> website::getKeywords() {
	return keywords;
}

//SETTERS
void website::setLink(string l) {
	link = l;
}
void website::setImpressions(int i) {
	numberofimpressions = i;
}
void website::setClicks(int c) {
	numberofclicks = c;
}
void website::setPagerank(double p) {
	pagerank = p;
}
void website::setCTR() {
	ctr = numberofclicks / numberofimpressions;
}
void website::setScore() {
	score = 0.4 * pagerank + ((1 - ((0.1 * numberofimpressions) / (1 + 0.1 * numberofimpressions))) * pagerank + ((0.1 * numberofimpressions) / (1 + 0.1 * numberofimpressions)) * ctr) * 0.6;

}
void website::setIndex(int i) {
	graphindex = i;
}
void website::setKeywords(vector<string> k) {
	keywords = k;
}
void website::addClick() {
	numberofclicks++;
}
void website::addImpression() {
	numberofimpressions++;
}