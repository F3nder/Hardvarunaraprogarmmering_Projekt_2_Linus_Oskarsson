/************************************************************************/
/* main.c: Program för 7-segmentsdisplayer för upp och ned räkning.
           Displayerna kontrolleras av 3 tryckknappar anslutna till 
		   pin 11, 12, 13.                                              */
/************************************************************************/
#include "header.h"


struct button b1, b2, b3;
struct timer debounce;

static inline void setup(void);

/************************************************************************/
/* main: Initierar programmet sedan resetar wdt-timern för att inte
         startaom programmet om allt går som det ska.                   */
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
/* setup: Initierar tryckknappar och sätter på avbrott på dessa.
          Initierar wdt-timer och aktiverar avbrott för den.
		  Initierar displayserna.
		  Initierar timer för skydd mot debounce.                       */
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