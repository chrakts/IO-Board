/*
 */

#include "IO-Board.h"


void setup()
{
	init_clock(SYSCLK,PLL,true,CLOCK_CALIBRATION);

	PORTA_DIRSET = 0xf0; // 4x Eingang, dann 4x LEDs
	PORTB_DIRSET = 0xff;; // nichts angeschlossen
	PORTC_DIRSET = 0xff; // 4x LED, dann 4x Ausgang
	PORTD_DIRSET = 0xff; // nur RS232 an Pin6/7
	PORTD_DIRCLR = SERIAL_RX_PIN_0; // RxD an Pin6
	PORTE_DIRSET = 0xff; // nichts angeschlossen

	PORTA_OUTSET = 0xf0;
	PORTC_OUTSET = 0xff;

	PORTA_INTCTRL = PORT_INT0LVL_HI_gc;
	PORTA_INT0MASK = 0x0f;
	PORTA_PIN0CTRL = PORT_SRLEN_bm | PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc | PORT_INVEN_bm; // | PORT_OPC_PULLUP_gc
	PORTA_PIN1CTRL = PORT_SRLEN_bm | PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc | PORT_INVEN_bm;
	PORTA_PIN2CTRL = PORT_SRLEN_bm | PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc | PORT_INVEN_bm;
	PORTA_PIN3CTRL = PORT_SRLEN_bm | PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc | PORT_INVEN_bm;

	uint8_t i,led;
	led = 0x10;
	for(i=0;i<=3;i++)
	{
		PORTA_OUT = ~led | 0x0f;
		_delay_ms(100);
		led = led<<1;
	}
	PORTA_OUT = 0xf0;
	led = 0x01;
	for(i=0;i<=3;i++)
	{
		PORTC_OUT = ~led | 0xf0;
		_delay_ms(100);
		led = led<<1;
	}
	PORTC_OUT = 0xff;
  PORTA_OUT =  (reverseBits(PORTA_IN) & 0xf0);
	//init_mytimer();

	PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
	sei();
  cmulti.open(Serial::BAUD_115200,F_CPU);
  cmulti.println("Hallo vom IO-Board");
}


int main(void)
{
  setup();
  cmulti.sendStandard("me","BR",'f','a','j','t');
  while(1)
  {
    comStateMachine(&cmulti);
    doJob(&cmulti);
  }

  return 0;
}

bool setOutputStatus(uint8_t bit, uint8_t status)
{
  if(bit<4)
  {
    if(status==1)
    {
      PORTC_OUTCLR = outputPins[bit];
    }
    else
    {
      PORTC_OUTSET = outputPins[bit];
    }
    return(true);
  }
  else
    return(false);
}

bool getInputStatus(uint8_t bit, uint8_t *status)
{
uint8_t pinStatus;
  if(bit<4)
  {
    pinStatus =  (PORTA_IN & 0x0f) & (0x01 << bit);
    if(pinStatus==0)
      *status = 1;
    else
      *status = 0;
    return(true);
  }
  else
    return(false);
}

static unsigned char lookup[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };

uint8_t reverseBits(uint8_t n)
{
   // Reverse the top and bottom nibble then swap them.
   return (lookup[n&0b1111] << 4) | lookup[n>>4];
}


SIGNAL(PORTA_INT0_vect)
{
  PORTA_OUT =  (reverseBits(PORTA_IN) & 0xf0);
}
