// AuraSDKWrapper.h

#pragma once
#include "AURALightingSDK.h"

using namespace System;

EnumerateMbControllerFunc EnumerateMbController;
SetMbModeFunc SetMbMode;
SetMbColorFunc SetMbColor;
GetMbColorFunc GetMbColor;
GetMbLedCountFunc GetMbLedCount;

EnumerateGPUFunc EnumerateGPU;
SetGPUModeFunc SetGPUMode;
SetGPUColorFunc SetGPUColor;
GetGPULedCountFunc GetGPULedCount;

CreateClaymoreKeyboardFunc CreateClaymoreKeyboard;
SetClaymoreKeyboardModeFunc SetClaymoreKeyboardMode;
SetClaymoreKeyboardColorFunc SetClaymoreKeyboardColor;
GetClaymoreKeyboardLedCountFunc GetClaymoreKeyboardLedCount;

CreateRogMouseFunc CreateRogMouse;
SetRogMouseModeFunc SetRogMouseMode;
SetRogMouseColorFunc SetRogMouseColor;
RogMouseLedCountFunc RogMouseLedCount;


namespace AuraSDKWrapper {

	public ref class AuraSDK
	{
	public:

		/// <summary>  
		/// Detects all aura devices
		/// </summary> 
		/// <returns>Returns 0 if successfull or error code if not< / returns>
		int DetectAuraDevices();

		/// <summary>  
		/// Sets motherboard controller's mode
		/// </summary> 
		/// <param name="controllerId">id of the controller, 0-N</param>
		/// <param name="mode">mode to set</param>
		void SetMBLedMode(int controllerId, int mode);

		/// <summary>  
		/// Sets motherboard controller's colors for all LEDs (zones)
		/// </summary> 
		/// <param name="controllerId">id of the controller, 0-N</param>
		/// <param name="colors">colors to set</param>
		void SetMBLedColor(int controllerId, array<System::Byte>^ colors);

		/// <summary>  
		/// Get motherboard controller's LEDs count (zones)
		/// </summary> 
		/// <param name="controllerId">id of the controller, 0-N</param>
		/// <returns>Number of LEDs (zones) on controller</returns>
		int GetMBLedCount(int controllerId);

		/// <summary>  
		/// Sets GPU controller's mode
		/// </summary> 
		/// <param name="controllerId">id of the controller, 0-N</param>
		/// <param name="mode">mode to set</param>
		void SetGPUCtrlLedMode(int controllerId, int mode);

		/// <summary>  
		/// Sets GPU controller's colors for all LEDs (zones)
		/// </summary> 
		/// <param name="controllerId">id of the controller, 0-N</param>
		/// <param name="colors">colors to set</param>
		void SetGPUCtrlLedColor(int controllerId, array<System::Byte>^ colors);

		/// <summary>  
		/// Get GPU controller's LEDs count (zones)
		/// </summary> 
		/// <param name="controllerId">id of the controller, 0-N</param>
		/// <returns>Number of LEDs (zones) on controller</returns>
		int GetGPUCtrlLedCount(int controllerId);

		/// <summary>  
		/// Sets keyboard's LEDs mode
		/// </summary> 
		void SetKeyboardLedMode(int mode);

		/// <summary>  
		/// Sets colors for all LEDs on keyboard
		/// </summary> 
		/// <param name="colors">colors to set</param>
		void SetKeyboardLedColor(array<System::Byte>^ colors);

		/// <summary>  
		/// Get keyboard LEDs count
		/// </summary> 
		/// <returns>Number of LEDs on keyboard</returns>
		int GetKeyboardLedCount();

		/// <summary>  
		/// Sets mouse LEDs mode
		/// </summary> 
		void SetMouseLedMode(int mode);

		/// <summary>  
		/// Sets colors for all LEDs on mouse
		/// </summary> 
		/// <param name="colors">colors to set</param>
		void SetMouseLedColor(array<System::Byte>^ colors);

		/// <summary>  
		/// Get mouse LEDs count
		/// </summary> 
		/// <returns>Number of LEDs on mouse</returns>
		int GetMouseLedCount();


		///<value>Gets the value of motherboard controllers</value>
		property int MBControllersCount {
			int get() {
				return  _mbLedControllers;
			}
		}

		///<value>Gets the value of GPU controllers</value>
		property int GPUControllersCount {
			int get() {
				return  _gpuLedControllers;
			}
		}

		///<value>Reports if Aura keyboard is present</value>
		property bool IsKeyboardPresent {
			bool get() {
				return  _isKeyboardPresent;
			}
		}

		///<value>Reports if Aura mouse is present</value>
		property bool IsMousePresent {
			bool get() {
				return  _isMousePresent;
			}
		}

	private:
		MbLightControl* _mbLightCtrl;
		GPULightControl* _gpuLightCtrl;
		ClaymoreKeyboardLightControl* _keyboardLightCtrl;
		RogMouseLightControl* _mouseLightCtrl;
		int _mbLedControllers;
		int _gpuLedControllers;
		bool _isKeyboardPresent;
		bool _isMousePresent;

	};
}
