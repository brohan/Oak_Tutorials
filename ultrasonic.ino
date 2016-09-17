/*
 US-100 Ping distance sensor:
 VCC to Oak vcc
 GND x2 to Ground Rail to Oak Ground
 Trig to Oak Pin 2
 Echo to Oak Pin 4
 */


int trigPin = 2; // Trigger Pin
int echoPin = 4; // Echo Pin
int LEDPin = 1; // Onboard LED

unsigned long Time_Echo_us = 0; 
unsigned long Len_mm  = 0; 


char post_Distance[16]; //particle post variable

void setup() {
 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(LEDPin, OUTPUT); // Use LED indicator for visual feedback
 
}

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 

 //reset trig pin
 digitalWrite(trigPin, LOW); 
 delay(100); 

//send pulse
 digitalWrite(trigPin, HIGH);
 delay(10); 
 
 //stop sending signal
 digitalWrite(trigPin, LOW);
 
//listen for echo pulse
Time_Echo_us = pulseIn(echoPin, HIGH);  
 
// Calculating distance by pulse width
 Len_mm = (Time_Echo_us*34/100)/2;

//Send distance to cloud for viewing
 sprintf(post_Distance, "%04d", Len_mm); //convert int to string for Particle.publish
  Particle.publish("distance in mm:", post_Distance);
 
//use onboard LED for visual feedback              
 if((Len_mm < 3000) && (Len_mm > 1)) {   // Length effective range (1, 3000).
  
digitalWrite(LEDPin, HIGH); 
 }
 else { 
 digitalWrite(LEDPin, LOW); 
 }                           
   
 delay(1000);                                
 
}
