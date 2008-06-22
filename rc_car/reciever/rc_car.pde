
#define POWER 8
#define STEER 9
#define DELAY 20


int powerDelay = 1500;
int steerDelay = 1500;

long lastUpdate;

int readingValue;
int readingIdent = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(POWER, OUTPUT);
  pinMode(STEER, OUTPUT);
  lastUpdate = millis();
}

void loop()
{
  while (Serial.available() > 0)
  {
    int value = Serial.read();
    switch (value)
    {
      case 't':
        readingIdent = POWER;
        readingValue = 0;
        break;
      case 's':
        readingIdent = STEER;
        readingValue = 0;
        break;
      case 'd':
        Serial.println("----------");
        Serial.println(steerDelay);
        Serial.println(powerDelay);
        break;
      case 'e':
        if (readingValue >= 1000 && readingValue <= 2000)
        {
          if (readingIdent == POWER)
          {
            powerDelay = readingValue;
          }
          if (readingIdent == STEER)
          {
            steerDelay = readingValue;
          }  
        }
        break;
        default:
          value = '0' - value;
          readingValue = (readingValue * 10) + abs(value);
          break;
    }
    if (millis() - lastUpdate > DELAY)
    {
      updateServo();
      lastUpdate = millis();
    }
  }

  if (millis() - lastUpdate > DELAY)
  {
    updateServo();
    lastUpdate = millis();
  }
}

void updateServo()
{
  digitalWrite(POWER, HIGH);
  delayMicroseconds(powerDelay);
  digitalWrite(POWER, LOW);
  digitalWrite(STEER, HIGH);
  delayMicroseconds(steerDelay);
  digitalWrite(STEER, LOW);
}
