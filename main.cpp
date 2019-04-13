#include "avr-core/Pins.hpp"
#include "avr-core/Util.hpp"
#include "avr-core/Servo.hpp"

#include <util/delay.h>
#include <avr/power.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

static char macAddress[18] = {0};
static char gatewayAddress[16] = {0};
static char ipAddress[16] = {0};

static inline void SendCommand(const char *str /*, char* buffer*/)
{
  Serial.write(str);
  Serial.write('\r');
  Serial.write('\n');

  //uint8_t c = Serial::Receive();
  //uint8_t i = 1;

  //buffer[0] = c;
}

struct retpointers
{
  char *command = 0;
  char *data = 0;
  char *status = 0;
};

static inline char Get()
{
  int c = Serial.read();
  while (c == -1)
  {
    c = Serial.read();
  }

  return (char)c;
}

static inline retpointers ReceiveCommand(char *buffer)
{
  uint8_t c = Get();
  uint8_t i = 1;

  buffer[0] = c;

  retpointers pointers;

  bool getCommand = true;

  while (true)
  {
    c = Get();
    buffer[i] = c;

    // Get the command that the AT firmware echos back.
    if (getCommand && i > 1 && buffer[i - 1] == '\r' && buffer[i] == '\n')
    {
      getCommand = false;
      pointers.command = buffer;
      pointers.data = buffer+i+1;

      buffer[i - 1] = 0;
      buffer[i] = 0;
    }

    
    // Check for OK status
    if (i > 3 && buffer[i - 3] == 'O' && buffer[i - 2] == 'K' && buffer[i - 1] == '\r' && buffer[i] == '\n')
    {
      buffer[i - 4] = 0;
      buffer[i - 5] = 0;

      if (buffer[i - 6] == '\n') buffer[i - 6] = 0;
      if (buffer[i - 7] == '\r') buffer[i - 7] = 0;

      pointers.status = buffer + (i - 3);
      buffer[i - 1] = 0;
      buffer[i] = 0;
      break;
    }

    // Check for ERROR status
    if (i > 6 && buffer[i - 6] == 'E' && buffer[i - 5] == 'R' && buffer[i - 4] == 'R' && buffer[i - 3] == 'O' && buffer[i - 2] == 'R' && buffer[i - 1] == '\r' && buffer[i] == '\n')
    {
      buffer[i - 7] = 0;
      buffer[i - 8] = 0;

      if (buffer[i - 9] == '\n') buffer[i - 9] = 0;
      if (buffer[i - 10] == '\r') buffer[i - 10] = 0;

      pointers.status = buffer + (i - 6);
      buffer[i - 1] = 0;
      buffer[i] = 0;
      break;
    }

    i++;
  }

  return pointers;
}

SoftwareSerial soft{2, 3};

void send(const char* str)
{
  SendCommand(str);

  char buffer[200] = {0};

  retpointers pointers = ReceiveCommand(buffer);

  soft.write("COMMAND: ");
  soft.write(pointers.command);
  soft.write('\n');
  soft.write("DATA: ");
  soft.write(pointers.data);
  soft.write('\n');
  soft.write("STATUS: ");
  soft.write(pointers.status);
  soft.write('\n');
  soft.write('\n');
}

// !!!MODIFIES str!!!
char* parseMac(char* str)
{
  char* p = str + 15;
  
  p[17] = 0;

  return p;
}

char* parseIp(char* str)
{
  char* p = str;
  p += 16;

  char* r = p;

  while(*r != '\"') {r++;}

  *r = 0;

  return p;
}

char* parseGateway(char* str)
{
  char* p = str;
  
  while (*p != '\n') {p++;}

  p += 22;

  char* r = p;

  while(*r != '\"') {r++;}

  *r = 0;

  return p;
}

void getMac()
{
SendCommand("AT+CIPAPMAC_CUR?");

  char buffer[200] = {0};

  retpointers pointers = ReceiveCommand(buffer);

  char* p = parseMac(pointers.data);

  soft.write("COMMAND: ");
  soft.write(pointers.command);
  soft.write('\n');
  soft.write("DATA: ");
  soft.write(p);
  soft.write('\n');
  soft.write("STATUS: ");
  soft.write(pointers.status);
  soft.write('\n');
  soft.write('\n');

  char* o = p;
  while (*o != 0)
  {
    if (*o >= 'a' && *o <= 'z')
    {
      *o = *o - 32;
    }
    o++;
  }

  strcpy(macAddress, p);
}

void getGateway()
{
  SendCommand("AT+CIPSTA_CUR?");

  char buffer[200] = {0};

  retpointers pointers2 = ReceiveCommand(buffer);
  char* i = parseIp(pointers2.data);
  char* p = parseGateway(pointers2.data);
  soft.write("COMMAND: ");
  soft.write(pointers2.command);
  soft.write('\n');
  soft.write("DATA: ");
  soft.write(p);
  soft.write('\n');
  soft.write("STATUS: ");
  soft.write(pointers2.status);
  soft.write('\n');
  soft.write('\n');

  strcpy(ipAddress, i);
  strcpy(gatewayAddress, p);
}

void connect()
{
  Serial.write("AT+CIPSTART=\"TCP\",\"");
  Serial.write(gatewayAddress);
  Serial.write("\",80");
  Serial.write('\r');
  Serial.write('\n');

  char buffer[200] = {0};

  retpointers pointers = ReceiveCommand(buffer);

  soft.write("COMMAND: ");
  soft.write(pointers.command);
  soft.write('\n');
  soft.write("DATA: ");
  soft.write(pointers.data);
  soft.write('\n');
  soft.write("STATUS: ");
  soft.write(pointers.status);
  soft.write('\n');
  soft.write('\n');
}

void addDevice()
{
  char buffer[250] = "GET /api/adddevice.php?mac=FF:FF:FF:FF:FF:FF";//"&ip=10.0.0.115&type=0&name=Hello%20World HTTP/1.1\r\n"
  
  char* p = buffer + (45 - 18);
  strcpy(p, macAddress);
  p = buffer + 44;
  strcpy(p, "&ip=");
  p += 4;
  strcpy(p, ipAddress);
  p += strlen(ipAddress);
  strcpy(p, "&type=0&name=HelloWorld HTTP/1.1\r\nHost: ");
  p += 40;
  strcpy(p, gatewayAddress);
  p += strlen(gatewayAddress);
  strcpy(p, "\r\n\r\n");
  p += 4;
  *p = 0;
  soft.write(buffer);

  uint16_t len = strlen(buffer);

  Serial.write("AT+CIPSEND=");
  {
    char buf[10] = {0};
    Serial.write(Util::UintToString<uint16_t>(len, buf, 10));
    soft.write(buf);
  }
  Serial.write('\r');
  Serial.write('\n');

  
  _delay_ms(500);

  Serial.write(buffer);
}

void setup()
{

  Serial.begin(9600);

  soft.begin(9600);

  _delay_ms(1000);

  // Station mode
  send("AT+CWMODE_CUR=1");

  send("AT+CIPAPMAC_CUR?");

  getMac();

  send("AT+CWJAP_CUR=\"CentralHub\",\"mynamejeff123\"");

  send("AT+CIPSTA_CUR?");

  getGateway();
  
  send("AT+CIPMUX=0");

  connect();

  addDevice();
}



void loop()
{
  soft.write(Get());
}