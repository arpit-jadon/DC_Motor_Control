//Keyboard Controls:
//
// C - Clockwise
// S - Stop
// A - Anti-clockwise
 
// Declare L298N Controller pins
// Motor 1
int dir1PinA = 7;
int dir2PinA = 8;
int speedPinA = 5; // PWM control
int refsig=200;
int count=0;
int Turns=6; // One more than the total number of revolutions required with taking top of the IR sensor the reference point.  
bool flag=HIGH;
 
void setup() { 
 
Serial.begin(9600); // baud rate

//Define L298N Dual H-Bridge Motor Controller Pins 
pinMode(dir1PinA,OUTPUT);
pinMode(dir2PinA,OUTPUT);
pinMode(speedPinA,OUTPUT);
 
}
 
void loop() {
 
//int sig = analogRead(A0);
//Serial.println(sig);

// Initialize the Serial interface:
while ((Serial.available() > 0)){
char inByte = Serial.read();
Serial.println(inByte);
int sig = analogRead(A0);

if (inByte=='C') 
  { 
  Serial.println("Clockwise rotation"); // Prints out “Motor 1 Forward” on the serial monitor
  while(count<=Turns && flag)
  {
  int sig = analogRead(A0);
  analogWrite(speedPinA, 255);//Sets speed variable via PWM 
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  //Serial.println("   "); // Creates a blank line printed on the serial monitor
  //Serial.println("Flag Status");
  //Serial.println(flag);
  //Serial.println(sig);
  if ((sig > refsig) && flag==HIGH) 
        { 
         count=count+1;
         Serial.println("No. of Revolutions");
         Serial.println(count);
           if (count>=Turns)
              {analogWrite(speedPinA,0);
               //digitalWrite(8,LOW);
               flag=LOW;
              }
         delay(300);
        }
    }
  }
 

else if (inByte=='A')
    { Serial.println("Anti-clockwise rotation");
      while(count<=Turns && flag){
      int sig = analogRead(A0);
    analogWrite(speedPinA, 255); // Maximum PWM (speed)
    digitalWrite(dir1PinA, HIGH);
    digitalWrite(dir2PinA, LOW);
    //Serial.println("   ");
    if ((sig > refsig) && flag==HIGH) 
        {
         count=count+1;
         Serial.println("No. of Revolutions");
         Serial.println(count);
           if (count>=Turns)
              {analogWrite(speedPinA,0);
               flag=LOW;
              }
         delay(300);
        }
      }
    }

else if (inByte=='S')
  {analogWrite(speedPinA, 0); // 0 PWM (Speed)
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  Serial.println("No rotation");
  }


  }
}

