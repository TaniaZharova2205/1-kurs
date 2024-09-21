#include<iostream>
#include<sys/ioctl.h>
#include<sstream>
#include<unistd.h>
#include <fcntl.h>

using namespace std;

namespace con 
{
	//размер экрана
	int comax() 
	{
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		return w.ws_col;
	}

	int romax() 
	{
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		return w.ws_row;
	}
	
	
	class estream 
	{
			string escape;
		public:
			estream(string e) : escape(e) {};//конструктор инициализации поля escape переданный через аргумент командной строкой 
			friend ostream& operator<< (ostream&,estream);//перегрузка оператора вывода
	};

	ostream& operator << (ostream& out, estream e) 
	{
		out << e.escape << flush;
		return out;
	}
	
	
	estream set(int y, int x) 
	{
		ostringstream sout;
		sout << "\033[" << x << ';' << y << "H";
		return estream(sout.str());
	}

	estream color(int c) 
	{
		ostringstream sout;
		sout << "\033[" << c << "m ";
		return estream(sout.str());
	}
	//очистка экрана
	ostream& clear(ostream& s) 
	{
		return s <<  string ("\033[2J");
	}
}

int kbin() 
{
	char buf[512];
	int n=0;
	int flags = fcntl(0, F_GETFL);
	usleep(1);
	fcntl(0, F_SETFL, flags | O_NONBLOCK);
	n = read(0, buf, 512);
	fcntl(0, F_SETFL, flags /* & ~O_NONBLOCK */);
	return(n);
}

int main(int argc, char* argv[]) 
{
	int comax=con::comax();
	int romax=con::romax();
	int col=1, row=1, color=7;
	cout << con::clear << con::set(1,comax-1);
	cout << comax << 'x' << romax << endl;
	cout << "^C or enter to exit.";

	while (true) 
	{
		for (int i=1; i<=romax-3; i++)
			cout << con::set(col, row++) << con::color(40+color);
		cout << con::set(++col, row=1);
		if (col>comax) 
		{
			col=1;
			/*if (--color<0)
				color=7;*/
		}
		if (--color<0)
				color=7;
		if (kbin()>0)
			break;
		usleep(100000);
	}
	cout << con::set(1,1) << con::color(0) << con::clear;
	return 0;
}
