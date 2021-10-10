const int trigPin = 2;
const int echoPin = 3;
const int red_light_pin = 11;
const int green_light_pin = 10;
const int blue_light_pin = 9;
const int cycleSpeed = 1;
int colourArray[3]; 
int colourState = 0;
bool isActive = false;
long duration = 0;
long distance  = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  colourArray[0]=255;
  colourArray[1]=0;
  colourArray[2]=0;
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  isActive = distance < 30;
  if (isActive) {
    rgbColour(255/2,0,255/2);
    Serial.println(1);
  }
  else {
    colourCycle();
    Serial.println(0);
  }
}

void rgbColour(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
void colourCycle()
{

  if (colourState == 0) {
    colourArray[2] = colourArray[2] + cycleSpeed;
    if (colourArray[2] >= 255) {
      colourState = 1;
    }
  }
  else if (colourState == 1) {
    colourArray[0] = colourArray[0] - cycleSpeed;
    if (colourArray[0] <= 0) {
      colourState = 2;
    }
  }
  else if (colourState == 2) {
    colourArray[1]=colourArray[1]+cycleSpeed;
    if (colourArray[1] >= 255) {
      colourState = 3;
    }
  }

  else if (colourState == 3) {
    colourArray[2] = colourArray[2] - cycleSpeed;
    if (colourArray[2] <= 0) {
      colourState = 4;
    }
  }
  else if (colourState == 4) {
    colourArray[0] = colourArray[0] + cycleSpeed;
    if (colourArray[0] >= 255) {
      colourState = 5;
    }
  }
  else if (colourState == 5) {
    colourArray[1] = colourArray[1] - cycleSpeed;
    if (colourArray[1] <=0) {
      colourState = 0;
    }
  }
  rgbColour(colourArray[0], colourArray[1], colourArray[2]);
}
