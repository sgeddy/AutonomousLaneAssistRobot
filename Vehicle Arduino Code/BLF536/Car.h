/**************************************************************
 * 
 * Class: Car
 * Author: Alper Ender, Ben Wagner, and Eli Buckner
 * Description: Holds the class variables and functions for the overall car
 * 
 **************************************************************/
class Car
{
  public:

    // Variables
    volatile unsigned long timer             = 0;            // Timer to ensure that the each loop runs T second intervals 
    volatile double        setPoint          = 0;            // Set point for system identification: 1 for system identification, 0 for regular control
    volatile double        pwmSetSpeed       = SETSPEED;     // Setting the PWM speed   
    volatile double        pos               = 0;            // The position of the vehicle in reference to the set point
    volatile double        posHold           = 0;           
    volatile double        totalError;                       // The total error of the vehicle from its set point
    volatile double        totalErrorHold[HOLD_AMOUNT];      // Holding the total error amounts
    volatile double        motorDiffPWM;                     // The motor differential PWM
    volatile double        motorDiffPWMHold[HOLD_AMOUNT];    // Holding the motor differential ammounts
    AF_DCMotor             *MotorRightPtr;
    AF_DCMotor             *MotorLeftPtr;

    // Functions
    void MotorDiff(void);
    void sysId(void);
    void Total_Error_Calc(void);
    void Sample_Time(void);
    void Obtain_Errors(void);
    void Controller(void);
    void Filter(void);

    // Constructor
    Car();
};
