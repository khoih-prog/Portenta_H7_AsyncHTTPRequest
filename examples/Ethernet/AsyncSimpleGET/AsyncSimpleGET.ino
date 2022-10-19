/****************************************************************************************************************************
  AsyncSimpleGET_STM32.ino
  
  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet or Murata WiFi
  
  Portenta_H7_AsyncHTTPRequest is a library for the Portenta_H7 with with Vision-Shield Ethernet Ethernet or Murata WiFi
  
  Portenta_H7_AsyncHTTPRequest is a library for Portenta_H7
  
  Based on and modified from asyncHTTPrequest Library (https://github.com/boblemaire/asyncHTTPrequest)
  
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest
  
  Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.  
 *****************************************************************************************************************************/
 
#include "defines.h"

#define PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN_TARGET      "Portenta_H7_AsyncHTTPRequest v1.3.1"
#define PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN             1003001

// Select a test server address           
//char GET_ServerAddress[]    = "ipv4bot.whatismyipaddress.com/";
char GET_ServerAddress[]    = "http://worldtimeapi.org/api/timezone/America/Toronto.txt";

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <Portenta_H7_AsyncHTTPRequest.h>         // https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest

AsyncHTTPRequest request;

void sendRequest()
{
  static bool requestOpenResult;
  
  if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone)
  {
    requestOpenResult = request.open("GET", GET_ServerAddress);
    
    if (requestOpenResult)
    {
      // Only send() if open() returns true, or crash
      request.send();
    }
    else
    {
      Serial.println("Can't send bad request");
    }
  }
  else
  {
    Serial.println("Can't send request");
  }
}

void requestCB(void *optParm, AsyncHTTPRequest *request, int readyState)
{
  (void) optParm;

  if (readyState == readyStateDone)
  {
    AHTTP_LOGWARN(F("\n**************************************"));
    AHTTP_LOGWARN1(F("Response Code = "), request->responseHTTPString());

    if (request->responseHTTPcode() == 200)
    {
      Serial.println(F("\n**************************************"));
      Serial.println(request->responseText());
      Serial.println(F("**************************************"));
    }
  }
}

void setup() 
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  Serial.print("\nStart AsyncSimpleGET on "); Serial.println(BOARD_NAME);
  Serial.println(PORTENTA_H7_ASYNC_TCP_VERSION);
  Serial.println(PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION);

#if defined(PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN)
  if (PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_INT < PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN_TARGET);
  }
#endif
  
  ///////////////////////////////////
  
  // start the ethernet connection and the server
  // Use random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  // Use DHCP dynamic IP and random mac
  Ethernet.begin(mac[index]);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) 
  {
    Serial.println("No Ethernet found. Stay here forever");
    
    while (true) 
    {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  
  if (Ethernet.linkStatus() == LinkOFF) 
  {
    Serial.println("Not connected Ethernet cable");
  }

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());

  ///////////////////////////////////

  request.setDebug(false);
  
  request.onReadyStateChange(requestCB);
}
  
void sendRequestRepeat()
{
  static unsigned long sendRequest_timeout = 0;

#define SEND_REQUEST_INTERVAL     60000L

  // sendRequest every SEND_REQUEST_INTERVAL (60) seconds: we don't need to sendRequest frequently
  if ((millis() > sendRequest_timeout) || (sendRequest_timeout == 0))
  {
    sendRequest();
    
    sendRequest_timeout = millis() + SEND_REQUEST_INTERVAL;
  }
}

void loop()
{
  sendRequestRepeat();
}
