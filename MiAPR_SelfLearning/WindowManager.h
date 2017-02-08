#pragma once

enum class WINDOW_TYPE
{
	NONE,
	MAIN
};

class Window;
class MainWindow;

class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	static void SetAppParams(HINSTANCE hInstanceValue, int nCmdShowValue)
	{
		hInstance = hInstanceValue;
		nCmdShow = nCmdShowValue;
	}
	static HINSTANCE GetHInstance()
	{
		return hInstance;
	}
	static int GetNCmdShow()
	{
		return nCmdShow;
	}
	static WindowManager* GetInstance();
	Window* GetWindow(WINDOW_TYPE wndType);
	void ShowWindow(WINDOW_TYPE wndType);

	//logic methods

	void SetInitialData(int image_vectors_count);
private:
	//fields
	static HINSTANCE hInstance;
	static int nCmdShow;
	MainWindow *mainWindow;
	Window *activeWindow;	
};

