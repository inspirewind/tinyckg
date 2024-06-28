#ifndef FASTAREADER_H
#define FASTAREADER_H

#include <string>
#include <vector>

class FastaReader {
public:
    FastaReader(const std::string &filename);
    void read();
    std::string getSequence() const;

private:
    std::string filename;
    std::string sequence;

    void parseFasta();
};

#endif // FASTAREADER_H
