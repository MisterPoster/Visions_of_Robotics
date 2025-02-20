#ifndef READ_WRITE_CALIB_H
#define READ_WRITE_CALIB_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class calibFile {
    public:
        // Constructor
        calibFile(string fileName);

        // Getters
        int getNumPoints() { return numPoints; }
        const float* getU() { return u.data(); }
        const float* getV() { return v.data(); }
        const float* getX() { return x.data(); }
        const float* getY() { return y.data(); }
        const float* getZ() { return z.data(); }
        const float* getZc() { return zc.data(); }

        // Public Methods
        void solveCalib();

    private:
        // Variables
        string fileName;
        int imageWidth;
        int imageHeight;
        int numPoints;
        vector<float> u;
        vector<float> v;
        vector<float> x;
        vector<float> y;
        vector<float> z;
        vector<float> zc;
        
        // Private methods
        void writeData();
        void readData();
};


// Reading calibration files
// int readNumPoints(string fileName);
// void readData(string fileName, float u[], float v[], float x[], float y[], float z[], float zc[]);

// // Solving for zc values
// void solveCalib();

// // Writing calibration files
// void writeData(string fileName, float u[], float v[], float x[], float y[], float z[], float zc[]);

#endif