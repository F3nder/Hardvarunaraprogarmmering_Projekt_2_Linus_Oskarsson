/********************************************************************************
* isr.c: Innehåller avbrottsrutiner.
********************************************************************************/
#include "header.h"

/************************************************************************/
/* ISR (PCINT0-vect): Avbrottsrutin för tryckknappar.
                     * Tryckknapp 1 pausar/fortsätter räkningen.
					 * Tryckknapp 2 byter håll på räkningen (upp eller ner).
					 * tryckknapp 3 tänder/släcker displayerna.         */
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
/* ISR (TIMER0_OVF-vect): Avbrottsrutin för debounce skydd på 
                          tryckknapparna för att inte få flera knapptryck.
						  Återaktiverar avbrott efter 300ms.            */
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
* ISR (TIMER1_COMPA_vect): Avbrottsrutin som äger rum vid uppräkning till 256 av
*                          Timer 1 i CTC Mode, vilket sker var 0.128:e
*                          millisekund när timern är aktiverad. En gång per
*                          millisekund togglas talet utskrivet på 
*                          7-segmentsdisplayerna mellan tiotal och ental.
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
   display_toggle_digit();
   return;
}

/********************************************************************************
* ISR (TIMER2_OVF_vect): Avbrottsrutin som äger rum vid uppräkning till 256 av
*                        Timer 2 i Normal Mode, vilket sker var 0.128:e
*                        millisekund när timern är aktiverad. En gång per sekund
*                        inkrementeras talet utskrivet på 7-segmentsdisplayerna.
********************************************************************************/
ISR (TIMER2_OVF_vect)
{
   display_count();
   return;
}
