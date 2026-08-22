const int fan_control_pin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(fan_control_pin, OUTPUT);
  
  // Start the fan at 0% (off) by default
  analogWrite(fan_control_pin, 0);
  
  Serial.println("--- Fan Speed Controller Ready ---");
  Serial.println("Fan is currently at 0%.");
  Serial.println("Type a percentage (0-100) or 'stop' to turn it off:");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming string and strip any spaces or newline characters
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toLowerCase(); // Makes it case-insensitive so "STOP" or "Stop" works too

    // Check if the user typed "stop"
    if (input == "stop") {
      analogWrite(fan_control_pin, 0);
      Serial.println("-> Fan stopped (0%).");
      Serial.println("Enter next percentage (0-100) or 'stop':");
    } 
    else {
      // Otherwise, try to convert the text to a number
      int percent = input.toInt();
      
      // Keep the percentage safely between 0 and 100
      percent = constrain(percent, 0, 100);

      // Map 0-100% to Arduino's 8-bit PWM range (0 to 255)
      int pwmValue = map(percent, 0, 100, 0, 255);

      // Send the signal to the fan
      analogWrite(fan_control_pin, pwmValue);

      // Print confirmation back to the terminal
      Serial.print("-> Fan speed set to: ");
      Serial.print(percent);
      Serial.print("% (PWM: ");
      Serial.print(pwmValue);
      Serial.println(")");
      Serial.println("Enter next percentage (0-100) or 'stop':");
    }
  }
}