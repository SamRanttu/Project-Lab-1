#include <MSP430.h>
#include <driverlib.h>
#include <math.h>

volatile uint8_t overcurrent = 0;


int main(void) {

    PMM_unlockLPM5();

    WDTCTL = WDTPW | WDTHOLD; //stop watchdog timer

    //p2.6 timer
    P2DIR |= BIT6 | BIT7; 
    P2SEL0 |= BIT6 | BIT7; 
    P2SEL1 &= ~BIT6 | BIT7;

    //Output pins
    P1DIR |= BIT3;
    P2DIR |= BIT2;
    P3DIR |= BIT0;
    P3DIR |= BIT1;
    P1DIR |= BIT0; 
    //comparator input
    P2DIR &= ~BIT0;
    P2REN &= ~BIT0;
    P2IES &= ~BIT0;
    P2IFG &= ~BIT0;
    P2IE |= BIT0;

    __enable_interrupt();
    movement();
}

int movement(void) {

    //pwm timer for pin 2.6
    TB0CCR0 = 48; 
    TB0CCR5 = 15;
    TB0CCTL5 = OUTMOD_7;
    //pwm timer for pin 2.7
    TB0CCTL6 = OUTMOD_7;
    TB0CCR6 = 15; 
    //timer clear
    TB0CTL = TBSSEL_2 | MC_1 | TBCLR;

    //Delay before movement to set rover down
    __delay_cycles(4000000);

    //Moving 1 foot forward
    P1OUT &= ~BIT0;
    

    P2OUT |= BIT2;
    P1OUT &= ~BIT3;
    P3OUT |= BIT0;
    P3OUT &= ~BIT1;

    __delay_cycles(1000000);

    P3OUT &= ~BIT0;
    P3OUT |= BIT1;

    __delay_cycles(950000);

    P3OUT &= ~BIT1;
    P2OUT &= ~BIT2;
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT_2(void){
    // Overcurrent detected → shut down PWM + motors
    
    if (P2IFG & BIT0) {
        P2IFG &= ~BIT0;
        overcurrent = 1;
        TB0CCTL5 = 0;
        TB0CCTL6 = 0;

        P1OUT &= ~BIT3;
        P2OUT &= ~BIT2;
        P3OUT &= ~(BIT0 | BIT1);
        P1OUT |= BIT0;
    }
}
