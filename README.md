# Word frequency counter

C++ console program which counts the frequency of words in a given text and prints out all words that have been mentioned more than 2 times, their places in lines and all links that appear in the text.

The main *words* object was built using *std::map, std::string* and *std::vector*

Supported input file format: .txt


## Installation and execution

 1. Download the code from [the releases page](https://github.com/Naktis/word-counter/releases) or using *git*:

    `git clone https://github.com/Naktis/word-counter.git`
 2. Download and install a C++ compiler (i.e. [GCC](https://gcc.gnu.org/))
 3. Navigate to the directory of the program
 4. Compile the program (If you use GCC, type `g++ counter.cpp -o counter`)
 5. Run the program with `./counter` (unix) or `counter` (win)
 6. Enter your file name with its extension (i.e. `text.txt`)
 7. View the results by typing (./)`statistics.txt`