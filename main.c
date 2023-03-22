/************************************************************************/
/* main.c: Program f�r 7-segmentsdisplayer f�r upp och ned r�kning.
           Displayerna kontrolleras av 3 tryckknappar anslutna till 
		   pin 11, 12, 13.                                              */
/************************************************************************/
#include "header.h"


struct button b1, b2, b3;
struct timer debounce;

static inline void setup(void);

/************************************************************************/
/* main: Initierar programmet sedan resetar wdt-timern f�r att inte
         startaom programmet om allt g�r som det ska.                   */
/************************************************************************/
int main(void)
{
	setup();
	
    while (1) 
    {
		wdt_reset();
    }
	return 0;
}

/************************************************************************/
/* setup: Initierar tryckknappar och s�tter p� avbrott p� dessa.
          Initierar wdt-timer och aktiverar avbrott f�r den.
		  Initierar displayserna.
		  Initierar timer f�r skydd mot debounce.                       */
/************************************************************************/
static inline void setup(void)
{
	button_init(&b1, 11);
	button_init(&b2, 12);
	button_init(&b3, 13);
	button_enable_interrupt(&b1);
	button_enable_interrupt(&b2);
	button_enable_interrupt(&b3);
	
	wdt_init(WDT_TIMEOUT_1024_MS);
	wdt_enable_interrupt();
	display_init();	
	timer_init(&debounce, TIMER_SEL_0, 300);
	return;
}