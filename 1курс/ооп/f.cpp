#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]) {
	int symCount=0, test=0, count=0;
	char byte;

	if (argc<2)  {
		cerr << "File name wasn't set.\n";
		return -1;
	}

	ifstream input(argv[1]);
	
	if(!input) {
		cerr << argv[1] << ": Can't open a file\n";
		return -2;
	}

	while ((byte=input.get()) != EOF) {
		if (byte=='\n') {
			if (symCount==0) {
				if (test==1)
					count++;
				test=0;
			}
			symCount=0;
		} else if (byte==' ' || byte=='\t');
		else {
			symCount++;
			test=1;
		}
	}
	if (test==1)
		count++;

	cerr << "This text has " << count << " paragraphs." << endl;

	input.close();
	return 0;
}
