    #include <NewPing.h>

    #define enA 9
    #define enB 6        
    #define in1 5 
    #define in2 4 
    #define in3 2 
    #define in4 3 
 
    int TRIGGER_PINF = A2; 
    int ECHO_PINF = A3; 
    
    int TRIGGER_PINL = A0;
    int ECHO_PINL =A1;
    
    int TRIGGER_PINR = A4;
    int ECHO_PINR = A5;
    #define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
    
   NewPing sonarLeft(TRIGGER_PINL, ECHO_PINL, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
   NewPing sonarRight(TRIGGER_PINR, ECHO_PINR, MAX_DISTANCE);
   NewPing sonarFront(TRIGGER_PINF, ECHO_PINF, MAX_DISTANCE);

   unsigned int pingSpeed = 30; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
   unsigned long pingTimer;     // Holds the next ping time.


float oldLeftSensor, oldRightSensor, leftSensor, rightSensor, frontSensor, oldFrontSensor, lSensor, rSensor, fSensor;
    
     
    void setup()
    {
        Serial.begin(115200);
        pinMode(TRIGGER_PINF, OUTPUT); 
        pinMode(ECHO_PINF, INPUT);
        
        pinMode(TRIGGER_PINL, OUTPUT);
        pinMode(ECHO_PINL, INPUT);       
        
        pinMode(TRIGGER_PINR, OUTPUT);
        pinMode(ECHO_PINR, INPUT);
       
        pinMode(enA, OUTPUT);
        pinMode(enB, OUTPUT);
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        pinMode(in3, OUTPUT);
        pinMode(in4, OUTPUT);     
        delay(1000);
    }
    
    void loop()
    {
      readwall();
      rightwallfollow();
      //leftwallfollow();
     // in giá khoảng cách đến tường
      Serial.print(" Left : ");
      Serial.print(leftSensor);
      Serial.print(" cm ");
      Serial.print(" Right : ");
      Serial.print(rightSensor);
      Serial.print(" cm ");
      Serial.print(" Front : ");
      Serial.print(frontSensor);
      Serial.println(" cm ");
    }
       

  void readwall(){
  
     //leftSensor = sonarLeft.ping_median(TestNUM);     //accurate but slow
  //rightSensor = sonarRight.ping_median(TestNUM);     //accurate but slow
  //frontSensor = sonarFront.ping_median(TestNUM);     //accurate but slow

  //leftSensor = sonarLeft.convert_cm(leftSensor);
  //rightSensor = sonarRight.convert_cm(rightSensor);
  //frontSensor = sonarFront.convert_cm(frontSensor);

  lSensor = sonarLeft.ping_cm(); //ping in cm
  rSensor = sonarRight.ping_cm();
  fSensor = sonarFront.ping_cm();


  leftSensor = (lSensor + oldLeftSensor) / 2; //average distance between old & new readings to make the change smoother
  rightSensor = (rSensor + oldRightSensor) / 2;
  frontSensor = (fSensor + oldFrontSensor) / 2;


  oldLeftSensor = leftSensor; // save old readings for movment
  oldRightSensor = rightSensor;
  oldFrontSensor = frontSensor;
     
  }
    
void rightwallfollow(){
    if(frontSensor >6) 
         {  
           if(rightSensor >=6 && rightSensor< 10) 
             {               
               analogWrite(enA, 255);
               analogWrite(enB, 255);
           
               analogWrite(in1, 255);
               analogWrite(in2, 0);
               analogWrite(in3, 0);
               analogWrite(in4, 255);                                                        
             }
         
           if(rightSensor >=10)  
             {

               
               analogWrite(enA, 225);
               analogWrite(enB, 40);

               analogWrite(in1, 255);
               analogWrite(in2, 0);
               analogWrite(in3, 0);
               analogWrite(in4, 255);
                                         
             }
             
                 
           if(rightSensor <6)   
             {
               analogWrite(enA, 80);
               analogWrite(enB, 255);
           
               analogWrite(in1, 255);
               analogWrite(in2, 0);
               analogWrite(in3, 0);
               analogWrite(in4, 255);                  
             }
         }
        
       if(  rightSensor<20 && frontSensor <=8) turnleft();       
       if(leftSensor <=20 && rightSensor>20 && frontSensor <=8) turnright();   
       if(leftSensor >20 && rightSensor>20 && frontSensor <=8) turnleft(); 
       if(rightSensor <=20 && leftSensor>20 && frontSensor <=8) turnleft(); 
       if(rightSensor<=20 && leftSensor<=20 && frontSensor<=8) returnright();
}


void leftwallfollow(){
  if(frontSensor >8) 
    {  
         if(leftSensor >=7 && rightSensor< 10) 
             {               
               analogWrite(enA, 150);
               analogWrite(enB, 150);
           
               analogWrite(in1, 255);
               analogWrite(in2, 0);
               analogWrite(in3, 0);
               analogWrite(in4, 255);                                                        
             }
         
         if(leftSensor >=10)  
             {
               analogWrite(enA, 45);
               analogWrite(enB, 150);

               analogWrite(in1, 255);
               analogWrite(in2, 0);
               analogWrite(in3, 0);
               analogWrite(in4, 255);
                                         
             }
                         
        if(leftSensor <7)   
             {
               analogWrite(enA, 200);
               analogWrite(enB, 80);
           
               analogWrite(in1, 255);
               analogWrite(in2, 0);
               analogWrite(in3, 0);
               analogWrite(in4, 255);                  
             }
         }
        
       if( leftSensor<20 && frontSensor <=6) turnright();       
       if(leftSensor <=20 && rightSensor>20 && frontSensor <=6) turnright();   
       if(leftSensor >20 && rightSensor>20 && frontSensor <=6) turnleft(); 
       if(rightSensor <=20 && leftSensor>20 && frontSensor <=6) turnleft(); 
       if(rightSensor<=20 && leftSensor<=20 && frontSensor<=6) returnleft();
}


    void turnleft() 
      {   
        analogWrite(enA,250);
        analogWrite(enB,250);

        analogWrite(in1, 0);
        analogWrite(in2, 255);
        analogWrite(in3, 0);
        analogWrite(in4, 255);          
        delay(100);   
      }
    
    void turnright() 
      {
        analogWrite(enA, 140);
        analogWrite(enB, 140);

        analogWrite(in1, 255);
        analogWrite(in2, 0);
        analogWrite(in3, 255);
        analogWrite(in4, 0); 
        delay(100);              
      }
    
    void returnright()
      {    
        analogWrite(enA, 120);
        analogWrite(enB, 120);
           
        analogWrite(in1, 0);
        analogWrite(in2, 255);
        analogWrite(in3, 0);
        analogWrite(in4, 255);
        delay(600); 
         
      }   
  void returnleft(){
       analogWrite(enA, 120);
        analogWrite(enB, 120);
           
        analogWrite(in1, 0);
        analogWrite(in2, 255);
        analogWrite(in3, 0);
        analogWrite(in4, 255);
        delay(600); 
  }
