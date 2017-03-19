/**************************************************************
 * 
 * Function: Tester
 * Author: Alper Ender
 * Description: Constructor of the Tester class
 * 
 **************************************************************/
Tester::Tester(){
  
}


/**************************************************************
 * 
 * Function: Print_Sensor_Values
 * Author: Alper Ender
 * Description: Prints the entire sensor array for both the left and right sensors
 * 
 **************************************************************/
void Tester::Print_Sensor_Values(void){
  int i;

  Serial.print("Pin "); Serial.print(leftSensor.pin); Serial.print(" Sensors: ");
  for (i = 0 ; i < NUM_SENSORS ; i++) {
    Serial.print(",\t"); Serial.print(i); Serial.print(":"); Serial.print(leftSensor.sensorVals_T0[i]);
  }
  
  Serial.print("\tPin "); Serial.print(rightSensor.pin); Serial.print(" Sensors: ");
  for (i = 0 ; i < NUM_SENSORS ; i++) {
    Serial.print(",\t"); Serial.print(i); Serial.print(":"); Serial.print(rightSensor.sensorVals_T0[i]);
  }
  
  Serial.println("");
}


/**************************************************************
 * 
 * Function: Print_Line_Values
 * Author: Alper Ender
 * Description: Obtains the line values for the sensors and Prints the Line Values for each sensor
 * 
 **************************************************************/
void Tester::Print_Line_Values(void){
  leftSensor.Get_Line_Value();
  Serial.print("Left:\t"); Serial.print(leftSensor.lineVal); Serial.print("\t");
  rightSensor.Get_Line_Value();
  Serial.print("Right:\t"); Serial.println(rightSensor.lineVal);
}


/**************************************************************
 * 
 * Function: Print_Total_Error
 * Author: Alper Ender
 * Description: Obtains the error valeus and prints the total error values for the car
 * 
 **************************************************************/
void Tester::Print_Total_Error(void){
  Serial.print("LeftSV:\t"); Serial.print(leftSensor.sensedVal); Serial.print("\t");
  Serial.print("LeftLV:\t"); Serial.print(leftSensor.lineVal); Serial.print("\t");

  Serial.print("RightSV:\t"); Serial.print(rightSensor.sensedVal); Serial.print("\t");
  Serial.print("RightLV:\t"); Serial.print(rightSensor.lineVal); Serial.print("\t");

  /*leftSensor.Sensor_Calc();
  Serial.print("Left:\t"); Serial.print(leftSensor.error); Serial.print("\t");
  rightSensor.Sensor_Calc();
  Serial.print("Right:\t"); Serial.println(rightSensor.error); Serial.print("\t");
  */
}


/**************************************************************
 * 
 * Function: Start_Timer
 * Author: Alper Ender
 * Description: Starts a local timer
 * 
 **************************************************************/
void Tester::Start_Timer(void){
  this->timerVal = micros();
}


/**************************************************************
 * 
 * Function: Display Timer
 * Author: Alper Ender
 * Description: Displays the amount of time in MICROSECONDS that has gone by since the timer was started
 * 
 **************************************************************/
void Tester::Display_Timer(void){
  Serial.println(micros() - this->timerVal);
}


