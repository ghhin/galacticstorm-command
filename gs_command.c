// ギャラクティックストームのコマンド入力&連射用
// PIC12F683

#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 8000000

#define WAIT_1MS 1000
#define COMMAND_DELAY 33334
#define START_DELAY 66668

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_ON & MCLRE_OFF);

void start_plus()
{
  if(GP3 == 0) {
    __delay_us(WAIT_1MS);
    if(GP3 == 0) {
      for(int i=0; i<77; i++) {
        if(i < 44) {
          GP1 = 0; // SHOT4
        }
        if(i < 33) {
          GP0 = 0; // SHOT3
        }
        GP4 = 0; // SHOT2
        __delay_us(COMMAND_DELAY);
        GP1 = 1;
        GP0 = 1;
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

void shot2_inout()
{
  GP4 = GP5;
  __delay_us(WAIT_1MS);
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
    shot2_inout();
  }
}
