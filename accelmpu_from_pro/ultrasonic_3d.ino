#include "ultrasonic_3d.h"

void ultrasonic_3d_setup(){
pinMode(XTRIG, OUTPUT);
pinMode(XECHO, INPUT);
pinMode(YTRIG, OUTPUT);
pinMode(YECHO, INPUT);
pinMode(ZTRIG, OUTPUT);
pinMode(ZECHO, INPUT);
    
}


void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

}
