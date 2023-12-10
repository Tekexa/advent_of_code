#include <iostream>
#include <array>
#include <string>
#include <cctype>
#include <fstream>
#include <limits>

using namespace std;

bool entryIsInLine(string line, unsigned long long entry);
array<unsigned long long, 3> getIntsInLine(string line);
unsigned long long entryToOutInLine(string line, unsigned long long entry);
unsigned long long seedToLocation(unsigned long long seed, ifstream myMap);
unsigned long long getMiniLocation(ifstream myMap);


string FILE_NAME = "input05.txt";

int main() {
    unsigned long long res;
    // Specify the file name or path

    ifstream gardenerMap(FILE_NAME);
    if (gardenerMap.is_open()) {

        res = getMiniLocation(move(gardenerMap));

        cout << "The minimum location is : " << res << endl;
        // Close the file after use
        gardenerMap.close();
    } else {
        // File opening failed
        cerr << "Unable to open file: " << FILE_NAME << endl;
    }

    return 0;
}


bool entryIsInLine(string line, unsigned long long entry){
    /*
    * This function checks if the number is in the line
    * For example, 
    * 10 is in the line "25 8 4" because the entries are 8, 9, 10 and 11
    * but not in the line "15 12 3" because the entries are 12, 13 and 14    
    */
   array<unsigned long long, 3> resInts = getIntsInLine(line);
   if (entry >= resInts[1] && entry <= resInts[1] + resInts[2]) {
       return true;
   } else {
       return false;
   }
}


array<unsigned long long, 3> getIntsInLine(string line) {
    /*
    This function returns the integers of the line
    For example, in line "10 20 30" the ints are 10, 20 and 30 
    */
    unsigned long long a, b, c;
    array<string, 3> s_array;
    array<unsigned long long, 3> res;
    int i = 0;
    s_array = {"", "", ""};

    for (char c : line) {
        if (c == ' '){
            i++;
        } else if (isdigit(c)){
            s_array[i] += c;
        }
        if (i == 3) {
            break;
        }
    }
    i = 0;
    for (int i = 0; i < 3; i++) {
        res[i] = stoull(s_array[i]);
    }

    return res;
}

unsigned long long entryToOutInLine(string line, unsigned long long entry) {
    /*
    Assuming the entry is in the line, returns the ocrresponding
    output
    */
   array<unsigned long long, 3> resInts = getIntsInLine(line);
   return (entry - resInts[1] + resInts[0]);
}

unsigned long long seedToLocation(unsigned long long seed, ifstream myMap) {
    /*
    Given the number of one seed, returns the location
    Assumes the file is already open
    */
    string line;
    bool found_entry = false;
    unsigned long long curr_entry = seed;
    myMap.seekg(0, ios::beg); /* Comes back to the first line */
    getline(myMap, line); /* Skips seeds */
    getline(myMap, line); /* Skips blank line */
    getline(myMap, line); /* Skips title of first block */
    while (getline(myMap, line)) { /* Stops reading when at the end*/
        if (!found_entry) { /* Saves some computing time */
            if (isdigit(line[0])) {
                if (entryIsInLine(line, curr_entry)) {
                    curr_entry = entryToOutInLine(line, curr_entry);
                    found_entry = true;
                    cout << " New one : " << curr_entry << endl;
                }
            }
        }
        
        if (!isdigit(line[0])){
            found_entry = false; /* reset found_entry for the next block*/
        }
    }
    return curr_entry;
    /* Not done here in the function, but remember to close the file*/
}

unsigned long long getMiniLocation(ifstream myMap) {
    unsigned long long curr_min_loc, curr_seed;
    string line, temp_string;
    
    myMap.seekg(0, ios::beg);
    curr_min_loc = numeric_limits<unsigned long long>::max();
    temp_string = "";
    
    getline(myMap, line);
    for (char c : line) {
        if (isspace(c)) {
            myMap.close();
            myMap.open(FILE_NAME);
            // getline(myMap, line); /* Skips seeds */
            // cout << "Rebeginning at line : " << line << endl;*/
            curr_seed = stoull(temp_string);
            temp_string = "";
            cout << "Exploring seed number : " << curr_seed << endl;
            cout << "Seed to location of this seed : " << seedToLocation(curr_seed, move(myMap)) << endl;
            myMap.close();
            myMap.open(FILE_NAME);
            curr_min_loc = min(curr_min_loc, seedToLocation(curr_seed, move(myMap)));
            cout << "Current minimum location is : " << curr_min_loc << endl;
        }
        else {
            temp_string += c;
        }
    }
    /* Needs to do it one last time for the last number in line*/

    myMap.close();
    myMap.open(FILE_NAME);
    curr_seed = stoull(temp_string);
    curr_min_loc = min(curr_min_loc, seedToLocation(curr_seed, move(myMap)));
    
    cout << "Current minimum location is : " << curr_min_loc << endl;

    return curr_min_loc;
}