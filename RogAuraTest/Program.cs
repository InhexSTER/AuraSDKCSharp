using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AuraSDKWrapper;
using System.Threading;
using System.Security.Principal;

namespace RogAuraTest
{
    class Program
    {
        static bool IsElevated => new WindowsPrincipal(WindowsIdentity.GetCurrent()).IsInRole(WindowsBuiltInRole.Administrator);

        static void Main(string[] args)
        {

            Console.WriteLine("Starting...");
            if (!IsElevated)
            {
                Console.WriteLine("Please run as administrator.");
                Console.WriteLine("Press any key to exit...");
                while (!(Console.KeyAvailable));
                    return;
            }

            AuraSDK auraSDK = new AuraSDK();
            int result = auraSDK.DetectAuraDevices();
            if (result != 0) {
                Console.WriteLine("Error during initialize: " + result);
                return;
            }

            Console.WriteLine("Found " + auraSDK.MBControllersCount + " motherboard controller(s)");
            Console.WriteLine("Found " + auraSDK.GPUControllersCount + " gpu controller(s)");
            Console.WriteLine("Found keybaord: " + auraSDK.IsKeyboardPresent);
            Console.WriteLine("Found mouse: " + auraSDK.IsMousePresent);

            if (auraSDK.MBControllersCount > 0)
            {
                Console.WriteLine("Press Escape to exit...");
                while (!(Console.KeyAvailable && Console.ReadKey(true).Key == ConsoleKey.Escape))
                {
                    int ledCount = auraSDK.GetMBLedCount(0);
                    byte[] colors = new byte[ledCount * 3];
                    colors[0] = 255;
                    colors[3] = 255;
                    colors[6] = 255;
                    colors[9] = 255;
                    colors[12] = 255;
                    auraSDK.SetMBLedColor(0, colors);
                    Thread.Sleep(100);
                    colors[1] = 255;
                    colors[4] = 255;
                    colors[7] = 255;
                    colors[10] = 255;
                    colors[13] = 255;
                    auraSDK.SetMBLedColor(0, colors);
                    Thread.Sleep(100);

                    colors[2] = 255;
                    colors[5] = 255;
                    colors[8] = 255;
                    colors[11] = 255;
                    colors[14] = 255;
                    auraSDK.SetMBLedColor(0, colors);
                    Thread.Sleep(100);
                }

            }

            Console.WriteLine("Done");
        }
    }
}
