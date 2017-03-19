/**************************************************************
 * 
 * Function: Sensor
 * Author: Alper Ender
 * Description: Constructor for the sensor. Initializes the pin and values for a new sensor
 * 
 **************************************************************/
Sensor::Sensor(const uint8_t& pinVal, int whiteLine) {
  this->pin = pinVal;
  this->whiteLine = whiteLine;
  
  this->sensorMin = MAX_SENSOR_VAL;
  this->sensorMax = MIN_SENSOR_VAL;
}


/**************************************************************
 * 
 * Function: Mux_Select
 * Author: Alper Ender
 * Description: Selects the correct S2, S1, and S0 to obtain the correct sensor depending on the input.
 *              There is a 4 uS delay for the mux to have time to properly switch
 *              
 **************************************************************/
void Sensor::Mux_Select(int muxSelect) {

  switch (muxSelect) {
    case 0: digitalWrite(PIN_S2, LOW);  digitalWrite(PIN_S1, LOW);  digitalWrite(PIN_S0, LOW);    break;    // 000
    case 1: digitalWrite(PIN_S2, LOW);  digitalWrite(PIN_S1, LOW);  digitalWrite(PIN_S0, HIGH);   break;    // 001
    case 2: digitalWrite(PIN_S2, LOW);  digitalWrite(PIN_S1, HIGH); digitalWrite(PIN_S0, LOW);    break;    // 010
    case 3: digitalWrite(PIN_S2, LOW);  digitalWrite(PIN_S1, HIGH); digitalWrite(PIN_S0, HIGH);   break;    // 011
    case 4: digitalWrite(PIN_S2, HIGH); digitalWrite(PIN_S1, LOW);  digitalWrite(PIN_S0, LOW);    break;    // 100
    case 5: digitalWrite(PIN_S2, HIGH); digitalWrite(PIN_S1, LOW);  digitalWrite(PIN_S0, HIGH);   break;    // 101
    case 6: digitalWrite(PIN_S2, HIGH); digitalWrite(PIN_S1, HIGH); digitalWrite(PIN_S0, LOW);    break;    // 110
    case 7: digitalWrite(PIN_S2, HIGH); digitalWrite(PIN_S1, HIGH); digitalWrite(PIN_S0, HIGH);   break;    // 111
    default: return;
  }

  // The delay necessary for the mux to switch
  delayMicroseconds(4);   
}


/**************************************************************
 * 
 * Function: Init_Sensors
 * Author: Alper Ender
 * Description: Initializes the sensor select pins and calibrates the sensor
 * 
 **************************************************************/
void Sensor::Init_Sensors(void) {

  pinMode(PIN_S2, OUTPUT);            // Select S2 - PIN A5
  pinMode(PIN_S1, OUTPUT);            // Select S1 - PIN A4
  pinMode(PIN_S0, OUTPUT);            // Select S0 - PIN A3
  pinMode(PIN_LED_ARDUINO, OUTPUT);   // Arduino LED

  this->Calibrate();
}


/**************************************************************
 * 
 * Function: Calibrate
 * Author: Alper Ender
 * Description: Calibrates a sensor array by cycling through the mux and obtaining the max and min values for the array
 * 
 **************************************************************/
void Sensor::Calibrate(void) {
  int i = 0;
  double sensorVal = 0;

  // Arduino LED ON during calibration
  digitalWrite(PIN_LED_ARDUINO, HIGH);        

  // Calibrate each individual sensor on the sensor array
  while (i++ < CALIBRATION_AMOUNT) {                     

    // Cycling through the mux
    this->Mux_Select(floor(i / MULTIPLIER));   

    // Reading the sensor
    sensorVal = analogRead(this->pin);

    // record and updates the maximum and minimum sensor values
    if (sensorVal > this->sensorMax) this->sensorMax = sensorVal;   
    if (sensorVal < this->sensorMin) this->sensorMin = sensorVal;
    
  }

  // Read all the sensors and get the initialized light value for the car's location
  this->Read_All_Sensors();
  this->Get_Line_Value();
  this->initLineVal = this->lineVal;

  // Turn off the LED when the calibration is completed
  digitalWrite(PIN_LED_ARDUINO, LOW);
}


/**************************************************************
 * 
 * Function: Read_All_Sensors
 * Author: Alper Ender
 * Description: Calibrates a sensor array by cycling through the mux and obtaining the max and min values for the array
 * 
 **************************************************************/
void Sensor::Read_All_Sensors(void) {
  int i = 0;
  this->tmp = 0;

  // Copying the current values to the old values to have values to hold onto in case we lose the line
  this->Array_Copy(); 
                                    
  for (i = 0 ; i < NUM_SENSORS ; i++) {
    
    this->tmp = 0;

    // Cycling through the mux
    this->Mux_Select(i);                                            

    // Obtaining an average of the readings
    this->tmp = analogRead(this->pin);

    // Obtaining the sensor values between the calibrated min and max and mapping them between 0 - 1023
    this->tmp = map(this->tmp, this->sensorMin, this->sensorMax, MIN_SENSOR_VAL, MAX_SENSOR_VAL);   

    // Constraining the values between 0 - 1023
    this->tmp = constrain(this->tmp, MIN_SENSOR_VAL, MAX_SENSOR_VAL);   

    // If we are reading a white line, then the values will invert but all the math will stay the same
    if (this->whiteLine) {
      this->tmp = MAX_SENSOR_VAL - this->tmp;                           
    }

    // Storing the sensor readings into the current T0 sensor values to be evaluated
    this->sensorVals_T0[i] = this->tmp;

  }
}


/**************************************************************
 * 
 * Function: Read_All_Sensors
 * Author: Alper Ender
 * Description: Storing the old sensor values in case we lose the line and we need to go off of old sensor values
 * 
 **************************************************************/
void Sensor::Array_Copy(void) {
  int i;
  for (i = 0 ; i < NUM_SENSORS ; i++) {
    this->sensorVals_T2[i] = this->sensorVals_T1[i];
    this->sensorVals_T1[i] = this->sensorVals_T0[i];
  }
}


/**************************************************************
 * 
 * Function: Read_Average
 * Author: Alper Ender
 * Description: Reading a couple of samples and obtaining the average of the samples
 * 
 **************************************************************/
int Sensor::Read_Average(void) {
  int i;
  double total = 0;
  double holdVal = 0;

  for (i = 0 ; i < NUM_SAMPLES ; i++) {

    holdVal = (double)analogRead(this->pin);
    
    // Total value from all the samples
    total += holdVal;
  }

  // Returning the average value of the sensor values
  return (total / NUM_SAMPLES);               
}


/**************************************************************
 * 
 * Function: Get_Line_Value
 * Author: Alper Ender
 * Description: Obtaining the value between 0 - 7000 where the center of the line is located on the array according to the sensors
 * 
 * Equation Used:     (Sensor0 * 0) + (Sensor1 * 1) + (Sensor2 * 2) + (Sensor3 * 3) ...
 *                    ----------------------------------------------------------------------
 *                    (   Sensor0   +   Sensor1   +   Sensor2   +   Sensor3 ...
 *                    
 * The exact center value of the line is obtained through calibration
 * 
 **************************************************************/
void Sensor::Get_Line_Value(void) {
  int     i     = 0;
  double  j     = 0;
  double  total = 0;
  double  sum   = 0;
  double  out   = 0;
  double  tmp   = 0;

  for (i = 0 ; i < NUM_SENSORS ; i++) {

    tmp = this->sensorVals_T0[i];

    // Numerator of equation
    total += tmp * i;

    // Denominator of Equation
    sum += tmp;                        
  }

  if(sum == 0){
    sum = 1;
  }

  // Dividing numerator by denominator
  out = total / sum;                          
  this->lineVal = out;

}

/**************************************************************
 * 
 * Function: Sensor_Error_Calc
 * Author: Alper Ender
 * Description: Obtain the sensed value for the array on the line
 * 
 **************************************************************/
void Sensor::Sensor_Calc(void) {

  // Get the line value between 0 - 7
  Get_Line_Value();  

  // Get the sensed value from the center of the sensor in CENTIMETERS
  // Equation: Sensed Value = ( Current Line Value - Initialized Line Value )
  this->sensedVal = (this->lineVal - this->initLineVal);
   
}


/**************************************************************
 * 
 * Function: Hold_Value
 * Author: Alper Ender
 * Description: Updates the T0 sensor values with the T1 sensor values to ensure that error calculations can still run
 * 
 **************************************************************/
void Sensor::Hold_Value(void){
  for (int i = 0 ; i < NUM_SENSORS ; i++) {
    this->sensorVals_T0[i] = this->sensorVals_T1[i];
  }
}


/**************************************************************
 * 
 * Function: Check_Sensed_Val
 * Author: Alper Ender
 * Description: Checks the current sensed value from the old sensed value for large deviations
 * 
 **************************************************************/
void Sensor::Check_Sensed_Val(void){
  if(        this->sensorVals_T0[0] < OFF_LINE_THRESHOLD && this->sensorVals_T0[1] < OFF_LINE_THRESHOLD
         &&  this->sensorVals_T0[2] < OFF_LINE_THRESHOLD && this->sensorVals_T0[3] < OFF_LINE_THRESHOLD
         &&  this->sensorVals_T0[4] < OFF_LINE_THRESHOLD && this->sensorVals_T0[5] < OFF_LINE_THRESHOLD
         &&  this->sensorVals_T0[6] < OFF_LINE_THRESHOLD && this->sensorVals_T0[7] < OFF_LINE_THRESHOLD){
    this->sensedVal = this->sensedValHold;
  }
  this->sensedValHold = this->sensedVal;
}

