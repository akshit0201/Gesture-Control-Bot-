
#include <VirtualWire.h>

int xPin=0;
int yPin=1;

int ledPin=13;//led on pin 13 is ON except when transmitter is parallel to the ground

void setup() 
{
  vw_setup(2000);//Bits per second
  pinMode(ledPin,OUTPUT);
  //Serial.begin(9600);//Initialise the serial connection debugging
}

void loop() 
{
  int xval=analogRead(xPin);
  int yval=analogRead(yPin);
  
  //Serial.print("xval=");
  //Serial.println(xval);
  
  //Serial.print("yval=");
  //Serial.println(yval); 
  
  //delay(1000); //used to display values after 1s delay
  
  //Serial.print("\n");
  
  if ((xval>240 && xval<330) && (yval>220 && yval<320)) //stationary or stop(transmitter parallel to ground)
  {
    digitalWrite(ledPin,LOW);
    send("s");
  } 
  else 
  { 
    if ((xval>370 && xval<420) && (yval>370 && yval<426)) //forward(transmitter tilted forward)
    {
      digitalWrite(ledPin,HIGH);
      send("f");
      
    }
    if ((xval>285 && xval<350) && (yval>265 && yval<335)) //backward(transmitter tilted backward)
    {
      digitalWrite(ledPin,HIGH);
      send("a");
      
    }
    if ((xval>285 && xval<340) && (yval>285 && yval<330)) //left(transmitter tilted to left)
    {
      digitalWrite(ledPin,HIGH);
      send("l");
     }
     if ((xval>350 && xval<410) && (yval>340 && yval<440))//right(transmitter tilted to right)
    {
      digitalWrite(ledPin,HIGH);
      send("r");
      
    }
  }
  //delay(1000);
  
}


void send(char *message)//send function definition
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}
