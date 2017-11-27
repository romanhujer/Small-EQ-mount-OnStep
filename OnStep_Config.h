// -----------------------------------------------------------------------------------
// Configuration (rename or copy to "Config.h" to use)

/*
 * For more information on setting OnStep up see http://www.stellarjourney.com/index.php?r=site/equipment_onstep and 
 * join the OnStep yahoo group at https://groups.yahoo.com/neo/groups/onsteptelescope/info
 * 
 * The Arduino Mega2560, Teensy3.x(3.1/3.2/3.5/3.6,) and some Launchpad TM4C devices are also supported (thanks to Luka.)
 * See the Pins.h file for detailed information on the pin maps
 *
 * The RA/Az (Axis1) and Dec/Alt (Axis2) stepper driver minimum connection is as follows:
 * RA/Az :  37,35 = Dir,Step (Teensy3.x 21,20)
 * Dec/Alt: 22,24 = Dir,Step (Teensy3.x  2, 3)
 * 
 * Optionally, a bluetooth or WiFi adapter (HC05, RN42, or ESP8266 for example) plugs into pins Tx1/Rx1.
 * +5VDC is normally used for the BT Adapter and +3.3VDC for the ESP8266 (make sure the regulator is sufficient to supply required current.)
 * I use two 2-wire cables for 0.1" headers.  Remember Rx goes to Tx and Tx goes to Rx. If using a Mega2560
 * be sure to get a BT module designed for 5 volt operation and signaling otherwise you'll have to design
 * and implement the level conversion hardware yourself.
*/

// ******************* These new pin assignments aren't well tested and mistakes might have been made, a mistake could damage your MCU etc. Use at your own risk. *****************
//
// This must be _ON to use the pin assignments given in this Config.h!  The Launchpad TM4C123GH6PM and LM4F120H5QR also have alternate pin assignments in this mode, see Pins.h
// this allows minimal wiring for Pololu style stepper driver modules and generally makes better use of the limited number of pins on a Teensy3.x
//
#define ALTERNATE_PINMAP_ON
// ******************* These new pin assignments aren't well tested and mistakes might have been made, a mistake could damage your MCU etc. Use at your own risk. *****************

// -------------------------------------------------------------------------------------------------------------------------
// ADJUST THE FOLLOWING TO CONFIGURE YOUR CONTROLLER FEATURES --------------------------------------------------------------

// Turns debugging on, used during testing, default=OFF
#define DEBUG_OFF

// Enables internal goto assist mount modeling (for Eq mounts), default=OFF (Experimental)
// Goto Assist in Sky Planetarium works even if this is off
#define ALIGN_GOTOASSIST_OFF

// Default speed for Serial1 com port, Default=9600
#define SERIAL1_BAUD_DEFAULT 9600

// ESP8266 reset and GPIO0 control, this sets run mode for normal operation.  Uploading programmer firmware to the OpStep MCU can then enable sending new firmware to the ESP8266-01
// Only supported on the Teensy3.x, Pin 18 (Aux1) for GPIO0 and Pin 5 (Aux2) for Rst control.  Choose only one feature on Aux1/2.
#define ESP8266_CONTROL_OFF

// Mount type, default is _GEM (German Equatorial) other options are _FORK, _FORK_ALT.  _FORK switches off Meridian Flips after (1, 2 or 3 star) alignment is done.  _FORK_ALT disables Meridian Flips (1 star align.)
// _ALTAZM is for Alt/Azm mounted 'scopes (1 star align only.)
#define MOUNT_TYPE_GEM

// Strict parking, default=OFF.  Set to ON and unparking is only allowed if successfully parked.  Otherwise unparking is allowed if at home and not parked (the Home/Reset command ":hF#" sets this state.) 
#define STRICT_PARKING_OFF

// ST4 interface on pins 47, 43, 45, 49.  Pin 47 is RA- (West), Pin 43 is Dec- (South), Pin 45 is Dec+ (North), Pin 49 is RA+ (East.)  (Teensy3.x pins 24, 25, 26, 27)
// ST4_ON enables the interface.  ST4_PULLUP enables the interface and any internal pullup resistors.
// It is up to you to create an interface that meets the electrical specifications of any connected device, use at your own risk.  Default=OFF
#define ST4_PULLUP
// If SEPARATE_PULSE_GUIDE_RATE_ON is used the ST4 port is limited to guide rates <= 1X except when ST4_HAND_CONTROL_ON is used.
// Additionally, ST4_HAND_CONTROL_ON enables special features: Press and hold [E]+[W] buttons for > 2 seconds...  In this mode [E] decreases and [W] increases guide rates (or if tracking isn't on yet adjusts illuminated recticule brightness.)
// [S] for Sync (or Accept if in align mode.) [N] for Tracking on/off. -OR- Press and hold [N]+[S] buttons for > 2 seconds...  In this mode [E] selects prior and [W] next user catalog item.
// [N] to do a Goto to the catalog item.  [S] for Sound on/off.  The keypad returns to normal operation after 4 seconds of inactivity.  ST4_HAND_CONTROL_ON also adds a 100ms de-bounce to all button presses.
// Finally, during a goto pressing any button aborts the slew.  If meridian flip paused at home, pressing any button continues.
#define ST4_HAND_CONTROL_ON
// ST4_ALTERNATE_PINS_ON moves the interface (Teensy3.x only) to pins 10, 11, 12, 13.  Pin 10 is RA- (West), Pin 11 is Dec- (South), Pin 12 is Dec+ (North), Pin 13 is RA+ (East.)  The default SPI interface is then unavailable.
#define ST4_ALTERNATE_PINS_ON

// Separate pulse-guide rate so centering and guiding don't disturb each other, default=ON
#define SEPARATE_PULSE_GUIDE_RATE_ON

// Guide time limit (in seconds,) default=0 (no limit.)  A safety feature, some guides are started with one command and stopped with another.  
// If the stop command is never received the guide will continue forever unless this is enabled.
#define GUIDE_TIME_LIMIT 0

// RTC (Real Time Clock) support, Default=OFF. Other options: RTC_DS3234 for a DS3234 on the default SPI interface pins (and CS on pin 10, optionally wire the SQW output to the PPS pin below.)
#define RTC_OFF
// PPS use _ON or _PULLUP to enable the input and use the built-in pullup resistor.  Sense rising edge on pin 21 for optional precision clock source (GPS, for example), default=OFF (Teensy3.x Pin 28)
#define PPS_SENSE_ON

// PEC sense on pin 2 or threshold value on analog 1 (pin 23/analog 9 on Teensy3.x) use _ON or _PULLUP to enable the input and use the built-in pullup resistor, default=OFF
// Analog values range from 0 to 1023 which indicate voltages from 0-5VDC (or 0-3.3VDC) on the analog pin, for example "PEC_SENSE 600" would detect an index when the voltage exceeds 2.92V (or 1.93V)
// with either index detection method, once triggered 60s must expire before another detection can happen.  This gives time for the index magnet to pass by the detector before another cycle begins.
// Ignored on Alt/Azm mounts.
#define PEC_SENSE_OFF
// PEC sense, rising edge (default with PEC_SENSE_STATE HIGH, use LOW for falling edge, ex. PEC_SENSE_ON) ; for optional PEC index
#define PEC_SENSE_STATE HIGH

// Switch close (to ground) on pin 3 for optional limit sense (stops gotos and/or tracking), default=OFF (Teensy3.x Pin 4)
#define LIMIT_SENSE_OFF

// Light status LED by sink to ground (pin 9) and source +5V (pin 8), default=ON.  (Teensy3.x Pin 19, no V+ pin)
// _ON and OnStep keeps this illuminated to indicate that the controller is active.  When sidereal tracking this LED will rapidly flash
#define STATUS_LED_PINS_ON
// Light 2nd status LED by sink to ground (pin 7), default=OFF. (Teensy3.x Pin 22)
// _ON sets this to blink at 1 sec intervals when PPS is synced.  Turns off if tracking is stopped.  Turns on during gotos.
#define STATUS_LED2_PINS_ON
// Light reticule LED by sink to ground (pin 44), default=OFF.  (Teensy3.x Pin 22, don't use with STATUS_LED2_PINS_ON)
// RETICULE_LED_PINS n, where n=0 to 255 activates this feature and sets default brightness
#define RETICULE_LED_PINS 64

// Sound/buzzer on pin 42, default=OFF.  (Teensy3.x Pin 29)
// Specify frequency for a piezo speaker (for example "BUZZER 2000") or use BUZZER_ON for a piezo buzzer.
#define BUZZER 443
// Sound state at startup, default=ON.
#define DEFAULT_SOUND_ON

// Optionally adjust tracking rate to compensate for atmospheric refraction, default=OFF
// can be turned on/off with the :Tr# and :Tn# commands regardless of this setting
#define TRACK_REFRACTION_RATE_DEFAULT_OFF

// Set to ON and OnStep will remember the last auto meridian flip setting (on/off), default=OFF
#define REMEMBER_AUTO_MERIDIAN_FLIP_OFF

// Set to ON and OnStep will remember the last meridian flip pause at home setting (on/off), default=OFF
#define REMEMBER_PAUSE_HOME_OFF

// ADJUST THE FOLLOWING TO MATCH YOUR MOUNT --------------------------------------------------------------------------------
#define REMEMBER_MAX_RATE_OFF        // set to ON and OnStep will remember rates set in the ASCOM driver or Android App, default=OFF 
#define MaxRate                   32 // this is the minimum number of micro-seconds between micro-steps
                                     // minimum* (fastest goto) is around 32 (Mega2560,) 16 (Teensy3.2,) 12 (Teensy3.5,) 8 (Teensy3.6,) default=96 higher is ok
                                     // too low and OnStep communicates slowly and/or freezes as the motor timers use up all the MCU time
                                     // * = minimum can be lower, when both AXIS1/AXIS2_MODE_GOTO are used by AXIS1/AXIS2_STEP_GOTO times
                                     
#define DegreesForAcceleration   5.0 // approximate number of degrees for full acceleration or deceleration: higher values=longer acceleration/deceleration
                                     // Default=5.0, too low (about <1) can cause gotos to never end if micro-step mode switching is enabled.
#define DegreesForRapidStop      1.0 // approximate number of degrees required to stop when requested or if limit is exceeded during a slew: higher values=longer deceleration
                                     // Default=1.0, too low (about <1) can cause gotos to never end if micro-step mode switching is enabled.

#define BacklashTakeupRate        25 // backlash takeup rate (in multipules of the sidereal rate): too fast and your motors will stall,
                                     // too slow and the mount will be sluggish while it moves through the backlash
                                     // for the most part this doesn't need to be changed, but adjust when needed.  Default=25


                                     // Axis1 is for RA/Az
#define StepsPerDegreeAxis1  12288.0  // calculated as    :  stepper_steps * micro_steps * gear_reduction1 * (gear_reduction2/360)
                                     // NEMA17 + PLANET   :  200           * 16          * 27/20          *  1024/360       = 12288.0

                                     // Axis2 is for Dec/Alt
#define StepsPerDegreeAxis2   12288.0   // calculated as    :  stepper_steps * micro_steps * gear_reduction1 * (gear_reduction2/360)
                                     // NEMA17 + PLANET  :   200           * 16         * 27/20            * 1024/360       = 12288.0
                                     
                                     // PEC, number of steps for a complete worm rotation (in RA), (StepsPerDegreeAxis1*360)/gear_reduction2.  Ignored on Alt/Azm mounts.
#define StepsPerWormRotationAxis1 3200L
                                     //  NEMA17 + PLANET         : (12288*360)/1382.4 = 3200



                                     //  NEMA17 + PLANET         : (15359*360)/138 = 40068L
#define PECBufferSize           824  // PEC, buffer size, max should be no more than 3384, your required buffer size >= StepsPerAxis1WormRotation/(StepsPerDegeeAxis1/240)
                                     // for the most part this doesn't need to be changed, but adjust when needed.  824 seconds is the default.  Ignored on Alt/Azm mounts.

#define REVERSE_AXIS1_OFF            // reverse the direction of movement for the HA/RA axis, adjust as needed or reverse your wiring so things move in the right direction
#define REVERSE_AXIS2_OFF            // reverse the direction of movement for the Dec axis (both reversed for my EM10b, both normal for G11)

#define MinutesPastMeridianE      60 // for goto's, how far past the meridian to allow before we do a flip (if on the East side of the pier) - one hour of RA is the default = 60.  Sometimes used for Fork mounts in Align mode.  Ignored on Alt/Azm mounts.
#define MinutesPastMeridianW      60 // as above, if on the West side of the pier.  If left alone, the mount will stop tracking when it hits the this limit.  Sometimes used for Fork mounts in Align mode.  Ignored on Alt/Azm mounts.
                                     // The above two lines can be removed and settings in EEPROM will be used instead, be sure to set the Meridian limits in control software if you do this!  
                                     // If you don't remove these lines Meridian limits will return to these defaults on power up.
#define UnderPoleLimit            12 // maximum allowed hour angle (+/-) under the celestial pole.  Default=12.  Ignored on Alt/Azm mounts.
                                     // If left alone, the mount will stop tracking when it hits this limit.  Valid range is 10 to 12 hours.
#define MinDec                   -91 // minimum allowed declination, default = -91 (off)  Ignored on Alt/Azm mounts.
#define MaxDec                   +91 // maximum allowed declination, default =  91 (off)  Ignored on Alt/Azm mounts.
                                     // For example, a value of +80 would stop gotos/tracking near the north celestial pole.
                                     // For a Northern Hemisphere user, this would stop tracking when the mount is in the polar home position but
                                     // that can be easily worked around by doing an alignment once and saving a park position (assuming a 
                                     // fork/yolk mount with meridian flips turned off by setting the minutesPastMeridian values to cover the whole sky)
#define MaxAzm                   180 // Alt/Az mounts only. +/- maximum allowed Azimuth, default =  180.  Allowed range is 180 to 360

// AXIS1/2 STEPPER DRIVER CONTROL ------------------------------------------------------------------------------------------

// Stepper driver Enable support, just wire Enable to Pins 23 (Axis1) and 36 (Axis2) and OnStep will pull these HIGH (Teensy3.x Pins 14,9)
// to disable stepper drivers on startup and when Parked or Homed.  An Align, Sync, or Un-Park will enable the drivers.  Adjust below if you need these pulled LOW to disable the drivers.
#define AXIS1_DISABLED_HIGH
#define AXIS2_DISABLED_HIGH
// For equatorial mounts, _ON powers down the Declination axis when it's not being used to help lower power use.  During low rate guiding (<=1x) the axis stays enabled
// for 10 minutes after any guide on either axis.  Otherwise, the Dec axis is disabled (powered off) 10 seconds after movement stops.
#define AUTO_POWER_DOWN_AXIS2_ON

// Stepper driver Mode control
// M0, M1, and M2 are on Pins 25,27, and 29 for RA (Teensy3.x Pins 15,16,17.)  M0, M1, M2 are on Pins 34,32,30 for Dec (Teensy3.x Pins 8,7,6.)
// values 0 to 7 (0b000 to 111): for example "#define AXIS1_MODE 4" is the same as "#define AXIS1_MODE 0b100" which sets M2 to HIGH, M1 to LOW, and M0 to LOW
//                                                                                                      / | \                  (1)         (0)            (0)
//                                                                                                    M2  M1 M0
// DRV8825 or A4988 or RAPS128:
// use MODE_SWITCH_BEFORE_SLEW_OFF
// micro-stepping modes: 5=32x, 4=16x, 3=8x, 2=4x, 1=2x, 0=1x (RAPS128 also supports 6=64x, 7=128x)
//
// SilentStepStick TMC2100/2130 configurations (M0 is CFG1, M1 is CFG2, M2 is CFG3):
// use MODE_SWITCH_BEFORE_SLEW_OFF.  CFG3 should always be OPEN*.  AXISn_MODE_GOTO_OFF is recommended so AXISn_STEP_GOTO would then be 1.
// Some useful modes (all with 256x interpolation):
// 16x stealthChop: CFG1 and CFG2 are both OPEN*.
// 16x spreadCycle: CFG1 can be wired to GND (LOW) or M0 (with AXISn_MODE 0).  CFG2 should be OPEN*.  
// 4x  spreadCycle: CFG2 should be OPEN*.  CFG2 can be wired to Vcc (HIGH) or M1 (with AXISn_MODE 2).
// * = For a pin to be considered OPEN it must be electrically disconnected (not wired in.)
//
// SilentStepStick TMC2130 SPI configurations:
// use MODE_SWITCH_BEFORE_SLEW_SPI.  Default operation in spreadCycle and with 256x interpolation on:
// AXISn_MODE and AXISn_MODE_GOTO can be set to 0-8 where 0=256x, 1=128x, 2=64x, 3=32x, 4=16x, 5=8x, 6=4x, 7=2x, 8=1x
// You can also turn stealthChop on (TMC_STEALTHCHOP) and/or disable 256x interpolation (TMC_NINTPOL.) For example 32x mode with stealthChop:
// AXIS1_MODE (3|TMC_STEALTHCHOP)
// Another option allows setting 50% power while tracking (TMC_LOWPWR.)  As above, with this option on too:
// AXIS1_MODE (3|TMC_STEALTHCHOP|TMC_LOWPWR)
//
#define AXIS1_MODE_OFF               // programs the RA/Az uStep mode M0/M1/M2, optional and default _OFF.
#define AXIS1_MODE_GOTO_OFF          // programs the RA/Az uStep mode M0/M1/M2, used during gotos, optional and default _OFF.
#define AXIS1_STEP_GOTO 1            // 1=goto mode is same as normal mode: for example if normal tracking mode is 32x and goto is 8x this would be 4
#define AXIS2_MODE_OFF               // programs the Dec/Alt uStep mode M0/M1/M2, optional and default _OFF.
#define AXIS2_MODE_GOTO_OFF          // programs the Dec/Alt uStep mode M0/M1/M2, used during gotos, optional and default _OFF.
#define AXIS2_STEP_GOTO 1            // 1=goto mode is same as normal mode: for example if normal tracking mode is 32x and goto is 8x this would be 4
#define MODE_SWITCH_BEFORE_SLEW_OFF  // _ON (or _SPI) for _MODE and _MODE_GOTO settings to start/stop just before/after the slew, otherwise they are active during the slew at <128uS/step speeds
                                     // _SPI as above but uses SPI (on M0/M1/M2/Aux) to do the switching (TMC2130.)  Uses Teensy3.x Pins 18 (Aux1) and 5 (Aux2,) choose only one feature on Aux1/2.

// Secondary stepper driver decay control (for both Axis, the _DECAY_MODE and _DECAY_MODE_GOTO settings always start/stop just before/after the slew)
// typically used for the DRV8825 or A9488 where decay control is separate from the micro-step mode control.  The driver modules usually need to be modified to accomplish this.
// Axis1 decay mode is on Pin 41 and Axis2 decay mode is on Pin 40.  Options are _HIGH, _LOW, _OPEN, default is _OFF (not supported on Teensy3.x)
// MODE_SWITCH_BEFORE_SLEW must be _OFF if using this.
#define DECAY_MODE_OFF
#define DECAY_MODE_GOTO_OFF

// if the decay/micro-step mode switch happens before/after a slew, inserts a 3ms delay before the motors take a step
#define MODE_SWITCH_SLEEP_OFF

// Stepper driver Fault detection, just wire the driver Fault signal to Pins 39 (Axis1) and 38 (Axis2), default=OFF.  Teensy3.x Pins 18 (Aux1) and 5 (Aux2,) choose only one feature to use on Aux1/2.
// other settings are LOW, HIGH, SPI (Teensy3.x applies internal pullup if _LOW and pulldown if _HIGH.)  The SPI interface (on M0/M1/M2/Aux) can be used to detect errors on the TMC2130.
#define AXIS1_FAULT_OFF
#define AXIS2_FAULT_OFF

// ------------------------------------------------------------------------------------------------------------------------
// FOCUSER ROTATOR OR ALT/AZ DE-ROTATION ----------------------------------------------------------------------------------
// A9,A8 = Step,Dir (Teensy3.x 30,33 choose either this option or the second focuser, not both)
#define ROTATOR_OFF                  // enable or disable rotator feature (for any mount type,) default=OFF (de-rotator is available only for MOUNT_TYPE_ALTAZM.)
#define MaxRateAxis3               8 // this is the minimum number of milli-seconds between micro-steps, default=8
#define StepsPerDegreeAxis3     64.0 // calculated as    :  stepper_steps * micro_steps * gear_reduction1 * (gear_reduction2/360)
                                     // Rotator          :  24            * 8           * 20              *  6/360                = 64
                                     // For de-rotation of Alt/Az mounts a quick estimate of the required resolution (in StepsPerDegree)
                                     // would be an estimate of the circumference of the useful imaging circle in (pixels * 2)/360
#define REVERSE_AXIS3_OFF            // reverse the direction of Axis3 rotator movement
#define MinAxis3                -180 // minimum allowed Axis3 rotator, default = -180
#define MaxAxis3                 180 // maximum allowed Axis3 rotator, default =  180

// FOCUSER1 ---------------------------------------------------------------------------------------------------------------
// A11,A10 = Step,Dir (Teensy3.2 pins 31,32) (Teensy3.5/3.6 pins 34,35)
#define FOCUSER1_OFF                 // enable or disable focuser feature, default=OFF
#define MaxRateAxis4               8 // this is the minimum number of milli-seconds between micro-steps, default=8
#define StepsPerMicrometerAxis4  0.5 // figure this out by testing or other means
#define REVERSE_AXIS4_OFF            // reverse the direction of Axis4 focuser movement
#define MinAxis4               -25.0 // minimum allowed Axis4 position in millimeters, default = -25.0
#define MaxAxis4                25.0 // maximum allowed Axis4 position in millimeters, default =  25.0

// FOCUSER2 ---------------------------------------------------------------------------------------------------------------
// A13,A12 = Step,Dir (Teensy3.x pins 30,33 choose either this option or the rotator, not both) 
#define FOCUSER2_OFF                 // enable or disable focuser feature, default=OFF
#define MaxRateAxis5               8 // this is the minimum number of milli-seconds between micro-steps, default=8
#define StepsPerMicrometerAxis5  0.5 // figure this out by testing or other means
#define REVERSE_AXIS5_OFF            // reverse the direction of Axis4 focuser movement
#define MinAxis5               -25.0 // minimum allowed Axis5 position in millimeters, default = -25.0
#define MaxAxis5                25.0 // maximum allowed Axis5 position in millimeters, default =  25.0

// THAT'S IT FOR USER CONFIGURATION!

// -------------------------------------------------------------------------------------------------------------------------
