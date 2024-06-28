#ifndef KMERHASH_H
#define KMERHASH_H

#include <string>

class KmerHash {
public:
    static unsigned long hash(const std::string &kmer);
    static std::string reverseHash(unsigned long hashValue, int kmerLength);
    static unsigned long kmerToBits(const std::string &kmer);
    static std::string bitsToKmer(unsigned long bits, int kmerLength);
    static unsigned long reverseComplementBits(unsigned long bits, int kmerLength);
    static std::string reverseComplement(const std::string &kmer);
};

#endif // KMERHASH_H

