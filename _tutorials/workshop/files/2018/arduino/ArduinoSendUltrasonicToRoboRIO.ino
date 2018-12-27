#include <math.h>

// largely from https://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/
#define trigPin 13
#define echoPin 12

int order_of_mag;
bool not_ready;
String message = "";

void setup() {
  Serial.begin(9600); // must match baud rate on roboRIO open too.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  order_of_mag = 0;
  while(!Serial); // wait for it to be connected

//  not_ready = true;
//  String result = "";
//  while(not_ready)
//  {
//    if(Serial.available() > 0)
//    {
//      result += Serial.readString();
//    }
//    not_ready = !result.endsWith("ready");
//  }
}

void loop() {
  long duration;
  float distance;
  

  // write a 10 microsend high pulse to the trigger - make sure it was low for at least 2 before
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure time echoPin is HIGH in microS
  duration = pulseIn(echoPin, HIGH); 

  // average time to send and receive
  distance = (duration/2);
  // convert time to cm
  // s * ( 343 m/s) = s * 343 m
  // distance / 1000 * 353 = d cm
  // distance * .0353 = d cm
  distance = distance * .0353;

  int old_order_of_mag = order_of_mag;
  order_of_mag = log10(distance);

  // HC-SRO4 only rated for 2-400 cm, ignore values outside of that
  if (distance < 2 || distance > 400 || order_of_mag != old_order_of_mag)
  {
    distance = -1;
  }
  // begin transmission
  Serial.print('^');
  // transmit distance
  Serial.print(distance);
  // end transmission
  Serial.print('$');

  // hold up 10 mS - don't need to overflow the buffer.
  delay(250);
  //check_serial();
}

void check_serial()
{
  if(Serial.available() > 0)
  {
    message += Serial.readString();
  }

  if(message.endsWith("stop") )
  {
    String result = "";
    message = "";
    not_ready = true;    
    while(not_ready)
    {
      if(Serial.available() > 0)
      {
        result += Serial.readString();
      }
      not_ready = !result.endsWith("ready");
    }
  }
}


