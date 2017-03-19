/**************************************************************
 * 
 * Function: FSM
 * Author: Ben Wagner and Alper Ender
 * Description: The finite state machine to determine the state of the vehicle
 * 
 *************************************************************/
void FSM(void) {
  Determine_State();
  
  switch (state) {
    
    case INIT: break;
      
    case FOLLOW_LEFT_LINE:  {
        Follow_Left();
        break;
      }
      
    case FOLLOW_RIGHT_LINE: {
        Follow_Right();
        break;
      }
      
    case INTERSECTION:    {
        Intersection();
        break;
      }
      
    default: state = INIT;
    
  }
}


/**************************************************************
 * 
 * Function: Determine_State
 * Author: Alper Ender and Ben Wagner
 * Description: The function that determines the next state based on what the sensors are seeing.
 *
 **************************************************************/
void Determine_State(void) {
  boolean lostLeft, lostRight;

  // Checking lost left or right lines
  lostLeft  = Check_Lost_Left_Line();
  lostRight = Check_Lost_Right_Line();

  // Lost Both Lines
  if(lostLeft && lostRight) {
    if(state == FOLLOW_LEFT_LINE)   state = FOLLOW_LEFT_LINE;
    else                            state = FOLLOW_RIGHT_LINE;
  }

  // Lost Left Line
  if(lostLeft && !lostRight) {
    state = FOLLOW_RIGHT_LINE;
  }

  // Lost Right Line
  if(!lostLeft && lostRight) {
    state = FOLLOW_LEFT_LINE;
  }

  // Lost No Lines
  if(!lostLeft && !lostRight) {
    if(state == FOLLOW_LEFT_LINE)   state = FOLLOW_LEFT_LINE;
    else                            state = FOLLOW_RIGHT_LINE;
  }

  #ifdef INTERSECTION_TRACK
  // Intersection state only available during the intersection track
  if(Check_Intersection() > 7000) {
    state = INTERSECTION;
  }
  #endif

}


/**************************************************************
 * 
 * Function: Check_Intersection
 * Author: Alper Ender
 * Description: Checks the RIGHT sensor to see if it sees a corner. If it does, then it changes the FSM to the intersection state to handle this intersection
 * 
 **************************************************************/
double Check_Intersection(void) {
  double sum = 0;

  for(int i = 0 ; i < 7 ; i++){
    sum += rightSensor.sensorVals_T0[i];
  }
  // Serial.println(sum);

  return sum;
}


/**************************************************************
 * 
 * Function: Check_Lost_Right_Line
 * Author: Alper Ender
 * Description: Checks to see if the right sensor lost the line. Returns 1 if it did, else it returns 0
 * 
 **************************************************************/
boolean Check_Lost_Right_Line(void) {
  if (       rightSensor.sensorVals_T0[0] < OFF_LINE_THRESHOLD && rightSensor.sensorVals_T0[1] < OFF_LINE_THRESHOLD
         &&  rightSensor.sensorVals_T0[2] < OFF_LINE_THRESHOLD && rightSensor.sensorVals_T0[3] < OFF_LINE_THRESHOLD
         &&  rightSensor.sensorVals_T0[4] < OFF_LINE_THRESHOLD && rightSensor.sensorVals_T0[5] < OFF_LINE_THRESHOLD
         &&  rightSensor.sensorVals_T0[6] < OFF_LINE_THRESHOLD && rightSensor.sensorVals_T0[7] < OFF_LINE_THRESHOLD) {
    return true;
  }

  return false;
}


/**************************************************************
 * 
 * Function: Check_Lost_Right_Line
 * Author: Alper Ender
 * Description: Checks to see if the left sensor lost the line. Returns 1 if it did, else it returns 0
 * 
 **************************************************************/
boolean Check_Lost_Left_Line(void) {
  if (       leftSensor.sensorVals_T0[0] < OFF_LINE_THRESHOLD && leftSensor.sensorVals_T0[1] < OFF_LINE_THRESHOLD
         &&  leftSensor.sensorVals_T0[2] < OFF_LINE_THRESHOLD && leftSensor.sensorVals_T0[3] < OFF_LINE_THRESHOLD
         &&  leftSensor.sensorVals_T0[4] < OFF_LINE_THRESHOLD && leftSensor.sensorVals_T0[5] < OFF_LINE_THRESHOLD
         &&  leftSensor.sensorVals_T0[6] < OFF_LINE_THRESHOLD && leftSensor.sensorVals_T0[7] < OFF_LINE_THRESHOLD) {
    return true;
  }

  return false;
}


int intersection_choice = 0;
  
/**************************************************************
 * 
 * Function: Intersection
 * Author: Ben Wagner, Eli Buckner, and Alper Ender
 * Description: What to do when the vehicle reaches an intersection
 * 
 **************************************************************/
void Intersection(void) {
  // Serial.println("INTERSECTION STATE");
  
  Stop_Vehicle();
  
  switch (intersection_choice) {
    case 0:   Go_Straight_OL(); break;
    case 1:   Right_Turn_OL();  break;
    case 2:   Left_Turn_OL();   break;
    default:  Go_Straight_OL(); break;
  }

  if(++intersection_choice > 2) intersection_choice = 0;

}


/**************************************************************
 * 
 * Function: Go_Straight_OL
 * Author: Ben Wagner, Eli Buckner, and Alper Ender
 * Description: OPEN LOOP - Going Straight through the intersection
 * 
 **************************************************************/
void Go_Straight_OL(void) {
  unsigned long timer = millis();
  BLF536.MotorRightPtr->setSpeed(115);
  BLF536.MotorLeftPtr->setSpeed(100);
  delay(300);
  
  while (millis() - timer < STRAIGHTTIME) {
    if(!Check_Lost_Right_Line()) break;
  }
}


/**************************************************************
 * 
 * Function: Right_Turn_OL
 * Author: Ben Wagner, Eli Buckner, and Alper Ender
 * Description: OPEN LOOP - Turning right at the intersection
 * 
 **************************************************************/
void Right_Turn_OL(void) {
  unsigned long timer = millis();
  BLF536.MotorRightPtr->setSpeed(0);
  BLF536.MotorLeftPtr->setSpeed(100);
  delay(500);
  
  while (millis() - timer < RIGHTTURNTIME) {
    if(!Check_Lost_Left_Line()) break;
  }
}


/**************************************************************
 * 
 * Function: Left_Turn_OL
 * Author: Ben Wagner, Eli Buckner, and Alper Ender
 * Description: OPEN LOOP - Turning left at the intersection
 * 
 **************************************************************/
void Left_Turn_OL() {
  unsigned long timer = millis();

  // Go Straight
  BLF536.MotorRightPtr->setSpeed(115);
  BLF536.MotorLeftPtr->setSpeed(100);
  delay(300);
  while (millis() - timer < LEFTTURNTIME) {
    if(!Check_Lost_Right_Line()) break;
  }

  // Go Left
  BLF536.MotorRightPtr->setSpeed(140);
  BLF536.MotorLeftPtr->setSpeed(0);

  timer = millis();
  while (millis() - timer < LEFTTURNTIME) {
    if(Check_Lost_Right_Line()) break;
  }

  delay(100);
  timer = millis();
  while (millis() - timer < LEFTTURNTIME) {
    if(!Check_Lost_Right_Line()) break;
  }

  delay(200);
}


/**************************************************************
 * 
 * Function: Follow_2_Line
 * Author: Alper Ender
 * Description: Follows both lines by averaging the error between them
 * 
 **************************************************************/
void Follow_2_Line(void) {
  // Serial.println("BOTH");
  
  BLF536.pos = (leftSensor.sensedVal + rightSensor.sensedVal) / 2L;
}


/**************************************************************
 * 
 * Function: Follow_Right
 * Author: Alper Ender
 * Description: Follows the right line
 * 
 **************************************************************/
void Follow_Right(void) {
  // Serial.println("RIGHT");
  
  BLF536.pos = rightSensor.sensedVal;
}


/**************************************************************
 * 
 * Function: Follow_Right
 * Author: Alper Ender
 * Description: Follows the left line
 * 
 **************************************************************/
void Follow_Left(void) {
  // Serial.println("LEFT");
  
  BLF536.pos = leftSensor.sensedVal;
}


/**************************************************************
 * 
 * Function: Stop_Vehicle
 * Author: Alper Ender
 * Description: Stops the vehicle at an intersection
 * 
 **************************************************************/
void Stop_Vehicle(void){
  BLF536.MotorRightPtr->setSpeed(0);
  BLF536.MotorLeftPtr->setSpeed(0);
  delay(1);
  BLF536.MotorRightPtr->setSpeed(100);
  BLF536.MotorLeftPtr->setSpeed(100);
  BLF536.MotorRightPtr->run(BACKWARD);
  BLF536.MotorLeftPtr->run(BACKWARD);
  delay(100);
  BLF536.MotorRightPtr->setSpeed(0);
  BLF536.MotorLeftPtr->setSpeed(0);
  BLF536.MotorRightPtr->run(FORWARD);
  BLF536.MotorLeftPtr->run(FORWARD);
}

