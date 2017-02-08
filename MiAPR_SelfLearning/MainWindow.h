#pragma once

#include "Window.h"
#include "resource.h"
#include "WindowManager.h"
#include "DialogManager.h"
#include "DrawingLogic.h"
#include <vector>
#include "ImageVector.h"
#include "SelfLearningLogic.h"
#include <process.h>

class MainWindow : public Window
{
public:
	MainWindow();
	~MainWindow();	
	void Show();
	void Hide();
	void SetInitialData(int image_vectors_count);
private:
	//fields
	std::vector<ImageVector*> image_vector_list;
	SelfLearningLogic* self_learning;
	int image_vectors_count;	

	CRITICAL_SECTION critical_section;

	//controls

	HMENU hMenu;

	//methods

	void Init();	
	void ClearData();
	void DrawImageVectorList(HDC hdc);
	void PerformNextStep();
	void PerformAllSteps();

	//friends procs

	static LRESULT CALLBACK MainWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);

	static unsigned __stdcall PerformAllStepsThreadFunc(void* param);
};

