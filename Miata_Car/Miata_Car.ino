//  Created by Matthew Chamot
//  For a Teensy LC
//  December 2017


#include <SparkFun_TB6612.h>
#include <Servo.h>

// Define pins for motor driver
#define AIN1 19
#define AIN2 20
#define PWMA 22
#define STBY 17

#define HLT 12  // Headlight
#define TLT 14  // Taillight


const int offsetA = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

// Define servo for steering
Servo myservo;

char data = 0;

void setup() {
  Serial1.begin(115200);
  pinMode(HLT,OUTPUT);
  pinMode(TLT,OUTPUT);
  myservo.attach(6); 

}

void loop()
{
    // Read a character sent from the controller over bluetooth and determine what action to do.
    if (Serial1.available()) {
      data = Serial1.read();
      if(data == '1') {
        digitalWrite(13, HIGH);
        Serial1.write("LED is on\n");
      }
      else if(data == '0') {
        digitalWrite(13, LOW);
        Serial1.write("LED is off\n");
      }
      else if(data == '2') {
        Serial1.write("Motor CW\n");
        motor1.drive(255,1000);
        motor1.brake();
      }
      else if(data == '3') {
        Serial1.write("Motor CCW\n");
        motor1.drive(-255,1000);
        motor1.brake();
      }
      else if(data =='4') {
        digitalWrite(HLT,HIGH);
        Serial1.write("Headlights On\n");
      }
      else if(data =='5') {
        digitalWrite(HLT,LOW);
        Serial1.write("Headlights Off\n");
      }
      else if(data =='6') {
        digitalWrite(TLT,HIGH);
        Serial1.write("Taillights On\n");
      }
      else if(data =='7') {
        digitalWrite(TLT,LOW);
        Serial1.write("Taillights Off\n");
      }
      else if(data =='l') {
        myservo.write(78);
        Serial1.write("Servo Right\n");
      }
      else if(data =='c') {
        myservo.write(88);
        Serial1.write("Servo Straight\n");
      }
      else if(data =='d') {
        myservo.write(98);
        Serial1.write("Servo Left\n");
      }
      else if(data == 'r') {
        Serial1.write("Motor CW On\n");
        motor1.drive(255);
      }
      else if(data == 'b') {
        Serial1.write("Motor CW Off\n");
        motor1.brake();
      }
      else if(data == 'f') {
        Serial1.write("Motor CCW On\n");
        motor1.drive(-255);
      }
      
      
      
    }    
}
