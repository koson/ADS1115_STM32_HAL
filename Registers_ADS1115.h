#ifndef SRC_REGISTERS_H_
#define SRC_REGISTERS_H_
#ifdef __cplusplus
extern "C" {
#endif


/*
 *
 * Address Pointer Register (address = N/A) [reset = N/A]
 *   bit [7:2]  reserver always write 0h
 *   bit [1:0]  Register address pointer
 *   				00 : Conversion register
 *   				01 : Config register
 *   				10 : Lo_thresh register
 *   				11 : Hi_thresh register
 *
 * Conversion Register (P[1:0] = 0h) [reset = 0000h]
 *   bit[15:0]	Conversion Register,
 *   				The 16-bit Conversion register contains the
 *   				result of the last conversion in binary
 *   				two's complement format.
 *
 * Config Register (P[1:0] = 1h) [reset = 8583h]
 *   bit 15			OS  Operational status or single-shot conversion start
 *   					When writing:
 *   						0 : No effect
 *   						1 : Start a single conversion (when in power-down state)
 *   					When reading:
 *   						0 : Device is currently performing a conversion
 *   						1 : Device is not currently performing a conversion
 *
 *   bit[14:12]		MUX[2:0] Input multiplexer configuration (ADS1115 only)
 *   			    	000 : AINP = AIN0 and AINN = AIN1 (default)
 *   			    	001 : AINP = AIN0 and AINN = AIN3
 *   			    	010 : AINP = AIN1 and AINN = AIN3
 *   			    	011 : AINP = AIN2 and AINN = AIN3
 *   			    	100 : AINP = AIN0 and AINN = GND
 *   			    	101 : AINP = AIN1 and AINN = GND
 *   			    	110 : AINP = AIN2 and AINN = GND
 *   			    	111 : AINP = AIN3 and AINN = GND
 *
 *   bit[11:9]		PGA[2:0] Programmable gain amplifier configuration
 *   					000 : FSR = ±6.144 V(1)
 *   					001 : FSR = ±4.096 V(1)
 *   					010 : FSR = ±2.048 V (default)
 *   					011 : FSR = ±1.024 V
 *   					100 : FSR = ±0.512 V
 *   					101 : FSR = ±0.256 V
 *   					110 : FSR = ±0.256 V
 *   					111 : FSR = ±0.256 V
 *
 *   bit 8			MODE Device operating mode
 *   			    	0 : Continuous-conversion mode
 *   			    	1 : Single-shot mode or power-down state (default)
 *
 *   bit[7:5]		DR[2:0] Data rate
 *						000 : 8 SPS
 *						001 : 16 SPS
 *						010 : 32 SPS
 *						011 : 64 SPS
 *						100 : 128 SPS (default)
 *						101 : 250 SPS
 *						110 : 475 SPS
 *						111 : 860 SPS
 *
 *   bit 4			COMP_MODE Comparator mode (ADS1114 and ADS1115 only)
 *   					0 : Traditional comparator (default)
 *   					1 : Window comparator
 *
 *   bit 3			COMP_POL Comparator polarity (ADS1114 and ADS1115 onl
 *   					0 : Active low (default)
 *   					1 : Active high
 *
 *   bit 2			 COMP_LAT Latching comparator (ADS1114 and ADS1115 only)
 *   					0 : Non latching comparator . The ALERT/RDY pin does not latch
 *   					when asserted (default).
 *   					1 : Latching comparator. The asserted ALERT/RDY pin remains
 *   					latched until conversion data are read by the master or an
 *   					appropriate SMBus alert response is sent by the master.
 *   					The device responds with its address, and it is the lowest
 *   					address currently asserting the ALERT/RDY bus line.
 *
 *   bit[1:0]		COMP_QUE[1:0] Comparator queue and disable (ADS1114 and ADS1115 only)
 *   					00 : Assert after one conversion
 *   					01 : Assert after two conversions
 *   					10 : Assert after four conversions
 *   					11 : Disable comparator and set ALERT/RDY pin to high-impedance (default)
 *
 *
 *
*/
enum ADS1115_ADDRESS {
	ADDR_TO_GND = 0x48,   	// slave address = 1001000
	ADDR_TO_VDD = 0x49,		// slave address = 1001001
	ADDR_TO_SDA = 0x4A,		// slave address = 1001010
	ADDR_TO_SCL = 0x4B		// slave address = 1001011

};

enum REG {
	CONV_REG = 0x0,			// Conversion Register
	CONF_REG = 0x1,			// Config Register
	Lo_thresh_REG = 0x2,	// Lower threshold values register
	Hi_thresh_REG = 0x3		// Upper threshold values register
};


enum OS {					// Operational status or single-shot conversion start
	W_NE = 0x0,				// No effect
	W_SC = 0x1,				// Start a single conversion (when in power-down state)
	R_CC = 0x0,				// Device is currently performing a conversion
	R_NCC = 0x1				// Device is not currently performing a conversion
};


enum MUX {					// Input multiplexer configuration (ADS1115 only)
	AIN0_AIN1 = 0x0,		// Differential P = AIN0, N = AIN1 (default)
	AIN0_AIN3 = 0x1,		// Differential P = AIN0, N = AIN3
	AIN1_AIN3 = 0x2,		// Differential P = AIN1, N = AIN3
	AIN2_AIN3 = 0x3,		// Differential P = AIN2, N = AIN3
	AIN0_AIN_GND = 0x4,		// Single-ended AIN0
	AIN1_AIN_GND = 0x5,		// Single-ended AIN1
	AIN2_AIN_GND = 0x6,		// Single-ended AIN2
	AIN3_AIN_GND = 0x7		// Single-ended AIN3
};


enum PGA {					// Programmable gain amplifier configuration
	FS6144 = 0x0,			// +/-6.144V range = Gain 2/3, LSB size = 187.5 μV
	FS4096 = 0x1,			// +/-4.096V range = Gain 1, LSB size = 125 μV
	FS2048 = 0x2,       	// +/-2.048V range = Gain 2 (default), LSB size = 62.5 μV
	FS1024 = 0x3,      	 	// +/-1.024V range = Gain 4, LSB size = 31.25 μV
	FS0512 = 0x4,       	// +/-0.512V range = Gain 8, LSB size = 15.625 μV
	FS0256_0 = 0x5,     	// +/-0.256V range = Gain 16, LSB size = 7.8125 μV
};

enum MODE {					// Device operating mode
	CCM = 0x0,				// Continuous-conversion mode
	PDSSM = 0x1				// Single-shot mode or power-down state (default)
};

enum DR {					// Data rate
	SPS8 = 0x0,				// 8 SPS
	SPS16 = 0x1,			// 16 SPS
	SPS32 = 0x2,			// 32 SPS
	SPS64 = 0x3,			// 64 SPS
	SPS128 = 0x4,			// 128 SPS
	SPS250 = 0x5,			// 250 SPS
	SPS475 = 0x6,			// 475 SPS
	SPS860 = 0x7			// 860 SPS
};

enum COMP_MODE {			// Comparator mode (ADS1114 and ADS1115 only)
	TCWH = 0x0,				// Traditional comparator (default)
	WC = 0x1				//  Window comparator
};

enum COMP_POL {				// Comparator polarity (ADS1114 and ADS1115 only)
	AL = 0x0,				// Active low (default)
	AH = 0x1				// Active high
};

enum COMP_LAT {				// Latching comparator (ADS1114 and ADS1115 only)
	NLC = 0x0,				// Non latching comparator
	LC = 0x1				// Latching comparator.
};

enum COMP_QUE {				// Comparator queue and disable (ADS1114 and ADS1115 only)
	AAOC = 0x0,				// Assert after one conversion
	AATC = 0x1,				// Assert after two conversions
	AAFC = 0x2,				// Assert after four conversions
	DC = 0x3				// Disable comparator and set ALERT/RDY pin to high-impedance (default)
};
#ifdef __cplusplus
}
#endif

#endif /* SRC_REGISTERS_H_ */

