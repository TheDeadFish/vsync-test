#pragma once
#include <ddraw.h>

extern LPDIRECTDRAW ddrawFb_dd;
extern LPDIRECTDRAWSURFACE ddrawFb_dds;
extern DDSURFACEDESC ddrawFb_ddsd;

HRESULT WINAPI ddrawFb_init(void);
HRESULT WINAPI ddrawFb_spinVsync(void);
HRESULT WINAPI ddrawFb_spinNotVsync(void);
