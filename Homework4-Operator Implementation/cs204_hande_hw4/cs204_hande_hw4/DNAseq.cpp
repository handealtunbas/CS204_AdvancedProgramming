//
// Created by Hande Altunbas on 20.04.2024.
//
#include <iostream>
#include "DNAseq.h"

using namespace std;

DNAseq::DNAseq() : length(0), sequence(nullptr) {}

DNAseq::DNAseq(const std::string& str) : length(str.length())
{
    sequence = new Nucleotide[length];
    char nucleotides[] = { 'A', 'C', 'G', 'T' };

    for (int i = 0; i < length; ++i)
    {
        int j = 0;
        while (j < 4 && str[i] != nucleotides[j])
        {
            ++j;
        }

        if (j < 4)
        {
            sequence[i] = static_cast<Nucleotide>(j);
        }
    }
}

DNAseq::DNAseq(const DNAseq& other)
{
    // Copy the length
    length = other.length;

    // Allocate memory for the new sequence
    sequence = new Nucleotide[length];

    // Copy the sequence from the other object
    for (int i = 0; i < length; ++i) {
        sequence[i] = other.sequence[i];
    }
}

DNAseq::~DNAseq()
{
    delete[] sequence;
}

bool DNAseq::operator<=(const DNAseq& rhs) const {
    int lhsLength = getLength();
    int rhsLength = rhs.getLength();

    // If the length of lhs is greater than rhs, it can't be a subsequence
    if (lhsLength > rhsLength) {
        return false;
    }

    // Iterate over lhs sequence and check for subsequence
    for (int i = 0; i <= rhsLength - lhsLength; ++i) {
        bool isSubsequence = true;

        // Check if lhs sequence matches rhs sequence starting from index i
        for (int j = 0; j < lhsLength; ++j) {
            if (sequence[j] != rhs.sequence[i + j]) {
                isSubsequence = false;
            }
        }

        // If lhs sequence is found as a subsequence, return true
        if (isSubsequence) {
            return true;
        }
    }

    // If lhs is equal to rhs, return true
    if (lhsLength == rhsLength) {
        return true;
    }

    // If lhs is not a subsequence and not equal to rhs, return false
    return false;
}

DNAseq DNAseq::operator*(int multiplier) const
{
    if (multiplier <= 0)
    {
        // Handle negative or zero multiplier (return empty DNA sequence or throw exception)
        // For simplicity, let's return an empty DNA sequence
        return DNAseq();
    }

    // Calculate the new length of the repeated sequence
    int newLength = length * multiplier;

    // Create a new DNA sequence object to store the repeated sequence
    DNAseq repeatedSequence;
    repeatedSequence.length = newLength;
    repeatedSequence.sequence = new Nucleotide[newLength];

    // Copy the sequence of the lhs operand into the repeated sequence 'multiplier' times
    for (int i = 0; i < newLength; ++i)
    {
        repeatedSequence.sequence[i] = sequence[i % length];
    }

    return repeatedSequence;
}

int DNAseq::operator%(Nucleotide nucleotide) const
{
    int count = 0;

    // Iterate over the sequence and count occurrences of the specified nucleotide
    for (int i = 0; i < length; ++i) {
        if (sequence[i] == nucleotide) {
            ++count;
        }
    }

    return count;
}

DNAseq DNAseq::operator!() const
{
    DNAseq complementSequence;
    complementSequence.length = length;
    complementSequence.sequence = new Nucleotide[length];

    // Map each nucleotide to its complement and store it in the complement sequence
    for (int i = 0; i < length; ++i)
    {
        if (sequence[i] == A)
        {
            complementSequence.sequence[i] = T;
        }
        else if (sequence[i] == T)
        {
            complementSequence.sequence[i] = A;
        }
        else if (sequence[i] == G)
        {
            complementSequence.sequence[i] = C;
        }
        else if (sequence[i] == C)
        {
            complementSequence.sequence[i] = G;
        }
    }

    return complementSequence;
}

DNAseq& DNAseq::operator=(const DNAseq& other){
    // Check for self-assignment
    if (this != &other)
    {
        // Deallocate memory for the current sequence
        delete[] sequence;

        // Copy the length
        length = other.length;

        // Allocate memory for the new sequence
        sequence = new Nucleotide[length];

        // Copy the sequence from the rhs to lhs
        for (int i = 0; i < length; ++i)
        {
            sequence[i] = other.sequence[i];
        }
    }
    return *this;
}

// Overloading + operator for DNAseq + DNAseq
/*DNAseq operator+(const DNAseq& lhs, const DNAseq& rhs)
{
    DNAseq result;

    // Calculate the length of the result sequence
    int resultLength = lhs.getLength() + rhs.getLength();

    // Allocate memory for the result sequence
    result.getLength() = resultLength;
    result.getSequence() = new Nucleotide[resultLength];

    // Copy lhs sequence into the result sequence
    for (int i = 0; i < rhs.getLength(); ++i)
    {
        result.getSequence()[i] = rhs.getSequence()[i];
    }

    // Copy rhs sequence into the result sequence after lhs sequence
    for (int i = 0; i < lhs.getLength(); ++i)
    {
        result.getSequence()[rhs.getLength() + i] = lhs.getSequence()[i];
    }

    return result;
}*/
/*DNAseq operator+(const DNAseq& lhs, const DNAseq& rhs)
{
    DNAseq result;

    // Calculate the length of the result sequence
    int resultLength = lhs.getLength() + rhs.getLength();

    // Allocate memory for the result sequence
    result.getLength() = resultLength;
    result.getSequence() = new Nucleotide[resultLength];

    // Find the index of the first nucleotide of rhs in lhs sequence
    int index = -1;
    for (int i = 0; i < lhs.getLength(); ++i)
    {
        if (lhs.getSequence()[i] == rhs.getSequence()[0])
        {
            index = i;
            break;
        }
    }

    // If the first nucleotide of rhs exists in lhs sequence, insert rhs after it
    if (index != -1)
    {
        // Copy lhs sequence before the found index
        for (int i = 0; i <= index; ++i)
        {
            result.getSequence()[i] = lhs.getSequence()[i];
        }

        // Copy rhs sequence after the found index
        for (int i = 0; i < rhs.getLength(); ++i)
        {
            result.getSequence()[index + 1 + i] = rhs.getSequence()[i];
        }

        // Copy the rest of lhs sequence
        for (int i = index + 1; i < lhs.getLength(); ++i)
        {
            result.getSequence()[index + 1 + rhs.getLength() + i] = lhs.getSequence()[i];
        }
    }
    else
    {
        // If the first nucleotide of rhs does not exist in lhs sequence, concatenate rhs after lhs
        // Copy lhs sequence
        for (int i = 0; i < lhs.getLength(); ++i)
        {
            result.getSequence()[i] = lhs.getSequence()[i];
        }

        // Copy rhs sequence after lhs sequence
        for (int i = 0; i < rhs.getLength(); ++i)
        {
            result.getSequence()[lhs.getLength() + i] = rhs.getSequence()[i];
        }
    }

    return result;
}*/
DNAseq operator+(const DNAseq& lhs, const DNAseq& rhs)
{
    DNAseq result;
    
}


// Overloading + operator for Nucleotide + DNAseq
/*DNAseq operator+(Nucleotide nucleotide, const DNAseq& dna) {
    DNAseq result;
    result.getLength() = dna.getLength() + 1; // Increment the length for the prepended nucleotide
    result.getSequence() = new Nucleotide[result.getLength()];

    // Copy the nucleotide to the beginning of the result sequence
    result.getSequence()[0] = nucleotide;

    // Copy the rest of the rhs sequence to the result sequence
    for (int i = 0; i < dna.getLength(); ++i) {
        result.getSequence()[i + 1] = dna.getSequence()[i];
    }

    return result;
}*/
DNAseq operator+(Nucleotide nucleotide, const DNAseq& dna) {
    // Create a new DNAseq object to store the result
    DNAseq result;

    // Calculate the length of the result sequence (original length + 1 for the prepended nucleotide)
    int resultLength = dna.getLength() + 1;

    // Allocate memory for the result sequence
    result.getLength() = resultLength;
    result.getSequence() = new Nucleotide[resultLength];

    // Copy the nucleotide to the beginning of the result sequence
    result.getSequence()[0] = nucleotide;

    // Copy the rest of the original sequence to the result sequence
    for (int i = 0; i < dna.getLength(); ++i) {
        result.getSequence()[i + 1] = dna.getSequence()[i];
    }

    // Return the resulting DNAseq object
    return result;
}

/*DNAseq operator+(Nucleotide nucleotide, const DNAseq& dna) {
    // Create a new DNAseq object to store the result
    DNAseq result;

    // Calculate the length of the result sequence (original length + 1 for the prepended nucleotide)
    int resultLength = dna.getLength() + 1;

    // Allocate memory for the result sequence
    result.getLength() = resultLength;
    result.getSequence() = new Nucleotide[resultLength];

    // Copy the nucleotide to the beginning of the result sequence
    result.getSequence()[0] = nucleotide;

    // Copy the rest of the original sequence to the result sequence
    for (int i = 0; i < dna.getLength(); ++i) {
        result.getSequence()[i + 1] = dna.getSequence()[i];
    }

    // Return the resulting DNAseq object
    return result;
}*/


/*DNAseq DNAseq::operator-(const DNAseq& rhs) const
{
    DNAseq result;
    bool found = false;
    int index = -1;
    // Find the index of the first occurrence of rhs sequence in lhs sequence
    for (int i = 0; i <= length - rhs.length && !found; ++i)
    {
        bool match = true;
        for (int j = 0; j < rhs.length; ++j)
        {
            if (sequence[i + j] != rhs.sequence[j])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            found = true;
            index = i;
        }
    }

    // If rhs sequence exists in lhs sequence, create result sequence with rhs removed
    if (found)
    {
        result.length = length - rhs.length;
        result.sequence = new Nucleotide[result.length];

        // Copy lhs sequence before the found index
        int k = 0;
        for (int i = 0; i < index; ++i)
        {
            result.sequence[k++] = sequence[i];
        }

        // Copy lhs sequence after the found sequence
        for (int i = index + rhs.length; i < length; ++i)
        {
            result.sequence[k++] = sequence[i];
        }
    }
    else
    {
        // If rhs sequence doesn't exist in lhs sequence, copy lhs sequence as is
        result.length = length;
        result.sequence = new Nucleotide[result.length];

        for (int i = 0; i < length; ++i)
        {
            result.sequence[i] = sequence[i];
        }
    }

    return result;
}*/

DNAseq DNAseq::operator-(const DNAseq& rhs) const
{
    DNAseq result;

    // Find the index of the first occurrence of rhs sequence in lhs sequence
    int index = -1;
    for (int i = 0; i <= length - rhs.length && index == -1; ++i)
    {
        bool match = true;
        int j = 0;
        while (match && j < rhs.length)
        {
            if (sequence[i + j] != rhs.sequence[j])
            {
                match = false;
            }
            ++j;
        }
        if (match)
        {
            index = i; // Store the index of the first occurrence of rhs sequence
        }
    }

    // If rhs sequence exists in lhs sequence, create result sequence with rhs removed
    if (index != -1)
    {
        result.length = length - rhs.length;
        result.sequence = new Nucleotide[result.length];

        // Copy lhs sequence before the found index
        int k = 0;
        for (int i = 0; i < index; ++i)
        {
            result.sequence[k++] = sequence[i];
        }

        // Copy lhs sequence after the found sequence
        for (int i = index + rhs.length; i < length; ++i)
        {
            result.sequence[k++] = sequence[i];
        }
    }
    else
    {
        // If rhs sequence doesn't exist in lhs sequence, copy lhs sequence as is
        result.length = length;
        result.sequence = new Nucleotide[result.length];

        for (int i = 0; i < length; ++i)
        {
            result.sequence[i] = sequence[i];
        }
    }

    return result;
}


DNAseq& DNAseq::operator+=(const DNAseq& rhs){
    *this = *this + rhs;
    return *this;
}


ostream& operator<<(ostream& os, const DNAseq& dna)
{
    const char nucleotideChars[] = {'A', 'C', 'G', 'T'};

    for (int i = 0; i < dna.getLength(); ++i) {
        // Output the character corresponding to the nucleotide
        // Use the value of the nucleotide enum as an index to access the corresponding character
        if (dna.getSequence()[i] >= A && dna.getSequence()[i] <= T)
        {
            os << nucleotideChars[dna.getSequence()[i]];
        }
    }
    return os;
}
