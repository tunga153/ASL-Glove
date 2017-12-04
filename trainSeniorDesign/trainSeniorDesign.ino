const int FLEX_PIN_THUMB = A0;
const int FLEX_PIN_POINTER_TOP = A1;
const int FLEX_PIN_POINTER_MIDDLE = A2;
const int FLEX_PIN_MIDDLE_TOP = A3;
const int FLEX_PIN_MIDDLE_MIDDLE = A4;
const int FLEX_PIN_RING_TOP = A5;
const int FLEX_PIN_RING_MIDDLE = A6;
const int FLEX_PIN_PINKY_TOP = A7;
const int LEFT_TILT_SENSOR = 2;
const int RIGHT_TILT_SENSOR = 3;

const float VCC = 4.86; // Measured voltage of Ardunio 5V line
const float R_DIV = 33000.0; // Measured resistor value

void setup()
{
  Serial.begin(9600);
  pinMode(FLEX_PIN_THUMB, INPUT);
  pinMode(FLEX_PIN_POINTER_TOP, INPUT);
  pinMode(FLEX_PIN_POINTER_MIDDLE, INPUT);
  pinMode(FLEX_PIN_MIDDLE_TOP, INPUT);
  pinMode(FLEX_PIN_MIDDLE_MIDDLE, INPUT);
  pinMode(FLEX_PIN_RING_TOP, INPUT);
  pinMode(FLEX_PIN_RING_MIDDLE, INPUT);
  pinMode(FLEX_PIN_PINKY_TOP, INPUT);
  pinMode(LEFT_TILT_SENSOR, INPUT);
  pinMode(RIGHT_TILT_SENSOR, INPUT);
}

void loop()
{  
  
  Serial.print(String(getResistorValue(FLEX_PIN_THUMB)));
  Serial.print(String(","));
  Serial.print(String(getResistorValue(FLEX_PIN_POINTER_TOP)));
  Serial.print(String(","));
  Serial.print(String(getResistorValue(FLEX_PIN_POINTER_MIDDLE)));
  Serial.print(String(","));
  Serial.print(String(getResistorValue(FLEX_PIN_MIDDLE_TOP)));
  Serial.print(String(","));
  Serial.print(String(getResistorValue(FLEX_PIN_MIDDLE_MIDDLE)));
  Serial.print(String(","));
  Serial.print(String(getResistorValue(FLEX_PIN_RING_TOP)));
  Serial.print(String(","));
  Serial.print(String(getResistorValue(FLEX_PIN_RING_MIDDLE)));
  Serial.print(String(","));
  Serial.print(String(getResistorValue(FLEX_PIN_PINKY_TOP)));
  Serial.print(String(","));
  Serial.print(String(getBinaryTiltSensor(LEFT_TILT_SENSOR)));
  Serial.print(String(","));
  Serial.print(String(getBinaryTiltSensor(RIGHT_TILT_SENSOR)));
  Serial.print(String(","));
  Serial.print(String(3));
  
  Serial.println();


  delay(500);
}

float getResistorValue(int pin)
{
  int flexADC = analogRead(pin);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  return flexR;
}

int getBinaryTiltSensor(int pin)
{
  //return 1;
  if (digitalRead(pin) == HIGH) {
    return 1;
  } else {
    return 0;
  }
}


