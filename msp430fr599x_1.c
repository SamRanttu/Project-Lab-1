#include <msp430.h>

int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;

    WDTCTL = WDTPW | WDTHOLD;               // Stop WDT

    P3DIR |= BIT7;
    P3SEL0 |= BIT7;
    P3SEL1 &= ~BIT7;

    TB0CCR0 = 25;
    TB0CCR6 = 12;
    TB0CCTL6 = OUTMOD_7;
    TB0CTL = TBSSEL_2 | MC_1 | TBCLR;
}

