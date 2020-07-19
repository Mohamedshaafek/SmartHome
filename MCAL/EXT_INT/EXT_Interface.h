#ifndef _EXT_INTERFACE_H_
#define _EXT_INTERFACE_H_

#define FALLING 		0
#define RISING  		1
#define IOC    		    2
#define LOW_LEVLE		3

#define SENCE_MODE_EX0  RISING		// to sense for EX INT0  you can choose all mode
#define SENCE_MODE_EX1  RISING		// to sense for EX INT1  you can choose all mode
#define SENCE_MODE_EX2  FALLING		// to sense for EX INT2  you can choose Rising or Falling ONLY

#define EXT0_EN 1		//to Enable EX interrupt 0 make value 1
#define EXT1_EN 0		//to Enable EX interrupt 1 make value 1
#define EXT2_EN 0		//to Enable EX interrupt 2 make value 1


void EXT_VidSense(void);
void EXT_Vidinit(void);
void EXT_VidEnable(void);
void EXT_VidDisable(void);



#endif
