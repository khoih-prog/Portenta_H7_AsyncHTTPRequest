/****************************************************************************************************************************
  multiFileProject.ino

  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet or Murata WiFi

  Portenta_H7_AsyncHTTPRequest is a library for the Portenta_H7 with with Vision-Shield Ethernet Ethernet or Murata WiFi

  Based on and modified from asyncHTTPrequest Library (https://github.com/boblemaire/asyncHTTPrequest)

  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#if !( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
	#error This code is intended to run on the Portenta_H7 platform! Please check your Tools->Board setting.
#endif

#define PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN_TARGET      "Portenta_H7_AsyncHTTPRequest v1.4.2"
#define PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN             1004002

// Uncomment for certain HTTP site to optimize
//#define NOT_SEND_HEADER_AFTER_CONNECTED        true

#include "multiFileProject.h"

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "Portenta_H7_AsyncHTTPRequest.h"

void setup()
{
	Serial.begin(115200);

	while (!Serial && millis() < 5000);

	Serial.println("\nStart multiFileProject");
	Serial.println(PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION);

#if defined(PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN)

	if (PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_INT < PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN)
	{
		Serial.print("Warning. Must use this example on Version equal or later than : ");
		Serial.println(PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN_TARGET);
	}

#endif
}

void loop()
{
	// put your main code here, to run repeatedly:
}
