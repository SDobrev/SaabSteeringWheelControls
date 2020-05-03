// Steering wheel buttons output voltages
const float voltageOffset = 0.2;
const float volDown = 0.7;
const float volUp = 1.2;
const float prev = 3.0;
const float next = 2.4;
const float src = 1.8;
const float mute = 3.6;

// Output digital pins. They trigger transistors with the right resistance for the Pioneer HU.
const int volDownPin = 5;
const int volUpPin = 6;
const int prevPin = 7;
const int nextPin = 8;
const int srcPin = 10;
const int mutePin = 9;

const int checkDuration = 10;
const int numberOfChecks = 3;
int lastPressedButton = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int pressedButton = getPressedButton();

  if (pressedButton > 0) {

    for ( int i = 0; i < numberOfChecks; i++) {

      if (getPressedButton() != pressedButton) {
        pressedButton = 0;

        return;
      }

      delay(checkDuration);
    }

    if (pressedButton > 0) {
      Serial.print("DigitalWrite = ");
      Serial.println(pressedButton);

      lastPressedButton = pressedButton;
      digitalWrite(pressedButton, HIGH);
    }
  }
  else {
    digitalWrite(lastPressedButton, LOW);
  }

  delay(checkDuration);
}

int getPressedButton() {

  int inputValue = analogRead(A3);
  float inputVoltage = inputValue * 5.0 / 1023;

  if (inputVoltage >= (volDown - voltageOffset) && inputVoltage <= (volDown + voltageOffset)) {
    return (volDownPin);
  }
  if (inputVoltage >= (volUp - voltageOffset) && inputVoltage <= (volUp + voltageOffset)) {
    return (volUpPin);
  }
  if (inputVoltage >= (prev - voltageOffset) && inputVoltage <= (prev + voltageOffset)) {
    return (prevPin);
  }
  if (inputVoltage >= (next - voltageOffset) && inputVoltage <= (next + voltageOffset)) {
    return (nextPin);
  }
  if (inputVoltage >= (src - voltageOffset) && inputVoltage <= (src + voltageOffset)) {
    return (srcPin);
  }
  if (inputVoltage >= (mute - voltageOffset) && inputVoltage <= (mute + voltageOffset)) {
    return (mutePin);
  }

  return (0);
}
