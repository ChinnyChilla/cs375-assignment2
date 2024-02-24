#include "stdlib.h"
#include "vector"
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

bool contains3dPoints(const string inputfile)
{
	ifstream file(inputfile);
	if (file.is_open())
	{
		string line;
		getline(file, line);
		istringstream iss(line);
		int count = 0;
		while (iss >> line)
		{
			count++;
			if (count == 3)
			{
				file.close();
				return true;
			}
		}
		file.close();
		return false;
	}
	else
	{
		cout << "Unable to open file";
		return false;
	}
};

bool readInputFile(const string &inputfile, vector<pair<int, int>> &points, vector<vector<int>> &points3d)
{
	bool has3d = contains3dPoints(inputfile);
	ifstream file(inputfile);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			int x, y;
			istringstream iss(line);
			if (has3d)
			{
				int z;
				iss >> x >> y >> z;
				points3d.push_back({x, y, z});
			}
			else
			{
				iss >> x >> y;
				points.push_back(make_pair(x, y));
			}
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file";
	}
	return has3d;
};

double distance(pair<int, int> p1, pair<int, int> p2) {
	return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

vector<pair<int, int>> bruteForce(vector<pair<int,int>> points) {
	double min_distance = INFINITY;
	vector<pair<int, int>> closest;
	int first_pair = -1;
	int second_pair = -1;

	for (unsigned long i = 0; i < points.size(); i++)
	{
		for (unsigned long j = i + 1; j < points.size(); j++)
		{
			double d = distance(points[i], points[j]);
			if (d < min_distance)
			{
				min_distance = d;
				first_pair = i;
				second_pair = j;
			}
		}
	}
	closest.push_back(points[first_pair]);
	closest.push_back(points[second_pair]);
	return closest;
}

vector<pair<int, int>> closestPair(vector<pair<int, int>> points) {
	if (points.size() <= 3) {
		return bruteForce(points);
	};
	int middle = points.size() / 2;
	
	vector<pair<int, int>> closestLeftPair = closestPair(vector<pair<int, int>>(points.begin(), points.begin() + middle));
	vector<pair<int, int>> closestRightPair = closestPair(vector<pair<int, int>>(points.begin() + middle, points.end()));
	double leftPairDistance = distance(closestLeftPair[0], closestLeftPair[1]);
	double rightPairDistance = distance(closestRightPair[0], closestRightPair[1]);


	double minDistance = min(leftPairDistance, rightPairDistance);
	double middleX = points[middle].first;

	vector<pair<int, int>> pointsInStrip;
	for (unsigned long i = 0; i < points.size(); i++)
	{
		if (abs(points[i].first - middleX) < minDistance)
		{
			pointsInStrip.push_back(points[i]);
		}
	}
	sort(pointsInStrip.begin(), pointsInStrip.end(), [](pair<int, int> p1, pair<int, int> p2) {
		return p1.second < p2.second;
	});
	double stripClosestDistance = INFINITY;
	vector<pair<int, int>> stripClosestPair;
	for (unsigned long i = 0; i < pointsInStrip.size(); i++)
	{
		for (unsigned long j = i + 1; j < pointsInStrip.size() && (pointsInStrip[j].second - pointsInStrip[i].second) < minDistance; j++)
		{
			double d = distance(pointsInStrip[i], pointsInStrip[j]);
			if (d < stripClosestDistance)
			{
				stripClosestDistance = d;
				stripClosestPair = {pointsInStrip[i], pointsInStrip[j]};
			}
		}
	}
	if (stripClosestDistance < minDistance) return stripClosestPair;
	return leftPairDistance < rightPairDistance ? closestLeftPair : closestRightPair;
	
};

vector<pair<int, int>> divide_2d(vector<pair<int, int>> points) {
	sort(points.begin(), points.end());
	return closestPair(points);
}



double distance3d(vector<int> p1, vector<int> p2) {
	return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2) + pow(p1[2] - p2[2], 2));
};
vector<vector<int>> bruteForce3d(vector<vector<int>> points) {
	double min_distance = INFINITY;
	vector<vector<int>> closest;
	int first_pair = -1;
	int second_pair = -1;

	for (unsigned long i = 0; i < points.size(); i++)
	{
		for (unsigned long j = i + 1; j < points.size(); j++)
		{
			double d = distance3d(points[i], points[j]);
			if (d < min_distance)
			{
				min_distance = d;
				first_pair = i;
				second_pair = j;
			}
		}
	}
	closest.push_back(points[first_pair]);
	closest.push_back(points[second_pair]);
	return closest;
}



vector<vector<int>> closestPair3d(vector<vector<int>> points) {
	if (points.size() <= 3) {
		return bruteForce3d(points);
	};
	int middle = points.size() / 2;
	vector<vector<int>> closestLeftPair = closestPair3d(vector<vector<int>>(points.begin(), points.begin() + middle));
	vector<vector<int>> closestRightPair = closestPair3d(vector<vector<int>>(points.begin() + middle, points.end()));
	double leftPairDistance = distance3d(closestLeftPair[0], closestLeftPair[1]);
	double rightPairDistance = distance3d(closestRightPair[0], closestRightPair[1]);

	double minDistance = min(leftPairDistance, rightPairDistance);
	double middleX = points[middle][0];
	vector<vector<int>> pointsInCube;
	for (unsigned long i = 0; i < points.size(); i++)
	{
		if (abs(points[i][0] - middleX) < minDistance)
		{
			pointsInCube.push_back(points[i]);
		}
	}
	sort(pointsInCube.begin(), pointsInCube.end(), [](vector<int> p1, vector<int> p2) {
		return p1[1] < p2[1];
	});
	double cubeClosestDistance = INFINITY;
	vector<vector<int>> cubeClosestPair;
	for (unsigned long i = 0; i < pointsInCube.size(); i++)
	{
		for (unsigned long j = i + 1; j < pointsInCube.size() && (distance3d(pointsInCube[i], pointsInCube[j]) < minDistance); j++)
		{
			double d = distance3d(pointsInCube[i], pointsInCube[j]);
			if (d < cubeClosestDistance)
			{
				cubeClosestDistance = d;
				cubeClosestPair = {pointsInCube[i], pointsInCube[j]};
			}
		}
	}
	if (cubeClosestDistance < minDistance) return cubeClosestPair;
	return leftPairDistance < rightPairDistance ? closestLeftPair : closestRightPair;
}

vector<vector<int>> divide_3d(vector<vector<int>> points) {

	sort(points.begin(), points.end(), [](vector<int> p1, vector<int> p2) {
		return p1[0] < p2[0];
	});
	return closestPair3d(points);
}

int main(int argc, char *argv[]) {

	if (argc < 3) {
		cout << "Missing arguments: " << argv[0] << " <inputfile> <outputfile>" << endl;
		return 1;
	
	}

	vector<pair<int, int>> points;
	vector<vector<int>> points3d;
	// Putting in test data
	string inputFile = argv[1];
	bool is3d = readInputFile(inputFile, points, points3d);


	ofstream outputfile(argv[2]);

	if (is3d) {
		outputfile << "found 3d points, running 3d algorithm" << endl;

		auto start = chrono::high_resolution_clock::now();
		vector<vector<int>> bruteForceResult = bruteForce3d(points3d);
		auto end = chrono::high_resolution_clock::now();
		auto diff = end - start;
		outputfile << "brute force took " << chrono::duration<double, milli>(diff).count() << " ms" << endl;
		outputfile << "the closest points (brute force) are: (" << bruteForceResult[0][0] << ", " << bruteForceResult[0][1] << ", " << bruteForceResult[0][2] << ") and (" << bruteForceResult[1][0] << ", " << bruteForceResult[1][1] << ", " << bruteForceResult[1][2] << ")" << endl;
		outputfile << "the closest distance (brute force) is: " << distance3d(bruteForceResult[0], bruteForceResult[1]) << endl;

		auto start2 = chrono::high_resolution_clock::now();
		vector<vector<int>> divide = divide_3d(points3d);
		auto end2 = chrono::high_resolution_clock::now();
		auto diff2 = end2 - start2;
		outputfile << "divide and conquer took " << chrono::duration<double, milli>(diff2).count() << " ms" << endl;
		outputfile << "the closest points (divide and conquer) are: (" << divide[0][0] << ", " << divide[0][1] << ", " << divide[0][2] << ") and (" << divide[1][0] << ", " << divide[1][1] << ", " << divide[1][2] << ")" << endl;
		outputfile << "the closest distance (divide and conquer) is: " << distance3d(divide[0], divide[1]) << endl;
	} else {
		auto start = chrono::high_resolution_clock::now();
		vector<pair<int, int>> bruteForceResult = bruteForce(points);
		auto end = chrono::high_resolution_clock::now();
		auto diff = end - start;

		outputfile << "brute force took " << chrono::duration<double, milli>(diff).count() << " ms" << endl;
		outputfile << "the closest points (brute force) are: (" << bruteForceResult[0].first << ", " << bruteForceResult[0].second << ") and (" << bruteForceResult[1].first << ", " << bruteForceResult[1].second << ")" << endl;
		outputfile << "the closest distance is: " << distance(bruteForceResult[0], bruteForceResult[1]) << endl;

		// divide and conquer
		auto start2 = chrono::high_resolution_clock::now();
		vector<pair<int, int>> divide = divide_2d(points);
		auto end2 = chrono::high_resolution_clock::now();
		auto diff2 = end2 - start2;

		outputfile << "divide and conquer took " << chrono::duration<double, milli>(diff2).count() << " ms" << endl;
		outputfile << "the closest points (divide and conquer) are: (" << divide[0].first << ", " << divide[0].second << ") and (" << divide[1].first << ", " << divide[1].second << ")" << endl;
		outputfile << "the closest distance (divide and conquer) is: " << distance(divide[0], divide[1]) << endl;
	}

	outputfile.close();
	return 0;
}