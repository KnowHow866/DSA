
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class dicTool
{
	public:
		void possibleWord(string word, vector<string>& Pos);
		bool prior(string word1,string word2);
};

class heap
{
	private:
		bool prior(string word1,string word2);
	public:
		vector<string> V;
		heap():V(1) {};

		int size() { return V.size()-1; }
		bool Empty() { return V.size()==1; }
		int left(int idx) { return 2*idx; }
		int right(int idx) { return 2*idx+1; }
		int parent(int idx){ if((idx%2)==0) return idx/2;
					else if((idx%2) == 1) return (idx-1)/2;}
		bool hasLeft(int idx){ return 2*idx <= size(); }
		bool hasRight(int idx){ return (2*idx+1) <= size(); }
		bool isRoot(int idx) { return idx==1; }
		static int root() { return 1;}
		int last() { return size(); }
		
		void addLast(string A) { V.push_back(A); }
		void removeLast() { V.pop_back(); }
		void swap(int idx1, int idx2)
		{
			string temp;
			temp = V[idx1];
			V[idx1] = V[idx2];
			V[idx2] = temp;
		}

		void sortLast(int idx)
		{
			if( prior( V[idx],V[parent(idx)] ) & !isRoot(idx) )
			{
				swap(idx, parent(idx) );
				sortLast( parent(idx) );
			}
		}

		void sortFirst(int idx)
		{
			if( hasLeft(idx) & !hasRight(idx) )
			{
				if( prior( V[left(idx)], V[idx] ) )
				{
					swap( idx, left(idx) );
					sortFirst( left(idx) );
				}
			}
			if( !hasLeft(idx) & hasRight(idx) )
			{
				if( prior( V[ right(idx) ], V[idx] ) )
				{
					swap( idx,right(idx) );
					sortFirst(idx);
				}
			}
			if( hasLeft(idx) & hasRight(idx) )
			{
				if( prior( V[right(idx)], V[left(idx)] ) )
				{
					if(prior( V[right(idx)], V[idx] ) )
					{
						swap( idx, right(idx) );
						sortFirst(right(idx) );
					}
				}
				if( prior( V[left(idx)], V[right(idx)] ) )
				{
					if( prior( V[left(idx)], V[idx]) )
					{
						swap(idx,left(idx) );
						sortFirst( left(idx));
					}
				}
			}
		}
};




