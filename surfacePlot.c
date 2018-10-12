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

void PlotPoint16(long col, long x, long y)
{
	char *temp = (char*)SP_Surface;
	temp += (x*2 + (y * SP_Pitch));
	*(unsigned short*)temp = (((col&7) << 11) | (((col>>8)&7) << 5) | ((col>>16)&7));
}

void PlotPoint(long col, long x, long y)
{
	switch(SP_BitDepth){
		case 16:
			PlotPoint16(col, x, y);
			break;
	}
}
void DrawLine(long col, long x1, long y1, long x2, long y2)
{
	int count;
	float xpos, ypos, xstep, ystep;
	xpos = x1; ypos = y1;
	if(abs(x2-x1)>=abs(y2-y1))
		count = abs(x2-x1);
	else
		count = abs(y2-y1);
	//printf("%d\n", count);
	if(count == 0) return;
	xstep = (float)(x2-x1)/(float)count;
	ystep = (float)(y2-y1)/(float)count;
	do{
		PlotPoint(col, (long)xpos, (long)ypos);
		xpos += xstep;
		ypos += ystep;
	}while(count--);
}

void ClearImg(unsigned long col)
{
	unsigned long xcount, ycount;
	ycount = SP_Height;
	while(ycount--){
		xcount = SP_Width;
		while(xcount--)
			PlotPoint(col, xcount, ycount);
	}
}

void TrashImg(int color, int width)
{
	printf("%d\n", SP_Pitch);

	DWORD *poit = (DWORD*)SP_Surface;
	unsigned long xcount, ycount;
	DWORD lineWrods, remWrods;
	lineWrods = width * SP_BitDepth;
	lineWrods /= 32;
	remWrods = SP_Pitch / 4;
	remWrods -= lineWrods;
	ycount = SP_Height;
	while(ycount--){
		xcount = lineWrods;
		while(xcount--)
			*poit++ = color;
		poit += remWrods;
	}
}

#include <intrin.h>


/*
void QuickTrash(int color)
{
	// 
	float *poit = (float*)SP_Surface;
	float* poitEnd = poit;
	PTRADD(poitEnd, SP_Pitch*SP_Height);

	__m128 x = _mm_load_ss((float*)&color);
	x = _mm_shuffle_ps(x, x, 0);
	
	do {
		_mm_store_ps(poit, x);	_mm_store_ps(poit+4, x);
		_mm_store_ps(poit+8, x); _mm_store_ps(poit+12, x);
		PTRADD(poit, SP_Pitch);
	} while( poit < poitEnd);
}
*/

__m128 QuickTrash_x[5];
float* QuickTrash_end;
	
void QuickTrash_init(int color)
{
	float *poit = ((float*)SP_Surface)+8;
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
	float *poit = ((float*)SP_Surface)+8;
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
