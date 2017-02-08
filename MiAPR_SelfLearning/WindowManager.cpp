#include "stdafx.h"
#include "WindowManager.h"

#include "Window.h"
#include "MainWindow.h"

HINSTANCE WindowManager::hInstance;
int WindowManager::nCmdShow;

WindowManager::WindowManager()
{
	mainWindow = NULL;
	activeWindow = NULL;
}


WindowManager::~WindowManager()
{
	if (mainWindow != NULL)
	{
		delete(mainWindow);
	}
}

WindowManager * WindowManager::GetInstance()
{
	static WindowManager instance = WindowManager();
	return &instance;
}

Window * WindowManager::GetWindow(WINDOW_TYPE wndType)
{
	switch (wndType)
	{
	case WINDOW_TYPE::MAIN:
		if (mainWindow == NULL)
		{
			mainWindow = new MainWindow();
		}
		return mainWindow;
	default:
		return NULL;
	}
}

void WindowManager::ShowWindow(WINDOW_TYPE wndType)
{
	Window* targetWindow = GetWindow(wndType);
	targetWindow->Show();
	activeWindow = (Window*)targetWindow;
}
