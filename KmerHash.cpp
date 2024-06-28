#include "KmerHash.h"
#include <stdexcept>
#include <algorithm>

unsigned long KmerHash::hash(const std::string &kmer) {
    unsigned long hashValue = 0;
    for (char nucleotide : kmer) {
        hashValue <<= 2;
        switch (nucleotide) {
            case 'A':
                hashValue |= 0;
                break;
            case 'C':
                hashValue |= 1;
                break;
            case 'G':
                hashValue |= 2;
                break;
            case 'T':
                hashValue |= 3;
                break;
            default:
                throw std::invalid_argument("Invalid nucleotide character in k-mer");
        }
    }
    return hashValue;
}

std::string KmerHash::reverseHash(unsigned long hashValue, int kmerLength) {
    std::string kmer(kmerLength, 'A');
    for (int i = kmerLength - 1; i >= 0; --i) {
        switch (hashValue & 3) {
            case 0:
                kmer[i] = 'A';
                break;
            case 1:
                kmer[i] = 'C';
                break;
            case 2:
                kmer[i] = 'G';
                break;
            case 3:
                kmer[i] = 'T';
                break;
        }
        hashValue >>= 2;
    }
    return kmer;
}

unsigned long KmerHash::kmerToBits(const std::string &kmer) {
    unsigned long bits = 0;
    for (char nucleotide : kmer) {
        bits <<= 2;
        switch (nucleotide) {
            case 'A':
                bits |= 0;
                break;
            case 'C':
                bits |= 1;
                break;
            case 'G':
                bits |= 2;
                break;
            case 'T':
                bits |= 3;
                break;
            default:
                throw std::invalid_argument("Invalid nucleotide character in k-mer");
        }
    }
    return bits;
}

std::string KmerHash::bitsToKmer(unsigned long bits, int kmerLength) {
    std::string kmer(kmerLength, 'A');
    for (int i = kmerLength - 1; i >= 0; --i) {
        switch (bits & 3) {
            case 0:
                kmer[i] = 'A';
                break;
            case 1:
                kmer[i] = 'C';
                break;
            case 2:
                kmer[i] = 'G';
                break;
            case 3:
                kmer[i] = 'T';
                break;
        }
        bits >>= 2;
    }
    return kmer;
}

unsigned long KmerHash::reverseComplementBits(unsigned long bits, int kmerLength) {
    unsigned long revComp = 0;
    for (int i = 0; i < kmerLength; ++i) {
        revComp <<= 2;
        revComp |= (~bits & 3);
        bits >>= 2;
    }
    return revComp;
}

std::string KmerHash::reverseComplement(const std::string &kmer) {
    unsigned long bits = kmerToBits(kmer);
    unsigned long revCompBits = reverseComplementBits(bits, kmer.size());
    return bitsToKmer(revCompBits, kmer.size());
}
