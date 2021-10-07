#include "WT59F064.h"
#include <stdlib.h>
#define RTC_PARAMETER	*((unsigned int *)0x00201038)
//#define To_ASCII 0x30

//#include "GPIO_PE.c"
unsigned char KeyIn, temp;
#define GOTO_LINE_1 0x8000
#define GOTO_LINE_2 0xC000

#define RS	0x0080
#define E	0x0040
#define RW	0x0020
#define CleanSet 0x0000

unsigned char Key = 0;
unsigned int note[16] = {0, 2551, 2273, 2024, 1912, 1704, 1517, 1433, 1276, 1136, 1012, 956, 851, 759, 716, 638};
unsigned char song[] = {0x72,0x01,0x72,0x01,0x72,0x01,0x42,0x01,0x52,0x01,0x52,0x01,0x42,0x42,0x42,0x04,0x92,0x01,0x92,0x01,0x82,0x01,0x82,0x01,0x72,0x72,0x72,0x02};
int Ass[8] = {0x8100, 0x8300, 0x8500, 0x8700, 0xC100, 0xC300, 0xC500, 0xC700};

int temp1[100];
int temp2[100];
int i = 0;

int sum = 0;
int  n;
void delay1(unsigned int nCount){
   unsigned int i;
   for(i = 0; i < nCount; i++);
}
void InitialLCD(void){
 	WriteIns(0x3800);  //FUNCTION SET
 	WriteIns(0x0800);  // off display
 	WriteIns(0x0100);  // clear buffer
 	WriteIns(0x0e00);  // on display
 	WriteIns(0x0600);  // set input mode
}
void KeyScan(void){ //±½´y«öÁä
	unsigned char Col, Row;
	unsigned char ScanLine = 0x8;
	unsigned char KeyIn, temp;
	for(Col=0;Col<4;Col++){
		GPIO_OMOD_PC = 0x3FF0; //¿é¥X±½´y«H¸¹Port C bit0~bit3
		GPIO_OEN_PC = 0x3FF0;
		GPIO_DAT_PC = ~ScanLine; //¿é¥X±½´y«H¸¹

		GPIO_RS_PC = 0x00FF;
		GPIO_REN_PC = 0x00FF;
		KeyIn = (PAD_PC & 0xF0); //Åª¨ú¥Ø«e«öÁäª¬ºA
		delay1(1000);
		temp = (PAD_PC & 0xF0);
		if(temp == KeyIn && KeyIn != 0xF0)
			Key = (PAD_PC & 0xFF); //§PÂ_«öÁä½X
		ScanLine >>= 1; //±½´y´`Àô
	}
}

void WriteString(char *p){
	while(*p){
		WriteData(*p);
		p++;
	}
}
void gotoxy(unsigned int x, unsigned int y)
{
	if(x == 1)
		WriteIns(GOTO_LINE_1 + (y << 8));
	else
		WriteIns(GOTO_LINE_2 + (y << 8));
}
void IntInitial(void){
	initIntr();
	GIE_ENABLE();
}
/*----------timer-----------------*/
void Timer0_Initial(void){
	TIM0_CTL |= BITF;  // Timer Enable
	TIM0_CNT = 0; //incremented every (pscl + 1) of trigger source
	TIM0_PSCL = 23999; //°£ÀW­È
	TIM0_MAT0A = 5; //Match mat0a register for output match mode
	TIM0_IE |= BIT4; // Interrupt enable for mat0a
	IE0_0 |= BIT3;  // 1: Enable Timer 0 interrupt
	TIM0_CTL |= BIT0; // Timer Start
}
void Timer1_Initial(void){

	TIM1_CTL |= BITF;  // Timer Enable
	TIM1_CNT = 0; //incremented every (pscl + 1) of trigger source
	TIM1_PSCL = 23999; //°£ÀW­È
	TIM1_MAT0B = 1000; //Match mat0a register for output match mode
	TIM1_IE |= BIT5; // Interrupt enable for mat0b
	IE1_0 |= BIT4;  // 1: Enable Timer 1 interrupt
	TIM1_CTL |= BIT0; // Timer Start
}
unsigned short LED = 0x7FFF;
void HW_TIMER0_routine(void){
	unsigned int count = 0;
	TIM0_CNT = 0;  // reset
	TIM0_OFIF |= BIT4;  // write ¡¥1¡¦ to clear Interrupt flag of mat0a

	WriteIns(0x3800);  //FUNCTION SET
	WriteIns(0x0C00);  //DISPLAY CONTROL
	WriteIns(0x0600);  //SET INPUT MODE
	n = rand() % 8;
	temp1[i] = n;
	WriteIns(Ass[n]);  //2-LINE DD RAM SET Address
	WriteData('D');
	delay1(1000000);
	InitialLCD();

	WriteIns(0x3800);  //FUNCTION SET
	WriteIns(0x0C00);  //DISPLAY CONTROL
	WriteIns(0x0600);  //SET INPUT MODE
	int a, b;
	a = sum % 10;
	b = sum / 10;
	char a1, b1, m0,m1;
	a1 = a + '0';
	b1 = b + '0';
	if(b == 0){
		WriteIns(0xCF00);
		WriteData(a1);  //2-LINE DD RAM SET Address
	}
	else{
		WriteIns(0xCF00);
		WriteData(a1);  //2-LINE DD RAM SET Address
		WriteIns(0xCE00);
		WriteData(b1);

	}
	if(LED == 0x0000){
			m0 = sum%10 + '0';
			m1 = sum/10 + '0';
			TIM0_CTL |= BIT3;
			InitialLCD();
			WriteIns(0x8000);
			WriteData('G');
			WriteData('A');
			WriteData('M');
			WriteData('E');
			WriteData(' ');
			WriteData('O');
			WriteData('V');
			WriteData('E');
			WriteData('R');
			WriteIns(0xC000);
			WriteData('S');
			WriteData('C');
			WriteData('O');
			WriteData('R');
			WriteData('E');
			WriteData(' ');
			if(m1 == 0){
				WriteIns(0xC700);
				WriteData(m0);  //2-LINE DD RAM SET Address
			}
			else{
				WriteIns(0xC700);
				WriteData(m0);  //2-LINE DD RAM SET Address
				WriteIns(0xC600);
				WriteData(m1);

			}
		}

	KeyScan(); //±½´y«öÁä
	if(Key != 0xFF) //°»´ú¨ì¦³«öÁä³QÄ²µo
	{
		switch(Key)
		{
			case 0xE7:
				temp2[i] = 0;
				delay1(10000);
			break;

			case 0xEB:
				temp2[i] = 1;
				delay1(10000);
			break;

			case 0xEE:
				temp2[i] = 3;
				delay1(10000);
			break;

			case 0xD7:
				temp2[i] = 4;
				delay1(10000);
			break;

			case 0xDB:
				temp2[i] = 5;
				delay1(10000);
			break;

			case 0xDD:
				temp2[i] = 6;
				delay1(10000);
			break;

			case 0xDE:
				temp2[i] = 7;
				delay1(10000);
			break;

		}
		Key = (0x7E & 0xFF);
	}
	int j;
	sum = 0;
	for(j = 0; j <= i; j++){
		if(temp1[j] == temp2[j])
			sum++;
	}
	i++;


	delay1(1000000);
	GPIO_DAT_PE = ~(LED);
	LED=LED>>1;



}
void HW_TIMER1_routine(void){
	TIM1_CNT = 0;  // reset
	TIM1_OFIF |= BIT4;  // write ¡¥1¡¦ to clear Interrupt flag of mat1a
	//GPIO_DAT_PE = 0xffff;//LED3
	delay1(10000);
}

/*-------------------voice------------------------*/
void note_translate (unsigned int note){
	PWM6_PERIOD = note;
	PWM6_DUTY = note/2;
}


void PWM_Initial(void){
	GPIO_ACT_PD = 0xFFFB;//GPIO port D.2 enables the PWM function.
	PWM4_PWM7_BASE_CLK = 0x3; 	// MUC Clock = 24MHz  => 2MHz
	PWM4_PWM7_ENABLE = 0x40; 	//PWM6 enable
}
void timer_delay(int cnt){
	int i;
	for(i=0; i<cnt; i+=15){
		TIM0_CTL |= BIT0; // Timer Start
		while(TIM0_CNT <= 187);
		TIM0_CTL &= ~BIT0; // Timer Stop
		TIM0_CNT = 0;
	}
}

void timer_initialize(){
	TIM0_CTL |= BITF; // Timer Enable
	TIM0_CNT = 0; //incremented every (pscl + 1) of trigger source
	TIM0_PSCL = 23999; //?¤é »??
}
/*-------------------------------------------------*/

void CheckBusy(void) {//BF ,Check busy flag
	unsigned short int i = 0x8000;
	while(i&0x8000){
		GPIO_ACT_PD = 0xFFFF; //Initialize GPIO_D output
		GPIO_OMOD_PD = 0x0;
		GPIO_OEN_PD = 0x0;

		GPIO_DAT_PD = (RW + E);

		GPIO_ACT_PD = 0xFF00; //Initialize GPIO_D input
		GPIO_RS_PD = 0xFF00;
		GPIO_REN_PD = 0xFF00;

		i = PAD_PD;

		GPIO_DAT_PD = CleanSet;
		delay1(100000);
	}
}

void WriteData(unsigned short int i){
	GPIO_ACT_PD = 0xFFFF; //Initialize GPIO_D outpot
	GPIO_OMOD_PD = 0x0;
	GPIO_OEN_PD = 0x0;

	GPIO_DAT_PD = ((i << 8) + RS + E);
	GPIO_DAT_PD = CleanSet;
	CheckBusy();
}

void WriteIns(unsigned short int instruction){
	GPIO_ACT_PD = 0xFFFF; //Initialize GPIO_D outpot
	GPIO_OMOD_PD = 0x0;
	GPIO_OEN_PD = 0x0;

	GPIO_DAT_PD = (instruction + E );
	GPIO_DAT_PD = CleanSet;

	CheckBusy();
}

void InitialRTC(void){
	System_Control_18 = ( System_Control_18 | 0x0060);
	//¨Ï¥Î¥~³¡¥Û­^¾_Àú¾¹32.768KHz.
	System_Control_20 = ( System_Control_20 | 0x0005);
	// Switch clock source from external crystal.

	RTC_PARAMETER = 0x07; //Clock out=32.768KHz
}

int main(){
	InitialLCD();
	GPIO_ACT_PB = 0xFFFF; //Initialize GPIO_B output
	GPIO_OMOD_PB = 0x0;
	GPIO_OEN_PB = 0x0;

	GPIO_ACT_PC = 0xFF; //Initialize GPIO_C in/output

	GPIO_ACT_PE = 0xFFFF; //Initialize GPIO_E output
	GPIO_OMOD_PE = 0x0;
	GPIO_OEN_PE = 0x0;

	int i = 0;
	System_Control_00 = ( System_Control_00 | 0x000E); // Using external crystal
	System_Control_04 = ( System_Control_04 | 0x0001);
	// Switch clock source from external crystal.

	PWM_Initial();
	timer_initialize();

	PWM6_CLOCK=1;

	unsigned char beat, temp;

	do{
		temp = song[i];
		if(temp == 0){
			i=0;
			temp = song[i];
		}
		beat=temp & 0x0f;
		temp=(temp>>4) & 0x0f;
		note_translate(note[temp]);
		timer_delay(beat);
		i++;
		KeyScan();
		if(Key == 0x7E){
				note_translate(note[12]);//°ª­µDO
				timer_delay(2);//ÅT¨â¬í
			    note_translate(note[0]);
				timer_delay(3);//ÅT¨â¬í
				note_translate(note[0]);
				timer_delay(3);//ÅT¨â¬í
				note_translate(note[1]);//­µDO
				timer_delay(5);//ÅT¨â¬í
				note_translate(note[0]);
				timer_delay(5);//ÅT¨â¬í
				note_translate(note[0]);
				timer_delay(3);//ÅT¨â¬í
				note_translate(note[1]);//­µDO
				timer_delay(5);//ÅT¨â¬í
				note_translate(note[0]);
				note_translate(note[0]);
				timer_delay(3);//ÅT¨â¬í
				timer_delay(5);//ÅT¨â¬í
				note_translate(note[1]);//­µDO
				timer_delay(5);//ÅT¨â¬í
				note_translate(note[0]);
				note_translate(note[0]);
				timer_delay(3);//ÅT¨â¬í
				timer_delay(5);//ÅT¨â¬í
				note_translate(note[12]);//°ª­µDO
				timer_delay(2);//ÅT¨â¬í
				note_translate(note[12]);//°ª­µDO
				timer_delay(2);//ÅT¨â¬í
			break;
		}
	}while(1);

	note_translate(note[0]);//§Ö³t°±¤î
	timer_delay(2);//ÅT¨â¬í

/*-------------voice end-------------------*/
	IntInitial();
	InitialLCD();
	InitialRTC();
	GPIO_ACT_PE = 0xFFFF; //Initialize GPIO
	GPIO_OMOD_PE = 0x0; // push/pull mode
	GPIO_OEN_PE = 0x0; //output enable
	Timer1_Initial();
	Timer0_Initial();
	return 0;
}
