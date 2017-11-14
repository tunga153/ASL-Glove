const int FLEX_PIN_THUMB = A0; // Pin connected to voltage divider output
const int FLEX_PIN_POINTER_TOP = A1;
const int FLEX_PIN_POINTER_MIDDLE = A2;
const int FLEX_PIN_MIDDLE_TOP = A3;
const int FLEX_PIN_MIDDLE_MIDDLE = A4;
const int FLEX_PIN_RING_TOP = A5;
const int FLEX_PIN_RING_MIDDLE = A6;
const int FLEX_PIN_PINKY_TOP = A7;
const int FLEX_PIN_PINKY_MIDDLE = A8;

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.86; // Measured voltage of Ardunio 5V line
const float R_DIV = 50300.0; // Measured resistor value

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 12000.0; // resistance when straight
const float BEND_RESISTANCE = 65000.0; // resistance at 90 deg
//const float STRAIGHT_RESISTANCE = 8000.0; // resistance when straight
//const float BEND_RESISTANCE = 27000.0; // resistance at 90 deg

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
  pinMode(FLEX_PIN_PINKY_MIDDLE, INPUT);
}

void loop()
{  
  Serial.print("Code to Send: ");
  Serial.print(String(getBinary(FLEX_PIN_THUMB)));
  Serial.print(String(getBinary(FLEX_PIN_POINTER_TOP)));
  Serial.print(String(getBinary(FLEX_PIN_POINTER_MIDDLE)));
  Serial.print(String(getBinary(FLEX_PIN_MIDDLE_TOP)));
  Serial.print(String(getBinary(FLEX_PIN_MIDDLE_MIDDLE)));
  Serial.print(String(getBinary(FLEX_PIN_RING_TOP)));
  Serial.print(String(getBinary(FLEX_PIN_RING_TOP)));
  Serial.print(String(getBinary(FLEX_PIN_PINKY_TOP)));
  Serial.print(String(getBinary(FLEX_PIN_PINKY_TOP)));
  Serial.println();


  delay(1000);
}

int getBinary(int pin)
{
  int flexADC = analogRead(pin);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);

  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                    0, 90.0);

   if (angle < 45)
   {
    return 0;
   }
   else
   {
    return 1;
   }
}

int standardizeOutput() {

  int signalToSend = getBinary(FLEX_PIN_THUMB) << 16 | getBinary(FLEX_PIN_POINTER_TOP) << 14
  | getBinary(FLEX_PIN_POINTER_MIDDLE) << 12 | getBinary(FLEX_PIN_MIDDLE_TOP) << 10
  | getBinary(FLEX_PIN_MIDDLE_MIDDLE) << 8 | getBinary(FLEX_PIN_RING_TOP) << 6
  | getBinary(FLEX_PIN_RING_MIDDLE) << 4 | getBinary(FLEX_PIN_PINKY_TOP) << 2
  | getBinary(FLEX_PIN_PINKY_MIDDLE);
}

void printAngles(int pin)
{
  int flexADC = analogRead(pin);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  Serial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                    0, 90.0);
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();
}

