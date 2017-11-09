/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC18F26K80
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"

void timer2ISR(void);
int count=0;
short time,time1;
short times[2];
uint8_t ls,ms;

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    //TMR2_SetInterruptHandler(timer2ISR);

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
   // INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        
        count=0;
        //INTERRUPT_GlobalInterruptEnable();
        //while(count<10000);
        __delay_ms(100);
        __delay_ms(100);
        __delay_ms(100);
        __delay_ms(100);
        __delay_ms(100);
        PORTCbits.RC4^=1;
        //EUSART1_Write(time);
        // Add your application code
        //TRISC = 0xA7;
        TRISCbits.TRISC3=0;//Make it output
        TRISCbits.TRISC2=0;//Make it output
        
        PORTCbits.RC3=1;//Make high
        PORTCbits.RC2=1;//Make high
        //count=0;
        //while(count<20){};
        __delay_us(10);
        TRISCbits.TRISC3=1;//make input
        TRISCbits.TRISC2=1;//make input
        count=0;
        
        TMR3_WriteTimer(0);
       // __delay_us(100);
        time=2500;
        time1=2500;
        //time=(TMR3_ReadTimer()/4);
        while((TMR3_ReadTimer()/4)<2500){
            if(PORTCbits.RC3==0&&TMR3_ReadTimer()/4<time){
                //time=count;
                time=TMR3_ReadTimer()/4;//16MHz clock, counts at 16/4=4MHz, divide by 4 to get 1MHz
                //break;
            }
            if(PORTCbits.RC2==0&&TMR3_ReadTimer()/4<time1){
                //time=count;
                time1=TMR3_ReadTimer()/4;//16MHz clock, counts at 16/4=4MHz, divide by 4 to get 1MHz
                //break;
            }
        }
       // INTERRUPT_GlobalInterruptDisable();
        ls=time&0xFF;
        ms=(time>>8)&0xFF;
        EUSART1_Write(ls);
        EUSART1_Write(ms);
        ls=time1&0xFF;
        ms=(time1>>8)&0xFF;
        EUSART1_Write(ls);
        EUSART1_Write(ms);

        
        
    }
}
/**
 End of File
*/
void timer2ISR(void){
    count++;
    //EUSART1_Write(count);
}