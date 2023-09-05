/**
  ******************************************************************************
  * @file    USBCAN.h
  * @project USB-CAN Converter SDK, AX070501SDK
  *
  * @version V2.0.0
  * @date    May 2022
  * @author  Oleksandr Bogush
  * 
  * @copyright
  * (c) Axiomatic Technologies Corp. All rights reserved.
  *
  * @brief
  * C Include file for USB-CAN Converter SDK.
  * Works with: Driver version: V1.1.x.x, August 2006.
  * Dll version:                V1.0.0.1, August 2006.
  * 
  * Define _USB_CAN_SDK_V1_XX macro if compatibility with SDK V1.xx
  * is necessary.
  */

#pragma once

#include <windows.h>

#define USBCANDLL_API __declspec(dllimport)
#pragma comment(lib,"USBCANDll.lib") 

#define CUSTOM_BAUD_RATE 0xffff

#define USBCAN_DEVICE_ACTIVE   0x00000001
#define USBCAN_DEVICE_DEFAULT  0x00000002
#define USBCAN_DEVICE_REMOVED  0x00000004

#define USBCAN_OVERLAPPED_MODE 0x00000001

// Runtime Error Codes
#define RUNTIME_ERROR_PARSING					0x01
#define RUNTIME_ERROR_CAN_QUEUES_FULL			0x02        // Not used
#define RUNTIME_ERROR_USB_QUEUES_FULL			0x03 	    // Not used
#define RUNTIME_ERROR_DRIVER_READ_QUEUE_FULL	0x04
#define RUNTIME_ERROR_IN_CAN_QUEUE_FULL			0x05
#define RUNTIME_ERROR_CAN_READ_WRITE_ERROR		0x06
#define RUNTIME_ERROR_CAN_IN_MESSAGE_LOST		0x07
#define RUNTIME_ERROR_CAN_WARNING 				0x08
#define RUNTIME_ERROR_CAN_PASSIVE				0x09
#define RUNTIME_ERROR_CAN_BUS_OFF				0x0a
#define RUNTIME_ERROR_CAN_LOW_POWER             0x0b

// Notification Codes
#define NOTIFICATION_CODE_EXT_POWER_ON			0x01
#define NOTIFICATION_CODE_EXT_POWER_OFF			0x02
#define NOTIFICATION_CODE_SUSPEND_MODE			0x03
#define NOTIFICATION_CODE_LOW_POWER				0x04
#define NOTIFICATION_CODE_USB_POWER_ON			0x05
#define NOTIFICATION_CODE_USB_POWER_OFF			0x06

#ifdef _USB_CAN_SDK_V1_XX
// Old definitions
typedef enum _USBCAN_MESSAGE_TYPE
{
	VOID_MESSAGE = 0,
	CAN_FRAME_MESSAGE = 1,
	CONTROL_FRAME_MESSAGE = 2
} USBCAN_MESSAGE_TYPE;

#define CONTROL_FRAME_DATA_LENGTH 4

// Control Message Identifiers
#define CONTROL_RUNTIME_ERROR      				0x20
#define CONTROL_NOTIFICATION_MESSAGE			0x30

typedef struct _USBCAN_DEVICE_INFO
{
	DWORD Flags;
	TCHAR DevicePath[MAX_PATH + 1];
} USBCAN_DEVICE_INFO, * PUSBCAN_DEVICE_INFO;

typedef struct _CAN_FRAME
{
	ULONG Id;

	BOOLEAN EIdFlag;
	BOOLEAN RemFrameFlag;
	BYTE Length;
	BYTE Data[8];

	ULONG TimeStamp;
} CAN_FRAME, *PCAN_FRAME;

typedef struct _CONTROL_FRAME
{
	BYTE Id;
	BYTE Data[CONTROL_FRAME_DATA_LENGTH];
} CONTROL_FRAME, *PCONTROL_FRAME;

typedef struct _USBCAN_MESSAGE
{
	USBCAN_MESSAGE_TYPE USBCANMessageType;
	union
	{
		CAN_FRAME CANFrame;
		CONTROL_FRAME ControlFrame;
	};
} USBCAN_MESSAGE, *PUSBCAN_MESSAGE;

typedef struct _CAN_BITRATE_SET
{
	WORD BaudRate;
	BYTE tseg1;
	BYTE tseg2;
	BYTE sjw;
	WORD brp;
} CAN_BITRATE_SET, *PCAN_BITRATE_SET;

typedef struct _FIRMWARE_VERSION
{
	WORD MainVersionNumber;
	WORD AuxVersionNumber;
	WORD Reserved_1;
	WORD Reserved_2;
} FIRMWARE_VERSION, *PFIRMWARE_VERSION;

typedef struct _DRIVER_VERSION
{
	WORD ProductMajorPart;
	WORD ProductMinorPart;
	WORD ProductBuildPart;
	WORD ProductPrivatePart;
} DRIVER_VERSION, *PDRIVER_VERSION;

typedef struct _DLL_VERSION
{
	WORD ProductMajorPart;
	WORD ProductMinorPart;
	WORD ProductBuildPart;
	WORD ProductPrivatePart;
} DLL_VERSION, *PDLL_VERSION;

#else
// New definitions
typedef enum _USBCAN_MESSAGE_TYPE
{
	VOID_MESSAGE = 0,
	CAN_FRAME_MESSAGE = 1,
	NOTIFICATION_FRAME_MESSAGE = 2
} USBCAN_MESSAGE_TYPE;

#define USBCAN_BLOCKING_MODE   0x00000000

#define NOTIFICATION_FRAME_DATA_LENGTH 4

// (Control Message Identifiers) 0x0-0x7f
#define NOTIFICATION_FRAME_ERROR_CODE  			0x20
#define NOTIFICATION_FRAME_MESSAGE_CODE			0x30

typedef struct _USBCAN_DEVICE_INFO
{
	DWORD dwFlags;
	TCHAR szDevicePath[MAX_PATH + 1];
} USBCAN_DEVICE_INFO, *PUSBCAN_DEVICE_INFO;

typedef struct _CAN_FRAME
{
	ULONG ulID;
	
	BOOLEAN bEIdFlag;
	BOOLEAN bRemFrameFlag;
	BYTE bLength;
	BYTE Data[8];
	
	ULONG ulTimeStamp;
} CAN_FRAME, *PCAN_FRAME;

typedef struct _NOTIFICATION_FRAME
{
	BYTE bID;
	BYTE Data[NOTIFICATION_FRAME_DATA_LENGTH];
} NOTIFICATION_FRAME, *PNOTIFICATION_FRAME;

typedef struct _USBCAN_MESSAGE
{
	USBCAN_MESSAGE_TYPE USBCANMessageType;
	union
	{
		CAN_FRAME CANFrame;
		NOTIFICATION_FRAME NotificationFrame;
	};
} USBCAN_MESSAGE, *PUSBCAN_MESSAGE;

typedef struct _CAN_BITRATE_SET
{
	WORD wBaudRate;
	BYTE bTseg1;
	BYTE bTseg2;
	BYTE bSjw;
	WORD wBrp;
} CAN_BITRATE_SET, *PCAN_BITRATE_SET;

typedef struct _FIRMWARE_VERSION
{
	WORD wMainVersionNumber;
	WORD wAuxVersionNumber;
	WORD wReserved_1;
	WORD wReserved_2;
} FIRMWARE_VERSION, *PFIRMWARE_VERSION;

typedef struct _DRIVER_VERSION
{
	WORD wProductMajorPart;
	WORD wProductMinorPart;
	WORD wProductBuildPart;
	WORD wProductPrivatePart;
} DRIVER_VERSION, *PDRIVER_VERSION;

typedef struct _DLL_VERSION
{
	WORD wProductMajorPart;
	WORD wProductMinorPart;
	WORD wProductBuildPart;
	WORD wProductPrivatePart;
} DLL_VERSION, *PDLL_VERSION;
#endif

USBCANDLL_API DWORD USBCANGetDeviceInfo(PUSBCAN_DEVICE_INFO pDeviceInfoArray, size_t DeviceInfoArraySize);
USBCANDLL_API DWORD USBCANGetDeviceHandle(LPCTSTR szDevicePath, ULONG ulMode, HANDLE* pDeviceHandle);
USBCANDLL_API DWORD USBCANCloseDeviceHandle(HANDLE hDeviceHandle);
USBCANDLL_API DWORD USBCANSendCANFrame(HANDLE hDeviceHandle, const PCAN_FRAME pCANFrame, LPOVERLAPPED pOverlapped);
USBCANDLL_API DWORD USBCANSendMessage(HANDLE hDeviceHandle, const PUSBCAN_MESSAGE pUSBCANMessage, LPOVERLAPPED pOverlapped);
USBCANDLL_API DWORD USBCANReceiveMessage(HANDLE hDeviceHandle, PUSBCAN_MESSAGE pUSBCANMessage, LPOVERLAPPED pOverlapped);

USBCANDLL_API DWORD USBCANSetBaudRate(HANDLE hDeviceHandle, int iBaudRate, LPOVERLAPPED pOverlapped);
USBCANDLL_API DWORD USBCANGetBaudRate(HANDLE hDeviceHandle, int *pBaudRate, LPOVERLAPPED pOverlapped);
USBCANDLL_API DWORD USBCANSetBaudRateSpecial(HANDLE hDeviceHandle, const PCAN_BITRATE_SET pBaudRateSet, LPOVERLAPPED pOverlapped);
USBCANDLL_API DWORD USBCANGetBaudRateSpecial(HANDLE hDeviceHandle, PCAN_BITRATE_SET pBaudRateSet, LPOVERLAPPED pOverlapped);
USBCANDLL_API DWORD USBCANGetFirmwareVersion(HANDLE hDeviceHandle, PFIRMWARE_VERSION pFirmwareVersion, LPOVERLAPPED pOverlapped);
USBCANDLL_API DWORD USBCANGetDriverVersion(HANDLE hDeviceHandle, PDRIVER_VERSION pDriverVersion, LPOVERLAPPED pOverlapped);
USBCANDLL_API void USBCANGetDllVersion(PDLL_VERSION pDllVersion);
