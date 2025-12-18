const int piezoPin = A0;        // Analog pin for the piezo sensor
const int ledPins[] = {2, 3, 4, 5, 6};  // Digital pins for LEDs
const int numLeds = 5;          // Total number of LEDs
int threshold = 100;             // Threshold to activate LEDs
int maxValue = 600;             // Adjust if values are too high
unsigned long lastActiveTime = 0;  // Stores the last time LEDs were activated
const int decayTime = 2;        // Time (ms) after which LEDs will turn off

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int piezoValue = analogRead(piezoPin);  // Read piezo sensor value

  if (piezoValue > threshold) {
    lastActiveTime = millis();  // Update the last activation time
    int ledCount = map(piezoValue, threshold, maxValue, 0, numLeds);
    ledCount = constrain(ledCount, 0, numLeds);

    // Turn on LEDs based on the piezo sensor value
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], (i < ledCount) ? HIGH : LOW);
    }
  } else if (millis() - lastActiveTime > decayTime) {
    // Turn off all LEDs if decay time has passed without new activation
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }

  Serial.println(piezoValue);  // Print sensor value for debugging
  delay(1);  // Small delay for stability
}