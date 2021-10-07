/*
 * global.h
 *
 *  Created on: 2016/5/16
 *      Author: admin
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

/*
 * ir_dev.h
 *
 *  Created on: 2016/5/16
 *      Author: admin
 */

#ifndef IR_DEV_H_
#define IR_DEV_H_

#define IR_KEY_NULL		0x00
/* for Leader code */
#define IR_LEAD_CNT		(unsigned char)((13.5*1000)/64) //210
#define LEAD_TOLERANCE	10 // tolerance=10 Range220~200
/* for Repeat code */
#define IR_REP_CNT		(unsigned char)((11.25*1000)/64) //175
#define REP_TOLERANCE 		20 // tolerance=20 Range195~155
/* for Data high bit */
#define IR_DATA0_CNT		(unsigned char)((1.125*1000)/64) //18
#define DATA0_TOLERANCE	(unsigned char)((1.125*1000*0.2)/64)+1
				// tolerance=5 Range23~13
/* for Data Low bit */
#define IR_DATA1_CNT		(unsigned char)((2.25*1000)/64) //35
#define DATA1_TOLERANCE	(unsigned char)((2.25*1000*0.2)/64)+1
				// tolerance=8 Range43~27

unsigned char gu8IrBit, u8IrCount;
unsigned char gu8IrAddr, gu8IrComm;
unsigned char gu8IrKey0, gu8IrKey1, gu8IrKey2, gu8IrKey3;
unsigned char gu8IrReceiveFlag;
unsigned int gu32IrData;

typedef enum
{	// H/W IR receive status(for NEC type)
	IR_IDLE = 0,
	IR_DATA_BIT0,
	IR_DATA_BIT1,
	IR_DATA_BIT2,
	IR_DATA_BIT3,
	IR_DATA_BIT4,
	IR_DATA_BIT5,
	IR_DATA_BIT6,
	IR_DATA_BIT7,
	IR_DATA_BIT8,
	IR_DATA_BIT9,
	IR_DATA_BIT10,
	IR_DATA_BIT11,
	IR_DATA_BIT12,
	IR_DATA_BIT13,
	IR_DATA_BIT14,
	IR_DATA_BIT15,
	IR_DATA_BIT16,
	IR_DATA_BIT17,
	IR_DATA_BIT18,
	IR_DATA_BIT19,
	IR_DATA_BIT20,
	IR_DATA_BIT21,
	IR_DATA_BIT22,
	IR_DATA_BIT23,
	IR_DATA_BIT24,
	IR_DATA_BIT25,
	IR_DATA_BIT26,
	IR_DATA_BIT27,
	IR_DATA_BIT28,
	IR_DATA_BIT29,
	IR_DATA_BIT30,
	IR_DATA_BIT31
} eIR_RECEIVE_STATUS;

#define TIMES 25
#define Digit_0	0x6000
#define Digit_1	0x4000
#define Digit_2	0x2000
#define Digit_3	0x0000
#define Digit_4	0xE000
#define Digit_5	0xC000
#define Digit_6	0xA000
#define Digit_7	0x8000

#define Number_0	0x3F3F
#define Number_1	0x0606
#define Number_2	0x5B5B
#define Number_3	0x4F4F
#define Number_4	0x6666
#define Number_5	0x6D6D
#define Number_6	0x7D7D
#define Number_7	0x2727
#define Number_8	0x7F7F
#define Number_9	0x6767
#define Number_Dot  0x8080

unsigned short int seven_seg[10] = {Number_0, Number_1, Number_2, Number_3, Number_4, Number_5, Number_6, Number_7, Number_8, Number_9};

#endif /* IR_DEV_H_ */


#endif /* GLOBAL_H_ */
