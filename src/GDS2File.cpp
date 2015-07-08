#include "GDS2File.h"

using namespace std;
using namespace gds;

GDS2File::GDS2File(const char* fileName) : m_gdsFile(fileName, ios::in | ios::binary) {

	while(!m_gdsFile.eof()) {
		char bufNumBytes[2];
		char* bufRecord;
		unsigned short numBytes;

		m_gdsFile.read(bufNumBytes, 2);
		if(m_gdsFile.eof())
			break;
		numBytes = (bufNumBytes[0] << 8) + bufNumBytes[1] - 2;
		bufRecord = new char[numBytes];
		m_gdsFile.read(bufRecord, numBytes);

		GDS2Record gdsRecord(numBytes, bufRecord);
		m_gdsRecords.push_back(gdsRecord);

		delete bufRecord;
	}
}

GDS2File::~GDS2File() {
	m_gdsFile.close();
}
