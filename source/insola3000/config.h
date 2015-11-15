#ifndef _CONFIG_H_
#define _CONFIG_H_

#define _INSOLA_3000_DEBUG_
#define SERIAL_BAUDRATE 9600

#define BUTTONS_COMMON_PIN    5
#define BUTTONS_COMMON_VALUE  LOW
#define UP_BUTTON_PIN         4
#define DOWN_BUTTON_PIN       2
#define STARTSTOP_BUTTON_PIN  3
#define DEBOUNCE_DELAY        20
#define LONGPRESS_DELAY       500
#define LONGPRESS_REPETITION  200

#define LCD_VCC_PIN    8
#define LCD_GND_PIN    9
#define LCD_DATA_PIN   7
#define LCD_CLOCK_PIN  6
#define LCD_UPDATE_PIN -1

#define OUTPUT_PIN 13

#define MAX_PROGRAMMABLE_TIME 90*60;


#endif /* _CONFIG_H_ */

