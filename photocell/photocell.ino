/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground
 
For more information see http://learn.adafruit.com/photocells */
 
int photocellPin = 15;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the analog resistor divider
int laserValue = 0; 
boolean tripped = false;
float lastTrippage = 0;
float tripPause = 50;

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);  
  laserValue = analogRead(photocellPin);  
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin);  
 
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);     // the raw analog reading
  if (millis() > (lastTrippage + tripPause)){
    if (photocellReading < laserValue - 100) {
      if(!tripped){
        Serial.println("tripped");
        usbMIDI.sendControlChange(1, 127, 1);
        lastTrippage = millis();
        tripped = true;
      }
    }else{
      tripped = false; 
    }
  }
  delay(10);
}
