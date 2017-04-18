#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <map>

using namespace std;

class point
{
	public:
		string Str;
		int value;

		point() 
		{
			Str = "None";  value = 0;
		}

		point(string A,int B)
		{
			Str = A;  value = B;
		}
};

class EDIT
{
	public:
		void EditNonePre(string typeIn, map<string,int>& Candidate, map<string,bool> prepoMap);
		void EditPre(string typeIn, map<string,int>& Candidate, map<string,bool> prepoMap, bool ED2, map<string,int> Compare);
		void reBuild(vector<bool> buildList, vector<string> verb, vector< vector<string> > prepoSet,
				map<string,int>& Candidate, int index, vector<string>& tempPre, int& EDcount);
		//void ranking( list< point >& Rank, string Str, int value);
};


