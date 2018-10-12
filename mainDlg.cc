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
extern int barDraw_delay1;
extern int barDraw_delay2;

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
	
	setDlgSpinRange(hwnd, IDC_CURPOS, 0, lrint(barDraw_ft.aTime));
	setDlgSpinRange(hwnd, IDC_DELAYPX, 0, barDraw_ft.aLines);
	setDlgSpinRange(hwnd, IDC_DELAYTM, 0, lrint(barDraw_ft.aTime));
}

void mainDlg_init(HWND hwnd)
{	
	mainDlgProc_frameTime(hwnd);
}

void mainDlg_curTime(HWND hwnd)
{
	int curPos = getDlgSpinValue(hwnd, IDC_CURPOS);
	setDlgItemFlt(hwnd, IDC_CURTIME,  barDraw_ft.pixToUsF(curPos));
}

void mainDlg_chgDelayMode(HWND hwnd)
{
	int curPos = getDlgSpinValue(hwnd, IDC_DELAYTM);
	if(IsDlgButtonChecked(hwnd, IDC_RBSYNC)) {
		barDraw_delay1 = curPos; barDraw_delay2 = 100;
	} else {
		barDraw_delay2 = curPos; barDraw_delay1 = 0; }
}

void mainDlg_chgDelay(HWND hwnd, int ctrlId)
{
	int curPos = getDlgSpinValue(hwnd, ctrlId);
	if(ctrlId == IDC_DELAYTM) {
		setDlgSpinValue(hwnd, IDC_DELAYPX, barDraw_ft.usToPix(curPos));
	} else {
		setDlgSpinValue(hwnd, IDC_DELAYTM, barDraw_ft.pixToUs(curPos)); }
	mainDlg_chgDelayMode(hwnd);
}

void mainDlg_scroll(HWND hwnd, HWND sender)
{
	int ctrlId = GetDlgCtrlID(sender);
	switch(ctrlId) {
	case IDC_CURPOS: 
		mainDlg_curTime(hwnd); break;
	case IDC_DELAYTM: case IDC_DELAYPX:
		mainDlg_chgDelay(hwnd, ctrlId);
		break;
	
	
		
	
	

		
	}
	
	

}

INT_PTR CALLBACK mainDlgProc(
	HWND hwnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	DLGMSG_SWITCH(
	 ON_MESSAGE(WM_INITDIALOG, mainDlg_init(hwnd))
	 ON_MESSAGE(WM_VSCROLL, mainDlg_scroll(hwnd, sender))
	 /*ON_MESSAGE(WM_CLOSE, mainDlg.close(); EndDialog(hwnd, 0))*/
	 CASE_COMMAND(
	  ON_COMMAND(IDC_RBSYNC, mainDlg_chgDelayMode(hwnd))
		ON_COMMAND(IDC_RBACT, mainDlg_chgDelayMode(hwnd))
	 ,)/*(
	 CASE_NOTIFY(
	  ON_LVN_ITEMACT(NM_DBLCLK, IDC_LIST1, mainDlg.dclk())
	 ,)*/
	,)
}



int main()
{
	barDraw_start();

	DialogBox(NULL, MAKEINTRESOURCE(
		IDD_DIALOG1), NULL, mainDlgProc);
}