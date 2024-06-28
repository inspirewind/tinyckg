#ifndef KMERGENERATOR_H
#define KMERGENERATOR_H

#include <string>
#include <vector>
#include <map>

class KmerGenerator {
public:
    KmerGenerator(const std::string &sequence, int kmerLength, bool canonical);
    void generateKmers();
    void saveKmersToFile(const std::string &filename);

private:
    std::string sequence;
    int kmerLength;
    bool canonical;
    std::map<std::string, int> kmerCounts;
};

#endif // KMERGENERATOR_H
