#include <elapsedMillis.h>

 

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
  int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
  long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
  long unsigned int pause = 5000;  

  boolean lockLow = true;
  boolean takeLowTime;  
  boolean personDetected = false;  
  
  elapsedMillis timeElapsed; 
  long unsigned int timeItTakesToGetMad = 6000;
    
    int pirPin = 7;
    
    int motorPin = 5;
     
    int redPin1 = 11;
    int yellowPin1 = 10; 
    int redPin2 = 9;
    int yellowPin2 = 6;
         
    
     
    void setup()
    {
      Serial.begin(9600);
      pinMode(pirPin, INPUT);
      digitalWrite(pirPin, LOW);
      pinMode(motorPin, OUTPUT);  
                                  
      pinMode(redPin1, OUTPUT);
      pinMode(yellowPin1, OUTPUT);
      pinMode(redPin2, OUTPUT);
      pinMode(yellowPin2, OUTPUT);
      
    }
     
    void loop()
    {  readPIR(); 
      if (personDetected == true){
      personIsThere();     }   
      
             
      else{
        candleFlicker();
    }
    
  }
      
      
    
    
    void candleFlicker()
    {
      int red = random(120);
      int yellow = random(120) + 135;
      setColor(red, yellow);
      delay(random(500));
    }
    
    void personIsThere()
    {
      int red = 255;
      int yellow = 0;
      setColor(red, yellow);
      delay(random(100));
    }
     
    void setColor(int red, int yellow)
    {      
      analogWrite(redPin1, red);
      analogWrite(yellowPin1, yellow);   
     analogWrite(redPin2, red);
      analogWrite(yellowPin2, yellow); 
     analogWrite(motorPin, red);  
    }
    
    
    void readPIR(){

     if(digitalRead(pirPin) == HIGH){
       personDetected = true;   
       if(lockLow){  
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50);         
         }         
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){       
       personDetected = false;   //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           digitalWrite(motorPin, LOW);
           }
       }
  }
