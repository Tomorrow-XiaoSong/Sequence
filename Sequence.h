#ifndef SEQUENCE_H
#define SEQUENCE_H

#include<string>
using namespace std;

class Sequence
{
private:
	string DNA;
public:
	Sequence(string filename);
	void setDNA(string dna){
		DNA = dna;
	}
	string getDNA(){
		return DNA;
	}
	int length();
	int numberOf(char base);
	string longestConsecutive();
	string longestRepeated();
};

#endif
