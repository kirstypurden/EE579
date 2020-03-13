//adapted from : http://www.learningaboutelectronics.com/Articles/Color-sensor-circuit.php
//Connections to the Arduino Microcontroller
int taosOutPin = 9;
int LED = 7;
int input = 0;
int before, after = 0, 0;

void setup() 
{
  TCS3200setup();
  Serial.begin(115200); //Sets the data rate in bits per second (baud) for serial data transmission.
  //Not sure where this number comes from or why it needs to be that value specifically
  Serial.print("Setup");
  delay(100); //wait for it to set up (100 ms)
}

Serial.print("Pressl n to take no light reading."); //Print no light reading message
void loop() //loop forever
{ 

  if (Serial.available() > 0) 
  {
      input = Serial.read();

      //Take no light reading
      if(input == 110) //n
      {
          before = detectColor(taosOutPin);//see what colour we're detecting
          Serial.print("Pressl l to take no light reading."); //Print light reading message
      }

      //Take light reading and display result
      if(input==108) //input=l
      {
        after = detectColor(taosOutPin);
  
        int difference, percentage_drop;
        difference = before - after;
        percentage_drop = difference/before;

        Serial.print("Before: ");
        Serial.print(before);
        Serial.print("\n");
        Serial.print("After: ");
        Serial.print(after);
        Serial.print("\n");
        Serial.print("Percentage_drop: ");
        Serial.print(percentage_drop);
        Serial.print("\n");
  

        if(percentage_drop<0.15)
        {
          Serial.print("Skittle is black");
        }
        if(percentage_drop>30)
        {
          Serial.print("Skittle is white");
        }
        Serial.print("Pressl n to take no light reading."); //Print no light reading message
        //delay(1000); //wait 1000 ms before reading again
      }
  }
}


int detectColor(int taosOutPin)
{
  //setting for a delay to let the sensor sit for a moment before taking a reading
  int sensorDelay = 100;

  // create a var where the pulse reading from sensor will go
  float readPulse;

  // now take a measurement from the sensor, timing a low pulse on the sensor's "out" pin
  readPulse = pulseIn(taosOutPin, LOW, 80000);

  //if the pulseIn times out, it returns 0 and that throws off numbers. just cap it at 80k if it happens
  if(readPulse < .1)
  {
    Serial.print("Read pulse being capped :");
    Serial.print(readPulse);
    readPulse = 80000;
  }

  if(readPulse<80000) //if there's a valid reading
  {
     digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  
 // Serial.print("colour: ");
  //Serial.println(readPulse); //display result of colour sensor (the output frequency)
  return readPulse;
}


void TCS3200setup()
  {
    //pin that turns led on/off
    pinMode(LED,OUTPUT);
    
    //color response pin (only actual input from taos)
    pinMode(taosOutPin, INPUT);

   return;
  }
