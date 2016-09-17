/*
 HC-SR04 with TCB0108 level shifter
 Oak VCC to level shifter VCCA + OE
 Oak GND to level shifter GND
 Oak Pin 2 to level shifter A1
 Oak Pin 4 to level shifter A2
 Oak VIN to level shifter VCCB
 Level Shifter VCCB to sensor VCC
 Level shifter B1 to sensor Echo
 Level shifter B2 to sensor Trig
 Level shifter GND to sensor GND
 */


int trigPin = 2; // Trigger Pin
int echoPin = 4; // Echo Pin
int LEDPin = 1; // Onboard LED

long duration; 
long inches; 


char post_Distance[8]; //particle post variable

void setup() {
 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(LEDPin, OUTPUT); // Use onboard LED as indicator
 
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
duration = pulseIn(echoPin, HIGH);  
 
// Calculating distance by pulse width
 inches = (duration/2) / 74;

//Send distance to cloud for viewing
 sprintf(post_Distance, "%03d", inches); //convert int to string for Particle.publish
  Particle.publish("distance:", post_Distance);
 
//use onboard LED for visual feedback              
 if((inches < 36) && (inches > 1)) {   // limit the distance from the sensor's overall range
  
digitalWrite(LEDPin, HIGH); 
 }
 else { 
 digitalWrite(LEDPin, LOW); 
 }                           
   
 delay(1000);                                
 
}
