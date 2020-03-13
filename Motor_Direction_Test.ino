//see here for source: https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/
//NOTE: "left" and "right" are relative terms when viewing car from above
//NOTE: "forward" denotes motor spinning towards target, v.v. for "backward"

// Left motor pins
//#define left_enable 9
#define left_1 8
#define left_2 7

//Right motor pins
//#define right_enable 3
#define right_1 5
#define right_2 4

/*
  MOTOR CONFIGURATION (Same for left and right)
    input 1   input 2   spin direction
      0         0           OFF
      1         0           FORWARD
      0         1           BACKWARD
      1         1           OFF
*/

void setup() {
  // Set all the motor control pins to outputs
  Serial.begin(9600);
  
  //pinMode(left_enable, OUTPUT);
  //pinMode(right_enable, OUTPUT);
  pinMode(left_1, OUTPUT);
  pinMode(left_2, OUTPUT);
  pinMode(right_1, OUTPUT);
  pinMode(right_2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, LOW);
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, LOW);
  delay(2000);
  //digitalWrite(left_enable, HIGH);
  //digitalWrite(right_enable, HIGH);
}

void loop() {
  directionControl();
  //delay(1000);
  //speedControl();
  //delay(1000);
}

// This function lets you control spinning direction of motors
void directionControl()
{
  // Set motors to maximum speed
  // For PWM possible values are 0 (absolute OFF) to 255 (max speed)
  //analogWrite(enable_left, 255);
  //analogWrite(right_enable, 255);

  // Turn on motor A & B
  digitalWrite(left_1, HIGH); //LEFT 1 0 >>> Forward mode
  digitalWrite(left_2, LOW);
  digitalWrite(right_1, HIGH);  //RIGHT 1 0 >>> Forward mode
  digitalWrite(right_2, LOW);
  Serial.print("forward");
  Serial.print("\n");
  delay(2000);
  
  // Now change motor directions
  digitalWrite(left_1, LOW);  //LEFT 0 1 >>> Backward mode
  digitalWrite(left_2, HIGH);
  digitalWrite(right_1, LOW); //RIGHT 0 1 >>> Backward mode 
  digitalWrite(right_2, HIGH);
  Serial.print("reverse");
  Serial.print("\n");
  delay(2000);

  // Turn off motors
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, LOW);
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, LOW);
  Serial.print("OFF");
  Serial.print("\n");
  delay(2000);
  
}
/*
// This function lets you control speed of the motors
void speedControl() {
  // Turn on motors
  digitalWrite(left_1, LOW); 
  digitalWrite(left_2, HIGH);
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, HIGH);
  
  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(enable_left, i);
    analogWrite(right_enable, i);
    delay(20);
  }
  
  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(enable_left, i);
    analogWrite(right_enable, i);
    delay(20);
  }
  
  // Now turn off motors
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, LOW);
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, LOW);
}
*/
