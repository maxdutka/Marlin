/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Arduino Mega with RAMPS v1.4 (or v1.3) pin assignments
 *
 * Applies to the following boards:
 *
 *  RAMPS_14_EFB_MD (Hotend, Fan, Bed, +MD Mod)
 *
 *  Other pins_MYBOARD.h files may override these defaults
 *
 */


#if NONE(IS_RAMPS_SMART, IS_RAMPS_DUO, IS_RAMPS4DUE, TARGET_LPC1768)
  #if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
    #error "Oops! Select 'Arduino/Genuino Mega or Mega 2560' in 'Tools > Board.'"
  #endif
#endif

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME "RAMPS 1.4"
#endif

//
// Servos
//
#ifndef SERVO0_PIN
  #ifdef IS_RAMPS_13
    #define SERVO0_PIN      7
  #else
    #define SERVO0_PIN     11
  #endif
#endif
#ifndef SERVO1_PIN
  #define SERVO1_PIN        6
#endif
#ifndef SERVO2_PIN
  #define SERVO2_PIN        5
#endif
#ifndef SERVO3_PIN
  #define SERVO3_PIN        4
#endif

//
// Limit Switches
//
#ifndef X_STOP_PIN
//  #ifndef X_MIN_PIN
//    #define X_MIN_PIN       3
//  #endif
  #ifndef X_MAX_PIN
    #define X_MAX_PIN       3
  #endif
#endif
#ifndef Y_STOP_PIN
//  #ifndef Y_MIN_PIN
//    #define Y_MIN_PIN      14
//  #endif
  #ifndef Y_MAX_PIN
    #define Y_MAX_PIN      2
  #endif
#endif


#ifndef Z_STOP_PIN
  #ifndef Z_MIN_PIN
    #define Z_MIN_PIN      5
  #endif
//  #ifndef Z_MAX_PIN
//    #define Z_MAX_PIN      19
//  #endif
#endif

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN  65
#endif

//
// Steppers
//
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#ifndef X_CS_PIN
  #define X_CS_PIN         X_ENABLE_PIN
#endif

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#ifndef Y_CS_PIN
  #define Y_CS_PIN         Y_ENABLE_PIN
#endif

#define Z_STEP_PIN         57
#define Z_DIR_PIN          58
#define Z_ENABLE_PIN       62
#ifndef Z_CS_PIN
  #define Z_CS_PIN         Z_ENABLE_PIN
#endif


#define E0_STEP_PIN        36
#define E0_DIR_PIN         34
#define E0_ENABLE_PIN      30

#ifndef E0_CS_PIN
#define E0_CS_PIN          E0_ENABLE_PIN
#endif

//#define E1_STEP_PIN        26
//#define E1_DIR_PIN         28
//#define E1_ENABLE_PIN      24
//#ifndef E1_CS_PIN
//  #define E0_CS_PIN        42
//#endif



//
// Temperature Sensors
//
#ifndef TEMP_0_PIN
  #define TEMP_0_PIN       13   // Analog Input
#endif
#ifndef TEMP_1_PIN
  #define TEMP_1_PIN       15   // Analog Input
#endif
#ifndef TEMP_BED_PIN
  #define TEMP_BED_PIN     14   // Analog Input
#endif

// SPI for Max6675 or Max31855 Thermocouple
#if DISABLED(SDSUPPORT)
  #define MAX6675_SS_PIN   66   // Don't use 53 if there is even the remote possibility of using Display/SD card
#else
  #define MAX6675_SS_PIN   66   // Don't use 49 as this is tied to the switch inside the SD card socket to detect if there is an SD card present
#endif

//
// Augmentation for auto-assigning RAMPS plugs
//
#if NONE(IS_RAMPS_EEB, IS_RAMPS_EEF, IS_RAMPS_EFB, IS_RAMPS_EFF, IS_RAMPS_SF) && !PIN_EXISTS(MOSFET_D)
  #if HOTENDS > 1
    #if TEMP_SENSOR_BED
      #define IS_RAMPS_EEB
    #else
      #define IS_RAMPS_EEF
    #endif
  #elif TEMP_SENSOR_BED
    #define IS_RAMPS_EFB
  #else
    #define IS_RAMPS_EFF
  #endif
#endif

//
// Heaters / Fans
//
#ifndef MOSFET_D_PIN
  #define MOSFET_D_PIN     -1
#endif
#ifndef RAMPS_D8_PIN
  #define RAMPS_D8_PIN      8
#endif
#ifndef RAMPS_D9_PIN
  #define RAMPS_D9_PIN      9
#endif
#ifndef RAMPS_D10_PIN
  #define RAMPS_D10_PIN    10
#endif

#define HEATER_0_PIN       RAMPS_D10_PIN

#if ENABLED(IS_RAMPS_EFB)                      // Hotend, Fan, Bed
  #define HEATER_BED_PIN   RAMPS_D8_PIN
#elif ENABLED(IS_RAMPS_EEF)                    // Hotend, Hotend, Fan
  #define HEATER_1_PIN     RAMPS_D9_PIN
#elif ENABLED(IS_RAMPS_EEB)                    // Hotend, Hotend, Bed
  #define HEATER_1_PIN     RAMPS_D9_PIN
  #define HEATER_BED_PIN   RAMPS_D8_PIN
#elif ENABLED(IS_RAMPS_EFF)                    // Hotend, Fan, Fan
  #define FAN1_PIN         RAMPS_D8_PIN
#elif DISABLED(IS_RAMPS_SF)                    // Not Spindle, Fan (i.e., "EFBF" or "EFBE")
  #define HEATER_BED_PIN   RAMPS_D8_PIN
  #if HOTENDS == 1
    #define FAN1_PIN       MOSFET_D_PIN
  #else
    #define HEATER_1_PIN   MOSFET_D_PIN
  #endif
#endif

#ifndef FAN_PIN
  #if EITHER(IS_RAMPS_EFB, IS_RAMPS_EFF)          // Hotend, Fan, Bed or Hotend, Fan, Fan
    #define FAN_PIN        RAMPS_D9_PIN
  #elif EITHER(IS_RAMPS_EEF, IS_RAMPS_SF)         // Hotend, Hotend, Fan or Spindle, Fan
    #define FAN_PIN        RAMPS_D8_PIN
  #elif ENABLED(IS_RAMPS_EEB)                  // Hotend, Hotend, Bed
    #define FAN_PIN         4                  // IO pin. Buffer needed
  #else                                        // Non-specific are "EFB" (i.e., "EFBF" or "EFBE")
    #define FAN_PIN        RAMPS_D9_PIN
  #endif
#endif

//
// Misc. Functions
//
#define SDSS               53
#define LED_PIN            13

#ifndef FILWIDTH_PIN
  #define FILWIDTH_PIN      5   // Analog Input on AUX2
#endif

// RAMPS 1.4 DIO 4 on the servos connector
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN    4
#endif

#ifndef PS_ON_PIN
  #define PS_ON_PIN        12
#endif

#if ENABLED(CASE_LIGHT_ENABLE) && !defined(CASE_LIGHT_PIN) && !defined(SPINDLE_LASER_ENA_PIN)
  #if NUM_SERVOS <= 1 // Prefer the servo connector
    #define CASE_LIGHT_PIN  6   // Hardware PWM
  #elif HAS_FREE_AUX2_PINS
    #define CASE_LIGHT_PIN 44   // Hardware PWM
  #endif
#endif

//
// M3/M4/M5 - Spindle/Laser Control
//
#if HAS_CUTTER && !defined(SPINDLE_LASER_ENA_PIN)
  #if !NUM_SERVOS                         // Use servo connector if possible
    #define SPINDLE_LASER_ENA_PIN     4   // Pullup or pulldown!
    #define SPINDLE_LASER_PWM_PIN     6   // Hardware PWM
    #define SPINDLE_DIR_PIN           5
  #elif HAS_FREE_AUX2_PINS
    #define SPINDLE_LASER_ENA_PIN    40   // Pullup or pulldown!
    #define SPINDLE_LASER_PWM_PIN    44   // Hardware PWM
    #define SPINDLE_DIR_PIN          65
  #else
    #error "No auto-assignable Spindle/Laser pins available."
  #endif
#endif

//
// TMC software SPI
//
#if ENABLED(TMC_USE_SW_SPI)
  #ifndef TMC_SW_MOSI
    #define TMC_SW_MOSI    66
  #endif
  #ifndef TMC_SW_MISO
    #define TMC_SW_MISO    44
  #endif
  #ifndef TMC_SW_SCK
    #define TMC_SW_SCK     64
  #endif
#endif

#if HAS_TMC220x
  /**
   * TMC2208/TMC2209 stepper drivers
   *
   * Hardware serial communication ports.
   * If undefined software serial is used according to the pins below
   */
  //#define X_HARDWARE_SERIAL  Serial1
  //#define X2_HARDWARE_SERIAL Serial1
  //#define Y_HARDWARE_SERIAL  Serial1
  //#define Y2_HARDWARE_SERIAL Serial1
  //#define Z_HARDWARE_SERIAL  Serial1
  //#define Z2_HARDWARE_SERIAL Serial1
  //#define E0_HARDWARE_SERIAL Serial1
  //#define E1_HARDWARE_SERIAL Serial1
  //#define E2_HARDWARE_SERIAL Serial1
  //#define E3_HARDWARE_SERIAL Serial1
  //#define E4_HARDWARE_SERIAL Serial1

  //
  // Software serial
  //

  #ifndef X_SERIAL_TX_PIN
    #define X_SERIAL_TX_PIN  40
  #endif
  #ifndef X_SERIAL_RX_PIN
    #define X_SERIAL_RX_PIN  63
  #endif
  #ifndef X2_SERIAL_TX_PIN
    #define X2_SERIAL_TX_PIN -1
  #endif
  #ifndef X2_SERIAL_RX_PIN
    #define X2_SERIAL_RX_PIN -1
  #endif

  #ifndef Y_SERIAL_TX_PIN
    #define Y_SERIAL_TX_PIN  59
  #endif
  #ifndef Y_SERIAL_RX_PIN
    #define Y_SERIAL_RX_PIN  64
  #endif
  #ifndef Y2_SERIAL_TX_PIN
    #define Y2_SERIAL_TX_PIN -1
  #endif
  #ifndef Y2_SERIAL_RX_PIN
    #define Y2_SERIAL_RX_PIN -1
  #endif

  #ifndef Z_SERIAL_TX_PIN
    #define Z_SERIAL_TX_PIN  42
  #endif
  #ifndef Z_SERIAL_RX_PIN
    #define Z_SERIAL_RX_PIN  65
  #endif
  #ifndef Z2_SERIAL_TX_PIN
    #define Z2_SERIAL_TX_PIN -1
  #endif
  #ifndef Z2_SERIAL_RX_PIN
    #define Z2_SERIAL_RX_PIN -1
  #endif

  #ifndef E0_SERIAL_TX_PIN
    #define E0_SERIAL_TX_PIN 44
  #endif
  #ifndef E0_SERIAL_RX_PIN
    #define E0_SERIAL_RX_PIN 66
  #endif
  #ifndef E1_SERIAL_TX_PIN
    #define E1_SERIAL_TX_PIN -1
  #endif
  #ifndef E1_SERIAL_RX_PIN
    #define E1_SERIAL_RX_PIN -1
  #endif
  #ifndef E2_SERIAL_TX_PIN
    #define E2_SERIAL_TX_PIN -1
  #endif
  #ifndef E2_SERIAL_RX_PIN
    #define E2_SERIAL_RX_PIN -1
  #endif
  #ifndef E3_SERIAL_TX_PIN
    #define E3_SERIAL_TX_PIN -1
  #endif
  #ifndef E3_SERIAL_RX_PIN
    #define E3_SERIAL_RX_PIN -1
  #endif
  #ifndef E4_SERIAL_TX_PIN
    #define E4_SERIAL_TX_PIN -1
  #endif
  #ifndef E4_SERIAL_RX_PIN
    #define E4_SERIAL_RX_PIN -1
  #endif
  #ifndef E5_SERIAL_TX_PIN
    #define E5_SERIAL_TX_PIN -1
  #endif
  #ifndef E5_SERIAL_RX_PIN
    #define E5_SERIAL_RX_PIN -1
  #endif
  #ifndef E6_SERIAL_TX_PIN
    #define E6_SERIAL_TX_PIN -1
  #endif
  #ifndef E6_SERIAL_RX_PIN
    #define E6_SERIAL_RX_PIN -1
  #endif
  #ifndef E7_SERIAL_TX_PIN
    #define E7_SERIAL_TX_PIN -1
  #endif
  #ifndef E7_SERIAL_RX_PIN
    #define E7_SERIAL_RX_PIN -1
  #endif
#endif

//
// Průša i3 MK2 Multiplexer Support
//
//#ifndef E_MUX0_PIN
//  #define E_MUX0_PIN 40   // Z_CS_PIN
//#endif
//#ifndef E_MUX1_PIN
//  #define E_MUX1_PIN 42   // E0_CS_PIN
//#endif
//#ifndef E_MUX2_PIN
//  #define E_MUX2_PIN 44   // E1_CS_PIN
//#endif

//////////////////////////
// LCDs and Controllers //
//////////////////////////


  //
  // LCD Display output pins
  //


#define LCD_PINS_RS         25   // CS chip select /SS chip slave select
#define LCD_PINS_ENABLE     27   // SID (MOSI)
#define LCD_PINS_D4         29   // SCK (CLK) clock

#define BEEPER_PIN      37

#define BTN_EN1           33
#define BTN_EN2           31
#define BTN_ENC           35
#define SD_DETECT_PIN     49

#define KILL_PIN          63


