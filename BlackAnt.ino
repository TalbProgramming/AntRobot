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



void setup()
{
  // put your setup code here, to run once:
  
  maestroSerial.begin(9600);
  
  Serial.begin(9600);
  
  Serial.println(ServoArray[1][0]);

   
  // ~~~~~~~~~~~~~~~~~~~~ //
  delay(500);
  
  /*פעולות הפעלה ראשוניות*/
  setSpeedAll(1000);// set motor speed  \\ SOURCE
  delay(500);
}


void loop() 
{ 
  // put your main code here, to run repeatedly:

  goMiddle(30);

  prepareForMovement(1, 30);
  moveForward(1, 30);
  moveForward(1, 30);
  moveForward(1, 30);
  moveForward(1, 30);
  moveForward(1, 30);
  moveForward(1, 30);
  
  prepareForRotation(0, 30);
  Rotate(0, 30);
  Rotate(0, 30);
  Rotate(0, 30);
  Rotate(0, 30);

  prepareForRotation(1, 30);
  Rotate(1, 30);
  Rotate(1, 30);
  Rotate(1, 30);
  Rotate(1, 30);

  prepareForMovement(0, 30);
  moveForward(0, 30);
  moveForward(0, 30);
  moveForward(0, 30);
  moveForward(0, 30);
  moveForward(0, 30);
  moveForward(0, 30);
  moveForward(0, 30);
  moveForward(0, 30); 
  delay(20000);
}

// ~~~~~~~~~~~~~~~~ Standing Methods ~~~~~~~~~~~~~~~~~~~~~

void defaultStandingPosition()
{ // goto default position
  goMiddle(30);
  delay(100);
  
  for(int i = 3; i<=19; i=i+3)
  {
    moveServoFromTo(i, 0, 30, 30);
  }
  // move legs vertically
  moveServoFromTo(1, 0, -20, 0); // leg1
  
  moveServoFromTo(7, 0, 20, 0); // leg3
  
  moveServoFromTo(10, 0, -20, 0); // leg4

  moveServoFromTo(16, 0, 20, 0); // leg6
  
}


void defaultPosition()
{
	// default position before walking
	goMiddle(30);
	delay(200);
	
	for(int servo = 3; servo <= 19; servo+=3)
	{
		moveServoFromTo(servo, 0, 50, 0);
    //moveServoFromTo(servo, 0, 30, 0); 
	}
}


void Crouch()
{ 
  // moves the whole body down.
  goMiddle(30);
  delay(100);
  defaultStandingPosition();
  delay(100);
  // third servo of every leg goes down
  for(int i = 3; i <= 19; i = i+3)
  {
    moveServoFromTo(i, 30, 50, 10);
  }

  //second servo of every leg goes up
   for(int ii = 2; ii <= 19; ii = ii+3)
  {
    moveServoFromTo(ii, 0, -30, 10);
  }
}


void Stretch()
{ // moves the body up
  goMiddle(30);
  delay(100);
  defaultStandingPosition();
  delay(100);
  // third servo of every leg goes up
  for(int i = 3; i <= 19; i = i+3)
  {
    moveServoFromTo(i, 30, 20, 10);
  }
  
  //second servo of every leg goes down
   for(int ii = 2; ii <= 18; ii = ii+3)
  {
    moveServoFromTo(ii, 0, 50, 10);
  }
}

void goMiddle(int myDelay)
{
  for (int i = 1 ; i <= 18 ; i++) {
    settarget(ServoArray[i][0], ServoArray[i][1]);
  delay(myDelay);
  }
}

// ~~~~~~~~ Moving Functions ~~~~~~~~

void prepareForMovement(int where, int Delay) //where = 0 - backward, 1 - forward
{
  int stepSize = -20;
  
  
  // NEEDS TO BE CHECKED !!!!!!!!!!!!!!!
  
  if(where == 0)
  {
	  // backward movement	  
	  stepSize = -stepSize;
  }
  
  if(where != 0 && where != 1)
  {
	  // wrong input
	  while(true)
    { // shows an error
       moveServoFromTo(2, 0, -30, 30);
       moveServoFromTo(3, 0, -30, 30);
       moveServoFromTo(2, -30, 0, 30);
       moveServoFromTo(3, -30, 0,30);
    }
  }
  goMiddle(30);
  defaultPosition();
  delay(50);

    // move the second servo of every leg up - 1,4,5
  moveServoFromTo(2, 0, -30, Delay);
  moveServoFromTo(11, 0, -30, Delay); // leg4
  moveServoFromTo(14, 0, -30, Delay);

  // move the first servo of every leg forward
  moveServoFromTo(1, 0, stepSize, Delay);
  moveServoFromTo(10, 0, -stepSize, Delay); // leg4
  moveServoFromTo(13, 0, -stepSize, Delay);

  // get them back down
  moveServoFromTo(2, -30, 0, Delay);
  moveServoFromTo(11, -30, 0, Delay); // leg4
  moveServoFromTo(14, -30, 0, Delay);
}


void moveForward(int where, int Delay)
{

  // every time, the 1st or 6th leg move the opppsite direciton of the other two legs
   // on rotation, the two sets of 3 legs go to the same direction
   // for going forward, we need the two sets of 3 legs to go to the opposite side.
  int stepsize = -20;
  
  if(where == 0)
  {
	  // backward movement	  
	  stepsize = -stepsize;
  }
  
  if(where != 0 && where != 1)
  {
	  // wrong input
	  while(true)
    { // shows an error
       moveServoFromTo(2, 0, -30, 30);
       moveServoFromTo(3, 0, -30, 30);
       moveServoFromTo(2, -30, 0, 30);
       moveServoFromTo(3, -30, 0,30);
    }
  }
  
  // move the first servo back 60 degrees
  moveServoFromTo(1, stepsize, -stepsize, Delay);
  moveServoFromTo(10, -stepsize, stepsize, Delay); // leg4
  moveServoFromTo(13, -stepsize, stepsize, Delay);

  // backword movement
  // move the second servo of every leg up - 2,3,6
  moveServoFromTo(5, 0, -30, Delay);
  moveServoFromTo(8, 0, -30, Delay); // leg3
  moveServoFromTo(17, 0, -30, Delay);

  // move the first servo of every leg forward
  moveServoFromTo(4, -stepsize, stepsize, Delay);
  moveServoFromTo(7, -stepsize, stepsize, Delay); // leg3
  moveServoFromTo(16, stepsize, -stepsize, Delay);

  // get them back down
  moveServoFromTo(5, -30, 0, Delay);
  moveServoFromTo(8, -30, 0, Delay); // leg3
  moveServoFromTo(17, -30, 0, Delay);

   // move the legs 60degrees back
  moveServoFromTo(4, stepsize, -stepsize, Delay);
  moveServoFromTo(7, stepsize, -stepsize, Delay); // leg3
  moveServoFromTo(16, -stepsize, stepsize, Delay);
    
  // backword movement
  // move the second servo of every leg up - 1,4,5
  moveServoFromTo(2, 0, -30, Delay);
  moveServoFromTo(11, 0, -30, Delay);// leg4
  moveServoFromTo(14, 0, -30, Delay);

  // move the first servo of every leg forward
  moveServoFromTo(1, -stepsize, stepsize, Delay);
  moveServoFromTo(10, stepsize, -stepsize, Delay);// leg4
  moveServoFromTo(13, stepsize, -stepsize, Delay);

  // get them back down
  moveServoFromTo(2, -30, 0, Delay);
  moveServoFromTo(11, -30, 0, Delay);// leg4
  moveServoFromTo(14, -30, 0, Delay); 
}


void prepareForRotation(int side, int Delay) // 0 = left, 1 = right
{ 

  // variables
  int stepSize = 30;

  if(side == 1)
  { // if you wanna turn to the right the stepsize equals to -stepsize
    stepSize = 0 - stepSize; 
  }

  if(side != 0 && side != 1)
  {
    // wrong input
    while(true)
    { // shows an error
       moveServoFromTo(2, 0, -30, 30);
       moveServoFromTo(3, 0, -30, 30);
       moveServoFromTo(2, -30, 0, 30);
       moveServoFromTo(3, -30, 0,30);
    }
  }
    // if side is 0, we dont hav to change anything about the stepsize variable...
  
  goMiddle(30);
  defaultPosition();
  delay(200);

  // move the second servo of every leg up - 1,4,5
  moveServoFromTo(2, 0, -30, Delay);
  moveServoFromTo(11, 0, -30, Delay); // leg4
  moveServoFromTo(14, 0, -30, Delay);

  // move the first servo of every leg forward
  moveServoFromTo(1, 0, stepSize, Delay);
  moveServoFromTo(10, 0, stepSize, Delay); // leg4
  moveServoFromTo(13, 0, stepSize, Delay);

  // get them back down
  moveServoFromTo(2, -30, 0, Delay);
  moveServoFromTo(11, -30, 0, Delay); // leg4
  moveServoFromTo(14, -30, 0, Delay);
  
}

void Rotate(int side, int Delay) // 0 - left, 1 - right
{
// variables
  int stepsize = 30;

  if(side == 1)
  { // if you wanna turn to the right the stepsize equals to -stepsize
    stepsize = 0 - stepsize; 
  }

  if(side != 0 && side != 1)
  {
    // wrong input
    while(true)
    { // shows an error
       moveServoFromTo(2, 0, -30, 30);
       moveServoFromTo(3, 0, -30, 30);
       moveServoFromTo(2, -30, 0, 30);
       moveServoFromTo(3, -30, 0, 30);
    }

    // if side is 0, we dont hav to change anything about the stepsize variable...
  }
 
  // move the first servo back 60 degrees
  moveServoFromTo(1, stepsize, -stepsize, Delay);
  moveServoFromTo(10, stepsize, -stepsize, Delay); // leg4
  moveServoFromTo(13, stepsize, -stepsize, Delay);

  // backword movement
  // move the second servo of every leg up - 2,4,6
  moveServoFromTo(5, 0, -30, Delay);
  moveServoFromTo(8, 0, -30, Delay); // leg3
  moveServoFromTo(17, 0, -30, Delay);

  // move the first servo of every leg forward
  moveServoFromTo(4, -stepsize, stepsize, Delay);
  moveServoFromTo(7, -stepsize, stepsize, Delay); // leg3
  moveServoFromTo(16, -stepsize, stepsize, Delay);

  // get them back down
  moveServoFromTo(5, -30, 0, Delay);
  moveServoFromTo(8, -30, 0, Delay); // leg3
  moveServoFromTo(17, -30, 0, Delay);

  // move the legs 60degrees back
  moveServoFromTo(4, stepsize,-stepsize, Delay);
  moveServoFromTo(7, stepsize, -stepsize, Delay); // leg3
  moveServoFromTo(16, stepsize, -stepsize, Delay);
  
  // backword movement
  // move the second servo of every leg up - 1,4,5
  moveServoFromTo(2, 0, -30, Delay);
  moveServoFromTo(11, 0, -30, Delay);// leg4
  moveServoFromTo(14, 0, -30, Delay);
  
  // move the first servo of every leg forward
  moveServoFromTo(1, -stepsize, stepsize, Delay);
  moveServoFromTo(10, -stepsize, stepsize, Delay);// leg4
  moveServoFromTo(13, -stepsize, stepsize, Delay);
  
  // get them back down
  moveServoFromTo(2, -30, 0, Delay);
  moveServoFromTo(11, -30, 0, Delay);// leg4
  moveServoFromTo(14, -30, 0, Delay);
}


// ~~~~~~~~~~~~~ Helping Methods ~~~~~~~~~~~~~~~

void moveAllSecondServos(int From, int To)
{ // dont use, should be used only once, not accurate
  moveServoFromTo(2, From, To, 30);
  moveServoFromTo(5, From, To, 30);
  moveServoFromTo(8, From, To, 30);
  moveServoFromTo(11, From, To, 30);
  moveServoFromTo(14, From, To, 30);
  moveServoFromTo(17, From, To, 30); 
}


void moveAllThirdServos(int From, int To)
{ // dont use, should be used only once, not accurate
  moveServoFromTo(3, From, To, 30);
  moveServoFromTo(6, From, To, 30);
  moveServoFromTo(9, From, To*0.42, 30);
  moveServoFromTo(12, From, To*0.42, 30);
  moveServoFromTo(15, From, To*0.5, 30);
  moveServoFromTo(18, From, To*0.5, 30);
  
}


void checkServos()
{
  for(int i=1; i<=19; i++)
  {
    moveServoFromTo(i, 0, -30, 100);
    moveServoFromTo(i, -30, 0, 100);
  }
  delay(2000);
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

void setSpeedAll(int set)
{//Engine speed setting function
  for (int i = 1 ; i <= 18 ; i++)  {
    //maestro.setSpeed(i, set);
    maestro.setSpeed(ServoArray[i][0], set);
    //maestro.setAcceleration(i,255);
  }
}


// Move specipic servoNum - move servo angle
// servoNum - list index, not port!!
void moveServoFromTo(int servoNum, int From, int To, int myDelay)
{
  
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
