#include "stdafx.h"
#include "ChooseVectorsCountDialog.h"


ChooseVectorsCountDialog::ChooseVectorsCountDialog(HWND hWndParent) : Dialog(ChooseVectorsCountProc, IDD_VECTORSCOUNT, hWndParent)
{
}


ChooseVectorsCountDialog::~ChooseVectorsCountDialog()
{
}

INT_PTR ChooseVectorsCountDialog::ChooseVectorsCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{	
	static HWND hTrach_vectors_count;
	static int vectors_count = 1000;
	int wmId;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:				
		//VECTORS_COUNT
		hTrach_vectors_count = GetDlgItem(hDlg, IDC_SLIDER_VECTORSCOUNT);
		SetDlgItemInt(hDlg, IDC_STATIC_VECTORSCOUNT, vectors_count, 0);
		SendMessage(hTrach_vectors_count, TBM_SETRANGEMIN, 0, 1000);
		SendMessage(hTrach_vectors_count, TBM_SETRANGEMAX, 0, 50000);
		SendMessage(hTrach_vectors_count, TBM_SETPOS, TRUE, vectors_count);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDOK:
			WindowManager::GetInstance()->SetInitialData(vectors_count);
			EndDialog(hDlg, LOWORD(wParam));
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			break;
		}
		return (INT_PTR)TRUE;
		break;
	case WM_HSCROLL:		
		//VECTORS_COUNT
		vectors_count = LOWORD(SendMessage(hTrach_vectors_count, TBM_GETPOS, 0, 0));
		SetDlgItemInt(hDlg, IDC_STATIC_VECTORSCOUNT, vectors_count, 0);

		InvalidateRect(hDlg, NULL, TRUE);
		break;
	}
	return (INT_PTR)FALSE;
}

