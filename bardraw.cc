#include <stdshit.h>
#include "frmtime.h"
#include "ddrawfb.h"
#include "surfacePlot.c"
#include "hpc.h"

FrameTime barDraw_ft;
HANDLE barDraw_event;
int barDraw_delay1;
int barDraw_delay2;
HANDLE barDraw_hThread;

void barDraw_init(void)
{
	if(HRESULT x = ddrawFb_init()) { fatalError(
		"failed to initialize direct draw: %X", x); }
	if(HRESULT x = barDraw_ft.init()) { fatalError(
		"failed to get frame timing: %X", x); }	
	SPInit(0, &ddrawFb_ddsd);
	SetEvent(barDraw_event);
}

void BarThread_test1(void)
{

}


DWORD WINAPI BarThreadProc(
  _In_ LPVOID lpParameter
) {
	barDraw_init();
	
	QuickTrash_init(RGB(0,255,0));

	int maxTime = lrint((2*barDraw_ft.vTime)
		* (floor((barDraw_ft.fTime * 0.95) /
			(2*barDraw_ft.vTime))-0.05));	
		
	int mulVal = lrint((4294967296.0/2)
		* 16 / barDraw_ft.vTime);
	
	while(1) {
		ddrawFb_spinVsync();
		int baseTime = hpc_getTime();
		QuickTrash(0);
		while(1) {
			int curTime = hpc_getTime()-baseTime;
			if(curTime > maxTime) break;
			QuickTrash(((INT64(curTime) * mulVal) >> 32));
		}
	}
}

void barDraw_start(void)
{
	barDraw_event = CreateEvent(0,0,0,0);
	barDraw_hThread = CreateThread(0, 0, 
		BarThreadProc, 0, 0, 0);
	WaitForSingleObject(
		barDraw_event, INFINITE);
}

void barDraw_stop(void)
{
	TerminateThread(barDraw_hThread,0);
	

}
