#include <ctime>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <vector>

#include "GDS2Record.h"

using namespace gds;
using namespace std;

GDS2Record::GDS2Record(unsigned short numBytes, char* bufRecord) {
	m_numBytes = numBytes;
	m_bufRecord = new char[numBytes];

	for(unsigned short i=0; i<numBytes; i++)
		m_bufRecord[i] = bufRecord[i];
}

GDS2Record::GDS2Record(const GDS2Record& record) {
	m_numBytes = record.m_numBytes;
	m_bufRecord = new char[m_numBytes];

	for(unsigned short i=0; i<m_numBytes; i++)
		m_bufRecord[i] = record.m_bufRecord[i];
}

GDS2Record::~GDS2Record() {
	delete m_bufRecord;
}

std::string GDS2Record::toString() {
	stringstream ssRecord, auxRecord;

	switch(type()) {
		case HEADER:
	//		ssRecord << "header version=" << getShort(2); break;
			break;
		case BGNLIB:
			ssRecord << "Begin Library" << endl;
//			ssRecord << "bgnlib lastmodtime=\"" << getDateString(2) << "\" lastacctime=\"" << getDateString(14) << "\""; break;
		case LIBNAME:
			ssRecord << "Library Name : " << getString(2) << ", "; break;
		case UNITS:
			//auxRecord << "User Unit=" << getReal(2) 
			ssRecord << " DB units per user unit =" << int(getReal(2)/getReal(10)) << endl; break;
		case ENDLIB: //nao existe
			ssRecord << "End Library";  break;
		//	ssRecord << "endlib"; break;
		case BGNSTR:
			ssRecord << "Begin Cell Definition" << endl; break;
		case STRNAME:
			ssRecord << "Cell Name : "<< getString(2) << endl; break;
		case ENDSTR: // nao existe
			ssRecord << "End Cell Definition" << endl; break;
//			ssRecord << "endstr"; break;
		case BOUNDARY: // boundary para polygon
			ssRecord << "Polygon - "; break;
//			ssRecord << "boundary"; break;
		case PATH:
			ssRecord << "path"; break;
		case SREF:
			ssRecord << "sref"; break;
		case AREF:
			ssRecord << "aref"; break;
		case LAYER: // L maiusculo :
			ssRecord << "Layer : " << getShort(2) << "  "; break;
		//	ssRecord << "layer " << getShort(2); break;
		case DATATYPE:// Data Type
			ssRecord << "Data Type : " << getShort(2) << "  "; break;
		//	ssRecord << "datatype " << getShort(2); break;
		case WIDTH:
			ssRecord << "width " << getInt(2); break;
		case XY: // tirando os erros de XY
		{
//			ssRecord << "xy ";
			auxRecord << "";
			int index = 2;
			int count=0;
			while(index < m_numBytes) {
				
				auxRecord << " (" << getInt(index) << "," << getInt(index+4) << ")";
				index += 8;
				count++;
				if(count%4 == 0) 
					auxRecord << endl;

				
//				ssRecord << "(x=" << getInt(index) << " y=" << getInt(index+4) << ") ";
//				index += 8;
			}

			ssRecord << "No of points : " << count << endl;
			ssRecord << auxRecord.str() << endl;
			break;
		}
		case ENDEL: // nao existe
			ssRecord << ""; break;
//			ssRecord << "endel"; break;

		case TEXT:
			ssRecord << "Text - "; break;

		case SNAME:
//			ssRecord << "sname \"" << getString(2) << "\""; break;
		case COLROW:
//			ssRecord << "colrow columns=" << getShort(2) << " rows=" << getShort(4); break;
		case TEXTNODE: // What is this?
//			return "record type not implemented."; 
		case NODE:
//			ssRecord << "node"; break;
		case TEXTTYPE:
//			ssRecord << "Text Type : " << getShort(2) << " "; break;
		case PRESENTATION: /// Incomplete. Extract report sepcicic elements.
//			ssRecord << "presentation " << getShort(2); break;
		case STRING:
//			ssRecord << "string \"" << getString(2) << "\"" << endl; break;
		case STRANS: // Incomplete. Extract report sepcicic elements.
//			ssRecord << "strans " << getShort(2); break;
		case MAG:
//			ssRecord << "mag " << getReal(2); break;
		case ANGLE:
//			ssRecord << "angle " << getReal(2); break;
		case REFLIBS:
//			ssRecord << "reflibs \"" << getString(2) << "\""; break;
		case FONTS:
//			ssRecord << "fonts \"" << getString(2) << "\""; break;
		case PATHTYPE:
//			ssRecord << "pathtype " << getShort(2); break;
		case GENERATIONS:
//			ssRecord << "generations " << getShort(2); break;
		case ATTRTABLE:
//			ssRecord << "attrtable " << getShort(2); break;
		case STYPTABLE:
//			ssRecord << "styptable " << getShort(2); break;
		case STRTYPE:
//			ssRecord << "strtype " << getShort(2); break;
		case ELFLAGS: // Incomplete. Extract report sepcicic elements.
//			ssRecord << "elflags " << getShort(2); break;
		case ELKEY:
//			ssRecord << "elkey " << getShort(2); break;
		case NODETYPE:
//			ssRecord << "nodetype " << getShort(2); break;
		case PROPATTR:
//			ssRecord << "propattr " << getShort(2); break;
		case PROPVALUE:
//			ssRecord << "propvalue " << getString(2); break;
		case BOX:
//			ssRecord << "box "; break;
		case BOXTYPE:
//			ssRecord << "boxtype " << getShort(2); break;
		case PLEX:
//			ssRecord << "plex " << getShort(2); break;
		case FORMAT:
//			ssRecord << "format " << getShort(2); break;
		case MASK:
//			ssRecord << "mask \"" << getString(2) << "\""; break;
		case ENDMASKS: // nao existe
			ssRecord << ""; break;
//			ssRecord << "endmasks "; break;

		default:
			return toHexString();
	}

	return ssRecord.str();
}

std::string GDS2Record::toHexString() {
	stringstream ssRecord;

	ssRecord.fill('0');
	ssRecord  << hex << setw(4) << m_numBytes+2;
	for(int i = 0; i < m_numBytes; i++)
		ssRecord << setw(2) << (static_cast<unsigned>(m_bufRecord[i])&0xff);

	return ssRecord.str();
}

short GDS2Record::getShort(unsigned short index) {
	char n[2];

	n[0] = m_bufRecord[index+1];
	n[1] = m_bufRecord[index];

	return *reinterpret_cast<short*>(n);
}

std::string GDS2Record::getDateString(unsigned short index) {
	stringstream ssDate;

	ssDate.fill('0');
	ssDate << setw(2) << getShort(index + 4) << "." << setw(2) << getShort(index + 2) << "." << setw(2) << getShort(index) << " " << setw(2) << getShort(index + 6) << ":" << setw(2) << getShort(index + 8) << ":" << setw(2) << getShort(index + 10);

	return ssDate.str();
}

std::string GDS2Record::getString(unsigned short index) {
	return std::string(m_bufRecord+2);
}

double GDS2Record::getReal(unsigned short index) {
	char e = (m_bufRecord[index]&0x7F)-64;
	short s = (m_bufRecord[index]&0x80)>>7;

	unsigned long  m = 0;
	for(int i = 0; i < 7; i++) {
		m |= (static_cast<unsigned long>(m_bufRecord[index+1+i])&0xFF)<<((6-i)*8);
	}

	double d = m;
	d = d*(pow(16, e-14));
	d = (s==1)?-d:d;

	return d;
}

int GDS2Record::getInt(unsigned short index) {
	char n[4];

	for(int i = 0; i<4; i++)
		n[i] = m_bufRecord[index+3-i];

	return *reinterpret_cast<int*>(n);
}
