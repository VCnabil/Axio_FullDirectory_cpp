// AxioCANUSBcon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "USBCAN.h"
#include <iostream>
#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <string.h>
#include <cstdint>  // for uint8_t
#include <cmath>    // for std::round
using namespace std;
USBCAN_DEVICE_INFO DeviceInfoArray[100];
HANDLE hDeviceHandle;
DWORD dwResult;
CAN_FRAME CANFrame;
USBCAN_MESSAGE USBCANMessage;
int iBaudRate = 250;
int iDeviceIndex = -1;
ULONG PGN_FF02 = 0x18FF0209;
BYTE* bptr;

int Connect_0();
void VoltsTo_2BYTEHex_withref_forPV780(float value, BYTE* ArrayOfBytes_ToSend);


int main()
{
    cout << "Hello World!\n";
	BYTE* _DATA_Bytes = new BYTE[8]{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	bptr = _DATA_Bytes;
	Connect_0();

	memset(&CANFrame, 0, sizeof(CANFrame));
	CANFrame.bEIdFlag = TRUE;
	CANFrame.bLength = 8;
	CANFrame.ulID = PGN_FF02;// PGN_FF78;

	float value;

	for (int i = 0; i < 15; ++i) {
		//cout << "Enter a float value between -10.00 and 10.00: ";
		cout << "Enter a float value between 0.00 and 5.00: ";
		cin >> value;


		VoltsTo_2BYTEHex_withref_forPV780(value, bptr);
		for (int j = 0; j < 8; j++) {
			CANFrame.Data[j] = bptr[j];
		}
		dwResult = USBCANSendCANFrame(hDeviceHandle, &CANFrame, NULL);

	}

	delete[] _DATA_Bytes;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


int Connect_0() {
	dwResult = USBCANGetDeviceInfo(DeviceInfoArray, sizeof(DeviceInfoArray));
	if (dwResult != ERROR_SUCCESS)
	{
		return -1;
	}
	for (int i = 0; i < sizeof(DeviceInfoArray) / sizeof(DeviceInfoArray[0]); i++)
	{
		if (DeviceInfoArray[i].szDevicePath[0] == _T('\0')) break;
		if (DeviceInfoArray[i].dwFlags & USBCAN_DEVICE_ACTIVE)
		{
			iDeviceIndex = i;
			break;
		}
	}
	if (iDeviceIndex == -1)
	{
		return -2;
	}


	dwResult = USBCANGetDeviceHandle(DeviceInfoArray[iDeviceIndex].szDevicePath, USBCAN_BLOCKING_MODE, &hDeviceHandle);
	if (dwResult != ERROR_SUCCESS)
	{
		return -3;
	}

	dwResult = USBCANGetBaudRate(hDeviceHandle, &iBaudRate, NULL);
	if (dwResult != ERROR_SUCCESS)
	{
		return -4;
	}
	if (iBaudRate == 0)
	{
		iBaudRate = 250;
		dwResult = USBCANSetBaudRate(hDeviceHandle, iBaudRate, NULL);
		if (dwResult != ERROR_SUCCESS)
		{
			return -5;
		}
	}
	return 0;
}




void VoltsTo_2BYTEHex_withref_forPV780(float value, BYTE* ArrayOfBytes_ToSend) {
	// Scale the value to fit into a 16-bit integer (you can adjust the scaling factor)
	uint16_t intBits = static_cast<uint16_t>(value * 1000);

	ArrayOfBytes_ToSend[7] = (intBits >> 8) & 0xFF; // Most significant byte
	ArrayOfBytes_ToSend[6] = intBits & 0xFF;        // Least significant byte
}