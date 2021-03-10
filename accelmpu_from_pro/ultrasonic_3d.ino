#include "ultrasonic_3d.h"

void ultrasonic_3d_setup() {
  pinMode(XTRIG, OUTPUT);
  pinMode(XECHO, INPUT);
  pinMode(YTRIG, OUTPUT);
  pinMode(YECHO, INPUT);
  pinMode(ZTRIG, OUTPUT);
  pinMode(ZECHO, INPUT);

}


void SonarSensor(int trigPin, int echoPin)
{
  static int previous_distanceX = 0;
  static int previous_distanceY = 0;
  static int previous_distanceZ = 0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;


  //apply complimetary time filter
  switch (echoPin) {
    case XECHO:
      distance = (tf) * distance + (1 - tf) * previous_distanceX;
      previous_distanceX = distance;
      break;
    case YECHO:
      distance = (tf) * distance + (1 - tf) * previous_distanceY;
      previous_distanceY = distance;
      break;
    case ZECHO:
      distance = (tf) * distance + (1 - tf) * previous_distanceZ;
      previous_distanceZ = distance;
      break;

  }
}
