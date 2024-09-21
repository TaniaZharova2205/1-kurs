#include <iostream>
#include "chesslib.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
		argv[1]=(char*)"nil";
	if(Figure::deskout(argv[1]))
	{
		std::cout<<"Correct"<<argv[1];
		std::cout<<"to"<<(argv[1]=(char*)"al")<<" Default\n";
		std::cout<<"Using example:chess+ e5\n";
	}
	Amazon f(argv[1]);
	do
	{
		f.danger();
		std::cout<<f<<'-'<<f.isa();
	}
	while(std::cin>>f);
	return(0);
}
