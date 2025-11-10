#include <msp430.h>

#define UART_RX BIT1
#define UART_TX BIT0

int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;

    WDTCTL = WDTPW | WDTHOLD;               // Stop WDT

    P3DIR |= BIT7; //Pin setup for PWM
    P3SEL0 |= BIT7;
    P3SEL1 &= ~BIT7;

    TB0CCR0 = 25; //Timer setup for appropriate pin
    TB0CCR6 = 12;
    TB0CCTL6 = OUTMOD_7;
    TB0CTL = TBSSEL_2 | MC_1 | TBCLR;

    P4DIR &= ~BIT3 | ~BIT2  | ~BIT1 | ~BIT4;
    P4REN |= BIT3 | BIT2  | BIT1 | BIT4;
    P4IES &= ~BIT3 | ~BIT2  | ~BIT1 | ~BIT4;
    P4IFG &= ~BIT3 | ~BIT2  | ~BIT1 | ~BIT4;
    P4IE |= BIT3 | BIT2  | BIT1 | BIT4;

    uart_init();
    __enable_interrupt();
}

void uart_init() {
    P6SEL0 |= UART_RX;
    P6SEL1 &= ~UART_RX;
    P6DIR &= ~UART_RX;

    P6SEL0 |= UART_TX;
    P6SEL1 &= ~UART_TX;
    P6DIR |= UART_TX;

    UCA3CTLW0 |= UCSWRST;
    UCA3CTLW0 |= UCSSEL__SMCLK;
    UCA3BRW = 52;
    UCA3MCTLW = UCOS16 | UCBRF_1 | 0x4900;
    UCA3CTLW0 &= ~UCSWRST;
}

#pragma vector=PORT4_VECTOR
__interrupt void PORT4(void) {
    if (P4IFG & BIT3) {
        if (P4IN & BIT3) {
            UCA3TXBUF = 0x4F;
        } else {
            UCA3TXBUF = 0XFF;
        }
        P4IES ^= BIT3;
        P4IFG &= ~BIT3;
    } else if (P4IFG & BIT2) {
        if (P4IN & BIT2) {
            UCA3TXBUF = 0xAA;
        } else {
            UCA3TXBUF = 0XFF;
        }
        P4IES ^= BIT2;
        P4IFG &= ~BIT2;
    } else if (P4IFG & BIT1) {
        if (P4IN & BIT1) {
            UCA3TXBUF = 0x23;
        } else {
            UCA3TXBUF = 0XFF;
        }
        P4IES ^= BIT1;
        P4IFG &= ~BIT1;
    } else if (P4IFG & BIT4) {
        if (P4IN & BIT4) {
            UCA3TXBUF = 0x98;
        } else {
            UCA3TXBUF = 0XFF;
        }
        P4IES ^= BIT4;
        P4IFG &= ~BIT4;
    }
}
