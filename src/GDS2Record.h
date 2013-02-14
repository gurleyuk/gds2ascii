#include <fstream>
#include <string>

namespace gds {
	const short HEADER		= 0x0002;
	const short BGNLIB		= 0x0102;
	const short LIBNAME		= 0x0206;
	const short UNITS		= 0x0305;
	const short ENDLIB		= 0x0400;
	const short BGNSTR		= 0x0502;
	const short STRNAME		= 0x0606;
	const short ENDSTR		= 0x0700;
	const short BOUNDARY		= 0x0800;
	const short PATH		= 0x0900;
	const short SREF		= 0x0a00;
	const short AREF		= 0x0b00;
	const short TEXT		= 0x0c00;
	const short LAYER		= 0x0d02;
	const short DATATYPE		= 0x0e02;
	const short WIDTH		= 0x0f03;
	const short XY			= 0x1003;
	const short ENDEL		= 0x1100;
	const short SNAME		= 0x1206;
	const short COLROW		= 0x1302; // Not implemented.
	const short TEXTNODE		= 0x1400;
	const short NODE		= 0x1500;
	const short TEXTTYPE		= 0x1602;
	const short PRESENTATION	= 0x1701; // Incomplete.
	const short STRING		= 0x1906;
	const short STRANS		= 0x1a01; // Incomplete.
	const short MAG			= 0x1b05;
	const short ANGLE		= 0x1c05;
	const short REFLIBS		= 0x1f06;
	const short FONTS		= 0x2006;
	const short PATHTYPE		= 0x2102;
	const short GENERATIONS		= 0x2202;
	const short ATTRTABLE		= 0x2306;
	const short STYPTABLE		= 0x2406;
	const short STRTYPE		= 0x2502;
	const short ELFLAGS		= 0x2601;
	const short ELKEY		= 0x2703;
	const short NODETYPE		= 0x2a02;
	const short PROPATTR		= 0x2b02;
	const short PROPVALUE		= 0x2c06;
	const short BOX			= 0x2d00;
	const short BOXTYPE		= 0x2e02;
	const short PLEX		= 0x2f03;
	const short BGNEXTN		= 0x3003; // Not implemented.
	const short ENDEXTN		= 0x3103; // Not implemented.
	const short TAPENUM		= 0x3202; // Not implemented.
	const short TAPECODE		= 0x3302; // Not implemented.
	const short STRCLASS		= 0x3401; // Not implemented.
	const short RESERVED		= 0x3503; // Not implemented.
	const short FORMAT		= 0x3602;
	const short MASK		= 0x3706;
	const short ENDMASKS		= 0x3800;
	const short LIBDIRSIZE		= 0x3902; // Not implemented.
	const short SRFNAME		= 0x3a06; // Not implemented.

	class GDS2Record {
	public:
		GDS2Record(unsigned short numBytes, char* bufRecord);
		GDS2Record(const GDS2Record& record);
		~GDS2Record();

		unsigned short size() {return m_numBytes;}
		unsigned short type() {return (m_bufRecord[0] << 8) + m_bufRecord[1];}
		std::string toString();
		std::string toHexString();
	private:
		short 		getShort(unsigned short index); 
		std::string	getDateString(unsigned short index);
		std::string	getString(unsigned short index);
		double		getReal(unsigned short index);
		int		getInt(unsigned short index);
		unsigned short m_numBytes;
		char* m_bufRecord;
	};
};
