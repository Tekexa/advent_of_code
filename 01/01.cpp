#include <iostream>
#include <fstream>
using namespace std;

int countInElfFile(string fileName);
int countInLine(string line);
bool isNumber(char p_char);

int main() {
    int res;
    // Specify the file name or path
    string fileName = "01/input.txt";

    res = countInElfFile(fileName);

    cout<< "The result is: " << res << endl;

    return 0;
}

int countInElfFile(string fileName){
    int resCount;

    resCount = 0;
    ifstream elfFile(fileName);

    // Check if the file is successfully opened
    if (elfFile.is_open()) {
        // For example, read and print the contents of the file
        string line;

        while (getline(elfFile, line)) {
            resCount += countInLine(line);
        }

        // Close the file after use
        elfFile.close();
    } else {
        // File opening failed
        cerr << "Unable to open file: " << fileName << endl;
    }
    return resCount;
}

int countInLine(string line) {
    int resLine;
    int n;
    int i;
    bool found;
    string numInStr;

    found = false;
    n = line.length();
    i = 0;
    numInStr = "";

    while ((i < n) && (!found)) {
        if (isNumber(line[i])){
            found = true;
            numInStr += line[i];
        }
        i++;
    }

    i = n - 1;
    found = false;

    while ((i>=0) && (!found)){
        if (isNumber(line[i])){
            found = true;
            numInStr += line[i];
        }
        i--;
    }
    resLine = stoi(numInStr);
    
    return resLine;
}

bool isNumber(char p_char){
    bool flag;
    flag = false;
    if ((int)p_char - '0' >= 0){
        if ((int)p_char - '0' <= 9){
            flag = true;
        }
    }
    return flag;
}