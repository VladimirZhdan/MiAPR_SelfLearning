#pragma once

#include "Dialog.h"
#include "resource.h"
#include <CommCtrl.h>

class ChooseVectorsCountDialog : public Dialog
{
public:
	ChooseVectorsCountDialog(HWND hWndParent);
	~ChooseVectorsCountDialog();
private:
	static INT_PTR CALLBACK ChooseVectorsCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

