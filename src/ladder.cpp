#include "ladder.h"
#include <vector>
#include <string>
#include <iostream>
#include <set>
using namespace std;

void error(string word1, string word2, string msg) {
    cout << "Error: Word1: " << word1 << " and Word2: " << word2 << ": " << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs((int)str1.length() - (int)str2.length()) > d) {
        return false;
    }
    return is_adjacent(str1, str2);
}
bool is_adjacent(const string& word1, const string& word2) {
    if (abs((int)word1.length() - (int)word2.length()) > 1) {
        return false;
    }

    if (word1.length() == word2.length()) {
        int differnt_count = 0;
        for(size_t i = 0; i < word1.length(); ++i) {
            if (word1[i] != word2[i]) ++differnt_count;
            if (differnt_count > 1) return false;
        }
        return differnt_count <= 1;
    }

    const string& shorter = (word1.length() < word2.length()) ? word1 : word2;
    const string& longer = (word1.length() < word2.length()) ? word2 : word1;

    for (size_t i = 0; i < longer.length(); ++i) {
        string test = longer;
        test.erase(i, 1);
        if (test == shorter) return true;
    }

    return false;
}
vector<string> get_pattern(const string& word, const set<string>& word_list) {
    vector<string> result;
    for (const string& w : word_list)
        if (is_adjacent(word, w)) result.push_back(w);
    return result;
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Begin and end word are same.");
        return {};
    } else if (word_list.find(end_word) == word_list.end()) {
        error(end_word, "", "End word not in dictionary.");
        return {};
    }
    vector<string> current;
    queue<vector<string>> partial;
    partial.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!partial.empty()) {
        current = partial.front();
        partial.pop();
        string last = current.back();
        vector<string> possible = get_pattern(last, word_list);
        for (auto const& word : possible) {
            if (visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = current;
                new_ladder.push_back(word);
                if (word == end_word) return new_ladder;
                partial.push(new_ladder);
            }
        }
    }
    error(begin_word, end_word, "No word ladder found.");
    return {};
}
void load_words(set<string> & word_list, const string& file_name) {
    ifstream f(file_name);
    if (!f.is_open()) {
        cout << "Error: Could not open file: " << file_name << endl;
        return;
    }

    string word;
    while (f >> word) {
        word_list.insert(word);
    }
    f.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}