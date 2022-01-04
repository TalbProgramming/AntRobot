// imported libraries

#include <PololuMaestro.h>
#ifdef SERIAL_PORT_HARDWARE_OPEN
#define maestroSerial SERIAL_PORT_HARDWARE_OPEN
#else
#include <SoftwareSerial.h>/*ספריה עבור תקשורת UART משנית*/
SoftwareSerial maestroSerial(4, 5);
#endif
MicroMaestro maestro(maestroSerial);/*שיוך ערוץ התקשורת עבור בקר המנועים*/

// ~~~~~~~~~~~~~~~~~~~~~ \\ 
// Variables


// an array of the servo motors[x] and angles[][x] of the middle position
int ServoArray[19][3] = {   {0, 0 , 0},
  {9, 90 , 3}, { 10, 90 , 6} , { 11, 105 , 6} ,
  {12, 90 , 3}, { 13, 90 , 6} , { 14, 105 , 6} ,
  {21, 90 , 3}, { 22, 90 , 6} , { 23, 100 , 6} ,
  {15, 90 , 3}, { 16, 100 , 6} , { 17, 90 , 6} ,
  {5, 90 , 3}, { 4, 90 , 6} , { 3, 90 , 6} ,
  {2, 90 , 3}, { 1, 90 , 6} , { 0, 90 , 6}
};



void setup() {
  // put your setup code here, to run once:
  
  maestroSerial.begin(9600);
  
  Serial.begin(9600);
  
  Serial.println(ServoArray[1][0]);

   
  // ~~~~~~~~~~~~~~~~~~~~ //
  delay(500);
  
  /*פעולות הפעלה ראשוניות*/
  setSpeedAll(1000);// set motor speed  \\ SOURCE
  delay(500);
  goMiddle(30); // set all servos to middle position
  delay(1000);
  //Legs_B_FromTo(0, 30, 1);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  //goMiddle(30);
   // works


  for(int i=1; i<19; i++)
  {
    moveServoFromTo(i, 0, -30, 100);
    moveServoFromTo(i, -30, 0, 100);
  }
  delay(5000);
 
}




// ~~~~~~~~ Leg functions ~~~~~~~~~~

void move_leg_forward(unsigned char servoNum, int tempDelay, int sideTurn = 0) // if sideturn is given, the function uses it to move the leg differently
{                                                      // if not than the value is 0  
 // moves a leg forward
}

void move_leg_backwords(unsigned char servoNum, int tempDelay, int sideTurn = 0) // if sideturn is given, the function uses it to move the leg differently
{                                                        // if not than the value is 0
 // move a leg backwords
}

void move_leg_up(unsigned char servoNum, int tempDelay)
{
 // moves the leg up - would be used to straighten up
}

void move_leg_down(unsigned char servoNum, int tempDelay)
{
 // moves the leg down - would be used to crouch
}

void reposition_middle(unsigned char servoNum, int tempDelay)
{
 // repositions the leg to the middle location
}







// ~~~~~~~~ Servo motor methods ~~~~~~~~~~

void settarget(unsigned char servo, unsigned int target)
{
  /*
    The angle adjustment function required for pulse
    time for transmission to a motor controller
  */
  target =  map(target, 0, 180, 2400, 9500); // relativity - changes from angle to servo instructions
  maestro.setTarget(servo, target);
}

void setSpeedAll(int set) {//Engine speed setting function
  for (int i = 1 ; i <= 18 ; i++)  {
    //maestro.setSpeed(i, set);
    maestro.setSpeed(ServoArray[i][0], set);
    //maestro.setAcceleration(i,255);
  }
}


// Move specipic servoNum - move servo angle
// servoNum - list index, not port!!
void moveServoFromTo(int servoNum, int From, int To, int myDelay) {
  
  int increment = 5;
  
  if (From < To)
    for (int ii = From ; ii <= To ; ii += increment) {
      settarget(ServoArray[servoNum][0], ii + ServoArray[servoNum][1]);
    delay(myDelay);
    }
  
  if (From > To)
    for (int ii = From ; ii >= To ; ii -= increment) {
      settarget(ServoArray[servoNum][0], ii + ServoArray[servoNum][1]);
    delay(myDelay);
    }
}


void goMiddle(int myDelay) {
  for (int i = 1 ; i <= 18 ; i++) {
    settarget(ServoArray[i][0], ServoArray[i][1]);
  delay(myDelay);
  }
}
 // #################### unclear whats happening here
void Legs_B_FromTo(int From, int To, int myDelay) {  // From CENTER
  if (From < To)
    for (int ii = From ; ii <= To ; ii ++) {
      for (int i = 2 ; i <= 18 ; i += 3) { // B Legs Only
        settarget(ServoArray[i][0], ii + ServoArray[i][1]);
    delay(myDelay);
      }
    }
  if (From > To)
    for (int ii = From ; ii >= To ; ii --) {
      for (int i = 2 ; i <= 18 ; i += 3) {  // B Legs Only
        settarget(ServoArray[i][0], ii + ServoArray[i][1]);
    delay(myDelay);
      }
    }
}
