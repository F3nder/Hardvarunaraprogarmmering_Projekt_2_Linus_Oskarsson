/********************************************************************************
* isr.c: Inneh�ller avbrottsrutiner.
********************************************************************************/
#include "header.h"

/************************************************************************/
/* ISR (PCINT0-vect): Avbrottsrutin f�r tryckknappar.
                     * Tryckknapp 1 pausar/forts�tter r�kningen.
					 * Tryckknapp 2 byter h�ll p� r�kningen (upp eller ner).
					 * tryckknapp 3 t�nder/sl�cker displayerna.         */
/************************************************************************/
ISR (PCINT0_vect)
{
	disable_pin_change_interrupt(IO_PORTB);
	timer_enable_interrupt(&debounce);
	
	if (button_is_pressed(&b1))
	{
		display_toggle_count();
	}
	else if (button_is_pressed(&b2))
	{
		display_toggle_count_direction();
	}
	else if (button_is_pressed(&b3))
	{
		display_toggle_output();
	}
}

/************************************************************************/
/* ISR (TIMER0_OVF-vect): Avbrottsrutin f�r debounce skydd p� 
                          tryckknapparna f�r att inte f� flera knapptryck.
						  �teraktiverar avbrott efter 300ms.            */
/************************************************************************/
ISR (TIMER0_OVF_vect)
{
	timer_count(&debounce);
	
	if (timer_elapsed(&debounce) == true)
	{
		enable_pin_change_interrupt(IO_PORTB);
		timer_reset(&debounce);
	}
	
	return;	
}

/********************************************************************************
* ISR (TIMER1_COMPA_vect): Avbrottsrutin som �ger rum vid uppr�kning till 256 av
*                          Timer 1 i CTC Mode, vilket sker var 0.128:e
*                          millisekund n�r timern �r aktiverad. En g�ng per
*                          millisekund togglas talet utskrivet p� 
*                          7-segmentsdisplayerna mellan tiotal och ental.
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
   display_toggle_digit();
   return;
}

/********************************************************************************
* ISR (TIMER2_OVF_vect): Avbrottsrutin som �ger rum vid uppr�kning till 256 av
*                        Timer 2 i Normal Mode, vilket sker var 0.128:e
*                        millisekund n�r timern �r aktiverad. En g�ng per sekund
*                        inkrementeras talet utskrivet p� 7-segmentsdisplayerna.
********************************************************************************/
ISR (TIMER2_OVF_vect)
{
   display_count();
   return;
}
