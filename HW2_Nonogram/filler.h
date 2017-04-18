
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Filler
{
	public:
		void Guess_filter( vector<vector<char> >Picture, vector<vector<char> >& guess, char ROC,int line);
		void filler_1(vector<char>line ,vector<int> clue, int space,vector< vector<char> >& Fill_ans, bool&  change);
		void filler_2(vector<char>line ,vector<int> clue, int space,vector< vector<char> >& Fill_ans, bool&  change);
		void filler_3(vector<char>line ,vector<int> clue, int space,vector< vector<char> >& Fill_ans, bool&  change);
		void Distribute(vector<int>& X, int X_value, vector< vector<int> >& Pos,int countX, int value);
		void filler_all(vector<char> line,vector<int> clue,int space,vector< vector<char> >& Fill_ans, bool& change);

};
