char SP_BitDepth;
DWORD SP_Width;
DWORD SP_Height;
DWORD SP_Pitch;
void *SP_Surface;

bool SPInit(HWND hwnd, DDSURFACEDESC *SInfo)
{
	SP_Height = SInfo->dwHeight;
	SP_Width = SInfo->dwWidth;
	SP_Pitch = SInfo->lPitch;
	SP_BitDepth = SInfo->ddpfPixelFormat.dwRGBBitCount;
	SP_Surface = SInfo->lpSurface;
	//if(SP_BitDepth != 16){
	//	MessageBoxA(hwnd, "Unsuported bit depth!", NULL, MB_OK);
	//	return(false);
	//}
	return(true);
}

#include <intrin.h>

__m128 QuickTrash_x[5];
float* QuickTrash_end;
	
void QuickTrash_init(int color)
{
	float *poit = ((float*)SP_Surface)+16;
	PTRADD(poit, SP_Pitch*SP_Height);
	QuickTrash_end = poit;

	// 
	for(int i = 0; i < 20; i++) {
		((int*)&QuickTrash_x)[i] = is_one_of(
			i,0,5,10,15) ? 0 : color; }
}


template <int n> ALWAYS_INLINE
void QuickTrash_loop(int xpos, __m128 x1, __m128 x2)
{
	float *poit = ((float*)SP_Surface)+16;
	float* poitEnd = QuickTrash_end;

	do {
		_mm_store_ps(poit, n==0 ? x1 : x2);	
		_mm_store_ps(poit+4, n==1 ? x1 : x2);
		_mm_store_ps(poit+8, n==2 ? x1 : x2);
		_mm_store_ps(poit+12, n==3 ? x1 : x2);
		PTRADD(poit, SP_Pitch);
	} while( poit < poitEnd);
}

REGCALL(1) void QuickTrash(int xpos)
{
	__m128 x1 = QuickTrash_x[xpos&3];
	__m128 x2 = QuickTrash_x[4];

	switch((xpos>>2)&3) {
	case 0: QuickTrash_loop<0>(xpos,x1,x2); break; 
	case 1: QuickTrash_loop<1>(xpos,x1,x2); break; 
	case 2: QuickTrash_loop<2>(xpos,x1,x2); break; 
	default: QuickTrash_loop<3>(xpos,x1,x2); break; }
}
