// Libraries
#include "Macros.h"
#include "AFMotor.h"
#include "TimerOne.h"
#include "Sensor.h"
#include "Tester.h"
#include "Car.h"


// Global Variables
enum {INIT, FOLLOW_LEFT_LINE, FOLLOW_RIGHT_LINE, INTERSECTION} state = INIT;
volatile unsigned long counter = 1;
volatile unsigned long counterHold = 0;


// Initializing Classes

// Initializing the left sensor and the right sensor arrays
Sensor leftSensor(PIN_ANALOG_0, BLACK_LINE);
Sensor rightSensor(PIN_ANALOG_1, BLACK_LINE);

// Initializing the tester class
Tester tester;

// Initializing our Car and Motors
Car BLF536;
AF_DCMotor MotorLeft(4);
AF_DCMotor MotorRight(3);


/**************************************************************
 * 
 * Function: Setup
 * Author: Alper Ender
 * Description: Runs once before the main loop
 * 
 **************************************************************/
void setup(){
  Serial.begin(115200);

  // --- INIT MOTORS --- //
  BLF536.MotorRightPtr  = &MotorRight;
  BLF536.MotorLeftPtr   = &MotorLeft;

  // --- INIT SENSORS --- //
  leftSensor.Init_Sensors();
  rightSensor.Init_Sensors();

  // --- INIT INTERRUPTS --- //
  Timer1.initialize(SAMPLING_TIME_MICRO); 
  Timer1.attachInterrupt(callback, SAMPLING_TIME_MICRO);
}


/**************************************************************
 * 
 * Function: loop
 * Author: Alper Ender
 * Description: The main of the program - runs forever
 * 
 **************************************************************/
void loop(){
  
  if(counter!=counterHold){
    
    // --- FINITE STATE MACHINE --- //
    FSM();

    if(state != INTERSECTION){
      // --- SENSOR --- //
      BLF536.Obtain_Errors();
  
      
      // --- CONTROLLER --- //
      BLF536.Controller();
  
  
      // --- MOTOR CONTROL --- //
      BLF536.MotorDiff();
  
  
      // --- TESTING: Uncomment any of these below if you want to see specific outputs to the serial port --- //

      // noInterrupts();
      // Serial.println(BLF536.pos);
      // Serial.println(BLF536.totalError);
      // Serial.println(BLF536.motorDiffPWM);
  
      // tester.Print_Total_Error();
      // tester.Print_Line_Values();
      // tester.Print_Sensor_Values();
      // interrupts();
  
      // --- DISPLAYING TIMERS --- //
      // tester.Display_Timer();  // Displays Timer
      // tester.Start_Timer();    // Begins Timer
    }
    
    // Updating counter to look for next interrupt
    counterHold = counter;
  }
}
