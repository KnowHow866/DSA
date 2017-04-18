
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <stack>

using namespace std;

class Process
{
	public:
		vector< vector<char> > Line_process(vector< vector<char> >Picture ,char ROC, int tar_line, vector<int> clue,bool guess, bool& ExistButNosol);
                void Result(vector< vector<char> >Picture ,bool& result);
		void Guess( stack< vector<vector<char> > >&guess, vector< vector<char> >Picture,vector<vector<int> >RowClue,vector<vector<int> >ColClue ); 
};
