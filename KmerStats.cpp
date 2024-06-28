#include "KmerStats.h"
#include <iostream>

KmerStats::KmerStats(const std::vector<std::string> &kmers) : kmers(kmers) {}

void KmerStats::computeStats() {
    for (const auto &kmer : kmers) {
        kmerCounts[kmer]++;
    }
}

void KmerStats::printStats() const {
    for (const auto &pair : kmerCounts) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}
