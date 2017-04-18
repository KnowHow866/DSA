
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

template <typename E>
class VectorCompleteTree{
	public:
		vector<E> V;
	public:
		typedef typename vector<E>::iterator Position;
	public:
		Position pos(int i) { return V.begin()+i ;}
		int idx(const Position& p)const { return p - V.begin() ;}

	public:
		VectorCompleteTree() : V(1) {};//constructor
		int size() const {return V.size() - 1;}
		Position left(const Position& p) {return pos( 2*idx(p) ); }
		Position right(const Position& p) {return pos( 2*idx(p) + 1 );}
		Position parent(const Position& p){ return pos( idx(p)/2 );}
		bool hasLeft( Position& p) {return 2*idx(p) <= size(); }
		bool hasRight( Position& p) {return 2*udx(p)+1 <= size();}
		bool isRoot( Position& p) {return idx(p) == 1 ;}
		Position root() {return pos(1);}
		Position last() {return pos( size() );}
		void addLast(const E& e) { V.push_back(e);}// do in cpp
		void removeLast() { V.pop_back();}
		//void removeFirst();//do in cpp
		void swap(const Position& p,const Position& q) { E e= *q; *q = *p; *p = e;}
};

class Bid
{
	public:
		int num,clientID,price,share;
		char action;

		Bid() {}
		Bid(int Num,int ClientID,char Action,int Price,int Share)
		{
			num = Num;
			clientID = ClientID;
			action = Action;
			price = Price;
			share = Share;
		}
};

class bidHeap
{
	public:
		vector<Bid> V;
		bidHeap():V(1) {};

		int size() const{return V.size() - 1;}
		bool isEmpty(){ return V.size()==1;}
		int left(int idx) {return 2*idx; }
		int right(int idx) {return 2*idx+1; }
		int parent(int idx) { if( idx%2 == 0) return idx/2;
				      else if(idx%2 == 1) return (idx-1)/2;}
		bool hasLeft(int idx) {return 2*idx <= size();}
		bool hasRight(int idx) {return (2*idx+1) <= size();}
		bool isRoot(int idx) {return idx==1;}
		static int root() {return 1;}
		int last() {return size();}
		int top() {return V[1].price;}

		void addLast(const Bid bid) {V.push_back(bid); }
		void removeLast() {V.pop_back(); }
		void swap(int idx1, int idx2)
		{
			Bid temp;
			temp = V[idx1];
			V[idx1] = V[idx2];
			V[idx2] = temp;
		}

		void sortLastMax(int idx)
		{
			if(V[idx].price > V[parent(idx)].price & !isRoot(idx) )
			{
				swap(idx , parent(idx) );
				sortLastMax(parent(idx) );
			}
		}
		void sortLastMin(int idx)
		{
			if(V[idx].price < V[parent(idx)].price & !isRoot(idx) )
			{
				swap(idx, parent(idx) );
				sortLastMin(parent(idx) );
			}
		}
		void sortFirstMax(int idx )
		{
			if(hasLeft(idx) & !hasRight(idx))
			{
				if( V[idx].price < V[left(idx)].price )
				{
					swap(idx, left(idx) );
					sortFirstMax( left(idx) );
				}
			}
			if(hasRight(idx) & !hasLeft(idx))
			{
				if( V[idx].price < V[right(idx)].price )
				{
					swap(idx, right(idx) );
					sortFirstMax( right(idx) );
				}
			}
			if(hasLeft(idx) & hasRight(idx) )
			{
				int select = 0;
				int pPrice = 0;
				if( V[left(idx)].price >= V[right(idx)].price )
				{
					select = 1; pPrice = V[left(idx)].price;
				}
				else if(V[right(idx)].price > V[left(idx)].price )
				{       select = 2; pPrice = V[right(idx)].price; }

				if( V[idx].price < pPrice)
				{
					switch(select)
					{
						case 1:
							swap(idx, left(idx) );
							sortFirstMax( left(idx) );
							break;
						case 2:
							swap(idx, right(idx) );
							sortFirstMax( right(idx) );
							break;
						default :
							break;
					}
				}
			}
		}
		void sortFirstMin(int idx)
		{	
			if(hasLeft(idx) & !hasRight(idx))
			{
				if( V[idx].price > V[left(idx)].price )
				{
					swap(idx, left(idx) );
					sortFirstMin( left(idx) );
				}
			}
			if(hasRight(idx) & !hasLeft(idx))
			{
				if( V[idx].price > V[right(idx)].price )
				{
					swap(idx, right(idx) );
					sortFirstMin( right(idx) );
				}
			}
			if(hasLeft(idx) & hasRight(idx) )
			{
				int select = 0;
				int pPrice = 0;
				if( V[left(idx)].price <= V[right(idx)].price )
				{
					select = 1; pPrice = V[left(idx)].price;
				}
				else if(V[right(idx)].price < V[left(idx)].price )
				{       select = 2; pPrice = V[right(idx)].price; }

				if( V[idx].price > pPrice)
				{
					switch(select)
					{
						case 1:
							swap(idx, left(idx) );
							sortFirstMin( left(idx) );
							break;
						case 2:
							swap(idx, right(idx) );
							sortFirstMin( right(idx) );
							break;
						default :
							break;
					}
				}
			}
		}

			


};
			




	
