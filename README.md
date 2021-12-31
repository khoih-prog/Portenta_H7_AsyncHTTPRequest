# Portenta_H7_AsyncHTTPRequest

[![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncHTTPRequest.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncHTTPRequest)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Portenta_H7_AsyncHTTPRequest.svg)](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Portenta_H7_AsyncHTTPRequest.svg)](http://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/issues)

---
---

## Table of Contents


* [Why do we need the new Async Portenta_H7_AsyncHTTPRequest library](#why-do-we-need-this-async-Portenta_H7_AsyncHTTPRequest-library)
  * [Features](#features)
  * [Supports](#supports)
  * [Principles of operation](#principles-of-operation)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Portenta_H7 boards using Arduino IDE in Linux](#1-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [2. To fix compile error relating to dns_gethostbyname and LwIP stack](#2-to-fix-compile-error-relating-to-dns_gethostbyname-and-lwip-stack)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error) 
* [Examples](#examples)
  * [1. For Vision-shield Ethernet](#1-for-Vision-shield-Ethernet)
    * [1. AsyncHTTPRequest](examples/Ethernet/AsyncHTTPRequest)
    * [2. AsyncCustomHeader](examples/Ethernet/AsyncCustomHeader)
    * [3. AsyncDweetGet](examples/Ethernet/AsyncDweetGet)
    * [4. AsyncDweetPost](examples/Ethernet/AsyncDweetPost)
    * [5. AsyncSimpleGET](examples/Ethernet/AsyncSimpleGET)
    * [6. AsyncWebClientRepeating](examples/Ethernet/AsyncWebClientRepeating)
  * [2. For Murata WiFi](#2-for-Murata-WiFi)
    * [1. AsyncHTTPRequest](examples/WiFi/AsyncHTTPRequest)
    * [2. AsyncCustomHeader](examples/WiFi/AsyncCustomHeader)
    * [3. AsyncDweetGet](examples/WiFi/AsyncDweetGet)
    * [4. AsyncDweetPost](examples/WiFi/AsyncDweetPost)
    * [5. AsyncSimpleGET](examples/WiFi/AsyncSimpleGET)
    * [6. AsyncWebClientRepeating](examples/WiFi/AsyncWebClientRepeating)
* [Example AsyncHTTPRequest](#example-asynchttprequest)
  * [1. File AsyncHTTPRequest.ino](#1-file-asynchttprequestino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. AsyncHTTPRequest running on PORTENTA_H7_M7 WiFi](#1-asynchttprequest-running-on-PORTENTA_H7_M7-WiFi)
  * [2. AsyncDweetPOST running on PORTENTA_H7_M7 WiFi](#2-AsyncDweetPOST-running-on-PORTENTA_H7_M7-WiFi)
  * [3. AsyncWebClientRepeating running on PORTENTA_H7_M7 WiFi](#3-AsyncWebClientRepeating-running-on-PORTENTA_H7_M7-WiFi)
  * [4. AsyncCustomHeader running on PORTENTA_H7_M7 Ethernet](#4-AsyncCustomHeader-running-on-PORTENTA_H7_M7-Ethernet)
  * [5. AsyncWebClientRepeating running on PORTENTA_H7_M7 Ethernet](#5-AsyncWebClientRepeating-running-on-PORTENTA_H7_M7-Ethernet)
  * [6. AsyncSimpleGET running on PORTENTA_H7_M7 Ethernet](#6-AsyncSimpleGET-running-on-PORTENTA_H7_M7-Ethernet)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License and credits](#license-and-credits)
* [Copyright](#copyright)

---
---

## Why do we need this Async [Portenta_H7_AsyncHTTPRequest library](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest)

### Features

1. Asynchronous HTTP Request library for Portenta_H7 using `Murata WiFi` or `Vision-shield Ethernet`. 
2. Providing a subset of HTTP.
3. Relying on on **[`Khoi Hoang's Portenta_H7_AsyncTCP`](https://github.com/khoih-prog/Portenta_H7_AsyncTCP)**
4. Methods similar in format and usage to XmlHTTPrequest in Javascript.

### Supports

1. **GET, POST, PUT, PATCH, DELETE and HEAD**
2. Request and response headers
3. Chunked response
4. Single String response for short (<~5K) responses (heap permitting).
5. Optional onData callback.
6. Optional onReadyStatechange callback.

### Principles of operation

This library adds a simple HTTP layer on top of the [`Portenta_H7_AsyncTCP`](https://github.com/khoih-prog/Portenta_H7_AsyncTCP) library to **facilitate REST communication from a Client to a Server**. The paradigm is similar to the XMLHttpRequest in Javascript, employing the notion of a ready-state progression through the transaction request.

**Synchronization can be accomplished using callbacks on ready-state change, a callback on data receipt, or simply polling for ready-state change**. Data retrieval can be incremental as received, or bulk retrieved when the transaction completes provided there is enough heap to buffer the entire response.

The underlying buffering uses a new xbuf class. It handles both character and binary data. Class xbuf uses a chain of small (64 byte) segments that are allocated and added to the tail as data is added and deallocated from the head as data is read, achieving the same result as a dynamic circular buffer limited only by the size of heap. The xbuf implements indexOf and readUntil functions.

For short transactions, buffer space should not be an issue. In fact, it can be more economical than other methods that use larger fixed length buffers. Data is acked when retrieved by the caller, so there is some limited flow control to limit heap usage for larger transfers.

Request and response headers are handled in the typical fashion.

Chunked responses are recognized and handled transparently.

This library is based on, modified from:

1. [Bob Lemaire's asyncHTTPrequest Library](https://github.com/boblemaire/asyncHTTPrequest)

---

### Currently Supported Boards

1. **Portenta_H7 boards** such as Portenta_H7 Rev2 ABX00042, etc., using [**ArduinoCore-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed) using `Vision-shield Ethernet` or `Murata WiFi`

<p align="center">
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/blob/main/pics/Portenta_Vision.jpg">
</p>


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`ArduinoCore-mbed mbed_portenta core 2.6.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino **Portenta_H7** boards, such as **Portenta_H7 Rev2 ABX00042, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
 3. [`Portenta_H7_AsyncTCP library v1.3.0+`](https://github.com/khoih-prog/Portenta_H7_AsyncTCP) for Portenta_H7 using `Vision-shield Ethernet` or `Murata WiFi`. [To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncTCP.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncTCP)

---
---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `Portenta_H7_AsyncHTTPRequest`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncHTTPRequest.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncHTTPRequest) for more detailed instructions.

### Manual Install

1. Navigate to [Portenta_H7_AsyncHTTPRequest](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest) page.
2. Download the latest release `Portenta_H7_AsyncHTTPRequest-master.zip`.
3. Extract the zip file to `Portenta_H7_AsyncHTTPRequest-master` directory 
4. Copy the whole `Portenta_H7_AsyncHTTPRequest-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Portenta_H7_AsyncHTTPRequest** library](https://platformio.org/lib/show/12945/Portenta_H7_AsyncHTTPRequest) by using [Library Manager](https://platformio.org/lib/show/12945/Portenta_H7_AsyncHTTPRequest/installation). Search for Portenta_H7_AsyncHTTPRequest in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/2.5.2/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 2.5.2. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`

#### 2. To fix compile error relating to dns_gethostbyname and LwIP stack

**To be able to compile, run on Portenta_H7 boards**, you have to copy the whole [mbed_portenta Packages_Patches](Packages_Patches/arduino/hardware/mbed_portenta/2.5.2) directory into Arduino mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2). 

Supposing the Arduino mbed_portenta version is 2.5.2. These file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/libraries/SocketWrapper/src/MbedUdp.h`
- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/libraries/SocketWrapper/src/MbedUdp.cpp`
- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/cores/arduino/src/mbed/connectivity/lwipstack/include/lwipstack/lwipopts.h`

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can use

```
#include <Portenta_H7_AsyncHTTPRequest.h>           //https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest
```

in many files. But be sure to use the following `#include <Portenta_H7_AsyncHTTPRequest_Impl.h>` **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <Portenta_H7_AsyncHTTPRequest_Impl.h>      // https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest
```

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)


---
---

### Examples

#### 1. For Vision-shield Ethernet

 1. [AsyncHTTPRequest](examples/Ethernet/AsyncHTTPRequest)
 2. [AsyncCustomHeader](examples/Ethernet/AsyncCustomHeader)
 3. [AsyncDweetGet](examples/Ethernet/AsyncDweetGet)
 4. [AsyncDweetPost](examples/Ethernet/AsyncDweetPost)
 5. [AsyncSimpleGET](examples/Ethernet/AsyncSimpleGET)
 6. [AsyncWebClientRepeating](examples/Ethernet/AsyncWebClientRepeating)

#### 2. For Murata WiFi

 1. [AsyncHTTPRequest](examples/WiFi/AsyncHTTPRequest)
 2. [AsyncCustomHeader](examples/WiFi/AsyncCustomHeader)
 3. [AsyncDweetGet](examples/WiFi/AsyncDweetGet)
 4. [AsyncDweetPost](examples/WiFi/AsyncDweetPost)
 5. [AsyncSimpleGET](examples/WiFi/AsyncSimpleGET)
 6. [AsyncWebClientRepeating](examples/WiFi/AsyncWebClientRepeating)


---

### Example [AsyncHTTPRequest](examples/Ethernet/AsyncHTTPRequest)

Please take a look at other examples, as well.

#### 1. File [AsyncHTTPRequest.ino](examples/Ethernet/AsyncHTTPRequest/AsyncHTTPRequest.ino)

```cpp
#include "defines.h"

#define PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN_TARGET      "Portenta_H7_AsyncHTTPRequest v1.1.0"
#define PORTENTA_H7_ASYNC_HTTP_REQUEST_VERSION_MIN             1001000

#include <Portenta_H7_AsyncHTTPRequest.h>         // https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "Portenta_H7_AsyncHTTPRequest_Impl.h"    // https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest

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

void requestCB(void* optParm, AsyncHTTPRequest* request, int readyState) 
{
  (void) optParm;
  
  if (readyState == readyStateDone) 
  {
    Serial.println("\n**************************************");
    Serial.println(request->responseText());
    Serial.println("**************************************");
    
    request->setDebug(false);
  }
}

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  
  Serial.print("\nStart AsyncHTTPRequest on "); Serial.println(BOARD_NAME);
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
```

---

#### 2. File [defines.h](examples/Ethernet/AsyncHTTPRequest/defines.h)


```cpp
#ifndef defines_h
#define defines_h

#if !( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
  #error For Portenta_H7 only
#endif

#define PORTENTA_H7_ASYNC_HTTP_DEBUG_PORT       Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _PORTENTA_H7_ATCP_LOGLEVEL_             1
#define _ASYNC_HTTP_LOGLEVEL_                   1


#include <Portenta_Ethernet.h>
#include <Ethernet.h>
#warning Using Portenta_Ethernet lib for Portenta_H7.

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x14 },
};

#endif    //defines_h
```

---
---

### Debug Terminal Ouput Samples

#### 1. [AsyncHTTPRequest](examples/WiFi/AsyncHTTPRequest) running on PORTENTA_H7_M7 WiFi 

```
Start AsyncHTTPRequest on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.3.0
Portenta_H7_AsyncHTTPRequest v1.1.0
Using mac index = 15
Connected! IP address: 192.168.2.101
Request sent

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T21:59:53.472764-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640919593
utc_datetime: 2021-12-31T02:59:53.472764+00:00
utc_offset: -05:00
week_number: 52
**************************************
Request sent

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T22:00:52.995098-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640919652
utc_datetime: 2021-12-31T03:00:52.995098+00:00
utc_offset: -05:00
week_number: 52
**************************************
```

---

#### 2. [AsyncDweetPOST](examples/WiFi/AsyncDweetPOST) running on PORTENTA_H7_M7 WiFi 

```
Start AsyncDweetPOST on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.3.0
Portenta_H7_AsyncHTTPRequest v1.1.0
Connecting to SSID: HueNet1
SSID: HueNet1
Local IP Address: 192.168.2.94
signal strength (RSSI):-25 dBm

Making new POST request

**************************************
{"this":"succeeded","by":"dweeting","the":"dweet","with":{"thing":"pinA0-Read","created":"2021-10-15T04:17:43.768Z","content":{"sensorValue":88},"transaction":"34ca3083-054b-42ef-bcb0-91f7150dc680"}}
**************************************
"sensorValue":88
Value string: 88
Actual value: 88
```

---

#### 3. [AsyncWebClientRepeating](examples/WiFi/AsyncWebClientRepeating) running on PORTENTA_H7_M7 WiFi

```
Start AsyncWebClientRepeating on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.3.0
Portenta_H7_AsyncHTTPRequest v1.1.0
Connecting to SSID: HueNet1
SSID: HueNet1
Local IP Address: 192.168.2.94
signal strength (RSSI):-26 dBm

**************************************

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

**************************************
```

---

#### 4. [AsyncCustomHeader](examples/Ethernet/AsyncCustomHeader) running on PORTENTA_H7_M7 Ethernet

```
Start AsyncCustomHeader on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.3.0
Portenta_H7_AsyncHTTPRequest v1.1.0
Using mac index = 15
Connected! IP address: 192.168.2.87

Sending GET Request to http://worldtimeapi.org/api/timezone/America/Toronto.txt

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T22:03:51.798061-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640919831
utc_datetime: 2021-12-31T03:03:51.798061+00:00
utc_offset: -05:00
week_number: 52
**************************************
```

---

#### 5. [AsyncWebClientRepeating](examples/Ethernet/AsyncWebClientRepeating) running on PORTENTA_H7_M7 Ethernet


```
Start AsyncWebClientRepeating on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.3.0
Portenta_H7_AsyncHTTPRequest v1.1.0
Using mac index = 16
Connected! IP address: 192.168.2.87

**************************************

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

**************************************
```

---

#### 6. [AsyncSimpleGET](examples/Ethernet/AsyncSimpleGET) running on PORTENTA_H7_M7 Ethernet


```
Start AsyncSimpleGET on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.3.0
Portenta_H7_AsyncHTTPRequest v1.1.0
Using mac index = 7
Connected! IP address: 192.168.2.87

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T22:07:34.904535-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640920054
utc_datetime: 2021-12-31T03:07:34.904535+00:00
utc_offset: -05:00
week_number: 52
**************************************
Request sent

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T22:08:34.580278-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640920114
utc_datetime: 2021-12-31T03:08:34.580278+00:00
utc_offset: -05:00
week_number: 52
**************************************
```


---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level from 0 to 4

```cpp
#define PORTENTA_H7_ASYNC_HTTP_DEBUG_PORT       Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _PORTENTA_H7_ATCP_LOGLEVEL_             1
#define _ASYNC_HTTP_LOGLEVEL_                   1
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the `ESP32 / ESP8266 / STM32` core for Arduino.

Sometimes, the library will only work if you update the `ESP32 / ESP8266 / STM32` core to the latest version because I am using newly added functions.

---

### Issues ###

Submit issues to: [Portenta_H7_AsyncHTTPRequest issues](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/issues)

---

## TO DO

 1. Fix bug. Add enhancement
 2. Add many more examples.

---

## DONE

 1. Add support to Portenta_H7 using `Vision-shield Ethernet`
 2. Add support to `Murata` WiFi
 3. Add debugging features.
 4. Add PUT, PATCH, DELETE and HEAD besides GET and POST.
 5. Fix `multiple-definitions` linker error and weird bug related to `src_cpp`.
 6. Optimize library code by using `reference-passing` instead of `value-passing`

---
---

### Contributions and Thanks

This library is based on, modified, bug-fixed and improved from:

1. [Bob Lemaire's **asyncHTTPrequest Library**](https://github.com/boblemaire/asyncHTTPrequest) to use the better **asynchronous** features of [`Portenta_H7_AsyncTCP`](https://github.com/khoih-prog/Portenta_H7_AsyncTCP).


<table>
  <tr>
    <td align="center"><a href="https://github.com/boblemaire"><img src="https://github.com/boblemaire.png" width="100px;" alt="boblemaire"/><br /><sub><b>⭐️ Bob Lemaire</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License and credits ###

- The library is licensed under [GPLv3](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/blob/master/LICENSE)

---

## Copyright

Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>

Copyright 2021- Khoi Hoang



