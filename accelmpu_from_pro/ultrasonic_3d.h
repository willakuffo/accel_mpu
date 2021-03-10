#ifndef ULTRA_ADDED
#define ULTRA_ADDED

//ultrasonic sensor pins
#define XTRIG 8
#define XECHO 9 
#define YTRIG 5
#define YECHO 6
#define ZTRIG 2
#define ZECHO 3

float tf = 0.2;
int distance,duration;
void SonarSensor(int trigPin,int echoPin);
void ultrasonic_3d_setup();
#endif
