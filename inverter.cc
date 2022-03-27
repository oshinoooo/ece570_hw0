#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<string> readFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open())
        return {};

    vector<string> out;
    string name;
    while (file >> name)
        out.push_back(name);

    file.close();

    return out;
}

vector<string> checkWords(const vector<string>& words) {
    vector<string> out;

    for (const string& word : words) {
        string tmp;

        for (const char& c : word) {
            if (isalpha(c))
                tmp.push_back(c);
            else {
                if (!tmp.empty())
                    out.push_back(tmp);
                tmp.clear();
            }
        }

        if (!tmp.empty())
            out.push_back(tmp);
    }

    return out;
}

int main(int argc, char* argv[]) {
    // check arguments
    if (argc != 2)
        return 0;

    // read first file
    vector<string> fileNames = readFile(argv[1]);
//    vector<string> fileNames = readFile("/Users/youlongliu/Desktop/TestCases/test.txt");

    // process files
    vector<vector<string>> words;
    for (const string& fileName : fileNames) {
        vector<string> originalContent = readFile(fileName);
        if (!originalContent.empty())
            words.push_back(checkWords(originalContent));
    }

    map<string, set<int>> records;
    for (int i = 0; i < words.size(); ++i) {
        for (const string& word : words[i])
            records[word].insert(i);
    }

    // print
    for (const pair<string, set<int>>& record : records) {
        cout << record.first << ":";
        for (const int& id : record.second)
            cout << " " << id;
        cout << endl;
    }
    return 0;
}
