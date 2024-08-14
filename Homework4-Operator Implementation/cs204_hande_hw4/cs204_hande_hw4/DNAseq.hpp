//
// Created by Hande Altunbas on 20.04.2024.
//

#ifndef DNASEQ_H
#define DNASEQ_H

#include <iostream>
using namespace std;

enum Nucleotide {A, C, G, T};

class DNAseq{

    private:
        int length;
        Nucleotide* sequence;

    public:
        DNAseq();
        DNAseq(const string& str);
        DNAseq(const DNAseq& other);
        ~DNAseq();

        int& getLength() { return length; }
        const int& getLength() const { return length; }
        Nucleotide*& getSequence()  { return sequence; }
        const Nucleotide* getSequence() const { return sequence; }

        bool operator<=(const DNAseq& rhs) const;
        DNAseq operator*(int multiplier) const;
        int operator%(Nucleotide nucleotide) const;
        DNAseq operator!() const;
        DNAseq& operator=(const DNAseq& other);
        DNAseq operator-(const DNAseq& other) const;
        DNAseq& operator+=(const DNAseq& other);
};

DNAseq operator+(Nucleotide nucleotide, const DNAseq& dna);
ostream& operator<<(ostream& os, const DNAseq& dna);
DNAseq operator+(const DNAseq& lhs, const DNAseq& rhs);

#endif //DNASEQ_H

