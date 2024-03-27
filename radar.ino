#include <Servo.h>
int trigger = 8;
int echo = 7;
unsigned long previous = 0;
unsigned long current;
long durationx, distance;
int led = 3;
unsigned long previousvoforward = 0; 
unsigned long ledprev = 0;
int servopos;
int servoincrement = 1;
int ledstate = LOW;
int pwm = 10;
Servo s;

void setup() {
  s.attach(pwm);
  pinMode(led,OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void readUltrasonicSensor() {
  if (current - previous >= 500) { 
  previous = current;
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  durationx = pulseIn(echo, HIGH);
  distance = (durationx * 0.0343) / 2;
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 30){
    ledc();
  }
  else{
    ledstate = LOW;
    digitalWrite(led,ledstate);
  }
  }
}
void ledc(){
  if (current - ledprev >= 100){
    ledprev = current;
  if (ledstate == LOW){
    ledstate = HIGH;
  }
  else{
    ledstate = LOW;
  }
 digitalWrite(led,ledstate);

  }
}
void servof(){
  if(current - previousvoforward >= 10){
    previousvoforward = current;
    servopos += servoincrement;

    if ((servopos > 180)||(servopos < 0)){
    servoincrement = -servoincrement;
    }
    s.write(servopos);
  }
}

void loop() {
  current = millis();
  servof();
  readUltrasonicSensor();
}
