// ギャラクティックストームのコマンド入力&連射用
// PIC12F683

#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 8000000

#define COMMAND_DELAY 16667
#define START_DELAY 33334
#define RAPID_DELAY 16667

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_ON & MCLRE_OFF);

void start_plus()
{
  if(GP3 == 0) {
    __delay_us(COMMAND_DELAY);
    if(GP3 == 0) {
      for(int i=0; i<44; i++) { // SHOT4
        GP1 = 0;
        __delay_us(COMMAND_DELAY);
        GP1 = 1;
        __delay_us(COMMAND_DELAY);
      }

      for(int i=0; i<33; i++) { // SHOT3
        GP0 = 0;
        __delay_us(COMMAND_DELAY);
        GP0 = 1;
        __delay_us(COMMAND_DELAY);
      }

      for(int i=0; i<77; i++) { // SHOT2
        GP4 = 0;
        __delay_us(COMMAND_DELAY);
        GP4 = 1;
        __delay_us(COMMAND_DELAY);
      }

      // PUSH START
      __delay_us(START_DELAY);
      GP2 = 0;
      __delay_us(START_DELAY);
      GP2 = 1;
      __delay_us(START_DELAY);
    }
  }
}

void shot2_pulse()
{
  if(GP5 == 0) {
    GP4 = 0;
    __delay_us(RAPID_DELAY);
    GP4 = 1;
    __delay_us(RAPID_DELAY);
  }
}

void main()
{
  // initialize
  OSCCON = 0b01110000;
  TRISIO = 0b00100000;
  ANSEL = 0x00;
  CMCON0 = 0x07;
  CMCON1 = 0x00;
  GP4 = 1; // SHOT2
  GP2 = 1; // START
  GP1 = 1; // SHOT4
  GP0 = 1; // SHOT3

  while(1) {
    start_plus();
    shot2_pulse();
  }
}
