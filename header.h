#ifndef HEADER_H_
#define HEADER_H_

/* Inkluderingsdirektiv */
#include "timer.h"
#include "wdt.h"
#include "display.h"
#include "button.h"
#include "eeprom.h"

/* Deklaration av externa struktar */
extern struct button b1, b2, b3;
extern struct timer debounce;

#endif /* HEADER_H_ */