
int pinSoundSensor = 2; // Sound sensor input pin
int LED = 3; // LED output pin
int stateLED = LOW;
int clapCount = 0; // Count of detected claps
int previousState = LOW;
long time = 0;
long debounce = 200;
long delayTime = 0; // Time when the delay started
boolean delayActive = false; // Flag to track if delay is active

void setup() {
  pinMode(pinSoundSensor, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  int stateSound = digitalRead(pinSoundSensor); // Read the sound sensor

  // Detect a clap (assuming HIGH signal for clap)
  if (stateSound == HIGH && previousState == LOW && millis() - time > debounce) {
    clapCount++; // Increment clap count
    Serial.println("Clap detected! Count: " + String(clapCount)); // Debugging output
    time = millis(); // Reset debounce timer
  }

  // Check if two claps have been detected
  if (clapCount >= 2) {
    // Start the 1 second delay
    delayTime = millis();
    delayActive = true;
    clapCount = 0; // Reset clap count
    Serial.println("Delay started"); // Debugging output
  }

  // Check if the delay is active
  if (delayActive) {
    // Check if 1 second has passed since the delay started
    if (millis() - delayTime >= 1000) {
      // Toggle the LED state after the delay
      stateLED = (stateLED == HIGH) ? LOW : HIGH;
      digitalWrite(LED, stateLED);
      delayActive = false; // Reset the delay flag
      Serial.println("LED toggled! New state: " + String(stateLED)); // Debugging output
    }
  }

  previousState = stateSound; // Update previous state
}


