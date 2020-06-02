#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>
 
void read(std::map<std::string, int>& freq, std::vector<std::string>& urls, std::map<std::string, std::vector<int>>& lines) {
    std::string row, word;
    std::istringstream rowStream;
    int numOfLine = 0;

    std::ifstream in ("text.txt");
    while (std::getline(in, row)) {       // Continue reading lines until the end of file is reached
        rowStream.clear();                // Delete previous error flags
        rowStream.str(row);               // Make the line readable
        numOfLine ++;

        while (rowStream >> word) {   // Continue reading words from ss until the end of line is reached
            if (word.find("www.") != std::string::npos || word.find("http") != std::string::npos) {
                urls.push_back(word);
            } else {
                // Remove all non-letter symbols from the word
                word.erase(std::remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());

                if (word != "") {   // If there are any characters left
                    // Turn all letters to lowercase
                    std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::tolower(c); });

                    freq[word] ++;  // Find the word in the map and increase its value (frequency)
                    lines[word].push_back(numOfLine);   // Save the line to the word's vector
                }
            }
        }
    }
    in.close();
}

void print(std::map<std::string, int>& freq, std::vector<std::string>& urls, std::map<std::string, std::vector<int>>& lines) {
    std::ofstream out ("stats.txt");
    // Header
    out << std::left << std::setw(15) << "Word" << std::setw(15) << "Frequency" << std::setw(15) << "Lines" << "\n";
    for (int i = 0; i < 50; i ++)
        out << "-";

    // Words, their frequency and lines where they are mentioned
    for (auto f : freq)
        if (f.second > 1) {
            out << "\n" << std::setw(15) << f.first << std::setw(15) << f.second;
            for (auto l : lines[f.first])
                out << l << " ";
        }

    // URLs
    out << "\n\nLinks\n------------------------------------\n";
    for (std::string u : urls)
        out << u << "\n";

    out.close();
}

int main() {
    std::vector<std::string> urls;
    std::map<std::string, int> freq;    // Every key is mapped with default value zero
    std::map<std::string, std::vector<int>> lines;
    
    read(freq, urls, lines);
    print(freq, urls, lines);

    return 0;
}