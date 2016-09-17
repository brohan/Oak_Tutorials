int calibrationTime = 30;        
long unsigned int lowIn;         
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  

int pirPin = 2; 
int ledPin = 1;


void setup(){
  
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate
    for(int i = 0; i < calibrationTime; i++){
      delay(1000);
      }
    delay(50);
  }

void loop(){

     if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, HIGH);
       Particle.publish("MOTION SENSOR", "Motion detected");
         if(lockLow){  
         lockLow = false;            
         delay(50);
         }         
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){       
       digitalWrite(ledPin, LOW);  

       if(takeLowTime){
        lowIn = millis();      
        takeLowTime = false;      
        }

       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           delay(50);
           }
       }
  }
