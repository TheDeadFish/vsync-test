#include <ddraw.h>
#include "ddrawfb.h"

LPDIRECTDRAW ddrawFb_dd;
LPDIRECTDRAWSURFACE ddrawFb_dds;
DDSURFACEDESC ddrawFb_ddsd;

HRESULT WINAPI ddrawFb_init(void)
{
	HRESULT ddrval;
	ddrval = DirectDrawCreate( NULL, &ddrawFb_dd, NULL );
	if(ddrval) return ddrval;		 
	ddrval = ddrawFb_dd->SetCooperativeLevel( NULL, DDSCL_NORMAL );
	if(ddrval){ ERR: ddrawFb_dd->Release(); return(ddrval); }
	
	// create primary surface
	memset( &ddrawFb_ddsd, 0, sizeof(ddrawFb_ddsd) );
		ddrawFb_ddsd.dwSize = sizeof( ddrawFb_ddsd );
	ddrawFb_ddsd.dwFlags = DDSD_CAPS;
		ddrawFb_ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	ddrval = ddrawFb_dd->CreateSurface( &ddrawFb_ddsd, &ddrawFb_dds, NULL );
	if( ddrval != DD_OK ) goto ERR;
	
	// lock primary surface
	ddrval = ddrawFb_dds->Lock(NULL, &ddrawFb_ddsd, DDLOCK_WRITEONLY, NULL);
	if(ddrval){ ddrawFb_dds->Release(); goto ERR; }
	return ddrval;
}

HRESULT WINAPI ddrawFb_spinVsync(void) {
	BOOL IsInVB; HRESULT ret; do { 
		ret = ddrawFb_dd->GetVerticalBlankStatus(&IsInVB);
	} while(!IsInVB && !ret); 
	return ret; }
	
HRESULT WINAPI ddrawFb_spinNotVsync(void) {
	BOOL IsInVB; HRESULT ret; do { 
		ret = ddrawFb_dd->GetVerticalBlankStatus(&IsInVB);
	} while(IsInVB && !ret); 
	return ret; }
