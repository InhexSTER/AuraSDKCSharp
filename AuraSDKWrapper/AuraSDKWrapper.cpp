// This is the main DLL file.

#include "stdafx.h"

#include "AuraSDKWrapper.h"

namespace AuraSDKWrapper {
	int AuraSDK::DetectAuraDevices() {

		_isMousePresent = false;
		_isKeyboardPresent = false;
		HMODULE hLib = nullptr;

		hLib = LoadLibraryA("AURA_SDK.dll");
		DWORD lastError = GetLastError();

		if (hLib == nullptr)
			return lastError;

		(FARPROC&)EnumerateMbController = GetProcAddress(hLib, "EnumerateMbController");
		(FARPROC&)SetMbMode = GetProcAddress(hLib, "SetMbMode");
		(FARPROC&)SetMbColor = GetProcAddress(hLib, "SetMbColor");
		(FARPROC&)GetMbColor = GetProcAddress(hLib, "GetMbColor");
		(FARPROC&)GetMbLedCount = GetProcAddress(hLib, "GetMbLedCount");

		(FARPROC&)EnumerateGPU = GetProcAddress(hLib, "EnumerateGPU");
		(FARPROC&)SetGPUMode = GetProcAddress(hLib, "SetGPUMode");
		(FARPROC&)SetGPUColor = GetProcAddress(hLib, "SetGPUColor");
		(FARPROC&)GetGPULedCount = GetProcAddress(hLib, "GetGPULedCount");

		(FARPROC&)CreateClaymoreKeyboard = GetProcAddress(hLib, "CreateClaymoreKeyboard");
		(FARPROC&)SetClaymoreKeyboardMode = GetProcAddress(hLib, "SetClaymoreKeyboardMode");
		(FARPROC&)SetClaymoreKeyboardColor = GetProcAddress(hLib, "SetClaymoreKeyboardColor");
		(FARPROC&)GetClaymoreKeyboardLedCount = GetProcAddress(hLib, "GetClaymoreKeyboardLedCount");
		(FARPROC&)EnumerateMbController = GetProcAddress(hLib, "EnumerateMbController");

		(FARPROC&)CreateRogMouse = GetProcAddress(hLib, "CreateRogMouse");
		(FARPROC&)SetRogMouseMode = GetProcAddress(hLib, "SetRogMouseMode");
		(FARPROC&)SetRogMouseColor = GetProcAddress(hLib, "SetRogMouseColor");
		(FARPROC&)RogMouseLedCount = GetProcAddress(hLib, "RogMouseLedCount");

		DWORD count = EnumerateMbController(NULL, 0);
		_mbLightCtrl = new MbLightControl[count];
		EnumerateMbController(_mbLightCtrl, count);
		_mbLedControllers = count;

		count = EnumerateGPU(NULL, 0);
		_gpuLightCtrl = new GPULightControl[count];
		EnumerateGPU(_gpuLightCtrl, count);
		_gpuLedControllers = count;

		_keyboardLightCtrl = new ClaymoreKeyboardLightControl();
		DWORD Create = CreateClaymoreKeyboard(_keyboardLightCtrl);

		if (Create > 0) {
			_isKeyboardPresent = true;
		}

		_mouseLightCtrl = new RogMouseLightControl();
		Create = CreateRogMouse(_mouseLightCtrl);

		if (Create > 0) {
			_isMousePresent = true;
		}

		return 0;
	}


	void AuraSDK::SetMBLedMode(int controllerId, int mode) {
		if (controllerId < 0 || controllerId>= _mbLedControllers)
			return;
		SetMbMode(_mbLightCtrl[controllerId], mode);
	}

	void AuraSDK::SetMBLedColor(int controllerId, array<System::Byte>^ colors) {
		if (controllerId < 0 || controllerId >= _mbLedControllers)
			return;
		pin_ptr<byte> p = &colors[0];
		SetMbColor(_mbLightCtrl[controllerId], p, colors->Length);
	}

	int AuraSDK::GetMBLedCount(int controllerId) {
		if (controllerId < 0 || controllerId >= _mbLedControllers)
			return -1;
		return GetMbLedCount(_mbLightCtrl[controllerId]);
	}

	void AuraSDK::SetGPUCtrlLedMode(int controllerId, int mode) {
		if (controllerId < 0 || controllerId >= _gpuLedControllers)
			return;
		SetGPUMode(_gpuLightCtrl[controllerId], mode);
	}

	void AuraSDK::SetGPUCtrlLedColor(int controllerId, array<System::Byte>^ colors) {
		if (controllerId < 0 || controllerId >= _gpuLedControllers)
			return;
		pin_ptr<byte> p = &colors[0];
		SetGPUColor(_gpuLightCtrl[controllerId], p, colors->Length);
	}

	int AuraSDK::GetGPUCtrlLedCount(int controllerId) {
		if (controllerId < 0 || controllerId >= _gpuLedControllers)
			return -1;
		return GetGPULedCount(_gpuLightCtrl[controllerId]);
	}


	void AuraSDK::SetKeyboardLedMode(int mode) {
		if (!_isKeyboardPresent)
			return;
		SetClaymoreKeyboardMode(_keyboardLightCtrl, mode);
	}

	void AuraSDK::SetKeyboardLedColor(array<System::Byte>^ colors) {
		if (!_isKeyboardPresent)
			return;
		pin_ptr<byte> p = &colors[0];
		SetClaymoreKeyboardColor(_keyboardLightCtrl, p, colors->Length);
	}

	int AuraSDK::GetKeyboardLedCount() {
		if (!_isKeyboardPresent)
			return -1;
		return GetClaymoreKeyboardLedCount(_keyboardLightCtrl);
	}


	void AuraSDK::SetMouseLedMode(int mode) {
		if (!_isMousePresent)
			return;
		SetRogMouseMode(_mouseLightCtrl, mode);
	}

	void AuraSDK::SetMouseLedColor(array<System::Byte>^ colors) {
		if (!_isMousePresent)
			return;
		pin_ptr<byte> p = &colors[0];
		SetRogMouseColor(_mouseLightCtrl, p, colors->Length);
	}

	int AuraSDK::GetMouseLedCount() {
		if (!_isMousePresent)
			return -1;
		return RogMouseLedCount(_mouseLightCtrl);
	}

}
