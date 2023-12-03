#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

int countInElfFile(string fileName, list<string> numList);
int countInLine(string line, list<string> numList);
bool isNumber(char p_char);
string firstNumber(string line, list<string> numList);
string lastNumber(string line, list<string> numList);
string lettersToDigit(string lettersInt, list<string> numList);

int main() {
    string resBeg, resEnd;
    string line1;

    // Specify the file name or path
    string fileName = "01/input.txt";
    list<string> listOfDigitsStr{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    ifstream elfFile(fileName);

    cout << "The final result is: " << countInElfFile(fileName, listOfDigitsStr);
    return 0;
}

int countInElfFile(string fileName, list<string> numList){
    int resCount;

    resCount = 0;
    ifstream elfFile(fileName);

    // Check if the file is successfully opened
    if (elfFile.is_open()) {
        string line;

        while (getline(elfFile, line)) {
            resCount += countInLine(line, numList);
        }
        // Close the file after use
        elfFile.close();
    } else {
        // File opening failed
        cerr << "Unable to open file: " << fileName << endl;
    }
    return resCount;
}

int countInLine(string line, list<string> numList) {
    int resLine;
    int n;
    int i;
    bool found;
    string numInStr;

    found = false;
    n = line.length();
    i = 0;
    numInStr = "";

    resLine = stoi(firstNumber(line, numList) + lastNumber(line, numList));
    
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

string firstNumber(string line, list<string> numList){
    int nLine;
    int nList;
    int i = 0;
    list<string>::iterator j;
    string res;
    bool found = false;
    int pos;

    nLine = line.length();
    nList = numList.size();

    // Iterate through the line with one more chracater each time
    while ((i < nLine) && (!found)) {
        if (isNumber(line[i])) {
            res = line[i];
            found = true;
        }
        else {
            for (j = numList.begin(); j != numList.end(); j++) {
                if (line.substr(0, i+1).find(*j) != line.npos){
                    res = lettersToDigit(*j, numList);
                    found = true;
                }
            }
        }
        i++;
    }
    return res;
}

string lastNumber(string line, list<string> numList){
    int nLine;
    int nList;
    int i;
    list<string>::iterator j;
    string res;
    bool found = false;
    int pos;

    nLine = line.length();
    nList = numList.size();

    i = nLine - 1;

    // Iterate through the line with one more chracater each time
    while ((i >= 0) && (!found)) {
        if (isNumber(line[i])) {
            res = line[i];
            found = true;
        }
        else {
            for (j = numList.begin(); j != numList.end(); j++) {
                if (line.substr(i, nLine + 1).find(*j) != line.npos){
                    res = lettersToDigit(*j, numList);
                    found = true;
                }
            }
        }
        i--;
    }
    return res;
}

string lettersToDigit(string lettersInt, list<string> numList) {
    int position = 0;
    list<string>::iterator it = find(numList.begin(), numList.end(), lettersInt);
    if (it != numList.end()) {
        position = distance(numList.begin(), it) + 1;
    }
    return to_string(position);
}
