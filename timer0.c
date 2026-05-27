#include <LPC21xx.H>
#include "timer0.h"
#define mCOUNTER_ENABLE (1<<0)
#define mCOUNTER_RESET (1<<1)
#define INTERRUPT_MR0 (1<<0)
#define MR0_RESET (1<<1)
#define INTERRUPT_FLAG_MR0 (1<<0)
#define INTERRUPT_FLAG_MR1 (1<<3)
void InitTimer0(void){
	T0TCR = mCOUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR |= mCOUNTER_RESET; //trzeba wywolac initTIMER0 
	T0TCR &= ~(mCOUNTER_RESET); //zerujemy wszystkie bity poza pierwszym(zerowanie flagi??)
	T0PR = 14;
	while( T0TC != (uiTime)){}

}

void InitTimer0Match0(unsigned int iDelayTime){
	T0PR = 14;
	T0MR0 = iDelayTime;
	
  T0MCR |= MR0_RESET|INTERRUPT_MR0;//|INTERRUPT_FLAG_MR1;//to tylko konfiguruje co ma sie stac kiedy timer osiagnie zadana wartosc
	T0TCR |= mCOUNTER_RESET;//reset timera
	T0TCR &= ~(mCOUNTER_RESET); //zeruje bit 1 aby licznik nie byl zablokowany  
  
	T0TCR |= mCOUNTER_ENABLE;
	
}
void WaitOnTimer0Match0(){
	while(1 != (T0IR&INTERRUPT_FLAG_MR0)){}
	
	T0IR |= INTERRUPT_FLAG_MR0;

}


	