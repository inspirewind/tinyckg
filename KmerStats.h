#ifndef KMERSTATS_H
#define KMERSTATS_H

#include <string>
#include <vector>
#include <map>

class KmerStats {
public:
    KmerStats(const std::vector<std::string> &kmers);
    void computeStats();
    void printStats() const;

private:
    std::vector<std::string> kmers;
    std::map<std::string, int> kmerCounts;
};

#endif // KMERSTATS_H
