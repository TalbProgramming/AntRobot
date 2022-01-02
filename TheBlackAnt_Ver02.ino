// במבט על משמאל לימין : 1,4,5 ובהחלפה 2,3,6 כך תתבצע התנועה.//


#include <PololuMaestro.h>
#ifdef SERIAL_PORT_HARDWARE_OPEN
#define maestroSerial SERIAL_PORT_HARDWARE_OPEN
#else
#include <SoftwareSerial.h>/*ספריה עבור תקשורת UART משנית*/
SoftwareSerial maestroSerial(4, 5);
#endif
MicroMaestro maestro(maestroSerial);/*שיוך ערוץ התקשורת עבור בקר המנועים*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int ServoArray[19][3] = {   {0, 0 , 0}, // Udi:  {pinNumController , MidDegrees}
  {2, 90 , 3}, { 1, 90 , 6} , { 0, 90 , 6} ,
  {5, 90 , 3}, { 4, 90 , 6} , { 3, 90 , 6} ,
  {15, 90 , 3}, { 16, 100 , 6} , { 17, 90 , 6} ,

  {21, 90 , 3}, { 22, 90 , 6} , { 23, 100 , 6} ,
  {12, 90 , 3}, { 13, 90 , 6} , { 14, 105 , 6} ,
  {9, 90 , 3}, { 10, 90 , 6} , { 11, 105 , 6}
};


//int ServoArray[19][3] = {   {0, 0 , 0},
//  {2, 90 , 3}, { 1, 90 , 6} , { 0, 110 , 6} ,
//  {5, 90 , 3}, { 4, 90 , 6} , { 3, 110 , 6} ,
//  {15, 90 , 3}, { 16, 100 , 6} , { 17, 110 , 6} ,
//
//  {21, 90 , 3}, { 22, 90 , 6} , { 23, 120 , 6} ,
//  {12, 90 , 3}, { 13, 90 , 6} , { 14, 125 , 6} ,
//  {9, 90 , 3}, { 10, 90 , 6} , { 11, 125 , 6}
//};





/*הגדרת הדקי התקשורת עבור יחידת התקשורת האל-חוטית ויצירת כתובת של הרכיב עבור המקלט*/
RF24 radio(10, 9); // CE, CSN
const byte address[6] = "00001"; //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
String st;/*מחרוזת עבור קבלת התשדורת*/
int numtimes = 3;
int jX = 320 , jY = 320 , M = 0;/*משתנים עבור פירוק ערכי המידע אשר נמתה במחרוזת*/
// ~~~~~~~~~~~~~~~~~~~~ //

void setup() {
  maestroSerial.begin(9600);
  Serial.begin(9600);
  Serial.println(ServoArray[1][0]);

  /*סידרת הוראות לייצירת תקשורת אל חוטית*/
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
  /*ניתן בבקר UNO לחבר את אחד מהדקי רכיב התקשורת לצורך יצירת  יצירת פסיקה לעדכון הנתונים בלייב,
    בבקר ה NANO RF לא ניתן לעשות זאת*/
  //attachInterrupt(digitalPinToInterrupt(2), interruptHandler, FALLING);
  // ~~~~~~~~~~~~~~~~~~~~ //
  delay(500);
  /*פעולות הפעלה ראשוניות*/
  setSpeedAll(1000);// set motor speed  \\ SOURCE
  // setSpeedAll(220);
  delay(500);

  //  goAll(100, 40);
  goMiddle(30);
  delay(1000);

  int delayAA = 0;
  Legs_B_FromTo(0, 30, 1);
  delay(500);
//  MoveLegs_145(1);
//  MoveLegs_236(1);
//  MoveLegs_145(1);
//  MoveLegs_236(1);
  //Legs_B_FromTo(40, 00, 1);


}


// ======================================================
// ===   LOOP    ======
// ======================================================
void loop() {

  MoveLegs_145(1);
  MoveLegs_236(1);


  //MoveLegs_145();
  // delay(1000);

  //    LegC_FromTo(-30, 50, 1);
  //    LegC_FromTo(50, -30, 1);
  //  LegC_ToPos(130,10);
  //  delay(1000);
  //  LegC_ToPos(90,10);
  //  delay(1000);
}



void MoveLegs_236(int Repeat) {

  int delayA = 0;
  int delayB = 2;
  int stepSize = 50; // was 40

  for (int i = 0 ; i <  Repeat; i++) {
    moveServoFromTo(18, 0, -30, delayB);
    moveServoFromTo(9, 0, -30, delayB);
    moveServoFromTo(6, 0, -30, delayB);
    delay(delayA);
    moveServoFromTo(16, 0, +stepSize, delayB);
    moveServoFromTo(7, 0, +stepSize, delayB);
    moveServoFromTo(4, 0, +stepSize, delayB);
    delay(delayA);
    moveServoFromTo(18, -30, 0, delayB);
    moveServoFromTo(9, -30, 0, delayB);
    moveServoFromTo(6, -30, 0, delayB);
    delay(delayA);

    moveServoFromTo(15, 0, -30, delayB);
    moveServoFromTo(12, 0, -30, delayB);
    moveServoFromTo(3, 0, -30, delayB);
    delay(delayA);

    moveServoFromTo(13, 0, -stepSize, delayB);
    moveServoFromTo(10, 0, -stepSize, delayB);
    moveServoFromTo(1, 0, -stepSize, delayB);
    delay(delayA);

    moveServoFromTo(15, -30, 0, delayB);
    moveServoFromTo(12, -30, 0, delayB);
    moveServoFromTo(3, -30, 0, delayB);
    delay(delayA);

    Legs_236_BodyBack();
  }
}



void MoveLegs_145(int Repeat) {
  int delayA = 0;
  int delayB = 2;
  int stepSize = 50; // was 40

  for (int i = 0 ; i <  Repeat; i++) {
    moveServoFromTo(3, 0, -30, delayB);
    moveServoFromTo(12, 0, -30, delayB);
    moveServoFromTo(15, 0, -30, delayB);
    delay(delayA);
    moveServoFromTo(1, 0, -stepSize, delayB);
    moveServoFromTo(10, 0, -stepSize, delayB);
    moveServoFromTo(13, 0, -stepSize, delayB);
    delay(delayA);
    moveServoFromTo(3, -30, 0, delayB);
    moveServoFromTo(12, -30, 0, delayB);
    moveServoFromTo(15, -30, 0, delayB);
    delay(delayA);

    moveServoFromTo(6, 0, -30, delayB);
    moveServoFromTo(9, 0, -30, delayB);
    moveServoFromTo(18, 0, -30, delayB);
    delay(delayA);

    moveServoFromTo(4, 0, stepSize, delayB);
    moveServoFromTo(7, 0, stepSize, delayB);
    moveServoFromTo(16, 0, stepSize, delayB);
    delay(delayA);

    moveServoFromTo(6, -30, 0, delayB);
    moveServoFromTo(9, -30, 0, delayB);
    moveServoFromTo(18, -30, 0, delayB);
    delay(delayA);

    Legs_145_BodyBack();
  }
}

void Legs_236_BodyBack() {
  int myDelay = 0;
  int backSize = 50; // was 30
  
  for (int ii = 0 ; ii <= backSize ; ii ++) {
    settarget(ServoArray[16][0], ServoArray[16][1] - backSize + ii);  delay(myDelay);
    settarget(ServoArray[7][0], ServoArray[7][1]  - backSize + ii); delay(myDelay);
    settarget(ServoArray[4][0], ServoArray[4][1] - backSize + ii); delay(myDelay);
    settarget(ServoArray[13][0], ServoArray[13][1] + backSize - ii); delay(myDelay);
    settarget(ServoArray[10][0], ServoArray[10][1] + backSize - ii); delay(myDelay);
    settarget(ServoArray[1][0], ServoArray[1][1] + backSize - ii); delay(myDelay);
  }
}



void Legs_145_BodyBack() {
  int myDelay = 0;
  int backSize = 50; // was 30
  
  for (int ii = 0 ; ii <= backSize ; ii ++) {
    settarget(ServoArray[1][0], ServoArray[1][1] + backSize - ii);  delay(myDelay);
    settarget(ServoArray[10][0], ServoArray[10][1]  + backSize - ii); delay(myDelay);
    settarget(ServoArray[13][0], ServoArray[13][1] + backSize - ii); delay(myDelay);
    settarget(ServoArray[4][0], ServoArray[4][1] - backSize + ii); delay(myDelay);
    settarget(ServoArray[7][0], ServoArray[7][1] - backSize + ii); delay(myDelay);
    settarget(ServoArray[16][0], ServoArray[16][1] - backSize + ii); delay(myDelay);
  }
}




// Move specipic servoNum
void moveServoFromTo(int servoNum, int From, int To, int myDelay) {
  int increment = 5;
  if (From < To)
    for (int ii = From ; ii <= To ; ii += increment) {
      settarget(ServoArray[servoNum][0], ii + ServoArray[servoNum][1]); delay(myDelay);
    }
  if (From > To)
    for (int ii = From ; ii >= To ; ii -= increment) {
      settarget(ServoArray[servoNum][0], ii + ServoArray[servoNum][1]); delay(myDelay);
    }
}








void goMiddle(int myDelay) {
  for (int i = 1 ; i <= 18 ; i++) {
    settarget(ServoArray[i][0], ServoArray[i][1]); delay(myDelay);
  }
}


void Legs_B_FromTo(int From, int To, int myDelay) {  // From CENTER
  if (From < To)
    for (int ii = From ; ii <= To ; ii ++) {
      for (int i = 2 ; i <= 18 ; i += 3) { // B Legs Only
        settarget(ServoArray[i][0], ii + ServoArray[i][1]); delay(myDelay);
      }
    }
  if (From > To)
    for (int ii = From ; ii >= To ; ii --) {
      for (int i = 2 ; i <= 18 ; i += 3) {  // B Legs Only
        settarget(ServoArray[i][0], ii + ServoArray[i][1]); delay(myDelay);
      }
    }
}






// LEG CCCC  ONLY //  Relative To Middle
void Legs_C_FromTo(int From, int To, int myDelay) {  // Servos: 3 6 9 12 15 18
  if (From < To)
    for (int ii = From ; ii <= To ; ii ++) {
      for (int i = 3 ; i <= 18 ; i += 3) { // C Legs Only
        settarget(ServoArray[i][0], ii + ServoArray[i][1]); delay(myDelay);
      }
    }
  if (From > To)
    for (int ii = From ; ii >= To ; ii --) {
      for (int i = 3 ; i <= 18 ; i += 3) {  // C Legs Only
        settarget(ServoArray[i][0], ii + ServoArray[i][1]); delay(myDelay);
      }
    }
}



void Legs_C_ToPos(int pos, int myDelay) {  // Servos: 3 6 9 12 15 18
  for (int i = 3 ; i <= 18 ; i += 3) {
    settarget(ServoArray[i][0], pos); delay(myDelay);
  }
}


void goAll(int pos, int myDelay) {
  for (int i = 1 ; i <= 18 ; i++) {
    settarget(ServoArray[i][0], pos); delay(myDelay);
  }
}

















void settarget(unsigned char servo, unsigned int target)
{
  /*
    The angle adjustment function required for pulse
    time for transmission to a motor controller
  */
  target = map(target, 0, 180, 2400, 9500);
  maestro.setTarget(servo, target);
}

void setSpeedAll(int set) {//Engine speed setting function
  for (int i = 1 ; i <= 18 ; i++)  {
    //maestro.setSpeed(i, set);
    maestro.setSpeed(ServoArray[i][0], set);
    //maestro.setAcceleration(i,255);
  }
}
