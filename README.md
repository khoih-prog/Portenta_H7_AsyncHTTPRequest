# Portenta_H7_AsyncHTTPRequest Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncHTTPRequest.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncHTTPRequest)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Portenta_H7_AsyncHTTPRequest.svg)](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Portenta_H7_AsyncHTTPRequest.svg)](http://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Important Change from v1.2.0](#Important-Change-from-v120)
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
    * [1. AsyncHTTPRequest](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncHTTPRequest)
    * [2. AsyncCustomHeader](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncCustomHeader)
    * [3. AsyncDweetGet](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncDweetGet)
    * [4. AsyncDweetPost](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncDweetPost)
    * [5. AsyncSimpleGET](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncSimpleGET)
    * [6. AsyncWebClientRepeating](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncWebClientRepeating)
  * [2. For Murata WiFi](#2-for-Murata-WiFi)
    * [1. AsyncHTTPRequest](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncHTTPRequest)
    * [2. AsyncCustomHeader](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncCustomHeader)
    * [3. AsyncDweetGet](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncDweetGet)
    * [4. AsyncDweetPost](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncDweetPost)
    * [5. AsyncSimpleGET](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncSimpleGET)
    * [6. AsyncWebClientRepeating](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncWebClientRepeating)
  * [3. For Portenta_H7](#3-For-Portenta_H7)
    * [1. **multiFileProject**](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/multiFileProject) **New**
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

### Important Change from v1.2.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)


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
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/raw/main/pics/Portenta_Vision.jpg">
</p>


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`ArduinoCore-mbed mbed_portenta core 3.5.4+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino **Portenta_H7** boards, such as **Portenta_H7 Rev2 ABX00042, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
 3. [`Portenta_H7_AsyncTCP library v1.4.0+`](https://github.com/khoih-prog/Portenta_H7_AsyncTCP) for Portenta_H7 using `Vision-shield Ethernet` or `Murata WiFi`. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncTCP.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncTCP)

---
---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `Portenta_H7_AsyncHTTPRequest`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncHTTPRequest.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncHTTPRequest) for more detailed instructions.

### Manual Install

1. Navigate to [Portenta_H7_AsyncHTTPRequest](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest) page.
2. Download the latest release `Portenta_H7_AsyncHTTPRequest-main.zip`.
3. Extract the zip file to `Portenta_H7_AsyncHTTPRequest-main` directory 
4. Copy the whole `Portenta_H7_AsyncHTTPRequest-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Portenta_H7_AsyncHTTPRequest** library](https://registry.platformio.org/libraries/khoih-prog/Portenta_H7_AsyncHTTPRequest) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/Portenta_H7_AsyncHTTPRequest/installation). Search for Portenta_H7_AsyncHTTPRequest in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`

#### 2. To fix compile error relating to dns_gethostbyname and LwIP stack

**To be able to compile, run on Portenta_H7 boards**, you have to copy the whole [mbed_portenta Packages_Patches](Packages_Patches/arduino/hardware/mbed_portenta/3.4.1) directory into Arduino mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1). 

Supposing the Arduino mbed_portenta version is 3.4.1. These file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/libraries/SocketWrapper/src/MbedUdp.h`
- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/libraries/SocketWrapper/src/MbedUdp.cpp`
- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/cores/arduino/src/mbed/connectivity/lwipstack/include/lwipstack/lwipopts.h`

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```cpp
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "Portenta_H7_AsyncHTTPRequest.hpp"     //https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "Portenta_H7_AsyncHTTPRequest.h"           //https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest
```

Check the new [**multiFileProject** example](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/multiFileProject) for a `HOWTO` demo.

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)


---
---

### Examples

#### 1. For Vision-shield Ethernet

 1. [AsyncHTTPRequest](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncHTTPRequest)
 2. [AsyncCustomHeader](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncCustomHeader)
 3. [AsyncDweetGet](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncDweetGet)
 4. [AsyncDweetPost](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncDweetPost)
 5. [AsyncSimpleGET](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncSimpleGET)
 6. [AsyncWebClientRepeating](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncWebClientRepeating)

#### 2. For Murata WiFi

 1. [AsyncHTTPRequest](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncHTTPRequest)
 2. [AsyncCustomHeader](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncCustomHeader)
 3. [AsyncDweetGet](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncDweetGet)
 4. [AsyncDweetPost](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncDweetPost)
 5. [AsyncSimpleGET](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncSimpleGET)
 6. [AsyncWebClientRepeating](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncWebClientRepeating)

#### 3. For Portenta_H7

 1. [**multiFileProject**](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/multiFileProject) **New**
    
    
---

### Example [AsyncHTTPRequest](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncHTTPRequest)

Please take a look at other examples, as well.

#### 1. File [AsyncHTTPRequest.ino](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncHTTPRequest/AsyncHTTPRequest.ino)

https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/blob/13c9304d5d4fbbfb54e8f7fef981dd8f68ce9994/examples/Ethernet/AsyncHTTPRequest/AsyncHTTPRequest.ino#L44-L184


---

#### 2. File [defines.h](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncHTTPRequest/defines.h)


https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/blob/13c9304d5d4fbbfb54e8f7fef981dd8f68ce9994/examples/Ethernet/AsyncHTTPRequest/defines.h#L23-L68


---
---

### Debug Terminal Output Samples

#### 1. [AsyncHTTPRequest](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncHTTPRequest) running on PORTENTA_H7_M7 WiFi 

```cpp
Start AsyncHTTPRequest on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncHTTPRequest v1.5.0
Using mac index = 15
Connected! IP address: 192.168.2.101
Request sent
**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2023-01-31T23:01:30.472515-05:00
day_of_week: 2
day_of_year: 31
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1675224090
utc_datetime: 2023-02-01T04:01:30.472515+00:00
utc_offset: -05:00
week_number: 5
**************************************

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2023-01-31T23:02:24.463788-05:00
day_of_week: 2
day_of_year: 31
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1675224144
utc_datetime: 2023-02-01T04:02:24.463788+00:00
utc_offset: -05:00
week_number: 5
**************************************
```

---

#### 2. [AsyncDweetPOST](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncDweetPOST) running on PORTENTA_H7_M7 WiFi 

```cpp
Start AsyncDweetPOST on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncHTTPRequest v1.5.0
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

#### 3. [AsyncWebClientRepeating](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/WiFi/AsyncWebClientRepeating) running on PORTENTA_H7_M7 WiFi

```cpp
Start AsyncWebClientRepeating on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncHTTPRequest v1.5.0
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

#### 4. [AsyncCustomHeader](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncCustomHeader) running on PORTENTA_H7_M7 Ethernet

```cpp
Start AsyncCustomHeader on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncHTTPRequest v1.5.0
Using mac index = 15
Connected! IP address: 192.168.2.87

Sending GET Request to http://worldtimeapi.org/api/timezone/America/Toronto.txt

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2023-01-31T23:03:24.464007-05:00
day_of_week: 2
day_of_year: 31
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1675224204
utc_datetime: 2023-02-01T04:03:24.464007+00:00
utc_offset: -05:00
week_number: 5
**************************************
```

---

#### 5. [AsyncWebClientRepeating](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncWebClientRepeating) running on PORTENTA_H7_M7 Ethernet


```cpp
Start AsyncWebClientRepeating on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncHTTPRequest v1.5.0
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

#### 6. [AsyncSimpleGET](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/tree/main/examples/Ethernet/AsyncSimpleGET) running on PORTENTA_H7_M7 Ethernet


```cpp
Start AsyncSimpleGET on PORTENTA_H7_M7
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncHTTPRequest v1.5.0
Using mac index = 7
Connected! IP address: 192.168.2.87

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2023-01-31T23:04:24.464088-05:00
day_of_week: 2
day_of_year: 31
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1675224264
utc_datetime: 2023-02-01T04:04:24.464088+00:00
utc_offset: -05:00
week_number: 5
**************************************
HH HHHH
**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2023-01-31T23:05:24.465017-05:00
day_of_week: 2
day_of_year: 31
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1675224324
utc_datetime: 2023-02-01T04:05:24.465017+00:00
utc_offset: -05:00
week_number: 5
************************************
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

If you get compilation errors, more often than not, you may need to install a newer version of the `mbed_portenta` core for Arduino.

Sometimes, the library will only work if you update the `mbed_portenta` core to the latest version because I am using newly added functions.

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
 7. Fix long timeout if using `IPAddress`
 8. Display only successful responseText in examples
 9. Improve debug messages by adding functions to display error messages instead of `cryptic error number`
10. Not try to reconnect to the same `host:port` after connected
11. Fix bug of wrong `reqStates`
12. Default to reconnect to the same `host:port` after connected for new HTTP sites.
13. Use `allman astyle` and add `utils`
14. Fix bug of `_parseURL()`. Check [Bug with _parseURL() #21](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues/21)
15. Improve `README.md` so that links can be used in other sites, such as `PIO`
 
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

- The library is licensed under [GPLv3](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/blob/main/LICENSE)

---

## Copyright

Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>

Copyright (C) 2021- Khoi Hoang



