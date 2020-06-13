#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

std::string getFileName() {
    bool badFile;
    std::string fileName;
    std::cout << "Enter file name (format: name.txt):\n";
    std::cin >> fileName;
    do {
        try {
            std::ifstream in (fileName);
            if (!in.good())         // Check if the data file exists
                throw 404;
            else if (fileName.substr(fileName.length()-4,4) != ".txt") { // Check its extension
                throw 321;
            } else {
                in.close();
                badFile = false;
            }
        } catch (int exception) {
            badFile = true;

            std::cout << "File " << fileName;
            if (exception == 404) 
                std::cout << " doesn't exist. ";
            else std::cout << " format is not supported. ";
            std::cout << "Please enter another name:\n";

            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> fileName;
        }
    } while (badFile); // Repeat until existing and supported file is entered
    return fileName;
}

void read(std::map<std::string, std::vector<int>>& words, std::vector<std::string>& urls) {
    std::string row, w;
    std::istringstream rowStream;
    int numOfLine = 0;

    std::ifstream in (getFileName());
    while (std::getline(in, row)) {       // Continue reading lines until the end of file is reached
        rowStream.clear();                // Delete previous error flags
        rowStream.str(row);               // Make the line readable
        numOfLine ++;

        while (rowStream >> w) {   // Continue reading words from ss until the end of line is reached
            if (w.find("www.") != std::string::npos || w.find("http") != std::string::npos) {
                urls.push_back(w);
            } else {
                // Remove all non-letter symbols from the w
                w.erase(std::remove_if(w.begin(), w.end(), [](char c) { return !isalpha(c); } ), w.end());

                if (w != "") {   // If there are any characters left
                    // Turn all letters to lowercase
                    std::transform(w.begin(), w.end(), w.begin(), [](unsigned char c){ return std::tolower(c); });
                    // Add the line number to the vector of lines
                    words[w].push_back(numOfLine);
                }
            }
        }
    }
    in.close();
}

void print(std::map<std::string, std::vector<int>>& words, std::vector<std::string>& urls) {
    std::ofstream out ("statistics.txt");
    // Header
    out << std::left << std::setw(15) << "Word" << std::setw(15) 
        << "Frequency" << std::setw(15) << "Lines" << "\n";
    for (int i = 0; i < 50; i ++)
        out << "-";

    for (auto w : words)
        if (w.second.size() > 1) {                   // If the word's frequency is > 1
            out << "\n" << std::setw(15) << w.first  // Print the word
                << std::setw(15) << w.second.size(); // Print its frequency
            for (auto line : w.second)       // Print lines where the word is mentioned
                out << line << " ";
        }

    // URLs
    out << "\n\nLinks\n";
    for (int i = 0; i < 50; i ++)
        out << "-";
    out << "\n";
    for (std::string u : urls)
        out << u << "\n";

    out.close();
}

int main() {
    std::vector<std::string> urls;
    std::map<std::string, std::vector<int>> words; // Key: word, value: lines of occurencies

    read(words, urls);
    print(words, urls);

    std::cout << "\nThe program finished successfully.\n";
    return 0;
}