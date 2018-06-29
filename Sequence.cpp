#include"Sequence.h"
#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
using namespace std;

Sequence::Sequence(string filename)
{
	ifstream fin(filename, ios::in);
	char chrs[101];				//记录一行的数据
	while(fin.getline(chrs,sizeof(chrs)))
	{
			DNA += chrs;		//新行接在旧行后，连成一串无换行符的DNA序列
	}
	fin.close();
}

int Sequence::length()
{
	return getDNA().length();
}

string Sequence::longestConsecutive()
{
	int old_sameCount = 1;			//记录之前的Consecutive的长度
	int new_sameCount = 1;			//记录新的Consecutive的长度
	char sameChar;				//记录相同的字符
	string this_DNA = getDNA();
	int length = this_DNA.length();
	//遍历一遍DNA序列，判断当前字符与前一字符是否相同
	//相同则new_sameCount++
	//不同则比较new_sameCount 与 old_sameCount 记录较长者的sameChar
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

int Compare_DNAs(const void* left,const void* right){
	return strcmp(*(char**)left,*(char**)right);
}
string Sequence::longestRepeated()
{
	string this_DNA = getDNA();			  //记录DNA
	int length = getDNA().length();			  //记录DNA长度
	//对后缀进行升序排序
	char** DNAs;					  //每个char*指向DNA字符串的一个后缀
	DNAs = new char* [length];			
	for(int i = 0;i < length;i++){
		DNAs[i] = &this_DNA[i];
	}
	qsort(DNAs,length,sizeof(char*),Compare_DNAs);	  //对后缀进行升序排序
							  //相邻后缀前端的相似性最大
							  //longestRepeated是这些相邻后缀相同前端的最长串
	//对相邻两个后缀进行处理，找出后缀开头具有的相等字符串的长度，并找出其中最长的一串
	int longestLength = 1;
	char *result = NULL;
	for(int i = 0;i<length-1;i++){
		int count = 0;
		int newLength = 0;
		while(DNAs[i][count] == DNAs[i+1][count]){
			newLength++;
			count++;
		}
		//若找到两串相同长度的longestRepeated，记录下先出现的那一串的后缀首地址
		if(newLength > longestLength){
			string strL(DNAs[i]);
			string strR(DNAs[i+1]);
			if(strL.length() > strR.length()) result=DNAs[i];
			else result = DNAs[i+1];
			longestLength = newLength;
		}
		else if(newLength == longestLength){
			string strL(DNAs[i]);
			string strR(DNAs[i+1]);
			string strLongest(result);
			if(strL.length() > strLongest.length()) result = DNAs[i];
			if(strR.length() > strLongest.length()) result = DNAs[i+1];
		}
	}
	string longestANS(result, longestLength);	  //截取最长串所在后缀的前longestLength个字符储存在longestANS中
	delete DNAs;
	return longestANS;
}
