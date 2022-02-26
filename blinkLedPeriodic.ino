/*** Define ***/
#define led 13

/*** Function Prototypes ***/
void blinkLed(void);
void readSerial(void);

/*** External variables ***/
 unsigned long previousTimeLed = millis();   
 long timeIntervalLed = 1000;
 
 int ledState;
 String incomingData;
 char START[6] = "start";

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  blinkLed();      // task for blink led 1 sec period
  readSerial();    // read incoming data and echo data for "start" command
}


void blinkLed(){
  unsigned long currentTime = millis();
  if(currentTime - previousTimeLed > timeIntervalLed) {    // waits for timeIntervalLed value without blocking
    previousTimeLed = currentTime;
    
    if (ledState == HIGH) ledState = LOW;
    else                  ledState = HIGH; 
    
    digitalWrite(led, ledState);
    }
}

void readSerial(void){
  if(Serial.available()){
    incomingData = Serial.readString();
    
    if(!strncmp(incomingData.c_str(), START, 5)){   // compare incomingData string  and "start" string first 5 character.
      Serial.println(incomingData);                 // echo incomingData string
    }
  }
}
