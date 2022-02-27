/*** Define ***/
#define led 13

/*** Function Prototypes ***/
void blinkLed(void);
void readSerial(void);
bool wait(int period, unsigned long *currentTime, unsigned long *previousTimeLed);

/*** External variables ***/

 int ledOnPeriod = 1000;                    // led on period default 1 sec
 int ledOffPeriod = 1000;                   // led off period default 1 sec

 
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  blinkLed();                               // task for blink led 1 sec period
  readSerial();                             // task for read incoming data and echo data for "start" command
}

// Task 1
void blinkLed(void){
   static unsigned long previousTimeLed = millis();      // set initial uc time   
   unsigned long currentTime;
   static int ledState = LOW;                            // led state default to LOW

  if(wait(ledOffPeriod, &currentTime, &previousTimeLed) && ledState == LOW) {    // check elapsed time and led state 
    previousTimeLed = currentTime;               // update previous time led value
    ledState = HIGH;
  }
  
  if(wait(ledOnPeriod, &currentTime, &previousTimeLed) && ledState == HIGH) {    // check elapsed time and led state 
    previousTimeLed = currentTime;               // update previous time led value
    ledState = LOW;
  }
  digitalWrite(led, ledState);                   // blink led
}

// Task 2
void readSerial(void){
 char buf[20];                              // incoming uart data
 char START[6] = "start";                   
 char STOP[5] = "stop";
 char LED[4] = "led";
 char ON[3] = "on";
 char OFF[4] = "off";
 char delimiter = '=';                      // delimiter of incoming data
 char *delimiterPtr;                        // points to delimiter in incoming data 
 int echoState = 1;                         // defualt to echo incoming data 
 
  if(Serial.available()){
    Serial.readBytesUntil('\n', buf, sizeof(buf)/sizeof(buf[0]));
    //Serial.println(buf);
    if(strstr(buf, START)){   // compare incomingData string  and "start" string first 5 character.
      echoState = 1;                                // echo incomingData string
    }
    else if(strstr(buf, STOP)){   // compare incomingData string  and "stop" string first 4 character.
      ledOnPeriod = 1000;                          // set led on period 
      ledOffPeriod = 1000;                         // set led off period 
      echoState = 0;
    }
    else if(strstr(buf, LED)){   // compare incomingData string  and "stop" string first 4 character.
      if(strstr(buf, ON)){
        delimiterPtr = strchr(buf, delimiter);
        ledOnPeriod = atoi(delimiterPtr+1);
      }
      else if(strstr(buf, OFF)){
        delimiterPtr = strchr(buf, delimiter);
        ledOffPeriod = atoi(delimiterPtr+1);
      }
    }
    if(echoState){
      Serial.println(buf);
    }
  }
  memset(buf, 0, sizeof(buf)/sizeof(buf[0]));
}

// if elapsed time bigger than period value return true, otherwise false
// takes wait period, previousTime and currentTime arguments
bool wait(int period, unsigned long *currentTime, unsigned long *previousTime){
  *currentTime = millis();
  if(*currentTime - *previousTime > period) return true;
  else                                          return false;
}
