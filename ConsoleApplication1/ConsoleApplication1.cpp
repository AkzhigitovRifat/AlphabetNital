#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unordered_set>

using namespace std;

void dfs(char letter, unordered_map<char, unordered_set<char>>& graph, unordered_set<char>& visited, vector<char>& result) {
    visited.insert(letter);

    for (char next : graph[letter]) {
        if (visited.find(next) == visited.end()) {
            dfs(next, graph, visited, result);
        }
    }

    result.push_back(letter);
}

string findAlphabet(vector<string>& glossary) {
    unordered_map<char, unordered_set<char>> graph;

    for (int i = 0; i < glossary.size() - 1; i++) {
        string word1 = glossary[i];
        string word2 = glossary[i + 1];

        for (int j = 0; j < min(word1.length(), word2.length()); j++) {
            if (word1[j] != word2[j]) {
                graph[word1[j]].insert(word2[j]);
                break;
            }
        }
    }

    unordered_set<char> visited;
    vector<char> result;

    for (auto& entry : graph) {
        if (visited.find(entry.first) == visited.end()) {
            dfs(entry.first, graph, visited, result);
        }
    }

    reverse(result.begin(), result.end());

    return string(result.begin(), result.end());
}

int main(int argc, const char* argv[]) {
    if (argc == 3) {
        try {
            string filename = argv[1];
            ifstream file(filename);
            ofstream outputFile(argv[2]);
            vector<string> glossary;
            if (!file.is_open()) {
                cerr << "Failed to open file: " << filename << endl;
                return 1;
            }
            string line;
            getline(file, line);
            while (getline(file, line)) {
                glossary.push_back(line);
            }

            string alphabet = findAlphabet(glossary);

            cout << "Alphabet of Nital people: " << alphabet << endl;
            outputFile << alphabet << endl;
        }
        catch (const exception& e) {
            cout << "Exeption: " << e.what() << endl;
        }
    }
    return 0;
}