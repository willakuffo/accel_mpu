# accel_mpu
Contains c++ source code (ARDUINO/ATMEGA) for interfacing with HC-SRO4 ultrasonic sensor and MPU6050 accel/gyro sensor. Sensor data is collected and used as features to to train a DNN for smart IMU positioning prediction.

`NB` This is a testing repo

## How to use
Settings for the project can be found in 'config.h' header [file](https://github.com/willakuffo/accel_mpu/blob/main/accelmpu/config.h)

`config.h`
Use this to configure the project. What features to compute for and print to serial by commenting or uncommenting out certain macros definitions

  `PRINT_TIME` print sample time ->sec and time past since run->millis 
  `DEPENDENCY`:None

                                                 
`ACCEL_AS_RAW ` uncomment to read accelerometer (x,y,z) as raw, with sensitivity -> 2g
`DEPENDENCY`: None
` PRINT_ACCEL_AS_RAW` print output of ACCEL_AS_RAW

 `ACCEL_AS_MS` uncomment to read accelerometer (x,y,z) as m/s with sensitivity -> 2g 
`DEPENDENCY`: None                                                         
`PRINT_ACCEL_AS_MS` print output of ACCEL_AS_MS

                                                        
`ACCEL_ANGLE` uncomment to read angle in deg -> This angle is in degrees and is dependent on ACCEL_AS_MS, therefore uncomment ACCEL_AS_MS before 
this angle can be read. This angle is calculated from the accelerometer only using euler's formula
`DEPENDENCY`: `ACCEL_AS_MS`
`PRINT_ACCEL_ANGLE`print output of ACCEL_ANGLE

 `ULTRASONIC` uncomment to read ultrasonic sensor 3d positions (x,y,z). True position of UAV at pitch,roll or yaw will be un-angled
i.e position*cos(angle) -> horizontal un-angled
`DEPENDENCY`: None                                                        
`PRINT_ULTRASONIC` print output of ULTRASONIC


`GYRO_AS_RAW` uncomment to read gyroscope (roll,pitch,yaw) as raw, with sensitivity -> 250deg/s 
`DEPENDENCY`: None                                                        
`PRINT_GYRO_AS_RAW`print output of GYRO_AS_RAW

`GYRO_AS_DEG`uncomment to read gyro angle rates (roll,pitch,yaw) in deg/s.
`DEPENDENCY`: None 
`PRINT_GYRO_AS_DEG` print output of GYRO_AS_DEG 

 `GYRO_ANGLE` read gyro angles in degrees dependent on GYRO_AS_DEG. Uncomment to read gyro angles in degrees. These angles are integrated from GYRO_AS_DEG angle rate values, 
therefore dependent on `GYRO_AS_DEG`. Use with `GYRO_AS_DEG`, therefore uncomment `GYRO_AS_DEG`
`DEPENDENCY`: `GYRO_AS_DEG`                                                       
 `PRINT_GYRO_ANGLE` print output of GYRO_ANGLE 

`COMPLIMETARY_FILTER`This is a complimentary filter using 96% of GYRO angles and 4% of ACCEL angles. GYRO is not reliable in long term but in short term.
ACCEL is reliable in long term but not in short term. Removes noise and smoothens out the angle signal. Best of both worlds :)
DEPENDENCY:`ACCEL_ANGLE`->[`ACCEL_AS_MS`], `GYRO_ANGLE`->[`GYRO_AS_DEG`]    
`PRINT_COMP` //print output of COMPLIMETARY_FILTER  

 `TEMP` uncomment to read temperature in celcius
`DEPENDENCY`: None
`PRINT_TEMP` print output of temp

`NB:Last feature should have println`
