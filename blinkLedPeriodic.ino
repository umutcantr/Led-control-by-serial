/*** Define ***/
#define led 13

/*** Function Prototypes ***/
void blinkLed(void);
void readSerial(void);

/*** External variables ***/
 unsigned long previousTimeLed = millis();   
 unsigned long previousTimeLed1 = millis(); 
 long timeIntervalLed = 1000;
 
 int ledState = LOW;
 String incomingData;
 char START[6] = "start";
 char STOP[5] = "stop";
 char LED[4] = "led";
 char ON[3] = "on";
 char OFF[4] = "off";
 char delimiter = '=';
 int echoState = 1;

 char *ptr;

 int ledOnPeriod = 1000;      // led on period default 1 sec
 int ledOffPeriod = 1000;      // led off period default 1 sec

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
  if((currentTime - previousTimeLed > ledOffPeriod) && ledState == LOW) {    // waits for timeIntervalLed value without blocking
    previousTimeLed = currentTime;
    ledState = HIGH;
  }
  
  if((currentTime - previousTimeLed > ledOnPeriod) && ledState == HIGH) {    // waits for timeIntervalLed value without blocking
    previousTimeLed = currentTime;
    ledState = LOW;
  }
  digitalWrite(led, ledState);
}

void readSerial(void){
  if(Serial.available()){
    incomingData = Serial.readString();
    
    if(!strncmp(incomingData.c_str(), START, 5)){   // compare incomingData string  and "start" string first 5 character.
      echoState = 1;             // echo incomingData string
    }
    else if(!strncmp(incomingData.c_str(), STOP, 4)){   // compare incomingData string  and "stop" string first 4 character.
      ledOnPeriod = 1000;                          // set led on period 
      ledOffPeriod = 1000;                         // set led off period 
      echoState = 0;
    }
    else if(strstr(incomingData.c_str(), LED)){   // compare incomingData string  and "stop" string first 4 character.
      if(strstr(incomingData.c_str(), ON)){
        ptr = strchr(incomingData.c_str(), delimiter);
        ledOnPeriod = atoi(ptr+1);
      }
      else if(strstr(incomingData.c_str(), OFF)){
        ptr = strchr(incomingData.c_str(), delimiter);
        ledOffPeriod = atoi(ptr+1);
      }
    }
    if(echoState){
      Serial.print(incomingData);
    }
  }
}
