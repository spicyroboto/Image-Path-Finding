#include "path.h"
#include <queue>
#include <stack>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e) {
	start = s;
	end = e;
	image = im;
	BFS();
}

void path::BFS(){
	vector<vector<bool>> V(image.height(), vector<bool> (image.width(),false));
	vector<vector<pair<int,int>>> P(image.height(), vector<pair<int,int>> (image.width(),end));
	queue<pair<int,int>> locationQ;

	V[start.second][start.first] = true;
	P[start.second][start.first] = start;
	locationQ.push(start);
	bool endWhile = true;

	while(!locationQ.empty() && endWhile) {
		pair<int,int> current = locationQ.front();
		V[current.second][current.first] = true;
		locationQ.pop();

		vector<pair<int,int>> nextPos = neighbors(current);

		for (size_t i = 0; i < nextPos.size(); i++) {
			if (good(V, current, nextPos[i])) {
				P[nextPos[i].second][nextPos[i].first] = current;
				V[nextPos[i].second][nextPos[i].first] = true;
				locationQ.push(nextPos[i]);
				if (current == end) {
					endWhile = false;
					break;
				}
			}

		}

	}

	pathPts = assemble(P,start,end);
}

PNG path::render(){
	PNG changed = image;
	pair<int,int> temp;
	while(!pathPts.empty()) {
		temp = pathPts.back();
		pathPts.pop_back();
		RGBAPixel* toChange = changed.getPixel(temp.first, temp.second);
		*toChange = RGBAPixel(255, 0, 0);
	}
	return changed;
}

bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
	bool inImage = false;
	bool notVisted = false;
	bool closeInColour = false;

	//(1)
	if (next.first > 0 && next.second > 0 && next.first < image.width() && next.second < image.height()) {
		inImage = true;

		if (v[next.second][next.first] == false) {
			notVisted = true;

			RGBAPixel* currP = image.getPixel(curr.first, curr.second);
			RGBAPixel* nextP = image.getPixel(next.first, next.second);
			if (closeEnough(*currP, *nextP)) {
				closeInColour = true;
			}
		}
	}
	return inImage && notVisted && closeInColour;
}

vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;
	n.push_back(pair<int,int>(curr.first + 1, curr.second));
	n.push_back(pair<int,int>(curr.first, curr.second + 1));
	n.push_back(pair<int,int>(curr.first - 1, curr.second));
	n.push_back(pair<int,int>(curr.first, curr.second - 1));
	return n;
}

vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p,pair<int,int> s, pair<int,int> e) {
	vector<pair<int,int>> allPts;
	stack<pair<int,int>> resultStack;
	pair<int,int> curr = e;

	while(curr != s) {
		resultStack.push(p[curr.second][curr.first]);
		curr = p[curr.second][curr.first];
	} 

	resultStack.push(s);
	
	while (!resultStack.empty()) {
		pair<int,int> value = resultStack.top();
		resultStack.pop();
		allPts.push_back(value);
	}
	
	return allPts;
}


/* PA4 - Completed for you for 2018S Semester */

bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
	int dist = (p1.r-p2.r)*(p1.r-p2.r);
	dist    += (p1.g-p2.g)*(p1.g-p2.g);
	dist    += (p1.b-p2.b)*(p1.b-p2.b);
	return (dist <= 80);
}

vector<pair<int,int>> path::getPath() { 
	return pathPts;
}

int path::length() { 
	return pathPts.size();
}
