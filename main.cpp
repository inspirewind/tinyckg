#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include "FastaReader.h"
#include "KmerGenerator.h"
#include "KmerStats.h"
#include "KmerHash.h"

void printUsage() {
    std::cout << "Usage:\n"
              << "  tinyckg count -i <input_fasta_file> -k <kmer_length> [-C] -o <output_file>\n"
              << "  tinyckg dump <input_ckg_file> -o <output_csv_file>\n";
}

void countKmers(const std::string& fastaFile, int kmerLength, const std::string& outputFile, bool canonical) {
    FastaReader fastaReader(fastaFile);
    fastaReader.read();

    KmerGenerator kmerGenerator(fastaReader.getSequence(), kmerLength, canonical);
    kmerGenerator.generateKmers();
    kmerGenerator.saveKmersToFile(outputFile);
}

void dumpKmers(const std::string& ckgFile, const std::string& outputFile) {
    std::ifstream infile(ckgFile, std::ios::binary);
    if (!infile.is_open()) {
        throw std::runtime_error("Unable to open input .ckg file");
    }

    int kmerSize;
    int kmerCount;
    infile.read(reinterpret_cast<char*>(&kmerSize), sizeof(kmerSize));
    infile.read(reinterpret_cast<char*>(&kmerCount), sizeof(kmerCount));

    std::map<std::string, int> kmerCounts;
    for (int i = 0; i < kmerCount; ++i) {
        unsigned long hash;
        int count;
        infile.read(reinterpret_cast<char*>(&hash), sizeof(hash));
        infile.read(reinterpret_cast<char*>(&count), sizeof(count));
        std::string kmer = KmerHash::reverseHash(hash, kmerSize);
        kmerCounts[kmer] = count;
    }
    infile.close();

    std::ofstream outfile(outputFile);
    if (!outfile.is_open()) {
        throw std::runtime_error("Unable to open output CSV file");
    }

    for (const auto& pair : kmerCounts) {
        outfile << pair.first << "\t" << pair.second << "\n";
    }

    outfile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return EXIT_FAILURE;
    }

    std::string command = argv[1];
    if (command == "count") {
        std::string fastaFile;
        std::string outputFile = "output.ckg";
        int kmerLength = 5;
        bool canonical = false;

        int opt;
        while ((opt = getopt(argc - 1, argv + 1, "i:k:o:C")) != -1) {
            switch (opt) {
                case 'i':
                    fastaFile = optarg;
                    break;
                case 'k':
                    kmerLength = std::stoi(optarg);
                    break;
                case 'o':
                    outputFile = optarg;
                    break;
                case 'C':
                    canonical = true;
                    break;
                default:
                    printUsage();
                    return EXIT_FAILURE;
            }
        }

        if (fastaFile.empty() || kmerLength <= 0) {
            printUsage();
            return EXIT_FAILURE;
        }

        std::cout << "Counting " << kmerLength << "-mers in " << fastaFile << ", canonical: " << canonical << std::endl;

        countKmers(fastaFile, kmerLength, outputFile, canonical);

    } else if (command == "dump") {
        if (argc < 4) {
            printUsage();
            return EXIT_FAILURE;
        }

        std::string ckgFile = argv[2];
        std::string outputFile = "output.csv";

        int opt;
        while ((opt = getopt(argc - 2, argv + 2, "o:")) != -1) {
            switch (opt) {
                case 'o':
                    outputFile = optarg;
                    break;
                default:
                    printUsage();
                    return EXIT_FAILURE;
            }
        }

        dumpKmers(ckgFile, outputFile);

    } else {
        printUsage();
        return EXIT_FAILURE;
    }

    return 0;
}
