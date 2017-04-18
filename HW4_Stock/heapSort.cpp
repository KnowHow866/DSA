
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "Heap.h"

using namespace std;

void dealMaker(bidHeap& B, bidHeap& S,int num,map<int, bool>& dealed);
void cancel(char BoS, bidHeap& bids,int bidID,map<int,int> bidPriceMap);
void AimMax(bidHeap bids, int bidID,int search,int price,int& pos);
void AimMin(bidHeap bids, int bidID,int search,int price,int& pos);
	
int main()
{
	

	bidHeap buyBid;
	bidHeap sellBid;
	int bidNum,bidClientID,bidAction1,bidPrice,bidShare;
	int dealNum = 0;
	int defaultBidNum = -1;
	map<int,bool> dealed;
	map<int,bool>::iterator iter;
	map<int,int> bidPriceMap;
	map<int,char> BoS;
	map<int,int>::iterator aim;

	//for(int i = 0;i< 16;i++)
	while(1)
	{
		cin >> bidNum >>bidClientID>> bidAction1 >> bidPrice >> bidShare;//cin a bid
		if(bidNum == defaultBidNum) break;//if reLoad the same bidNum ,Break
		if(bidAction1 == 0) //bid ->Buy
		{
			Bid* temp = new Bid(bidNum,bidClientID, 'B',bidPrice, bidShare);
			buyBid.addLast(*temp);
			buyBid.sortLastMax( buyBid.size() );
			BoS[bidNum] = 'B';
		}
		else if(bidAction1 == 1)//bid->Sell
		{
			Bid* temp = new Bid(bidNum,bidClientID, 'S',bidPrice, bidShare);
			sellBid.addLast( *temp);
			sellBid.sortLastMin( sellBid.size() );
			BoS[bidNum] = 'S';
		}
		else if(bidAction1 == 2)
		{
			if(dealed[bidPrice] == false)//if the bid haven't been dealed
			{				
				char theAction = BoS[bidPrice];	
				if(theAction == 'B') cancel(theAction, buyBid, bidPrice, bidPriceMap);
				else if(theAction == 'S') cancel(theAction,sellBid, bidPrice,bidPriceMap);
			}
		}
		defaultBidNum = bidNum;
		dealed[ bidNum ] = false;
		bidPriceMap[ bidNum ] = bidPrice;

		
		while(buyBid.V[1].price >= sellBid.V[1].price & !buyBid.isEmpty() & !sellBid.isEmpty())//Deal can be made
		{
			//dealed[ buyBid.V[1].num ] = true; dealed[ sellBid.V[1].num] = true;
			dealMaker(buyBid, sellBid, dealNum,dealed);
			dealNum ++;		
		}
	}
	
	int num = 0;
	/*while(buyBid.top() >= sellBid.top())
	{
		cout<<"the  deal: "<<endl;
		cout<<num<<" "<<buyBid.V[1].clientID<<" "<<sellBid.V[1].clientID<<" "<<buyBid.V[1].price<<" "<<buyBid.V[1].share<<endl;

		buyBid.swap( 1, buyBid.last() );//remove largest of buyBid & sort
		buyBid.removeLast();
		buyBid.sortFirstMax(1);

		sellBid.swap(1, sellBid.last() );
		sellBid.removeLast();
		sellBid.sortFirstMin(1);

		num++;
	}*/
	
	/*cout << "buyBid sequence :"<<endl;
	for(int i = 1;i < buyBid.V.size() ;i++)
	{
		cout<<" "<< buyBid.V[i].num <<" "<< buyBid.V[i].clientID<<" "<< buyBid.V[i].price<<" "<< buyBid.V[i].share<<endl;
	}
	cout << "sellBid sequence :"<<endl;
	for(int i = 1;i < sellBid.V.size();i++)
	{
		cout<<" "<< sellBid.V[i].num <<" "<< sellBid.V[i].clientID<<" "<< sellBid.V[i].price<<" "<< sellBid.V[i].share<<endl;
	}*/
	
}


void dealMaker(bidHeap& B, bidHeap& S,int num,map<int, bool>& dealed)
{
	int dealShare = 0;
	if(B.V[1].share >= S.V[1].share) dealShare = S.V[1].share;
	else dealShare = B.V[1].share;

	cout<< num<<"	"<<B.V[1].clientID<<"	"<<S.V[1].clientID<<"	"<<S.V[1].price<<"	"<<dealShare<<endl;//cout maked deal

	if(dealShare < B.V[1].share) B.V[1].share -= dealShare;
	else{
		dealed[B.V[1].num] = true;
		B.swap(1, B.last() );
		B.removeLast();
		B.sortFirstMax(1);
	}
	if(dealShare < S.V[1].share) S.V[1].share -= dealShare;
	else{
		dealed[S.V[1].num] = true;
		S.swap(1, S.last() );
		S.removeLast();
		S.sortFirstMin(1);
	}
}

void cancel(char BoS, bidHeap& bids,int bidID,map<int,int> bidPriceMap)
{
	int thePrice = bidPriceMap[bidID];
	int pos = 1;
	
	if(BoS == 'B')  AimMax(bids, bidID, 1, thePrice,pos); 
	else if(BoS =='S') AimMin(bids, bidID, 1, thePrice,pos); 
	
	//cout<<"cancel "<<bids.V[pos].num <<"bid"<<endl;
	bids.swap( pos, bids.last() );
	bids.removeLast();
	
	if(BoS == 'B') bids.sortFirstMax(pos);
	else if(BoS == 'S') bids.sortFirstMin(pos);
}

void AimMax(bidHeap bids, int bidID,int search,int price,int& pos)
{	
	if( bids.V[search].num == bidID ) pos = search; 
	else if( bids.V[search].num != bidID)
	{
		//if(bids.hasLeft(search)) cout<<"Bid "<<bids.V[search].num<<"has left " << bids.V[ bids.left(search) ].num<<endl;//---------
		//if(bids.hasRight(search)) cout<<"Bid "<<bids.V[search].num<<"has right "<<bids.V[ bids.right(search) ].num<<endl;//--------
		if(bids.hasLeft(search) /*& bids.V[ bids.left(search) ].price >= price*/) AimMax(bids,bidID,bids.left(search),price,pos );
		if(bids.hasRight(search)/* & bids.V[ bids.right(search) ].price >= price*/) AimMax(bids,bidID,bids.right(search),price,pos );

	}
}

void AimMin(bidHeap bids, int bidID,int search,int price,int& pos)
{	
	if( bids.V[search].num == bidID ) pos=  search;
	else if( bids.V[search].num != bidID)
	{
		if(bids.hasLeft(search) /*& bids.V[ bids.left(search) ].price <= price*/) AimMax(bids,bidID, bids.left(search),price,pos );
		if(bids.hasRight(search)/* & bids.V[ bids.right(search) ].price <= price*/) AimMax(bids,bidID,bids.right(search),price,pos );
	}
}

	


