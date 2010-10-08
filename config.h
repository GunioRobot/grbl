/*
  config.h - eeprom and compile time configuration handling 
  Part of Grbl

  Copyright (c) 2009 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef config_h
#define config_h

#define VERSION "0.51"

// Settings that can only be set at compile-time:

//#define BAUD_RATE 9600
#define BAUD_RATE 115200

#define STEPPERS_ENABLE_DDR     DDRB
#define STEPPERS_ENABLE_PORT    PORTB
#define STEPPERS_ENABLE_BIT         5

#define STEPPING_DDR       DDRC
#define STEPPING_PORT      PORTC 
#define X_STEP_BIT           0
#define Y_STEP_BIT           2
#define Z_STEP_BIT           4
#define X_DIRECTION_BIT            1
#define Y_DIRECTION_BIT            3
#define Z_DIRECTION_BIT            5

#define LCD_DB0
#define LCD_DB1
#define LCD_DB2
#define LCD_DB3
#define LCD_ENABLE
#define LCD_

#define LIMIT_DDR      DDRB
#define LIMIT_PORT     PORTB
#define X_LIMIT_BIT          4
#define Y_LIMIT_BIT          3
#define Z_LIMIT_BIT          2

#define SPINDLE_ENABLE_DDR DDRB
#define SPINDLE_ENABLE_PORT PORTB
#define SPINDLE_ENABLE_BIT 1

#define SPINDLE_DIRECTION_DDR DDRB
#define SPINDLE_DIRECTION_PORT PORTB
#define SPINDLE_DIRECTION_BIT 0


// Version of the EEPROM data. Will be used to migrate existing data from older versions of Grbl
// when firmware is upgraded. Always stored in byte 0 of eeprom
#define SETTINGS_VERSION 1

// Current global settings (persisted in EEPROM from byte 1 onwards)
struct Settings {
  double steps_per_mm[3];
  uint8_t microsteps;
  uint8_t pulse_microseconds;
  double default_feed_rate;
  double default_seek_rate;
  double seek_rate;
  uint8_t invert_mask;
  double mm_per_arc_segment;
};
struct Settings settings;

// Initialize the configuration subsystem (load settings from EEPROM)
void config_init();

// Print current settings
void dump_settings();

// A helper method to set new settings from command line
void store_setting(int parameter, double value);


// Default settings (used when resetting eeprom-settings)
#define MICROSTEPS 8
// DV:
// 200 steps = 0.05" = 25.4*0.05mm = 1.27 mm, so steps/mm = 200/1.27 = 157.48031496063
// including microsteps = 1600/1.27 = 1259.84251969
// reciprocal is 

#define X_STEPS_PER_MM (157.48031496063*MICROSTEPS)
#define Y_STEPS_PER_MM (157.48031496063*MICROSTEPS)
#define Z_STEPS_PER_MM (157.48031496063*MICROSTEPS)
#define STEP_PULSE_MICROSECONDS 30

#define MM_PER_ARC_SEGMENT 0.1

#define RAPID_FEEDRATE 480.0 // in millimeters per minute
#define DEFAULT_FEEDRATE 480.0

#define DEFAULT_X_STEPS_PER_MM (157.48031496063*MICROSTEPS)
#define DEFAULT_Y_STEPS_PER_MM (157.48031496063*MICROSTEPS)
#define DEFAULT_Z_STEPS_PER_MM (157.48031496063*MICROSTEPS)
#define DEFAULT_MM_PER_ARC_SEGMENT 0.1
#define DEFAULT_STEP_PULSE_MICROSECONDS 30
#define DEFAULT_SEEKRATE 480.0

// Use this line for default operation (step-pulses high)
#define STEPPING_INVERT_MASK 0
// Uncomment this line for inverted stepping (step-pulses low, rest high)
// #define STEPPING_INVERT_MASK (STEP_MASK)
// Uncomment this line to invert all step- and direction bits
// #define STEPPING_INVERT_MASK (STEPPING_MASK)
// Or bake your own like this adding any step-bits or directions you want to invert:
// #define STEPPING_INVERT_MASK (STEP_MASK | (1<<X_DIRECTION_BIT) | (1<<Y_DIRECTION_BIT))


// Some useful constants
#define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits
#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits
#define STEPPING_MASK (STEP_MASK | DIRECTION_MASK) // All stepping-related bits (step/direction)
#define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

#endif
