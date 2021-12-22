#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>
#define pi   3.14159265358979323846264338327950288419716939937510
using namespace std;

void parseTextIntoMap(istream& in, map<string,int> & words) {
    string line;
    if (in) {
        while (getline(in, line)) {
            stringstream ss(line);
            while (getline(ss, line, '.')) {
                stringstream ss(line);
                while (getline(ss, line, ',')) {
                    stringstream ss(line);
                    while (getline(ss, line, ' ')) {

                        words[line]++;
                    }

                }
            }
        }
        words.erase("");
    }
    else {
        cout << "file reading error ";
    }
}

int main()
{
    double similarity, distance;
    unsigned int vectorproduct = 0, mod1 = 0, mod2 = 0;
    ifstream f1, f2;
    f1.open("file1.txt", ios::in);
    f2.open("file2.txt", ios::in);
    map<string, int> f1wordsMap, f2wordsMap;
    parseTextIntoMap(f1, f1wordsMap);
    parseTextIntoMap(f2, f2wordsMap);
    map<string, int >::const_iterator it1, it2;
        for (it1 = f1wordsMap.begin(); it1 != f1wordsMap.end(); it1++) {
            mod1 += it1->second * it1->second;
            for (it2 = f2wordsMap.begin(); it2 != f2wordsMap.end(); it2++) {
                if (it1->first == it2->first)
                        vectorproduct += (it1->second * it2->second);
                if (it1 == --f1wordsMap.end()) {
                        mod2 += it2->second * it2->second;
                }
            }
        }
    similarity = vectorproduct / sqrt(mod1 * mod2);
    distance = 180 * acos(similarity) / pi;
    cout << setprecision(4) << "the similarity between the two docments is " << similarity*100 << "% and the angle between the vector that represent each of document is " << distance << "\370." ;
}