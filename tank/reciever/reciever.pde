
#define DISTANCE 0

#define LEFT_FOR 6
#define LEFT_REV 5

#define RIGHT_FOR 10
#define RIGHT_REV 9

#define LEFT_TRACK 'l'
#define RIGHT_TRACK 'r'
#define NO_TRACK ' '

#define MSG_END 'e'

char msg_track = ' '; // track the current serial message is controlling
char msg_buffer[6]; // -255e
char *msg;
int msg_value;

void setup()
{
  Serial.begin(9600);
}

void update_track(char track, int value)
{
  byte forward, reverse;
  if (track == LEFT_TRACK)
  {
    forward = LEFT_FOR;
    reverse = LEFT_REV;
  }
  else
  {
    forward = RIGHT_FOR;
    reverse = RIGHT_REV;
  }
  analogWrite(forward, 0);
  analogWrite(reverse, 0);
  
  if (value > 0)
  {
    analogWrite(forward, value);
  }
  else
  {
    analogWrite(reverse, abs(value));
  }
}

void loop()
{ 
  
  while (Serial.available() > 0)
  {
    char data = Serial.read();
    if (data == RIGHT_TRACK || data == LEFT_TRACK)
    {
      //start of new message
      msg_track = data;
      msg = msg_buffer;
      *msg = 0;
    }
    else
    {
      if (data == MSG_END)
      {
        //perform command
        if (msg_track != NO_TRACK)
        {
          msg_value = atoi(msg_buffer);
          update_track(msg_track, msg_value);
          msg_track = NO_TRACK;
        }
      }
      else
      {
        //append data to message buffer
        *msg = data;
        msg ++;
        *msg = 0;
      }
    }
  }
}

