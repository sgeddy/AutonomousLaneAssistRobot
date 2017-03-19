// --- HARDWARE I/O PINS --- //
#define PIN_ANALOG_0          (A0)      // Pin A0 for analog input - Left Sensor
#define PIN_ANALOG_1          (A1)      // Pin A1 for analog input - Right Sensor

#define PIN_S2                (A5)      // Pin A5 used for digital output - Mux select bit 2
#define PIN_S1                (A4)      // Pin A4 used for digital output - Mux select bit 1
#define PIN_S0                (A3)      // Pin A3 used for digital output - Mux select bit 0

#define PIN_LED_ARDUINO       (13)      // Arduino LED pin 13 for digital output


// --- READING SENSORS --- //
#define MULTIPLIER            (1000L)   // General 1000 multiplier - used for various conversions

#define MIN_SENSOR_VAL        (0L)       // Min sensor value = 0
#define MAX_SENSOR_VAL        (1023L)    // Max sensor value = 1023

#define NUM_SAMPLES           (1L)       // Number of samples to average
#define CALIBRATION_AMOUNT    (8000L)    // Calibration Sample Limit - 1000 samples per calibrated sensor

#define BLACK_LINE            (0)        // Black or white line selection
#define WHITE_LINE            (1)

#define ON_LINE_THRESHOLD     (800L)      // On the line threshold
#define OFF_LINE_THRESHOLD    (500L)      // Off the line threshold

#define NUM_SENSORS           (8)        // Number of sensors on the sensor array

#define SAMPLING_TIME         (10)       // Sampling time (T) in MILLISECONDS
#define SAMPLING_TIME_MICRO   (10000L)   // Sampling time (T) in MICROSECONDS

#define HOLD_AMOUNT           (5)        // Number of past calculations we are holding onto

#define DIFFERENCE_THRESHOLD  (4)        // The threshold between the difference of the current sensedVal and the past sensedVal.
                                         // If the difference is greater than this threshold, the old value is used.

// --- MOTOR CONTROL --- ///
#define SETSPEED              (100L)     // Arbitrary - found through experemental values
#define KPROP                 (100L)     // Proportional controller constant
#define MAX_SPEED_VAL         (255L)     // Max input into the motors

// --- TRACK TYPE --- //
#define INTERSECTION_TRACK    (1)

// --- TURNS ---//
#define STRAIGHTTIME          (2000)
#define RIGHTTURNTIME         (3000)
#define LEFTTURNTIME          (2000)
