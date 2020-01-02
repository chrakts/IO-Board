#ifndef MYCONSTANTS_H_INCLUDED
#define MYCONSTANTS_H_INCLUDED

//enum{QUARZ,CLK2M,CLK32M};

#define SYSCLK CLK32M

#define PLL 0

#define CLOCK_CALIBRATION 0x83

#define Q0_PINS 0d00011000
#define Q2_PINS 0d00100100
#define Q3_PINS 0d01000010
#define Q4_PINS 0d10000001

enum{CRC_NIO,CRC_IO,CRC_NO,CRC_YES};
enum{MEMORY_ERROR,PARAMETER_ERROR,UNKNOWN_ERROR,TRANSMISSION_ERROR,SECURITY_ERROR,CRC_ERROR,NO_ACTIVE_SENSOR};


#endif // MYCONSTANTS_H_INCLUDED
