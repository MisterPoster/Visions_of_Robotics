#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctime>
#include <string> 
#include <sstream>

using namespace std;

int readParams (string fileName) {
	// Declaring variables
	ifstream infile;
	string line;
	int value;
	int numPoints;

	// Open file
	infile.open (fileName);

	// Read first line to get image parameters
	getline(infile,line); // Saves the line in STRING.

	istringstream iss(line);

	value=0;
	do {
		string sub;
		iss >> sub;
		if(value==2) numPoints = atoi(sub.c_str());

		value++;
	} while(iss);

	infile.close();

	return numPoints;
}
