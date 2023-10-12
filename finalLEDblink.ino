#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX (change pin numbers as needed)

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int greenLED = 8;
int redLED = 9;

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Fingerprint sensor test");

  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Couldn't find a fingerprint sensor :(");
    while (1);
  }

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
}

void loop() {
  uint8_t p = getFingerprintID();
  delay(1000);
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    return p;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    return p;
  }

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    Serial.println("Fingerprint ID found!");
    return p;
  } else {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    Serial.println("Fingerprint not found");
    return p;
  }
}
