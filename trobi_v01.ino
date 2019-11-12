// Schrittmotor -------------------------------- 
#include <AccelStepper.h>
#define dirPin 8
#define stepPin 9
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

// Gleichstrommotor 1 - Ballmixer 1
int GSM1 = 7; // PWM Pin
int in1 = 20;
int in2 = 21;

// Gleichstrommotor 2 - Ballmixer 2
int GSM2 = 6; //PWM Pin
int in3 = 22;
int in4 = 23;

// Bluetooth -------------------------------- 
//#include <SoftwareSerial.h>
//Serial BT(5, 6);
String a;
String b;
String c;
int d;

// Servo -------------------------------- 
#include <Servo.h>
Servo myservoA;
Servo myservoB;
Servo myservoC;
const int myservoA_Center = 1450; // Mittelposition Servo A
const int myservoB_Center = 1400; // Mittelposition Servo B
const int myservoC_Center = 1500; // Mittelposition Servo C
int pos = 0;

// Servo ESC Brushless ------------------

Servo myservo_ESC_A;
Servo myservo_ESC_B;

// ------------------------------------------ 

void setup() {
Serial.begin(9600);
Serial1.begin(9600);   // serial port 1

// Motoren für Ballmixer - Drehzahl 0
analogWrite(GSM1, 0);
analogWrite(GSM2, 0);

pinMode(GSM1, OUTPUT);    
pinMode(GSM2, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);

// Servo Rotation Kopf Drehung----------------------
myservoA.attach(2); 
myservoA.writeMicroseconds(myservoA_Center);
delay(1000);

// Servo Rotation Kopf Neigung----------------------
myservoB.attach(3); 
myservoB.writeMicroseconds(myservoB_Center);
delay(1000);

// Servo Rotation Turm ----------------------
myservoC.attach(4); 
myservoC.writeMicroseconds(myservoC_Center);
delay(1000);

// Servo ESC Brushless ------------------

myservo_ESC_A.attach(14); // BackSpin
myservo_ESC_B.attach(15); // TopSpin

// Bluetooth -------------------------------- 
//BT.begin(9600);                   
//BT.println("Hello from Arduino");



// Schrittmotor  ----------------------------
stepper.setMaxSpeed(8000);
stepper.setSpeed(0);

// Microstepping ----------------------------
//  Low   Low   Low   Full step
//  High  Low   Low   Half step
//  Low   High  Low   1/4 step
//  High  High  Low   1/8 step
//  Low   Low   High  1/16 step
//  High  Low   High  1/32 step
//  Low   High  High  1/32 step
//  High  High  High  1/32 step

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

}

void loop() {
  stepper.runSpeed();
  
  digitalWrite(in1, HIGH);  // Motor 1 beginnt zu rotieren
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);  // Motor 2 beginnt zu rotieren
  digitalWrite(in4, LOW );

  
  if (Serial1.available())
  {
    a=Serial1.readString(); 
    b = a.substring(0,1);
    c = a.substring(1);
    d = c.toInt();

        if ((b=="M" || b=="m"))
        {               
          Serial.println(a);
          Serial.println(b);
          Serial.println(c);
          stepper.setSpeed(d);
          analogWrite(GSM1, 50);
          analogWrite(GSM2, 50);    
        }
        
        if ((b=="O" || b=="o"))
        {               
          Serial.println(a);
          Serial.println(b);
          Serial.println(c);
          myservoA.writeMicroseconds(d);
        }
        
        if ((b=="P" || b=="p"))
        {               
          Serial.println(a);
          Serial.println(b);
          Serial.println(c);
          myservoB.writeMicroseconds(d);
        }
        
        if ((b=="Q" || b=="q"))
        {               
          Serial.println(a);
          Serial.println(b);
          Serial.println(c);
          myservoC.writeMicroseconds(d);
        }

        if ((b=="T" || b=="t"))
        {               
          Serial.println(a);
          Serial.println(b);
          Serial.println(c);
          myservo_ESC_A.writeMicroseconds(d);
        }

        if ((b=="B" || b=="b"))
        {               
          Serial.println(a);
          Serial.println(b);
          Serial.println(c);
          myservo_ESC_B.writeMicroseconds(d);
        }

        if ((b=="X" || b=="x"))  // Stop
        {  
          stepper.setSpeed(0);
          myservo_ESC_A.writeMicroseconds(0);             
          myservo_ESC_B.writeMicroseconds(0);
          analogWrite(GSM1, 0);
          analogWrite(GSM2, 0);
        }
                        
        else
        {
          //BT.println("NULL");
          //stepper.setSpeed(0);
        }
   
  }


}
