/****************************************************************************************************************************
  AsyncDweetGET.ino
  
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

/**
  Connects to dweet.io once every 1 minutes, sends a GET request and a request body.

  Shows how to use Strings to assemble path and parse content from response. 
  dweet.io expects: https://dweet.io/dweet/for/thingName

  For more on dweet.io, see https://dweet.io/play/ 
 * */

#include "defines.h"

// Select a test server address           
const char GET_ServerAddress[] = "dweet.io";

// use your own thing name here
String dweetName = "/dweet/for/currentSecond?second=";

#include <Portenta_H7_AsyncHTTPRequest.h>       // https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest

AsyncHTTPRequest request;

void sendRequest()
{ 
  static bool requestOpenResult;
  
  if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone)
  {      
    requestOpenResult = request.open("GET", (GET_ServerAddress + dweetName + String(millis()/1000)).c_str() );
    
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

void parseResponse(String responseText)
{
  /*
    Typical response is:
    {"this":"succeeded",
    "by":"getting",
    "the":"dweets",
    "with":[{"thing":"my-thing-name",
      "created":"2016-02-16T05:10:36.589Z",
      "content":{"sensorValue":456}}]}

    You want "content": numberValue
  */
  // now parse the response looking for "content":
  int labelStart = responseText.indexOf("content\":");
  // find the first { after "content":
  int contentStart = responseText.indexOf("{", labelStart);
  // find the following } and get what's between the braces:
  int contentEnd = responseText.indexOf("}", labelStart);
  String content = responseText.substring(contentStart + 1, contentEnd);
  
  Serial.println(content);

  // now get the value after the colon, and convert to an int:
  int valueStart = content.indexOf(":");
  String valueString = content.substring(valueStart + 1);
  int number = valueString.toInt();
  
  Serial.print("Value string: ");
  Serial.println(valueString);
  Serial.print("Actual value: ");
  Serial.println(number);
}

void requestCB(void* optParm, AsyncHTTPRequest* request, int readyState)
{
  (void) optParm;
  
  if (readyState == readyStateDone)
  {
    String responseText = request->responseText();
    
    Serial.println("\n**************************************");
    //Serial.println(request->responseText());
    Serial.println(responseText);
    Serial.println("**************************************");

    parseResponse(responseText);
      
    request->setDebug(false);
  }
}

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  
  Serial.print("\nStart AsyncDweetGET on "); Serial.println(BOARD_NAME);
  Serial.println(PORTENTA_H7_ASYNC_TCP_VERSION);
  Serial.println(PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION);

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
