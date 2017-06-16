#include "p30f6010a.h"
#define FCY 5000000
#define FPWM 10000

#define I0portA 0x----
#define I0portB 0x----
#define I0portC 0x----
#define I0portD 0x----
#define I0portE 0x----
#define I0portF 0x----
#define I0portG 0x----
#define PortB_logique 0x----

void I0_Init (void)
{ 
    ADPCFG=PortB_logique;
    TRISA=I0portA;   
    TRISB=I0portB;  
    TRISC=I0portC;   
    TRISD=I0portD; 
    TRISE=I0portE;  
    TRISF=I0portF;
    TRISG=I0portG;
}

void Timer1_Init (void)
{
    T1CONbits.TGATE = 0 ;
    T1CONbits.TSYNC = 0 ;
    T1CONbits.TSIDL = 0 ;
    T1CONbits.TCKPS = 2 ;
    T1CONbits.TCS = 0 ;
    PR1 = -- ;
    IFS0bits.T1IF = 0 ;
    IEC0bits.T1IE = 0 ;
    T1CONbits.TON = 0 ;
}

void ADC_Init (void)
{
    ADCON1 = 0x00E0;
    ADCON2 = 0x0000;
    ADCON3 = 0x1F02;
    ADCSSL = 0x0000;
}

void PWM_Init(void)
{
    PTCONbits.PTEN = 0;
    PTCON = 0x0000;
    PTPER = (FCY/FPWM - 1);
    //PWMCON1=0x0330;
    //PWMCON1=0x0303;
    PWMCON2=0x004;
    DTCON1 = 0x0000;
    DTCON2 = 0x0000;
    OVDCON = 0x0F00;
    PTCONbits.PTEN = 1;
}

void tempo_ms (unsigned int duree_ms)
{
    unsigned int compteur=0;
    T1CONbits.TON = 1 ;
    while (compteur < duree_ms)
    {
        if (IFS0bits.T1IF == 1)
        {
            compteur++;
            IFS0bits.T1IF = 0;
        }
    }
    T1CONbits.TON = 0.
}

unsigned int Read_Analog (unsigned int channel)
{
    unsigned int ADCValue;
    ADCHS = channel;
    ADcon1bits.ADON = 1;
    ADCON1bits.SAMP = 1.
    while (!ADCON1bits.DONE);
    ADCValue = ADCBUF0;
    ADCON1bits.ADON = 0;
    return ADCValue;
}

void main(void)
{
    I0_Init();
    Timer1_Init();
    ADC_Init();
    PWM_Init();
    
    while(1)
    {
     //code à développer   
    }
}
