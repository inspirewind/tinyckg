#include "FastaReader.h"
#include <fstream>
#include <iostream>

FastaReader::FastaReader(const std::string &filename) : filename(filename) {}

void FastaReader::read() {
    parseFasta();
}

std::string FastaReader::getSequence() const {
    return sequence;
}

void FastaReader::parseFasta() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        if (line[0] != '>') {
            sequence += line;
        }
    }

    file.close();
}
