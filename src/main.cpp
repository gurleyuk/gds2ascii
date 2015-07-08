#include <iostream>

#include "GDS2File.h"

using namespace std;
using namespace gds;

int main(int argc, char* argv[]) {
	GDS2File gds2File(argv[1]);

	for(int i = 0; i < gds2File.numRecords(); i++) {
		GDS2Record record = gds2File.getRecord(i);

		cout << record.toString() << endl;

		// stops at the end of the lib
		if(! record.toString().compare("endlib") == true)
			break;
	}

	return 0;
}
