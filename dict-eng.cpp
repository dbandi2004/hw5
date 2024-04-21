#include <fstream>
#include <set>
#include <string>
#include "dict-eng.h"

const std::set<std::string>& readDictWords(std::string filename) {
    static std::set<std::string> dict;
    if (dict.size() == 0U) {
        std::ifstream ifile(filename.c_str());
        if (ifile.fail()) {
            throw std::logic_error("Cannot open dictionary file.");
        }
        std::string instr;
        while (ifile >> instr) {
            bool onlyLetters = true;
            for (char c : instr) {
                if (!isalpha(c)) {
                    onlyLetters = false;
                    break;
                }
            }
            if (onlyLetters) {
                dict.insert(instr);
            }
        }
        ifile.close();
    }
    return dict;
}
