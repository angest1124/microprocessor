#include <nds32_intrinsic.h>

volatile int trigger;
volatile int g_nIntCount=0;
/*#define HW_IR_ISR()	HW_IR_NEC_TYPE_routine(); //IR*/
#define HW_TIMER0_ISR()	HW_TIMER0_routine();
#define HW_TIMER1_ISR()	HW_TIMER1_routine();


void initIntr()
{
	/* enable SW0, HW0 and HW1 */
	//__nds32__mtsr(0x10003, NDS32_SR_INT_MASK);
	__nds32__mtsr(0x0003, NDS32_SR_INT_MASK);
	//intc_reset();


}

void clear_swi ()
{
	unsigned int int_pend;

	int_pend = 0x10;
	__nds32__mtsr(int_pend, NDS32_SR_INT_PEND);
	__nds32__dsb();
}

/* User can use our handler or Default_Handler */
#if 0
void exception_handler(int exception_nr)
{
	unsigned int *led = 0x902ffffc;
	*led = exception_nr;
	//DRV_PutStr("exception handler\n");
	while(1);
}

void tlb_exception_handler(int exception_nr)
{
	unsigned int *led = 0x902ffffc;
	*led = exception_nr;
	//DRV_PutStr("tlb exception handler\n");
	while(1);
}

void error_exception_handler(int exception_nr)
{
	unsigned int *led = 0x902ffffc;
	*led = exception_nr;
	//DRV_PutStr("error exception handler\n");
	while(1);
}
#endif

void syscall_handler()
{
	static int cnt = 0;

	if (++cnt < 5)
		asm("syscall 0x5000\n\t");

}

void HW0_ISR()
{
	//#define INT0_IR_ENABLE	*((unsigned int *)0x00200D04)
	//#define INT0_IR_FLAG	*((unsigned int *)0x00200D14)
	#define INT0_TIMER0_ENABLE	*((unsigned int *)0x00200D00)
	#define INT0_TIMER0_FLAG	*((unsigned int *)0x00200D10)

	unsigned short int u16IntFlag0, u16IntFlag1;

	u16IntFlag0 = (INT0_TIMER0_FLAG & INT0_TIMER0_ENABLE);
	//u16IntFlag1 = (INT0_IR_FLAG & INT0_IR_ENABLE);

	if(u16IntFlag0 & 0x08)
	{	INT0_TIMER0_FLAG &= ~0x08;
		HW_TIMER0_ISR();
	}
	//else if(u16IntFlag1 & 0x0002)
	//{	INT0_IR_FLAG &= ~(0x02);
		//HW_IR_ISR();
	//}
}
void HW1_ISR()
{
	#define INT1_0_ENABLE	*((unsigned int *)0x00200D08)
	#define INT1_0_FLAG	*((unsigned int *)0x00200D18)

	unsigned short int u16IntFlag1;

	u16IntFlag1 = (INT1_0_FLAG & INT1_0_ENABLE);

	if(u16IntFlag1 & 0x10)
	{	INT1_0_FLAG &= ~0x10;
		HW_TIMER1_ISR();
	}
}

void SW0_ISR()
{
	*(unsigned int *)0x001F6A10=0x000000ff;
	return;
}

inline void GIE_ENABLE()
{
	__nds32__setgie_en();
	__nds32__dsb();
}

inline void GIE_DISABLE()
{
	__nds32__setgie_dis();
	__nds32__dsb();
}

 /* this function generates a s/w interrupt */
void gen_swi()
{
	unsigned int int_pend;

	int_pend = __nds32__mfsr(NDS32_SR_INT_PEND);
	int_pend |= 0x10000;
	__nds32__mtsr(int_pend, NDS32_SR_INT_PEND);
	__nds32__dsb();
}

#if 0
void SYSirq_Disable_Interrupts_Save_Flags(unsigned int *flags)
{
	unsigned int tmp_flags;

	*flags = __nds32__mfsr(NDS32_SR_PSW) & 0x1;
	__nds32__setgie_dis();
	__nds32__dsb();
}

void SYSirq_Enable_Interrupts_Save_Flags(unsigned int *flags)
{
	unsigned int tmp_flags;

	*flags = __nds32__mfsr(NDS32_SR_PSW) & 0x1;
	__nds32__setgie_en();
	__nds32__dsb();
}

void SYSirq_Interrupts_Restore_Flags(unsigned int flags)
{
 	unsigned int tmp;

	tmp = __nds32__mfsr(NDS32_SR_PSW);
	tmp = __nds32__bclr(tmp, 0) | flags;
	__nds32__mtsr(tmp, NDS32_SR_PSW);
	__nds32__dsb();
}
#endif
