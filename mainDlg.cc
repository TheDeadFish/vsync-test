#include <stdshit.h>
#include <win32hlp.h>
#include "resource.h"
#include "frmtime.h"
#include "ddrawfb.h"
#include "hpc.h"

const char progName[] = "test";

// barDraw interface
void barDraw_start(void);
extern FrameTime barDraw_ft;

void setDlgItemFlt(HWND hwnd,
	int ctrlId, float value)
{
	char buff[20];
	sprintf(buff, "%.2f", value);
	SetDlgItemTextA(hwnd, ctrlId, buff);
}

void mainDlgProc_frameTime(HWND hwnd)
{
	SetDlgItemInt(hwnd, IDC_TOTLINE, barDraw_ft.fLines, 0);
	SetDlgItemInt(hwnd, IDC_ACTLINE, barDraw_ft.aLines, 0);
	SetDlgItemInt(hwnd, IDC_VLINES, barDraw_ft.vLines, 0);
	setDlgItemFlt(hwnd, IDC_FTIME, hpc_toUsFF(barDraw_ft.fTime));
	setDlgItemFlt(hwnd, IDC_ATIME, hpc_toUsFF(barDraw_ft.aTime));
	setDlgItemFlt(hwnd, IDC_VTIME, hpc_toUsFF(barDraw_ft.vTime));
	setDlgItemFlt(hwnd, IDC_LTIME, hpc_toUsFF(barDraw_ft.lTime));
}

LRESULT CALLBACK wndProc(
	HWND hwnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_ERASEBKGND ) {
		RECT rc; GetClientRect(hwnd, &rc);
		SetDCBrushColor((HDC)wParam, RGB(255,255,0));
		FillRect((HDC)wParam, &rc, (HBRUSH)
			GetStockObject(DC_BRUSH));
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void mainDlg_init(HWND hwnd)
{	
	stdClass_create(L"", WS_POPUP|WS_VISIBLE, 
		WS_EX_TOPMOST, 0, 0, 32, ddrawFb_ddsd.dwHeight,
		hwnd, NULL, wndProc, 0);

	mainDlgProc_frameTime(hwnd);
}

INT_PTR CALLBACK mainDlgProc(
	HWND hwnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	DLGMSG_SWITCH(
	 ON_MESSAGE(WM_INITDIALOG, mainDlg_init(hwnd))
	 ON_MESSAGE(WM_CLOSE, EndDialog(hwnd, 0));
	,)
}



int main()
{
	barDraw_start();

	DialogBox(NULL, MAKEINTRESOURCE(
		IDD_DIALOG1), NULL, mainDlgProc);
	exit(1);
}