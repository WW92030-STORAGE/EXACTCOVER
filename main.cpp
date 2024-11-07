#include <bits/stdc++.h>

#include "cover.h"

using namespace std;
#define pii pair<int, int>

#include <chrono>

// HOW TO USE

// Input file is csv. Lines with two slashes at the beginning (//) are comments and ignored.
// Each line has same number of entries which is N + 1. First entry is name and is only used for row identification.
// The remaining N entries denote the subset corresponding to that row and are used in calculating the cover.

// CONSTANTS

#define NUM_INACTIVE 2



void cover_matdisp(std::vector<std::vector<bool>>& mat, std::set<int>& rows, std::set<int>& cols) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            if (rows.find(i) != rows.end()) std::cout << "X";
            else if (cols.find(j) != cols.end()) std::cout << "X";
            else std::cout << mat[i][j];
        }
        std::cout << std::endl;
    }
}

vector<string> parserow(string s) {
    vector<string> res;
    int prev = -1;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ',') {
            res.push_back(s.substr(prev + 1, i - 1 - prev));
            prev = i;
            continue;
        }
    }
    res.push_back(s.substr(prev + 1));
    return res;
}

const bool DEBUG = false;

int main() // Example code. Input file must be formatted similarly to the provided one.
{
    ifstream fin("rareprotogens.in");
    string s;
    
    vector<vector<bool>> mat;
    vector<string> names;
    
    while (getline(fin, s)) {
        if (s[0] == '/' && s[1] == '/') continue;
        vector<string> a = parserow(s);
        names.push_back(a[0]);
        if (DEBUG) {
        cout << a[0] << " = ";
        for (int i = 1; i < a.size(); i++) cout << a[i] << " ";
        cout << "\\" << endl;
        }
        vector<bool> row;
        for (int i = 1; i < a.size(); i++) row.push_back((a[i][0] != '0'));
        mat.push_back(row);
    }
    
    DLX dlx;
    dlx.translate(mat);
    
    cout << dlx.solve(0) << endl;
    
    for (int i = 0; i < dlx.sol.size(); i++) {
        cout << (dlx.sol[i]->row - 1) << " = " << names[dlx.sol[i]->row - 1] << endl;
    }
    return 0;
}
