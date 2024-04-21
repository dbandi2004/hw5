#include <iostream>
#include <set>
#include <vector>

using namespace std;

// Helper function to check if a word meets the criteria
bool is_valid_word(const string& word, const string& in, const string& floating, const set<string>& dict) {
    // Check if the word is in the dictionary
    if (dict.find(word) == dict.end()) {
        return false;
    }
    
    // Check for floating letter constraints
    vector<int> count(26, 0);
    for (char c : floating) {
        count[c - 'a']++;
    }

    for (char c : word) {
        count[c - 'a']--;
    }

    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            return false;
        }
    }

    return true;
}

// Recursive function to generate all valid words
void generate_words(string& current, int index, const string& in, const string& floating, const set<string>& dict, set<string>& results) {
    if (index == static_cast<int>(current.size())) {
        if (is_valid_word(current, in, floating, dict)) {
            results.insert(current);
        }
        return;
    }

    if (in[index] != '-') {
        current[index] = in[index];
        generate_words(current, index + 1, in, floating, dict, results);
    } else {
        for (char c = 'a'; c <= 'z'; c++) {
            current[index] = c;
            generate_words(current, index + 1, in, floating, dict, results);
        }
    }
}


// Main function to find matching words
set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
    set<string> results;
    string current = in;
    generate_words(current, 0, in, floating, dict, results);
    return results;
}
