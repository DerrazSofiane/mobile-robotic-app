//PROJET ROBOT GROUPE: PIGEON
//NOM : DILARD GEOFFROY ; ROUSSEL CEDRIC ; HERICY MAXIME 






#include "p30f6010a.h"
#define logique 0xF9EB
#define FCY 5000000
#define FPWM 10000

//Codes pour afficheurs 7 segments
#define off 0x00
#define on 0xFF

void IO_Init(void)
{
	//Configuration des Entrées/Sorties
	ADPCFG=logique;		//Port B logique-attention ICD3 utilise RB0/RB1 pour PGD/PGC
	TRISA=0xFFFF;		//Configuration du port A-1:Input
	TRISB=0xFFFF;		//Configuration du port B-0:Output
	TRISC=0xFFFF;		//Configuration du port C-1:Input
	TRISD=0x0001;		//Configuration du port D-1:Input
	TRISE=0x0000;		//Configuration du port E-0:Output
	TRISF=0xFFFF;		//Configuration du port F-1:Input
	TRISG=0xFFFF;		//Configuration du port G-1:Input
}

// Configuration Timer 1 (résolution 1ms)
void Timer1_Init(void)
{
	// Quartz 20 MHz et diviseur par 4 --> FCY = 5 MHz --> TCY = 200ns
	T1CONbits.TGATE = 0 ; 	// inutilisé
	T1CONbits.TSYNC = 0 ; 	// inutilisé
	T1CONbits.TSIDL = 0 ; 	// inutilisé
	T1CONbits.TCKPS = 2 ; 	// Diviseur de fréquence 1:64
	T1CONbits.TCS = 0 ; 	// Source "Internal Clock" TCY
	PR1 = 78 ; 				// Résolution du Timer 1: 1ms = 78 x 64 x 200ns
	IFS0bits.T1IF = 0 ; 	// Remise à 0 du flag interruption Timer 1
	IEC0bits.T1IE = 0 ; 	// Interruption Timer 1 désactivée
	T1CONbits.TON = 0 ; 	// Timer 1 désactivé
}

// Configuration ADC
void ADC_Init(void)
{
	ADCON1 = 0x00E0; 	// Conversion automatique après échantillonnage - format : integer
	ADCON2 = 0x0000; 	// Référence de tension : AVDD et AVSS
	ADCON3 = 0x1F02; 	// Temps d'échantillonnage = 31xTad, Tad=2xTcy
	ADCSSL = 0x0000; 	// Pas de scan séquentiel des entrées analogiques
}

// Configuration Interface PWM
void PWM_Init(void)
{
	PTCONbits.PTEN = 0; 	// interface PWM OFF
	PTCON = 0x0000; 		// Mode Free Running - diviseur de fréquence par 1
	PTPER = (FCY/FPWM-1);	// Période du signal PWM
	//PWMCON1=0x0330; // PWM1H et PWM2H en sorties indépendantes
	PWMCON1=0x0303; // PWM1L et PWM2L en sorties indépendantes
	PWMCON2=0x0004; 		// Mise à jour immédiate des registres PDC "duty cycle"
	DTCON1 = 0x0000; 		// Temps morts non pris en compte
	DTCON2 = 0x0000; 		// Temps morts non pris en compte
	OVDCON = 0x0F00; 		// Les sorties PWM 1 et 2 sont commandées par l'interface PWM
	PTCONbits.PTEN = 1; 	// interface PWM ON
}

// Temporisation (résolution 1ms)
void tempo_ms(unsigned int duree_ms)
{
	unsigned int compteur=0;
	T1CONbits.TON = 1 ; 		// Timer 1 activé
	while (compteur < duree_ms)
	{
		if (IFS0bits.T1IF == 1)
		{
			compteur++; 		// incrémentation du compteur
			IFS0bits.T1IF = 0; 	// raz flag interruption Timer 1
		}
	}
	T1CONbits.TON = 0 ; 		// Timer 1 désactivé
}

// Lecture ADC
unsigned int Read_Analog (unsigned int channel)
{
	unsigned int ADCValue;
	ADCHS = channel; 			// Voie à numériser
	ADCON1bits.ADON = 1; 		// ADC ON
	ADCON1bits.SAMP = 1; 		// Echantillonnage (31xTad) et conversion
	while (!ADCON1bits.DONE); 	// Fin de conversion ?
	ADCValue = ADCBUF0; 		// Lecture du résultat
	ADCON1bits.ADON = 0; 		// ADC OFF
	return ADCValue;
}

void demi_tour(void)
{
	_RD5=1;
	PDC1=0.5*499;		//ou PDC2=0.5*PTPER; Modification du rapport cyclique
	tempo_ms(420);
}

void acceleration(void)
{
	int i;
	for(i=0;i<6;i++)
	{
		PDC1=PDC1+0.125*499;
		PDC2=PDC2+0.159375*499;
		tempo_ms(500);
	}
}

void deceleration(void)
{
	int i;
	for(i=0;i<6;i++)
	{
		PDC1=PDC1-0.125*499;
		PDC2=PDC2-0.159375*499;
		tempo_ms(500);
	}
}

void stop(void)
{
	PDC1=0;			//ou PDC1=0.5*PTPER; Modification du rapport cyclique		coeff = 1.275
	PDC2=0;		//ou PDC2=0.5*PTPER; Modification du rapport cyclique
}

void main(void)
{
	//Configurations
	IO_Init();		//Appel de la fonction IO_Init() - Entrées-Sorties
	Timer1_Init(); 	// Configuration du Timer 1
	ADC_Init(); 	// Configuration ADC
	PWM_Init(); 	// Configuration Interface PWM
	
	//Programme principal

		_RD4=1;
		_RD5=0;

		//PDC1=0.5*499;			//ou PDC1=0.5*PTPER; Modification du rapport cyclique		coeff = 1.275
		//PDC2=0.6375*499;		//ou PDC2=0.5*PTPER; Modification du rapport cyclique

		_RE0=1;
		_RE2=1;
		
		acceleration();
		tempo_ms(5000);
		deceleration();
		stop();
		while(1);
}
