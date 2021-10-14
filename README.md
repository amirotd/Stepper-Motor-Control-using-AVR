# Stepper-Motor-Control-using-AVR
This is an *AVR* based project that is written in **codevisionAVR** environment and simulated in **proteus**.<br>
perpose of this project is to control Speed, Direction of Rotation and Selecting a specific Mode for Stepper Motors.<br>

## Hardware-and-tools:
In this project i used *ATMEGA8* as a Microcontroller and *L293D driver* for a *Bipolar(4-Wire) Stepper Motor*.<br>

## three supported Modes of operation for stepper motors in this project:
- Full-step 
- Half-step
- Microstep

## Micro-step-calculation:
Microstep functions declared in this project are: 
'''
void u16Step(int cnt, char forwards);
void u24Step(int cnt, char forwards);
void u32Step(int cnt, char forwards);
void u48Step(int cnt, char forwards);
void u64Step(int cnt, char forwards);
void u96Step(int cnt, char forwards);
'''
:information_source: ***I assumed Step Angle of the stepper motor is 90 degree(step angle of Stepper Motor in simulation is 90 degree)***.<br>
so `u16Step` means that it takes **16 steps** for a motor with 90 degree step angle to complete **one revolution**.(obviously it takes 4 steps for 90 degrees) and similarly we can calculate steps per revolution for other functions and for other motors with different step angle.
