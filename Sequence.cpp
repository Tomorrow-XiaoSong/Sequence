#include"Sequence.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

Sequence::Sequence(string filename)
{
	ifstream fin(filename, ios::in);
	char chrs[101];
	while(fin.getline(chrs,sizeof(chrs)))
	{
			DNA += chrs;
	}
	fin.close();
}

int Sequence::length()
{
	return getDNA().length();
}

string Sequence::longestConsecutive()
{
	int old_sameCount = 1;
	int new_sameCount = 1;
	char sameChar;
	string this_DNA = getDNA();
	int length = this_DNA.length();
	for(int i = 1;i < length;i++){
		if(this_DNA[i] == this_DNA[i-1]){
			new_sameCount++;
		}
		else{
			if(new_sameCount > old_sameCount){
				old_sameCount = new_sameCount;
				sameChar = this_DNA[i-1];
			}
			new_sameCount = 1;
		}
	}
	string result(old_sameCount,sameChar);
	return result;
}

