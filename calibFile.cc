#include "calibFile.h"
using namespace std;

// Constructor
calibFile::calibFile(string fileName_) {
    // Initialize variables
    fileName = fileName_;
    numPoints = -1;
    imageWidth = -1;
    imageHeight = -1;

    // Read the data
    this->readData();
}

// Public Methods
void calibFile::solveCalib() {
    // Get the distance from the camera to the calibration cube
    cout << "Enter the distance (in mm) from the camera to the calibration cube: ";
    float distance;
    cin >> distance;

    // TODO: Doing what ever math we had before

    // Write data to file
    this->writeData();
}

// Private Methods
void calibFile::readData() {
    // Open file
    ifstream infile(fileName);
    
    // Read first line to get image parameters
    string line;
    getline(infile, line); // Saves the line in STRING.
    
    istringstream iss(line);
    
    int value = 0;
    string sub;
    while (iss >> sub) {
        if (value == 0) imageWidth = atoi(sub.c_str());
        if (value == 1) imageHeight = atoi(sub.c_str());
        value++;
    }

    printf("Image params %d %d \n", imageWidth, imageHeight);

    // Read point data
    numPoints = 0;
    while (getline(infile, line)) {
        istringstream iss(line);

        value = 0;
        while (iss >> sub) {
            if (value == 0) u.push_back(imageWidth - atof(sub.c_str()));
            if (value == 1) v.push_back(atof(sub.c_str()));
            if (value == 2) x.push_back(atof(sub.c_str()) * 25.0);
            if (value == 3) y.push_back(atof(sub.c_str()) * 25.0);
            if (value == 4) z.push_back(atof(sub.c_str()) * 25.0);
            if (value == 5) zc.push_back(atof(sub.c_str()));
            value++;
        }

        printf("Calibration data  %f %f %f %f %f %f \n", u.back(), v.back(), x.back(), y.back(), z.back(), zc.back());
        numPoints++;
    }

    infile.close();
}

void calibFile::writeData() {
    // Open the file
    ofstream outfile(fileName);
    int numPoints = sizeof(u) / sizeof(u[0]);

    // Write the parameters
    outfile << imageWidth << " " << imageHeight << endl;

    // Write the data
    for (int i = 0; i < numPoints; i++) {
        outfile << u[i] << " " << v[i] << " " << x[i] << " " << y[i] << " " << z[i] << " " << zc[i] << endl;
    }

    outfile.close();
}