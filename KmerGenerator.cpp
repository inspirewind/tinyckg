#include "KmerGenerator.h"
#include "KmerHash.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>

KmerGenerator::KmerGenerator(const std::string &sequence, int kmerLength, bool canonical)
    : sequence(sequence), kmerLength(kmerLength), canonical(canonical) {}

void KmerGenerator::generateKmers() {
    for (size_t i = 0; i <= sequence.length() - kmerLength; ++i) {
        std::string kmer = sequence.substr(i, kmerLength);
        if (canonical) {
            std::string revComp = KmerHash::reverseComplement(kmer);
            if (revComp < kmer) {
                kmer = revComp;
            }
        }
        kmerCounts[kmer]++;
    }
}

void KmerGenerator::saveKmersToFile(const std::string &filename) {
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    int kmerSize = kmerLength;
    int kmerCount = kmerCounts.size();

    outfile.write(reinterpret_cast<const char*>(&kmerSize), sizeof(kmerSize));
    outfile.write(reinterpret_cast<const char*>(&kmerCount), sizeof(kmerCount));

    for (const auto& pair : kmerCounts) {
        unsigned long hash = KmerHash::hash(pair.first);
        outfile.write(reinterpret_cast<const char*>(&hash), sizeof(hash));
        outfile.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
    }

    outfile.close();
}
