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
  //goMiddle(30); // set all servos to middle position
  //delay(1000);
  //Legs_B_FromTo(0, 30, 1);
  //delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  //goMiddle(30);
  //delay(2000);
  //defaultPosition();
  //delay(2000);
  prepareForMovement();
  RotateRight();
  RotateRight();
  RotateRight();
  RotateRight();
  RotateRight();
  RotateRight();
  RotateRight();
  RotateRight();
  RotateRight();
  RotateRight();
  RotateRight();
  
  
  delay(2000);
  //checkServos();
  //bodyUp(10);
}



// ~~~~~~~~ Robot Functions ~~~~~~~~
void prepareForMovement()
{
  goMiddle(30);
  defaultPosition();
  //delay(1000);

    // move the second servo of every leg up - 1,3,5
  moveServoFromTo(2, 0, -30, 0);
  moveServoFromTo(8, 0, -30, 0);
  moveServoFromTo(14, 0, -30, 0);

  // move the first servo of every leg forward
  moveServoFromTo(1, 0, -30, 0);
  moveServoFromTo(7, 0, -30, 0);
  moveServoFromTo(13, 0, -30, 0);

  // get them back down
  moveServoFromTo(2, -30, 0, 0);
  moveServoFromTo(8, -30, 0, 0);
  moveServoFromTo(14, -30, 0, 0);
}


void RotateRight()
{ // going forward position1
  int forwardServos[3] = {1,3,5};
  int backwordServos[3] = {2,4,6};

  // move the first servo back 60 degrees
  moveServoFromTo(1, -30, 30, 0);
  moveServoFromTo(7, -30, 30, 0);
  moveServoFromTo(13, -30, 30, 0);
  //delay(30);

  // backword movement
  // move the second servo of every leg up - 2,4,6
  moveServoFromTo(5, 0, -30, 0);
  moveServoFromTo(11, 0, -30, 0);
  moveServoFromTo(17, 0, -30, 0);
  //delay(30);
  // move the first servo of every leg forward
  moveServoFromTo(4, 30, -30, 0);
  moveServoFromTo(10, 30, -30, 0);
  moveServoFromTo(16, 30, -30, 0);
  //delay(30);
  // get them back down
  moveServoFromTo(5, -30, 0, 0);
  moveServoFromTo(11, -30, 0, 0);
  moveServoFromTo(17, -30, 0, 0);
  //delay(30);


   // move the legs 60degrees back
  moveServoFromTo(4, -30, 30, 0);
  moveServoFromTo(10, -30, 30, 0);
  moveServoFromTo(16, -30, 30, 0);
  //delay(30);
  
  // backword movement
  // move the second servo of every leg up - 1,3,5
  moveServoFromTo(2, 0, -30, 0);
  moveServoFromTo(8, 0, -30, 0);
  moveServoFromTo(14, 0, -30, 0);
  //delay(30);
  // move the first servo of every leg forward
  moveServoFromTo(1, 30, -30, 0);
  moveServoFromTo(7, 30, -30, 0);
  moveServoFromTo(13, 30, -30, 0);
  //delay(30);
  // get them back down
  moveServoFromTo(2, -30, 0, 0);
  moveServoFromTo(8, -30, 0, 0);
  moveServoFromTo(14, -30, 0, 0);
  //delay(30);
}


void bodyUp(int Delay)
{ // moves the whole body up.
  int inc = 5;
  goMiddle(30);

  for(int i = 3; i <= 19; i+1)
  {
    moveServoFromTo(ServoArray[i][0], 0, -30, 30);
  }
  
  /*
  for(int Serv = 1; Serv < 19; Serv++)
  {
    moveServoFromTo(Serv, 1-Serv, -Serv, 30);
    delay(Delay);
  }
  */
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

void checkServos()
{
  for(int i=1; i<=19; i++)
  {
    moveServoFromTo(i, 0, -30, 100);
    moveServoFromTo(i, -30, 0, 100);
    //moveServoFromTo(i, 30, 0, 100);
  
  }
  delay(2000);
}

void defaultPosition()
{ // goto default position
  int moreHight = 10;
  for(int servo = 3; servo <= 19; servo+=3)
  { // move all servos from current position 10 moreHight more
    moveServoFromTo(servo, ServoArray[servo][1],ServoArray[servo][1] + moreHight, 30); 
  }
  
}
/*
void goMid()
{
  // if the servo is not in the FROM position, it just goes to it!!!!!!!!
  for(int j = 0; j<=60; j=j+5)
  {
    for(int i=1; i<19; i++)
    {
     moveServoFromTo(i, j, j+5, 100);
        // move 20
    }
  }
}
*/
