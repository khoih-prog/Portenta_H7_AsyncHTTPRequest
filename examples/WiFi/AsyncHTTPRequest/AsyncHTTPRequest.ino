/****************************************************************************************************************************
  AsyncHTTPRequest.ino - Dead simple AsyncHTTPRequest Portenta_H7

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
//************************************************************************************************************
//
// There are scores of ways to use AsyncHTTPRequest.  The important thing to keep in mind is that
// it is asynchronous and just like in JavaScript, everything is event driven.  You will have some
// reason to initiate an asynchronous HTTP request in your program, but then sending the request
// headers and payload, gathering the response headers and any payload, and processing
// of that response, can (and probably should) all be done asynchronously.
//
// In this example, a Ticker function is setup to fire every 5 seconds to initiate a request.
// Everything is handled in AsyncHTTPRequest without blocking.
// The callback onReadyStateChange is made progressively and like most JS scripts, we look for
// readyState == 4 (complete) here.  At that time the response is retrieved and printed.
//
// Note that there is no code in loop().  A code entered into loop would run oblivious to
// the ongoing HTTP requests.  The Ticker could be removed and periodic calls to sendRequest()
// could be made in loop(), resulting in the same asynchronous handling.
//
// For demo purposes, debug is turned on for handling of the first request.  These are the
// events that are being handled in AsyncHTTPRequest.  They all begin with Debug(nnn) where
// nnn is the elapsed time in milliseconds since the transaction was started.
//
//*************************************************************************************************************

#include "defines.h"

#define PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN_TARGET      "Portenta_H7_AsyncHTTPRequest v1.4.2"
#define PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN             1004002

// Uncomment for certain HTTP site to optimize
//#define NOT_SEND_HEADER_AFTER_CONNECTED        true

// Seconds for timeout, default is 3s
#define DEFAULT_RX_TIMEOUT           5

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <Portenta_H7_AsyncHTTPRequest.h>         // https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest

AsyncHTTPRequest request;

void sendRequest()
{
  static bool requestOpenResult;

  if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone)
  {
    //requestOpenResult = request.open("GET", "http://worldtimeapi.org/api/timezone/Europe/London.txt");
    requestOpenResult = request.open("GET", "http://worldtimeapi.org/api/timezone/America/Toronto.txt");
    //requestOpenResult = request.open("GET", "http://213.188.196.246/api/timezone/America/Toronto.txt");

    if (requestOpenResult)
    {
      Serial.println("Request sent");

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

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("Local IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  Serial.print("\nStart AsyncHTTPRequest on ");
  Serial.println(BOARD_NAME);
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

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");

    // don't continue
    while (true);
  }

  Serial.print(F("Connecting to SSID: "));
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);

  delay(1000);

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED)
  {
    delay(500);

    // Connect to WPA/WPA2 network
    status = WiFi.status();
  }

  printWifiStatus();

  ///////////////////////////////////

  request.setDebug(false);

  request.onReadyStateChange(requestCB);
}

void sendRequestRepeat()
{
  static unsigned long sendRequest_timeout = 0;

#define SEND_REQUEST_INTERVAL     10000L

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
