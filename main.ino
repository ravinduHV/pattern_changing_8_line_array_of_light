#include "relay.h"

using namespace std;

float time = 1000;
float weight;
int round_count;
int pins[] = {3,4,6,5,7,8,10,9};
const int relay_array_size = 8;
relay relay_array [relay_array_size];

void setup()
{
  Serial.begin(9600); 
  for (int i = 0; i < relay_array_size; i++)
  {
    relay_array[i].set_pin(pins[i]);
    if(i > 0)
    {
      relay_array[i-1].set_next_relay(&relay_array[i]);
    }
  } 
  relay_array[relay_array_size-1].set_next_relay(&relay_array[0]);
}


void loop()
{
  //pattern_1();
  pattern_2();
  pattern_3();
  pattern_4();
  reverse_pattern_1();
  reverse_pattern_2();
}


//Pattern 1 - blinking one by one 
void pattern_1()
{
  weight = 0.4;
  for (int i = 0; i < relay_array_size; i++)
  {
    relay_array[i].on();
    delay(time*weight);
    relay_array[i].off();
  }
}

//Pattern 2 - blink two by two
void pattern_2()
{
  weight = 0.4;
  round_count = 3;
  for(int i = 0; i < relay_array_size/2-1; i++)
  {
    relay_array[i].on();
    relay_array[i].next_relay()->on();
    relay_array[i+4].on();
    relay_array[i+4].next_relay()->on();

    delay(time*weight);
    relay_array[i].off();
    relay_array[i+4].off();

    if((i == relay_array_size/2 - 2) and round_count > 0)
      i = 0;
      round_count--;
  }
}

//Pattern 3
void pattern_3()
{
  weight = 0.5;
  for(int i = 0; i < relay_array_size; i++)
  {
    relay_array[i].on();
    relay_array[i].next_relay()->next_relay()->on();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->on();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->on();
    delay(time*weight);
    relay_array[i].off();
    relay_array[i].next_relay()->next_relay()->off();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->off();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->off();
  }
}

//Pattern 4 : modified pattern 3
void pattern_4()
{
  weight = 0.5;
  down_all();
  for(int i = 0; i < relay_array_size-1; i++)
  {
    relay_array[i].on();
    relay_array[i].next_relay()->next_relay()->on();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->on();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->on();
    delay(time*weight);
    relay_array[i].next_relay()->on();
    relay_array[i].next_relay()->next_relay()->next_relay()->on();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->on();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->on();
    delay(time*weight/2);
    relay_array[i].off();
    relay_array[i].next_relay()->next_relay()->off();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->off();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->off();
  }
}

//Reverse of pattern 1
void reverse_pattern_1()
{
  weight = 0.6;
  round_count = 3;
  up_all();
  for (int i = 0; i < relay_array_size && round_count > 0; i++)
  {
    relay_array[i].off();
    delay(weight*time);
    relay_array[i].on();
    if(i == relay_array_size -1)
    {
      i = -1;
      round_count--;
    }
  }
}

//Reverse of pattern 2
void reverse_pattern_2()
{
  weight = 3;
  //round_count = 3;
  
  up_all();

  for(int i = 0; i < relay_array_size; i++)
  {
    relay_array[i].off();
    relay_array[i].next_relay()->off();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->off();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->off();

    delay(time*weight);

    relay_array[i].on();
    relay_array[i].next_relay()->on();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->on();
    relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->on();

    //if((i == relay_array_size/2 - 2) and round_count > 0)
    //{
    //  i = -1;
    //  round_count--;
    //}
  }
}

void down_all()
{
  for (int i = 0; i < relay_array_size; i++)
  {
    relay_array[i].off();
  }
}

void up_all()
{
  for (int i = 0; i < relay_array_size; i++)
  {
    relay_array[i].on();
  }
}

