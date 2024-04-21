#include <iostream>
#include <set>
#include "wordle.h"
#include "dict-eng.h"

// Helper function to load dictionary
std::set<std::string> loadTestDictionary() {
    std::set<std::string> dict = {"apple", "apply", "ban", "band", "bond"};
    std::cout << "Loaded dictionary words: ";
    for (const auto& word : dict) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    return dict;
}


// Function to print test result
void printTestResult(bool passed, const std::string& testName) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

// Test for basic functionality
void testBasicFunctionality() {
    auto dict = loadTestDictionary();
    auto results = wordle("a--le", "pp", dict);
    bool passed = results.size() == 2 && results.find("apple") != results.end() && results.find("apply") != results.end();
    printTestResult(passed, "testBasicFunctionality");
}

// Test for no valid words
void testNoValidWords() {
    auto dict = loadTestDictionary();
    auto results = wordle("x--z-", "qrs", dict);
    bool passed = results.empty();
    printTestResult(passed, "testNoValidWords");
}

// Test with no floating characters
void testNoFloatingChars() {
    auto dict = loadTestDictionary();
    auto results = wordle("band", "", dict);
    bool passed = results.size() == 1 && results.find("band") != results.end();
    printTestResult(passed, "testNoFloatingChars");
}

// Main function that runs all tests
int main() {
    testBasicFunctionality();
    testNoValidWords();
    testNoFloatingChars();
    std::cout << "All tests executed!" << std::endl;
    return 0;
}
