

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class function 
{
	public:
		void accept(int** Data,int Data_size);
		void items(int** Data,int Data_size);
		void users(int** Data,int Data_size);
                void ratio(int** Data,int Data_size);
		void findtime_item(int** Data,int Data_size);

		void ratio_02(int** Data,int Data_size);
		void findtime_item02(int** Data,int Data_size);
		void users02(int** Data,int Data_size);
		void items02(int** Data,int Data_size);
};
