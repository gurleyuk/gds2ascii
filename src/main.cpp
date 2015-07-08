#include <iostream>

#include "GDS2File.h"

using namespace std;
using namespace gds;

int main(int argc, char* argv[]) {
	GDS2File gds2File(argv[1]);

	for(int i = 0; i < gds2File.numRecords(); i++) {
		GDS2Record record = gds2File.getRecord(i);

		cout << record.toString();

		// stops at the end of the lib
		if(! record.toString().compare("End Library") == true)
			{	cout << endl;
				break;
			}
	}


	return 0;
}
