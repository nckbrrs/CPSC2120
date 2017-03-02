/*
	Nicholas Barrs	
	nbarrs
	CPSC 2121-001
	10 November 2015
	lab 10 - closest pair of points with STL
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair <double, double> Point;

vector<Point> v;
set<Point> s;
double D = sqrt(2);

double distance(double x1, double x2, double y1, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	return sqrt(dx*dx + dy*dy);
}

void solve (void)
{
	double new_dist;
	int i=0;

	for (int j=0; j<v.size(); j++) {
		s.insert(Point(v[j].second, v[j].first));
		set<Point>::iterator it;

		// loop back until more than D y-distance from v[j]
		it = s.find(Point(v[j].second, v[j].first)); it--;
		while (v[j].second - it->first < D && it != s.begin()) {
			new_dist = distance(v[j].first, it->second, v[j].second, it->first);
			if (new_dist < D) D = new_dist;
			it--;
		}
	
		// reset it to v[j] and loop forward until more D y-distance from v[j]
		it = s.find(Point(v[j].second, v[j].first)); it++;
		while (it != s.end() && it->first - v[j].second < D) {
			new_dist = distance(v[j].first, it->second, v[j].second, it->first);
			if (new_dist < D) D = new_dist;
			it++;			
		}
	
		// remove points that are farther than D from v[j] from s
		while (v[j].first-v[i].first > D) {
			s.erase(s.find(Point(v[i].second, v[i].first)));
			i++;
		}
	}
}


int main (void)
{
	ifstream input("points.txt");
	double x, y;
	while (input >> x >> y) v.push_back(Point(x,y));	
	sort(v.begin(), v.end());
	solve();
	cout << D;
}
