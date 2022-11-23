# Portenta_H7_AsyncHTTPRequest Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncHTTPRequest.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncHTTPRequest)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Portenta_H7_AsyncHTTPRequest.svg)](https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Portenta_H7_AsyncHTTPRequest.svg)](http://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>
<a href="https://profile-counter.glitch.me/khoih-prog/count.svg" title="Total khoih-prog Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog/count.svg" style="height: 30px;width: 200px;"></a>
<a href="https://profile-counter.glitch.me/khoih-prog-Portenta_H7_AsyncHTTPRequest/count.svg" title="Portenta_H7_AsyncHTTPRequest Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog-Portenta_H7_AsyncHTTPRequest/count.svg" style="height: 30px;width: 200px;"></a>

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.4.2](#releases-v142)
  * [Releases v1.4.1](#releases-v141)
  * [Releases v1.4.0](#releases-v140)
  * [Releases v1.3.1](#releases-v131)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.0](#releases-v110)
  * [Initial Releases v1.0.0](#Initial-Releases-v100)

---
---

## Changelog

### Releases v1.4.2

1. Default to reconnect to the same `host:port` after connected for new HTTP sites. Check [Host/Headers not always sent with 1.10.1 #44](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/44)
2. Use `allman astyle` and add `utils`

### Releases v1.4.1

1. Fix bug of wrong `reqStates`. Check [Release 1.9 breaks previously running code #39](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/39) and [Callback behaviour is buggy (ESP8266) #43](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/43)
2. Optional larger `DEFAULT_RX_TIMEOUT` from default 3s, for slower networks

### Releases v1.4.0

1. Fix bug. 
2. Clean up
3. Update `Packages' Patches`

### Releases v1.3.1

1. Not try to reconnect to the same host:port after connected. Check [setReuse feature #12](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues/12)
2. Update `Packages' Patches`

### Releases v1.3.0

1. Fix long timeout if using `IPAddress`
2. Optimize code
3. Display only successful responseText in examples
4. Improve debug messages by adding functions to display error messages instead of `cryptic error number`

### Releases v1.2.0

1. Reduce the breaking effect of v1.5.0 by enabling compatibility with old code to include only `Portenta_H7_AsyncHTTPRequest.h`
2. Add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project
3. Update `Packages' Patches`

### Releases v1.1.0

1. Fix `multiple-definitions` linker error and weird bug related to `src_cpp`. Check [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)
2. Optimize library code by using `reference-passing` instead of `value-passing`
3. Update all examples

### Initial Releases v1.0.0

1. Initial coding to support **Portenta_H7 boards** such as Portenta_H7 Rev2 ABX00042, etc., using [**ArduinoCore-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed) with `Vision-shield Ethernet` or `Murata WiFi`
