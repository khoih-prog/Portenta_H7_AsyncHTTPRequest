/****************************************************************************************************************************
  Portenta_H7_AsyncHTTPRequest.h - Dead simple AsyncHTTPRequest Portenta_H7
  
  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet or Murata WiFi
  
  Portenta_H7_AsyncHTTPRequest is a library for the Portenta_H7 with with Vision-Shield Ethernet Ethernet or Murata WiFi
   
  Based on and modified from asyncHTTPrequest Library (https://github.com/boblemaire/asyncHTTPrequest)
  
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncHTTPRequest
  Licensed under MIT license
  
  Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.  
 
  Version: 1.3.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0    K Hoang     13/10/2020 Initial coding for Portenta_H7
  1.1.0    K Hoang     30/12/2021 Fix `multiple-definitions` linker error
  1.2.0    K Hoang     24/01/2022 Enable compatibility with old code to include only AsyncHTTPRequest_Generic.h
  1.3.0    K Hoang     02/09/2022 Fix bug. Improve debug messages. Optimize code
 *****************************************************************************************************************************/

#pragma once

#ifndef PORTENTA_H7_ASYNC_HTTP_REQUEST_H
#define PORTENTA_H7_ASYNC_HTTP_REQUEST_H

#include "Portenta_H7_AsyncHTTPRequest.hpp"
#include "Portenta_H7_AsyncHTTPRequest_Impl.h"

#endif    // PORTENTA_H7_ASYNC_HTTP_REQUEST_H
