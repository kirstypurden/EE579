//Code adapted from example at https://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/

#******Define the Arduino pins that the ode will use*************
#define trigPin 13 #pin to connect to trigger of sensor (sensor transmits when trig high)
#define echoPin 12 #pin to connect to echo of sensor (echo recieves the reflected waves)
#define led 11 #pin to set the red led high when something is too close to the sensor 
#define led2 10 #pin to set the green led high when something is a good distance from the sensor

#*****Set-up the arudino for use**********
void setup() 
{
  #set up serial
  Serial.begin (9600); 
  #set up the selected pins to input/output as appropraite
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

#*****Code to continuously read from sensor*******
void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  //initially, set trig low (not transmitting)
  delayMicroseconds(2); //wait for this to happen
  
  digitalWrite(trigPin, HIGH); //now set it high (start transmitting)
  delayMicroseconds(10); //give it time to transmit the 8 cycles it wants to do 
  
  digitalWrite(trigPin, LOW); //set it low again to stop transmitting
  
  duration = pulseIn(echoPin, HIGH); //see how long it takes for the echo pin to receive something
  
  distance = (duration/2) / 29.1; //from datasheet, to get distance in cm need to (time/58), which can also be represented as (time/2)/29
  
  if (distance < 20) # if something is within a certain distance of the sensor
  {
	#Do something
	#in this case, we turn on the red led, and turn the green LED off
    digitalWrite(led,HIGH); //red led high
	digitalWrite(led2,LOW); //green led low
	#Later this will interact with the motors of the car to get it to slow down/stop/act appropriately 
  }
  else #if it's a safe distance away 
  {
	#continue as normal
	#in this case, we turn on the green led and turn the red LED off
    digitalWrite(led,LOW); // red led low
    digitalWrite(led2,HIGH); //green led high
	#Later this will keep the car moving as normal
  }
  
  if (distance >= 400 || distance <= 0) # if the distance from the sensor is outside the range. Range of sensor is between 2cm and 4m
  {
    Serial.println("Out of range");
	#later might want to split this
	#if it's greater than the range of the sensor, that's ok and we can continue until something is in range
	#but if it's <=0 then something is wrong with the sensor reading and we might need to handle an error
  }
  else 
  {
    Serial.print(distance); //display the distance on the serial monitor
    Serial.println(" cm");
  }
  delay(200); //wait a short period of time before starting again
}
