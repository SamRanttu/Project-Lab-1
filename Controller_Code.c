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

    uart_init();

    while(1) {
        UCA3TXBUF = 0x4F;
    }
}

void uart_init() {
    P6SEL0 |= UART_RX; //Set UART Receiver pin (not required for controller)
    P6SEL1 &= ~UART_RX;
    P6DIR &= ~UART_RX;

    P6SEL0 |= UART_TX; // Set UART Transmitter pin
    P6SEL1 &= ~UART_TX;
    P6DIR |= UART_TX;

    UCA3CTLW0 |= UCSWRST; //Sets baud rate
    UCA3CTLW0 |= UCSSEL__SMCLK;
    UCA3BRW = 52;
    UCA3MCTLW = UCOS16 | UCBRF_1 | 0x4900;
    UCA3CTLW0 &= ~UCSWRST;
}

