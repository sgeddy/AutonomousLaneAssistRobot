/**************************************************************
 * 
 * Class: Sensor
 * Author: Alper Ender
 * Description: Holds the class variables and functions for all the sensors
 * 
 **************************************************************/
class Sensor{
  public:
  
    // Variables
    int       whiteLine;                             // Whether we are reading a black or white line
    uint8_t   pin;                                   // Analog input pin select for the sensor
    volatile double    sensorVals_T0[NUM_SENSORS];   // Sensor values for T = 0
    volatile double    sensorVals_T1[NUM_SENSORS];   // Sensor valeus for T = -1 (Sensor values from one time interval before
    volatile double    sensorVals_T2[NUM_SENSORS];   // Sensor valeus for T = -2 (Sensor values from two time intervals before
    volatile double    sensorMin;                    // Minimum sensor value
    volatile double    sensorMax;                    // Maximum sensor value
    volatile double    tmp;                          // Temporary value for sensor readings
    volatile double    error;                        // Error value for the sensor - between -3.5 and 3.5 CENTIMETERS
    volatile double    lineVal;                      // The line value calculated from the current sensor values - between 0 and 7000
    volatile double    initLineVal;                  // Initialized line value based on where the car begins
    volatile double    sensedVal;                    // The sensed value of the sensors from the zero reference line
    volatile double    sensedValHold    = 0;         // The a holding variable for the sensedVal
    
    // Functions
    void Init_Sensors();
    void Read_All_Sensors(void);
    void Get_Line_Value(void);
    void Sensor_Calc(void);
    void Calibrate(void);
    void Mux_Select(int);
    void Array_Copy(void);
    void Hold_Value(void);
    void Check_Sensed_Val(void);
    int  Read_Average(void);
    
    // Constructor
    Sensor(const uint8_t&, int);

};
