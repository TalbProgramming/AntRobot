// imports for the transmittor
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>


// set up radio
RF24 radio(5, 6);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001"; // Address


// Define the radio communication
radio.begin();
radio.openWritingPipe(address);
radio.setAutoAck(false);
radio.setDataRate(RF24_250KBPS);
radio.setPALevel(RF24_PA_LOW);





/* Funduino Joystick Shield Example

This program simply captures all of the inputs of the Funduino Joystick Shield buttons and
joystick every second and displays them in the Serial Monitor Window.  
The Arduino pins below are defined by the shield and cannot be changed.
*/
int const UP_BTN = 2;
int const DOWN_BTN = 4;
int const LEFT_BTN = 5;
int const RIGHT_BTN = 3;
int const E_BTN = 6;
int const F_BTN = 7;
int const JOYSTICK_BTN = 8;
int const JOYSTICK_AXIS_X = A0;
int const JOYSTICK_AXIS_Y = A1;
int buttons[] = {UP_BTN, DOWN_BTN, LEFT_BTN, RIGHT_BTN, E_BTN, F_BTN, JOYSTICK_BTN};



struct Data
{
  // preinitialized value 0 - 1
  int up;
  int down;
  int left;
  int right;
  int eButton;
  int fButton;

  // preinitialized value 0 - 1023
  int JoyStickButton;
  int JoyStickX;
  int JoyStickY;
}

Data data; //Create a variable with the above structure

// Define data veriables
data.up = 1;
data.down = 1;
data.left = 1;
data.right = 1;
data.eButton = 1;
data.fButton = 1;
data.JoyStickButton = 1;
data.JoyStickX = 512;
data.JoyStickY = 512;
// ~~~~~~~~~~~~~~ \\ 
//===============================================================================
//  Initialization
//===============================================================================

void setup() {
  //Set all button pins as inputs with internal pullup resistors enabled.
  for (int i; i < 7; i++)  pinMode(buttons[i], INPUT_PULLUP);
  Serial.begin(9600);
}
//===============================================================================
//  Main
//===============================================================================
void loop() {
  // Check each button input and print the status to the Serial Monitor Window
  Serial.print("UP="),Serial.print(digitalRead(UP_BTN));
  Serial.print("\tDOWN="),Serial.print(digitalRead(DOWN_BTN));
  Serial.print("\tLEFT="),Serial.print(digitalRead(LEFT_BTN));
  Serial.print("\tRIGHT="),Serial.print(digitalRead(RIGHT_BTN));
  Serial.print("\tE="),Serial.print(digitalRead(E_BTN));
  Serial.print("\tF="),Serial.print(digitalRead(F_BTN));
  Serial.print("\tJOYSTICK BTN="),Serial.print(digitalRead(JOYSTICK_BTN));
      
  // Print the full X/Y joystick values (0-1023)
  Serial.print("\tX="),Serial.print(analogRead(JOYSTICK_AXIS_X));
  Serial.print("\tY="),Serial.println(analogRead(JOYSTICK_AXIS_Y)); 
  delay(250);

  // put the inputs in the data variable to be initialized
  // will be 0 if the button is pressed
  data.up = digitalRead(UP_BTN);
  data.down = digitalRead(DOWN_BTN);
  data.left = digitalRead(LEFT_BTN);
  data.right = digitalRead(RIGHT_BTN);
  data.eButton = digitalRead(E_BTN);
  data.fButton = digitalRead(F_BTN);
  data.JoyStickButton = digitalRead(JOYSTICK_BTN);
  data.JoyStickX = analogRead(JOYSTICK_AXIS_X); // reads between 0 - 1023
                                                // the default is 512
  data.JoyStickY = analogRead(JOYSTICK_AXIS_Y); // reads between 0 - 1023


  // ~~~~~~~~~~~~~~~~~~~~~ Data initialization ~~~~~~~~~~~~~~~~~~~~~~~~~~ \\
  // the data will be initalized in the controller to not overload the arduino in the robot.

  int command; 
  // command variable value - command
  // 0 = Stretch, 1 = Crouch, 2 = defaultPosition, 3 = inc speed, 4 = dec speed,
  // 5 = forward, 6 = backward, 7 = right, 8 = left

  // not very efficient 

  if((data.up + data.down + data.left + data.right + data.eButton + data.fButton) < 5)
  { // if a button was pressed
    if(data.up == 0)
    {
      command = 0;
    }
      else if(data.down == 0)
      {
        command = 1;
      }
        else if(data.left == 0)
        {
          command = 2;       
        }
          else if(data.eButton == 0)
          {
            command = 3;
          }
            else if(data.fButton == 0)
            {
              command = 4;
            }
  }
    else // if none of the buttons were pressed 
    {
      // check for the joyStick
      continue 
      if(abs(data.JoyStickX - 512) > abs(JoyStickY - 512))
      { // the x moved more then the y 
        if(data.JoyStickX < 450)
        { // move left
          command = 8;
        }
        else if(data.JoyStickX > 580)
        { // move right
          command = 7;
        }
      }
      else
      {
         if(data.JoyStickY < 450)
        { // move backward
          command = 6;
        }
        else if(data.JoyStickY > 580)
        { // move forward
          command = 5;
        }     
      }      
    }






   // ~~~ End of data initialization ~~~ \\ 
  // Send the whole data from the structure to the receiver
  radio.write(&data, sizeof(Data));
  delay(250); 
 }
