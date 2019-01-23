#include <Timer.h>
#include <Event.h>
#include <Tilt.h>
#include <Accelerometer.h>

Timer t; //instance of timer
const int TILTPIN = 2;
const int aypin = A3;
const int axpin = A2;
bool aux = false;
Tilt tilt(TILTPIN); //instance of Tilt
Accelerometer accelerometer(axpin,aypin); //instance of Accelerometer

int lastStep = -1; // variable to print only if the steps done are diferent from the last steps

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //where we will see the results
  pinMode(TILTPIN, INPUT); //initializase the tilt to input mode
  int steps = t.every(1000, stepsDone, (void*)2); //event to see every 1000 miliseconds the steps done if they changed  
  float distance = t.every(2000, distanceDone, (void*)1);
  pinMode(axpin, OUTPUT); //initializase the accelerometer x absis to output mode
  pinMode(aypin, OUTPUT); //initializase the accelerometer y absis to output mode
}

void loop() {
  // put your main code here, to run repeatedly:
  tilt.updateTilt(); //function to update the steps done
  t.update(); //function to print the steps done if they changed
}

void stepsDone(void* context){
  if(tilt.stepsTilt!=lastStep && accelerometer.hasChanged()){ //if the steps done are diferent from the last steps done
    Serial.print("Steps Done: "); //we print the steps done
    Serial.println(tilt.stepsTilt);
    lastStep=tilt.stepsTilt; // we change the last step done 
    aux=true;
  }
}

void distanceDone(void* context){
  if(tilt.stepsTilt!=lastStep && aux){ 
    Serial.print("Distance: ");
    Serial.println(tilt.stepsTilt*0.02);
    lastStep=tilt.stepsTilt; // we change the last step done 
    aux=false;
  }
}
