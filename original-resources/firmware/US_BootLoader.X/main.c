/* 
 * File:   main.c
 * Author: Sparky
 * Compiler: Microchip XC8 1.12
 *
 * Created on ??????, 2013, ?????? 5, 3:15
 */
#define _MAIN_C

#include "mcu.h"
#include "usb/usb.h"
#include "usb/usb_function_hid.h"
#include "io.h"
#include "OLED.h"

UINT8 OLED;

void displayTasts(void);

void main(void){
    int i;
    mcuInit();

    if(((B1 == 0) || (B3 == 0)) && (NVMDATA != 0x6193471A)){
        if(mcuValidAppPresent() == 1)mcuJumpToApp();
    }
    NVMDATA = 0xFFFFFFFF;

    OLED=1;     //detect OLED
    i=20;
    while(i){
        i--;
        SDISDO_IO;
        SDO_OUT=1;
        _delay_ms(1);
        if(SDI_IN!=1)break;
        SDO_OUT=0;
        _delay_ms(1);
        if(SDI_IN!=0)break;
        SDISDO_OI;
        SDI_OUT=1;
        _delay_ms(1);
        if(SDO_IN!=1)break;
        SDI_OUT=0;
        _delay_ms(1);
        if(SDO_IN!=0)break;
    }
    SDI_OUT=0;
    SDO_OUT=0;
    SDISDO_OO;
    if(i)OLED=0;

    if(OLED){
        mcuSPIOpen();
        OLEDInit();
    }
    
    IOInit();
    while(1){
        displayTasts();
        IOTasks();
    }
}

void displayTasts(void){
    volatile static int CT;
    volatile static int CTT;
    int i;

    CT++;

    if(!OLED){
        i=IND1;
        IND1=IND2;
        IND2=IND3;
        IND3=i;
    }
    if((CT & 4095) == 4095){
        CTT++;
        if(OLED){
            i=128;
            while(i--){
                OLEDBUFF.B[3][i]=((CTT+i) & 8)?0xFF:0;
                OLEDBUFF.B[4][i]=~OLEDBUFF.B[3][i];
            }
            OLEDUpdate();
        }
        else{
            i=LEDA;
            LEDA=LEDB;
            LEDB=LEDC;
            LEDC=LEDD;
            LEDD=LEDE;
            LEDE=LEDF;
            LEDF=LEDG;
            LEDG=i;
        }
    }
}

#undef _MAIN_C