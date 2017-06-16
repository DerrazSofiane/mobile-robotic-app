//IUT GEII LE HAVRE - ER Robotique
//Informatique industrielle - MICROCONTROLEUR dSPIC30F6010A
//Configuration Bits : Mode XT / Watchdog disable
//FCY = Fquartz/4 = 5 MHz

#include "p30f6010a.h"
#define FCY 5000000
#define FPWM 10000

#define IOportA 0x---- // 1:Input,0:Output
#define IOportB 0x---- // 1:Input,0:Output
#define IOportC 0x---- // 1:Input,0:Output
#define IOportD 0x---- // 1:Input,0:Output
#define IOportE 0x---- // 1:Input,0:Output
#define IOportF 0x---- // 1:Input,0:Output
#define IOportG 0x---- // 1:Input,0:Output
#define PortB_logique 0x---- // 1:Logique,0:Analogique

//configuration des IO
void IO_Init (void)
{
    ADPCFG=PortB_logique; // Port B logique - attention ICD3 utilise RB0/RB1 pour PGD/PGC
    TRISA=IOportA;  //configuration Port A -
    TRISA=IOportB;  //configuration Port A - 1:Input,0:Output
    TRISA=IOportC;  //configuration Port A - 1:Input,0:Output
    TRISA=IOportD;  //configuration Port A - 1:Input,0:Output
    TRISA=IOportE;  //configuration Port A - 1:Input,0:Output
    TRISA=IOportF;  //configuration Port A - 1:Input,0:Output
    TRISA=IOportG;  //configuration Port A - 1:Input,0:Output
}

//configuration timer 1 (r�solution 1ms)
void Timer1_Init(void)
{
    //Quartz 20 MHz et duvuseyr oar 4 -->FCY = 5 MHz -->TCY = 200ns
    T1CONbits.TGATE = 0; //inutileis�
    T1CONbits.TSYNC = 0; //inutileis�
    T1CONbits.TSIDL = 0; //inutileis�
    T1CONbits.TCKPS = 2; //Diviseur de fr�quence 1:64
    T1CONbits.TCS = 0  ; //Source "Internal Clock" TCY
    PR1 = -- ;//R�solution du Timer 1 : 1ms = -- x 64 x 200ns
    IfS0bits.T1IF = 0; //Remise � 0 du flag interruption Timer 1
    IEC0bits.T1IE = 0; //Interrution Timer 1 d�sactiv�e
    T1CONbits.TON = 0 ;//Timer 1 d�sactiv�
}

//Configuration ADC
void ADC_Init(void)
{
    ADCON1 = 0x00E0; //Conversion automatique apr�s �chatillonnage - format : integer
    ADCON2 = 0x0000; //R�f�rence de tension : AVDD et AVSS
    ADCON3 = 0x1F02; //Temps d'�chantillonnage = 31xTad,Tad=2xTcy
    ADCONL = 0x0000; //Pas de scan s�quentiel des entr�es analogiques
}

//Configuration Interface PWM
voidPWM_Init(void)
{
    PTCONbits.PTEN= 0; // interface PWM OFF
    PTCON = 0x0000; // Mode Free Running -diviseur de fr�quence par 1
    PTPER = (FCY/FPWM -1); // P�riode du signal PWM
    //PWMCON1=0x0330; // PWM1H et PWM2H en sorties ind�pendantes
    //PWMCON1=0x0303; // PWM1L et PWM2L en sorties ind�pendantes
    PWMCON2=0x0004; // Mise � jour imm�diate des registres PDC "dutycycle"
    DTCON1 = 0x0000; // Temps morts non pris en compte
    DTCON2 = 0x0000; // Temps morts non pris en compte
    OVDCON = 0x0F00; // Les sorties PWM 1 et 2 sont command�es par l'interface PWM
    PTCONbits.PTEN= 1; // interface PWM ON
}

void tempo_ms(unsigned intduree_ms)
{
    unsignedintcompteur=0;
    T1CONbits.TON = 1 ; // Timer1 activ�
    while(compteur < duree_ms)
    {
        if (IFS0bits.T1IF== 1)
        {
            compteur++; // incr�mentation du compteur
            IFS0bits.T1IF= 0; // raz flag interruption Timer1
        }
    }
    T1CONbits.TON = 0 ; // Timer1 d�sactiv�
}

//lecture ADC
unsignedintRead_Analog(unsignedintchannel)
{
    unsignedintADCValue;
    ADCHS = channel; // Voie � num�riser
    ADCON1bits.ADON= 1; // ADC ON
    ADCON1bits.SAMP= 1; // Echantillonnage (31xTad) et conversion
    while(!ADCON1bits.DONE); // Fin de conversion ?
    ADCValue= ADCBUF0; // Lecture du r�sultat
    ADCON1bits.ADON= 0; // ADC OFF
    return ADCValue;
}

void main(void)
{
    IO_Init(); // Configuration des IO
    timer1_Init(); // Configuration du Timer 1
    ADC_Init(); // Configuration ADC
    PWM_Init(); // Configuration Interface PWM    
    while(1)
    {
         //Code � d�velopper
    }
}
