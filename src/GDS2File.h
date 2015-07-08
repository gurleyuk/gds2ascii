#include <fstream>
#include <vector>

#include "GDS2Record.h"

namespace gds {

class GDS2File {
public:
	GDS2File(const char* fileName);
	~GDS2File();

	unsigned int numRecords() {return m_gdsRecords.size();}
	GDS2Record getRecord(unsigned int numRecord) {return m_gdsRecords[numRecord];}
private:
	std::ifstream m_gdsFile;
	std::vector<GDS2Record> m_gdsRecords;
};

};
