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
	
	setDlgSpinRange(hwnd, IDC_CURPOS, 0, lrint(barDraw_ft.aLines));
}

int cursorPos;
HWND hYelWnd;

LRESULT CALLBACK wndProc(
	HWND hwnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_PAINT ) {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		
	
		RECT rc; GetClientRect(hwnd, &rc);
		SetDCBrushColor(hdc, RGB(255,255,0));
		FillRect(hdc, &rc, (HBRUSH)
			GetStockObject(DC_BRUSH));
			
		if(cursorPos) {
			SetDCPenColor(hdc, RGB(0,128,255));
			SelectObject(hdc, GetStockObject(DC_PEN));
			MoveToEx(hdc, 0, cursorPos, 0);
			LineTo(hdc, rc.right, cursorPos);
		}
		
		EndPaint(hwnd, &ps);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void mainDlg_curTime(HWND hwnd)
{
	// get cursor position
	int curPos = getDlgSpinValue(hwnd, IDC_CURPOS);
	cursorPos = curPos;
	if(IsDlgButtonChecked(hwnd, IDC_RBVTIME))
		curPos += barDraw_ft.vLines;
	
	// update controls
	setDlgItemFlt(hwnd, IDC_CURTIME, 
		barDraw_ft.pixToUsF(curPos));
	SetDlgItemInt(hwnd, IDC_CURBYTE, 
		curPos * ddrawFb_ddsd.lPitch, 0);

	InvalidateRect(hYelWnd, 0, TRUE);
}

void mainDlg_init(HWND hwnd)
{	
	hYelWnd = stdClass_create(L"", WS_POPUP|WS_VISIBLE, 
		WS_EX_TOPMOST, 8, 0, 32, ddrawFb_ddsd.dwHeight,
		hwnd, NULL, wndProc, 0);

	mainDlgProc_frameTime(hwnd);
	CheckDlgButton(hwnd, IDC_RBATIME, 1);
	mainDlg_curTime(hwnd);
}

INT_PTR CALLBACK mainDlgProc(
	HWND hwnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	DLGMSG_SWITCH(
	 ON_MESSAGE(WM_INITDIALOG, mainDlg_init(hwnd))
	 ON_MESSAGE(WM_VSCROLL, mainDlg_curTime(hwnd))
	 ON_MESSAGE(WM_CLOSE, EndDialog(hwnd, 0));
	 CASE_COMMAND(
	  ON_COMMAND(IDC_RBATIME, mainDlg_curTime(hwnd))
		ON_COMMAND(IDC_RBVTIME, mainDlg_curTime(hwnd))
	 ,)
	,)
}



int main()
{
	barDraw_start();

	DialogBox(NULL, MAKEINTRESOURCE(
		IDD_DIALOG1), NULL, mainDlgProc);
	exit(1);
}