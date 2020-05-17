// GUITest.cpp : Defines the entry point for the application.
//
//#include "Direct2DHelloWorld.h"
#include "SimpleD2DApplication.h"

//
// Provides the entry point to the application.
//
int WINAPI WinMain(
	HINSTANCE /*hInstance*/,
	HINSTANCE /*hPrevInstance*/,
	LPSTR /*lpCmdLine*/,
	int /*nCmdShow*/
)
{
	// Ignore the return value because we want to run the program even in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			//DemoApp app;
			SimpleD2DApp app;

				if (SUCCEEDED(app.Initialize()))
				{
					app.RunMessageLoop();
				}
		}
		CoUninitialize();
	}

	return 0;
}

