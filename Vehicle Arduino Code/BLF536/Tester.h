/**************************************************************
 * 
 * Class: Tester
 * Author: Alper Ender
 * Description: Holds the class variables and functions for printing and displaying values onto the serial
 * 
 **************************************************************/
class Tester{
  public:
  
    // Variables
    unsigned long timerVal;     // Timer value for testing the time it takes to complete a specific task
    
    // Functions
    void Print_Sensor_Values(void);
    void Print_Line_Values(void);
    void Print_Total_Error(void);
    void Start_Timer(void);
    void Display_Timer(void);
    
    // Constructor
    Tester();
};
